#pragma once
#include "CommandBufferPool.h"

class FencedCommandBufferPool
	: CommandBufferPool
{
public:
	FencedCommandBufferPool();
	virtual ~FencedCommandBufferPool();

	virtual void Initialize(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level, size_t commandBufferCount);
	virtual void Destroy();
	VkResult WaitAndGet(VkCommandBuffer* outputCommandBuffer, VkFence* outputFence, uint64_t timeout = 1000000000);

private:
	std::vector<VkFence> Fences;

	void DestroyFences();
};
