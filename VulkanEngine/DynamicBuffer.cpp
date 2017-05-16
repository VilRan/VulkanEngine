#include "DynamicBuffer.h"

DynamicBuffer::DynamicBuffer()
{
}

DynamicBuffer::DynamicBuffer(void* data, VkBuffer* handlePointer, VkDeviceSize offset, VkDeviceSize size, uint32_t dynamicOffset)
	: Buffer(data, handlePointer, offset, size)
{
	DynamicOffset = dynamicOffset;
}

DynamicBuffer::~DynamicBuffer()
{
}
