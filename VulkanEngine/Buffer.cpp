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

bool Buffer::operator==(const Buffer other) const
{
	return
		Data == other.Data &&
		DeviceBuffer == other.DeviceBuffer &&
		Offset == other.Offset &&
		Size == other.Size;
}
