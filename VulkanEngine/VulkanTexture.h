#pragma once
#include "Texture.h"
#include <vulkan/vulkan.h>

class VulkanTexture :
	public Texture
{
public:
	VulkanTexture();
	virtual ~VulkanTexture();

	VkDeviceSize GetSize();
	//inline const VkImageView GetImageView() const { return ImageView; }
	//inline const VkDescriptorSet GetDescriptorSet() const { return DescriptorSet; }
	void Create(const char* path, VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	void UpdateDescriptorSet(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorSetLayout imageDescriptorSetLayout, VkSampler sampler);
	void Destroy(VkDevice device);
	void Bind(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

private:
	VkImage Image = VK_NULL_HANDLE;
	VkDeviceMemory ImageMemory = VK_NULL_HANDLE;
	VkImageView ImageView = VK_NULL_HANDLE;
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
};

