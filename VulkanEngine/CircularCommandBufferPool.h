#pragma once
#include "CommandBufferPool.h"
class CircularCommandBufferPool :
	public CommandBufferPool
{
public:
	CircularCommandBufferPool();
	virtual ~CircularCommandBufferPool();

	VkCommandBuffer GetNext();

private:
	size_t CurrentIndex = -1;
};

