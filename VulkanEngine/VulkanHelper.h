#pragma once

#include <vulkan/vulkan.h>

#include "VDeleter.h"
#include "Buffer.h"

class VulkanHelper
{
public:
	VulkanHelper();
	virtual ~VulkanHelper();

	static void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory);
	static void CopyBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	static void CopyBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, Buffer* buffers, size_t bufferCount);
	static VkCommandBuffer BeginSingleTimeCommands(VkDevice device, VkCommandPool commandPool);
	static void EndSingleTimeCommands(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkCommandBuffer commandBuffer);
	static uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

