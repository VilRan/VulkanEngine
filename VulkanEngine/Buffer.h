#pragma once

#include <vulkan/vulkan.h>

class Buffer
{
public:
	Buffer();
	Buffer(void* data, VkBuffer* deviceBuffer, VkDeviceSize offset, VkDeviceSize size);
	virtual ~Buffer();

	inline const void* GetData() const { return Data; }
	inline void SetData(void* data) { Data = data; }
	inline const VkBuffer GetDeviceBuffer() const { return *DeviceBuffer; }
	inline VkBuffer* GetHandlePointer() const { return DeviceBuffer; }
	inline const VkDeviceSize GetOffset() const { return Offset; }
	inline const VkDeviceSize GetSize() const { return Size; }
	bool operator==(const Buffer other) const;

private:
	void* Data = nullptr;
	VkBuffer* DeviceBuffer = nullptr;
	VkDeviceSize Offset = 0;
	VkDeviceSize Size = 0;
};
