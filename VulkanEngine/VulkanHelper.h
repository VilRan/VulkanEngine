#pragma once

#include <vulkan/vulkan.h>

#include "VDeleter.h"

class VulkanHelper
{
public:
	VulkanHelper();
	virtual ~VulkanHelper();

	static void CreateBuffer(VkPhysicalDevice& physicalDevice, VkDevice& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkBuffer>& buffer, VDeleter<VkDeviceMemory>& bufferMemory);
	static void CopyBuffer(VkDevice& device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	static VkCommandBuffer BeginSingleTimeCommands(VkDevice& device, VkCommandPool commandPool);
	static void EndSingleTimeCommands(VkDevice& device, VkCommandPool commandPool, VkQueue& graphicsQueue, VkCommandBuffer commandBuffer);
	static uint32_t FindMemoryType(VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

