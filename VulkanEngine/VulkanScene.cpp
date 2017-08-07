#include "VulkanScene.h"

VulkanScene::VulkanScene(
	VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, 
	VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet, 
	::DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass, std::shared_ptr<ICamera> camera
)
	: VulkanScene(
		device, commandPool, graphicsPipeline, pipelineLayout,
		viewProjectionDescriptorSet, modelDescriptorSet,
		dynamicBufferPool, renderPass
	)
{
	SetCamera(camera, false);
	ViewProjectionBuffer = DynamicBufferPool.Reserve(&ViewProjection);
}

VulkanScene::VulkanScene(
	VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout,
	VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet,
	::DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass, float aspectRatio
)
	: VulkanScene(
		device, commandPool, graphicsPipeline, pipelineLayout,
		viewProjectionDescriptorSet, modelDescriptorSet,
		dynamicBufferPool, renderPass, CreateDefaultCamera(aspectRatio)
	)
{
}

VulkanScene::~VulkanScene()
{
	DynamicBufferPool.Release(ViewProjectionBuffer);

	//This is here for now because - as it is - labels must be deleted before actors
	for (auto label : Labels)
	{
		delete label;
	}

	for (const auto& actorsByTexture : GroupedActors)
	{
		for (const auto& actorsByModel : actorsByTexture.second)
		{
			for (auto actor : actorsByModel.second)
			{
				delete actor;
			}
		}
	}

	for (auto vacantActor : VacantActors)
	{
		delete vacantActor;
	}
}

Actor* VulkanScene::AddActor(Sprite* sprite, glm::vec3 position, glm::vec3 angles, glm::vec3 scale)
{
	return AddActor(sprite->GetModel(), sprite->GetTexture(), position, angles, scale);
}

Actor* VulkanScene::AddActor(Model* model, Texture* texture, glm::vec3 position, glm::vec3 angles, glm::vec3 scale)
{
	auto vulkanTexture = static_cast<VulkanTexture*>(texture);
	auto vulkanModel = static_cast<VulkanModel*>(model);
	VulkanActor* actor;

	//TODO: Create a single actor pool shared by all scenes.
	if (VacantActors.size() > 0)
	{
		actor = VacantActors.back();
		actor->SetTexture(vulkanTexture);
		actor->SetModel(vulkanModel);
		VacantActors.pop_back();
	}
	else
	{
		actor = new VulkanActor(vulkanModel, vulkanTexture, *this, DynamicBufferPool);
	}

	glm::quat rotation = glm::quat(angles);
	actor->SetTransform(position, rotation, scale);

	GroupedActors[vulkanTexture][vulkanModel].push_back(actor);

	ActorCount++;
	VertexCount += model->GetVertexCount();
	Status = Changed;
	return actor;
}

void VulkanScene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
	{
		return;
	}

	auto actorTexture = static_cast<VulkanTexture*>(actor->GetTexture());
	auto actorModel = static_cast<VulkanModel*>(actor->GetModel());
	auto& actorGroup = GroupedActors[actorTexture][actorModel];

	auto vulkanActor = static_cast<VulkanActor*>(actor);
	auto position = std::find(actorGroup.begin(), actorGroup.end(), actor);
	if (position != actorGroup.end())
	{
		actorGroup.erase(position);
		VacantActors.push_back(vulkanActor);

		ActorCount--;
		VertexCount -= actorModel->GetVertexCount();
		Status = Changed;
	}
}

Scene* VulkanScene::AddScene()
{
	auto scene = new VulkanScene(
		Device, CommandPool, GraphicsPipeline, PipelineLayout, 
		ViewProjectionDescriptorSet, ModelDescriptorSet, 
		DynamicBufferPool, RenderPass, GetCamera()
	);
	ChildScenes.push_back(scene);
	return scene;
}

void VulkanScene::Reset(VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, float aspectRatio)
{
	for (auto childScene : ChildScenes)
	{
		auto childVulkanScene = static_cast<VulkanScene*>(childScene);
		childVulkanScene->Reset(graphicsPipeline, pipelineLayout, renderPass, aspectRatio);
	}

	GraphicsPipeline = graphicsPipeline;
	PipelineLayout = pipelineLayout;
	RenderPass = renderPass;
	GetCamera()->SetAspectRatio(aspectRatio);
	Status = Changed;
}

void VulkanScene::BuildSecondaryCommandBuffer()
{
	//TODO: Create secondary command buffers for all frame buffers for possible performance increase?
	VkCommandBufferInheritanceInfo inheritanceInfo = {};
	inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inheritanceInfo.renderPass = RenderPass;
	inheritanceInfo.subpass = 0;
	inheritanceInfo.framebuffer = VK_NULL_HANDLE;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	beginInfo.pInheritanceInfo = &inheritanceInfo;
	
	CommandBuffer = CommandBufferPool.GetNext();
	vkBeginCommandBuffer(CommandBuffer, &beginInfo);

	BuildCommandBuffer(CommandBuffer);

	if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to record scene command buffer!");
	}

	Status = Ready;
}

void VulkanScene::BuildPrimaryCommandBuffer(VkCommandBuffer commandBuffer)
{
	if (IsVisible() == false)
	{
		return;
	}

	VkCommandBuffer secondaryCommandBuffer = CommandBuffer;
	vkCmdExecuteCommands(commandBuffer, 1, &secondaryCommandBuffer);
	for (auto childScene : ChildScenes)
	{
		auto childVulkanScene = static_cast<VulkanScene*>(childScene);
		childVulkanScene->BuildPrimaryCommandBuffer(commandBuffer);
	}
}

void VulkanScene::Update()
{
	for (auto childScene : ChildScenes)
	{
		auto childVulkanScene = static_cast<VulkanScene*>(childScene);
		childVulkanScene->Update();
	}

	if (Status == Changed || DynamicBufferPool.HasResized())
	{
		BuildSecondaryCommandBuffer();
	}

	ViewProjection = GetCamera()->GetViewProjection();
	DynamicBufferPool.Update(ViewProjectionBuffer);
}

VulkanScene::VulkanScene(
	VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, 
	VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet, 
	::DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass
)
	: DynamicBufferPool(dynamicBufferPool)
{
	Device = device;
	CommandPool = commandPool;
	GraphicsPipeline = graphicsPipeline;
	PipelineLayout = pipelineLayout;
	ViewProjectionDescriptorSet = viewProjectionDescriptorSet;
	ModelDescriptorSet = modelDescriptorSet;
	RenderPass = renderPass;

	CommandBufferPool.Initialize(Device, CommandPool, VK_COMMAND_BUFFER_LEVEL_SECONDARY, 2);
}

void VulkanScene::BuildCommandBuffer(VkCommandBuffer commandBuffer)
{
	//TODO: Create a secondary command buffer for each actor group.

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);

	uint32_t dynamicOffset = ViewProjectionBuffer.GetDynamicOffset();
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &ViewProjectionDescriptorSet, 1, &dynamicOffset);

	for (const auto& actorsByTexture : GroupedActors)
	{
		auto texture = actorsByTexture.first;
		texture->Bind(commandBuffer, PipelineLayout);
		for (const auto& actorsByModel : actorsByTexture.second)
		{
			auto model = actorsByModel.first;
			actorsByModel.first->Bind(commandBuffer);
			for (auto actor : actorsByModel.second)
			{
				if (DynamicBufferPool.HasResized())
				{
					actor->UpdateBuffer();
				}

				dynamicOffset = actor->GetDynamicBuffer().GetDynamicOffset();
				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 1, 1, &ModelDescriptorSet, 1, &dynamicOffset);
				vkCmdDrawIndexed(commandBuffer, model->GetIndexCount(), 1, 0, 0, 0);
			}
		}
	}
}
