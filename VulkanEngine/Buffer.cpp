#include "Buffer.h"



Buffer::Buffer()
{
}

Buffer::Buffer(void* data, VkBuffer* deviceBuffer, VkDeviceSize offset, VkDeviceSize size)
{
	Data = data;
	DeviceBuffer = deviceBuffer;
	Offset = offset;
	Size = size;
}

Buffer::~Buffer()
{
}

