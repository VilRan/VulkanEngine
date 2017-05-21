#include "VulkanScene.h"

VulkanScene::VulkanScene(
	VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, 
	VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet, VkDescriptorSet imageDescriptorSet, 
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
	ImageDescriptorSet = imageDescriptorSet;
	RenderPass = renderPass;
}

VulkanScene::~VulkanScene()
{
	FreeCommandBuffer();

	for (auto childScene : ChildScenes)
	{
		delete childScene;
	}

	for (auto actor : Actors)
	{
		delete actor;
	}
}

Actor* VulkanScene::AddActor(Model* model, Texture* texture)
{
	auto vulkanModel = static_cast<VulkanModel*>(model);
	auto dynamicBuffer = DynamicBufferPool.Reserve(nullptr);
	auto actor = new VulkanActor(vulkanModel, texture, dynamicBuffer, this);

	glm::vec3 position(0.0f, 0.0f, 0.0f);
	glm::vec3 eulerAngles(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(eulerAngles);
	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	actor->SetTransform(position, rotation, scale);

	Actors.push_back(actor);
	Status = Changed;
	return actor;
}

void VulkanScene::RemoveActor(Actor* actor)
{
	auto position = std::find(Actors.begin(), Actors.end(), actor);
	Actors.erase(position);
	Status = Changed;
	delete actor;
}

void VulkanScene::QueueBufferUpdate(Buffer buffer)
{
	BufferUpdateQueue.push_back(buffer);
}

void VulkanScene::Reset(VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass)
{
	for (auto childScene : ChildScenes)
	{
		childScene->Reset(graphicsPipeline, pipelineLayout, renderPass);
	}

	GraphicsPipeline = graphicsPipeline;
	PipelineLayout = pipelineLayout;
	RenderPass = renderPass;
	BuildCommandBuffer();
}

void VulkanScene::BuildCommandBuffer()
{
	//FreeCommandBuffer();

	if (CommandBuffer == VK_NULL_HANDLE)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = CommandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(Device, &allocInfo, &CommandBuffer) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate scene command buffer!");
		}
	}

	VkCommandBufferInheritanceInfo inheritanceInfo = {};
	inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inheritanceInfo.renderPass = RenderPass;
	//inheritanceInfo.subpass = 0;
	inheritanceInfo.framebuffer = VK_NULL_HANDLE;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	beginInfo.pInheritanceInfo = &inheritanceInfo;

	vkBeginCommandBuffer(CommandBuffer, &beginInfo);

	vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);

	vkCmdBindDescriptorSets(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &ViewProjectionDescriptorSet, 0, nullptr);
	vkCmdBindDescriptorSets(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 2, 1, &ImageDescriptorSet, 0, nullptr);

	for (auto actor : Actors)
	{
		VulkanModel& model = static_cast<VulkanModel&>(actor->GetModel());
		model.Bind(CommandBuffer);

		uint32_t dynamicOffset = actor->GetDynamicBuffer().GetDynamicOffset();
		vkCmdBindDescriptorSets(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 1, 1, &ModelDescriptorSet, 1, &dynamicOffset);
		vkCmdDrawIndexed(CommandBuffer, model.GetIndexCount(), 1, 0, 0, 0);
	}

	if (ChildScenes.size() > 0)
	{
		std::vector<VkCommandBuffer> childCommandBuffers(ChildScenes.size());
		for (auto childScene : ChildScenes)
		{
			if (childScene->CommandBuffer == VK_NULL_HANDLE)
			{
				childScene->BuildCommandBuffer();
			}

			childCommandBuffers.push_back(childScene->CommandBuffer);
		}

		vkCmdExecuteCommands(CommandBuffer, childCommandBuffers.size(), childCommandBuffers.data());
	}

	if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to record scene command buffer!");
	}

	Status = Ready;
}

void VulkanScene::BuildInlineCommandBuffer(VkCommandBuffer commandBuffer)
{
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);

	for (auto actor : Actors)
	{
		VulkanModel& model = static_cast<VulkanModel&>(actor->GetModel());
		model.Bind(CommandBuffer);

		uint32_t dynamicOffset = actor->GetDynamicBuffer().GetDynamicOffset();
		vkCmdBindDescriptorSets(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &ModelDescriptorSet, 1, &dynamicOffset);
		vkCmdDrawIndexed(CommandBuffer, model.GetIndexCount(), 1, 0, 0, 0);
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
		BuildCommandBuffer();
	}

	if (BufferUpdateQueue.size() > 0)
	{
		DynamicBufferPool.UpdateBuffers(BufferUpdateQueue.data(), BufferUpdateQueue.size());
		BufferUpdateQueue.clear();
	}
}

void VulkanScene::FreeCommandBuffer()
{
	if (CommandBuffer != VK_NULL_HANDLE)
	{
		vkFreeCommandBuffers(Device, CommandPool, 1, &CommandBuffer);
	}
}
