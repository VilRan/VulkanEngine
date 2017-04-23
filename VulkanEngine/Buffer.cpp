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

void* Buffer::GetData()
{
	return Data;
}

VkBuffer Buffer::GetDeviceBuffer()
{
	return *DeviceBuffer;
}

VkDeviceSize Buffer::GetOffset()
{
	return Offset;
}

VkDeviceSize Buffer::GetSize()
{
	return Size;
}
