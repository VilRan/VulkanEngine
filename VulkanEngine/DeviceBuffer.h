#pragma once

#include <vulkan/vulkan.h>
#include "Buffer.h"

class DeviceBuffer
{
public:
	DeviceBuffer();
	virtual ~DeviceBuffer();

	void Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	void Resize(VkDeviceSize newSize);
	void Update(Buffer buffer);
	void CopyTo(DeviceBuffer& destination);
	void CopyTo(DeviceBuffer& destination, Buffer* regions, size_t regionCount);
	void Destroy();

	VkBuffer GetHandle();
	VkBuffer* GetHandlePointer();

private:
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkQueue GraphicsQueue = VK_NULL_HANDLE;
	VkBufferUsageFlags Usage = 0;
	VkMemoryPropertyFlags Properties = 0;
	VkDeviceSize Size = 0;
	VkBuffer Buffer = VK_NULL_HANDLE;
	VkDeviceMemory Memory = VK_NULL_HANDLE;
};

