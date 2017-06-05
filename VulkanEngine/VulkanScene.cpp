#include "VulkanScene.h"

#include "Camera3D.h"

VulkanScene::VulkanScene(
	VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, 
	VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet, 
	::DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass, float aspectRatio
)
	: VulkanScene(
		device, commandPool, graphicsPipeline, pipelineLayout, 
		viewProjectionDescriptorSet, modelDescriptorSet, 
		dynamicBufferPool, renderPass
	)
{
	Camera = std::make_shared<Camera3D>(
		glm::vec3(3.0f, 3.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		60.0f, aspectRatio, 0.1f, 10.0f
	);
	ViewProjection = Camera->GetViewProjection();
	ViewProjectionBuffer = DynamicBufferPool.Reserve(&ViewProjection);
}

VulkanScene::VulkanScene(
	VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, 
	VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet, 
	::DynamicBufferPool & dynamicBufferPool, VkRenderPass renderPass, std::shared_ptr<ICamera> camera
)
	: VulkanScene(
		device, commandPool, graphicsPipeline, pipelineLayout,
		viewProjectionDescriptorSet, modelDescriptorSet,
		dynamicBufferPool, renderPass
	)
{
	Camera = camera;
	ViewProjection = Camera->GetViewProjection();
	ViewProjectionBuffer = DynamicBufferPool.Reserve(&ViewProjection);
}

VulkanScene::~VulkanScene()
{
	DynamicBufferPool.Release(ViewProjectionBuffer);
	FreeCommandBuffer();

	for (auto childScene : ChildScenes)
	{
		delete childScene;
	}

	for (auto label : Labels)
	{
		delete label;
	}

	for (const auto& actorsByModel : GroupedActors)
	{
		for (const auto& actorsByTexture : actorsByModel.second)
		{
			for (auto actor : actorsByTexture.second)
			{
				delete actor;
			}
		}
	}
	/*
	for (auto actor : Actors)
	{
		delete actor;
	}
	*/
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
	auto vulkanModel = static_cast<VulkanModel*>(model);
	auto vulkanTexture = static_cast<VulkanTexture*>(texture);
	VulkanActor* actor;

	if (VacantActors.size() > 0)
	{
		actor = VacantActors.back();
		actor->SetModel(vulkanModel);
		actor->SetTexture(vulkanTexture);
		VacantActors.pop_back();
	}
	else
	{
		actor = new VulkanActor(vulkanModel, vulkanTexture, *this, DynamicBufferPool);
	}

	glm::quat rotation = glm::quat(angles);
	actor->SetTransform(position, rotation, scale);

	GroupedActors[vulkanModel][vulkanTexture].push_back(actor);
	//Actors.push_back(actor);

	ActorCount++;
	VertexCount += model->GetVertexCount();
	Status = Changed;
	return actor;
}

Label* VulkanScene::AddLabel(const char* text, SpriteFont* font, glm::vec3 position, glm::vec3 angles, glm::vec3 scale)
{
	auto label = new Label(text, *font, *this, position);
	Labels.push_back(label);
	return label;
}

void VulkanScene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
	{
		return;
	}

	auto actorModel = static_cast<VulkanModel*>(actor->GetModel());
	auto actorTexture = static_cast<VulkanTexture*>(actor->GetTexture());
	auto& actorGroup = GroupedActors[actorModel][actorTexture];

	auto vulkanActor = static_cast<VulkanActor*>(actor);
	auto position = std::find(actorGroup.begin(), actorGroup.end(), actor);
	if (position != actorGroup.end())
	{
		actorGroup.erase(position);
		VacantActors.push_back(vulkanActor);
	}

	ActorCount--;
	VertexCount -= actorModel->GetVertexCount();

	Status = Changed;
}

int VulkanScene::GetActorCount()
{
	int count = 0;
	for (auto childScene : ChildScenes)
	{
		count += childScene->GetActorCount();
	}
	//count += Actors.size();
	count += ActorCount;
	return count;
}

int VulkanScene::GetVertexCount()
{
	int count = 0;
	for (auto childScene : ChildScenes)
	{
		count += childScene->GetVertexCount();
	}
	count += VertexCount;
	return count;
}

Scene* VulkanScene::AddScene()
{
	auto scene = new VulkanScene(
		Device, CommandPool, GraphicsPipeline, PipelineLayout, 
		ViewProjectionDescriptorSet, ModelDescriptorSet, 
		DynamicBufferPool, RenderPass, Camera
	);
	ChildScenes.push_back(scene);
	return scene;
}

void VulkanScene::RemoveScene(Scene* scene)
{
	auto position = std::find(ChildScenes.begin(), ChildScenes.end(), scene);
	ChildScenes.erase(position);
	delete scene;
}

std::shared_ptr<ICamera> VulkanScene::GetCamera()
{
	return Camera;
}

void VulkanScene::SetCamera(std::shared_ptr<ICamera> camera, bool passToChildScenes)
{
	Camera = camera;
	if (passToChildScenes)
	{
		for (auto childScene : ChildScenes)
		{
			childScene->SetCamera(camera);
		}
	}
}

void VulkanScene::QueueBufferUpdate(Buffer buffer)
{
	BufferUpdateQueue.push_back(buffer);
}

void VulkanScene::Reset(VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, float aspectRatio)
{
	for (auto childScene : ChildScenes)
	{
		childScene->Reset(graphicsPipeline, pipelineLayout, renderPass, aspectRatio);
	}

	GraphicsPipeline = graphicsPipeline;
	PipelineLayout = pipelineLayout;
	RenderPass = renderPass;
	Camera->SetAspectRatio(aspectRatio);
	Status = Changed;
}

void VulkanScene::BuildSecondaryCommandBuffer()
{
	//FreeCommandBuffer();

	if (SecondaryCommandBuffer == VK_NULL_HANDLE)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = CommandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(Device, &allocInfo, &SecondaryCommandBuffer) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate scene command buffer!");
		}
	}

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
	
	//TODO: Use a better synchronization method.
	vkDeviceWaitIdle(Device);
	vkBeginCommandBuffer(SecondaryCommandBuffer, &beginInfo);
	vkCmdBindPipeline(SecondaryCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);

	uint32_t dynamicOffset = ViewProjectionBuffer.GetDynamicOffset();
	vkCmdBindDescriptorSets(SecondaryCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &ViewProjectionDescriptorSet, 1, &dynamicOffset);

	for (const auto& actorsByModel : GroupedActors)
	{
		auto model = actorsByModel.first;
		model->Bind(SecondaryCommandBuffer);
		for (const auto& actorsByTexture : actorsByModel.second)
		{
			actorsByTexture.first->Bind(SecondaryCommandBuffer, PipelineLayout);
			for (auto actor : actorsByTexture.second)
			{
				dynamicOffset = actor->GetDynamicBuffer().GetDynamicOffset();
				vkCmdBindDescriptorSets(SecondaryCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 1, 1, &ModelDescriptorSet, 1, &dynamicOffset);
				vkCmdDrawIndexed(SecondaryCommandBuffer, model->GetIndexCount(), 1, 0, 0, 0);
			}
		}
	}
	/*
	for (auto actor : Actors)
	{
		auto& model = static_cast<VulkanModel&>(actor->GetModel());
		model.Bind(SecondaryCommandBuffer);

		dynamicOffset = actor->GetDynamicBuffer().GetDynamicOffset();
		vkCmdBindDescriptorSets(SecondaryCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 1, 1, &ModelDescriptorSet, 1, &dynamicOffset);

		auto& texture = static_cast<VulkanTexture&>(actor->GetTexture());
		texture.Bind(SecondaryCommandBuffer, PipelineLayout);

		vkCmdDrawIndexed(SecondaryCommandBuffer, model.GetIndexCount(), 1, 0, 0, 0);
	}
	*/
	if (vkEndCommandBuffer(SecondaryCommandBuffer) != VK_SUCCESS)
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

	Camera->SetChanged(false);
	vkCmdExecuteCommands(commandBuffer, 1, &SecondaryCommandBuffer);
	for (auto childScene : ChildScenes)
	{
		childScene->BuildPrimaryCommandBuffer(commandBuffer);
	}
}

void VulkanScene::Update()
{
	for (auto childScene : ChildScenes)
	{
		childScene->Update();
	}

	if (Status == Changed)
	{
		BuildSecondaryCommandBuffer();
	}

	if (Camera->HasChanged())
	{
		ViewProjection = Camera->GetViewProjection();
		DynamicBufferPool.UpdateBuffers(&ViewProjectionBuffer, 1);
	}

	if (BufferUpdateQueue.size() > 0)
	{
		DynamicBufferPool.UpdateBuffers(BufferUpdateQueue.data(), BufferUpdateQueue.size());
		BufferUpdateQueue.clear();
	}
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
}

void VulkanScene::FreeCommandBuffer()
{
	if (SecondaryCommandBuffer != VK_NULL_HANDLE)
	{
		vkFreeCommandBuffers(Device, CommandPool, 1, &SecondaryCommandBuffer);
		SecondaryCommandBuffer = VK_NULL_HANDLE;
	}
}
