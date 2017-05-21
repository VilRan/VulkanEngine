#pragma once

#include <vulkan/vulkan.h>

class Buffer
{
public:
	Buffer();
	Buffer(void* data, VkBuffer* handle, VkDeviceSize offset, VkDeviceSize size);
	virtual ~Buffer();

	inline const void* GetData() const { return Data; }
	inline void SetData(void* data) { Data = data; }
	inline const VkBuffer GetHandle() const { return *Handle; }
	inline VkBuffer* GetHandlePointer() const { return Handle; }
	inline const VkDeviceSize GetOffset() const { return Offset; }
	inline const VkDeviceSize GetSize() const { return Size; }
	bool operator==(const Buffer other) const;

private:
	void* Data = nullptr;
	VkBuffer* Handle = nullptr;
	VkDeviceSize Offset = 0;
	VkDeviceSize Size = 0;
};
