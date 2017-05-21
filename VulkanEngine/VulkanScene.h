#pragma once
#include "Scene.h"
#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanActor.h"
#include "DynamicBufferPool.h"

enum SceneStatus
{
	Changed,
	Ready
};

class VulkanActor;

class VulkanScene :
	public Scene
{
public:
	VulkanScene(
		VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, 
		VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet,  
		DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass
	);
	virtual ~VulkanScene();

	virtual Actor* AddActor(Model* model, Texture* texture);
	virtual void RemoveActor(Actor* actor);
	void QueueBufferUpdate(Buffer buffer);
	void Reset(VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass);
	void BuildSecondaryCommandBuffer();
	void BuildPrimaryCommandBuffer(VkCommandBuffer commandBuffer);
	void Update();
	inline VkCommandBuffer GetCommandBuffer() { return CommandBuffer; }
	inline VkCommandBuffer* GetCommandBufferPointer() { return &CommandBuffer; }

private:
	std::vector<VulkanScene*> ChildScenes;
	std::vector<VulkanActor*> Actors;
	std::vector<Buffer> BufferUpdateQueue;
	DynamicBufferPool& DynamicBufferPool;
	VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkPipeline GraphicsPipeline = VK_NULL_HANDLE;
	VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
	VkDescriptorSet ViewProjectionDescriptorSet = VK_NULL_HANDLE;
	VkDescriptorSet ModelDescriptorSet = VK_NULL_HANDLE;
	VkRenderPass RenderPass = VK_NULL_HANDLE;
	SceneStatus Status = Changed;

	void FreeCommandBuffer();
};

