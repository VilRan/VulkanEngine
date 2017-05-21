#include "Buffer.h"

Buffer::Buffer()
{
}

Buffer::Buffer(void* data, VkBuffer* handle, VkDeviceSize offset, VkDeviceSize size)
{
	Data = data;
	Handle = handle;
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
		Handle == other.Handle &&
		Offset == other.Offset &&
		Size == other.Size;
}
