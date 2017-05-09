#pragma once
#include "Texture.h"
#include <vulkan/vulkan.h>
#include "VDeleter.h"

class VulkanTexture :
	public Texture
{
public:
	VulkanTexture(stbi_uc* pixels, int width, int height, int channels);
	virtual ~VulkanTexture();

	VkDeviceSize GetSize();

private:
	/*
	VkDevice& Device;

	VDeleter<VkImage> TextureImage{ Device, vkDestroyImage };
	VDeleter<VkDeviceMemory> TextureImageMemory{ Device, vkFreeMemory };
	VDeleter<VkImageView> TextureImageView{ Device, vkDestroyImageView };
	VDeleter<VkSampler> TextureSampler{ Device, vkDestroySampler };
	*/
};

