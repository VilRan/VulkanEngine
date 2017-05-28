#pragma once
#include "Texture.h"
#include <vulkan/vulkan.h>

class VulkanTexture :
	public Texture
{
public:
	VulkanTexture(const char* path, VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual ~VulkanTexture();

	VkDeviceSize GetSize();
	void Create(const char* path, VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	void UpdateDescriptorSet(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorSetLayout imageDescriptorSetLayout, VkSampler sampler);
	void Bind(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

private:
	VkDevice Device = VK_NULL_HANDLE;
	VkImage Image = VK_NULL_HANDLE;
	VkDeviceMemory ImageMemory = VK_NULL_HANDLE;
	VkImageView ImageView = VK_NULL_HANDLE;
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;

	void Destroy();
};

