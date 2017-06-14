#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class FencedCommandBufferPool
{
public:
	FencedCommandBufferPool();
	virtual ~FencedCommandBufferPool();

	void Initialize(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level, size_t commandBufferCount);
	void Destroy();
	VkResult WaitAndGet(VkCommandBuffer* outputCommandBuffer, VkFence* outputFence, uint64_t timeout = 1000000000);
	const size_t Count() const { return CommandBuffers.size(); }

private:
	std::vector<VkCommandBuffer> CommandBuffers;
	std::vector<VkFence> Fences;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
};
