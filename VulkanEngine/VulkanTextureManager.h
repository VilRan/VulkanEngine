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

	virtual Texture* Load(const char* path);

private:
	std::vector<VulkanTexture*> Textures;
};

