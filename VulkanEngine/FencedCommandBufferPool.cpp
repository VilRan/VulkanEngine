#include "FencedCommandBufferPool.h"

FencedCommandBufferPool::FencedCommandBufferPool()
{
}

FencedCommandBufferPool::~FencedCommandBufferPool()
{
	Destroy();
}

void FencedCommandBufferPool::Initialize(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level, size_t commandBufferCount)
{
	Destroy();

	Device = device;
	CommandPool = commandPool;

	CommandBuffers.resize(commandBufferCount);

	VkCommandBufferAllocateInfo commandBufferInfo = {};
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.commandPool = CommandPool;
	commandBufferInfo.level = level;
	commandBufferInfo.commandBufferCount = CommandBuffers.size();

	if (vkAllocateCommandBuffers(Device, &commandBufferInfo, CommandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate fenced command buffers!");
	}

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
	if (CommandBuffers.size() > 0)
	{
		vkFreeCommandBuffers(Device, CommandPool, CommandBuffers.size(), CommandBuffers.data());
		CommandBuffers.clear();
	}

	for (auto fence : Fences)
	{
		vkDestroyFence(Device, fence, nullptr);
	}
	Fences.clear();
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
