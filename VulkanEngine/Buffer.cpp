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

const VkBufferCopy Buffer::GetCopyRegion()
{
	VkBufferCopy region;
	region.srcOffset = Offset;
	region.dstOffset = Offset;
	region.size = Size;
	return region;
}

bool Buffer::operator==(const Buffer other) const
{
	return
		Data == other.Data &&
		Handle == other.Handle &&
		Offset == other.Offset &&
		Size == other.Size;
}
