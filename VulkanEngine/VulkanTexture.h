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
	inline const VkImageView GetImageView() const { return ImageView; }
	void Create(const char* path, VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	void Destroy(VkDevice device);

private:
	VkImage Image = VK_NULL_HANDLE;
	VkDeviceMemory ImageMemory = VK_NULL_HANDLE;
	VkImageView ImageView = VK_NULL_HANDLE;
};

