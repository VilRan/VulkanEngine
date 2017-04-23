#pragma once

#include <vulkan/vulkan.h>

class Buffer
{
public:
	Buffer();
	Buffer(void* data, VkBuffer* deviceBuffer, VkDeviceSize offset, VkDeviceSize size);
	virtual ~Buffer();

	inline const void* GetData() const { return Data; }
	inline const VkBuffer GetDeviceBuffer() const { return *DeviceBuffer; }
	inline const VkDeviceSize GetOffset() const { return Offset; }
	inline const VkDeviceSize GetSize() const { return Size; }

private:
	void* Data;
	VkBuffer* DeviceBuffer;
	VkDeviceSize Offset;
	VkDeviceSize Size;
};

