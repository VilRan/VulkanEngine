#include "CircularCommandBufferPool.h"

CircularCommandBufferPool::CircularCommandBufferPool()
{
}

CircularCommandBufferPool::~CircularCommandBufferPool()
{
}

VkCommandBuffer CircularCommandBufferPool::GetNext()
{
	CurrentIndex++;
	if (CurrentIndex >= CommandBuffers.size())
	{
		CurrentIndex = 0;
	}

	return CommandBuffers[CurrentIndex];
}
