#pragma once
#include "TextureManager.h"
#include <vector>
#include "VulkanTexture.h"

class VulkanTextureManager :
	public TextureManager
{
public:
	VulkanTextureManager();
	virtual ~VulkanTextureManager();

	void Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual Texture* Load(const char* path);

private:
	std::vector<VulkanTexture*> Textures;
	VkPhysicalDevice PhysicalDevice;
	VkDevice Device;
	VkCommandPool CommandPool;
	VkQueue GraphicsQueue;
};

