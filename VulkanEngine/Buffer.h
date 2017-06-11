#pragma once

#include <vulkan/vulkan.h>

class Buffer
{
public:
	Buffer();
	Buffer(void* data, VkBuffer* handle, VkDeviceSize offset, VkDeviceSize size);
	virtual ~Buffer();

	void* GetData() const { return Data; }
	void SetData(void* data) { Data = data; }
	const VkBuffer GetHandle() const { return *Handle; }
	VkBuffer* GetHandlePointer() const { return Handle; }
	const VkDeviceSize GetOffset() const { return Offset; }
	const VkDeviceSize GetSize() const { return Size; }
	const VkDeviceSize GetEnd() const { return Offset + Size; }
	const VkBufferCopy GetCopyRegion();
	bool operator==(const Buffer other) const;

private:
	void* Data = nullptr;
	VkBuffer* Handle = nullptr;
	VkDeviceSize Offset = 0;
	VkDeviceSize Size = 0;
};
