#include "FencedCommandBufferPool.h"

FencedCommandBufferPool::FencedCommandBufferPool()
{
}

FencedCommandBufferPool::~FencedCommandBufferPool()
{
	DestroyFences();
}

void FencedCommandBufferPool::Initialize(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level, size_t commandBufferCount)
{
	CommandBufferPool::Initialize(device, commandPool, level, commandBufferCount);

	Fences.resize(CommandBuffers.size());

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (auto& fence : Fences)
	{
		if (vkCreateFence(Device, &fenceInfo, nullptr, &fence) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create fence!");
		}
	}
}

void FencedCommandBufferPool::Destroy()
{
	CommandBufferPool::Destroy();

	DestroyFences();
}

VkResult FencedCommandBufferPool::WaitAndGet(VkCommandBuffer* outputCommandBuffer, VkFence* outputFence, uint64_t timeout)
{
	VkResult result = vkWaitForFences(Device, Fences.size(), Fences.data(), VK_FALSE, timeout);

	if (result == VK_SUCCESS)
	{
		for (size_t i = 0; i < Fences.size(); i++)
		{
			VkFence fence = Fences[i];
			if (vkGetFenceStatus(Device, fence) == VK_SUCCESS)
			{
				*outputCommandBuffer = CommandBuffers[i];
				*outputFence = fence;
				return result;
			}
		}
	}

	*outputCommandBuffer = VK_NULL_HANDLE;
	*outputFence = VK_NULL_HANDLE;
	return result;
}

void FencedCommandBufferPool::DestroyFences()
{
	for (auto fence : Fences)
	{
		vkDestroyFence(Device, fence, nullptr);
	}
	Fences.clear();
}
