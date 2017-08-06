#include "CommandBufferPool.h"

CommandBufferPool::CommandBufferPool()
{
}

CommandBufferPool::~CommandBufferPool()
{
	DestroyCommandBuffers();
}

void CommandBufferPool::Initialize(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level, size_t size)
{
	Destroy();

	Device = device;
	CommandPool = commandPool;

	CommandBuffers.resize(size);

	VkCommandBufferAllocateInfo commandBufferInfo = {};
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.commandPool = CommandPool;
	commandBufferInfo.level = level;
	commandBufferInfo.commandBufferCount = CommandBuffers.size();

	if (vkAllocateCommandBuffers(Device, &commandBufferInfo, CommandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate fenced command buffers!");
	}
}

void CommandBufferPool::Destroy()
{
	DestroyCommandBuffers();
}

void CommandBufferPool::DestroyCommandBuffers()
{
	if (CommandBuffers.size() > 0)
	{
		vkFreeCommandBuffers(Device, CommandPool, CommandBuffers.size(), CommandBuffers.data());
		CommandBuffers.clear();
	}
}
