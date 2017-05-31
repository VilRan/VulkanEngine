#pragma once

#include <vulkan/vulkan.h>
#include "Buffer.h"

class DeviceBuffer
{
public:
	DeviceBuffer();
	virtual ~DeviceBuffer();

	void Create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	void Update(Buffer buffer);
	void CopyTo(DeviceBuffer& destination, VkCommandPool commandPool, VkQueue graphicsQueue);
	void CopyTo(DeviceBuffer& destination, Buffer* regions, size_t regionCount, VkCommandPool commandPool, VkQueue graphicsQueue);
	void Destroy();

	VkBuffer GetHandle();
	VkBuffer* GetHandlePointer();

private:
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;
	VkBuffer Buffer = VK_NULL_HANDLE;
	VkDeviceMemory Memory = VK_NULL_HANDLE;
	VkDeviceSize Size = 0;
};

