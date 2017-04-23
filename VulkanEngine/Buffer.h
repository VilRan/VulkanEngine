#pragma once

#include <vulkan/vulkan.h>

class Buffer
{
public:
	Buffer();
	Buffer(void* data, VkBuffer* deviceBuffer, VkDeviceSize offset, VkDeviceSize size);
	virtual ~Buffer();

	void* GetData();
	VkBuffer GetDeviceBuffer();
	VkDeviceSize GetOffset();
	VkDeviceSize GetSize();

private:
	void* Data;
	VkBuffer* DeviceBuffer;
	VkDeviceSize Offset;
	VkDeviceSize Size;
};

