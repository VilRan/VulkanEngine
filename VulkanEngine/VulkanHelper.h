#pragma once

#include <vulkan/vulkan.h>

#include "VDeleter.h"
#include "Buffer.h"

class VulkanHelper
{
public:
	VulkanHelper(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual ~VulkanHelper();

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory);
	static void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory);

	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	static void CopyBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, Buffer* buffers, size_t bufferCount);
	static void CopyBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, Buffer* buffers, size_t bufferCount);

	VkCommandBuffer BeginSingleTimeCommands();
	static VkCommandBuffer BeginSingleTimeCommands(VkDevice device, VkCommandPool commandPool);

	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	static void EndSingleTimeCommands(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkCommandBuffer commandBuffer);

	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	static uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView* imageView);
	static void CreateImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView* imageView);

	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage* image, VkDeviceMemory* imageMemory);
	static void CreateImage(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage* image, VkDeviceMemory* imageMemory);

	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	static void TransitionImageLayout(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	void CopyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);
	static void CopyImage(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);

	static bool HasStencilComponent(VkFormat format);

private:
	VkPhysicalDevice PhysicalDevice;
	VkDevice Device;
	VkCommandPool CommandPool;
	VkQueue GraphicsQueue;
};

