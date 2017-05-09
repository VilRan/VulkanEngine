#include "VulkanTextureManager.h"

VulkanTextureManager::VulkanTextureManager()
{
}

VulkanTextureManager::~VulkanTextureManager()
{
	for (auto texture : Textures)
	{
		delete texture;
	}
}

Texture* VulkanTextureManager::Load(const char* path)
{
	int width, height, channels;
	stbi_uc* pixels = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	if (!pixels)
	{
		throw std::runtime_error("failed to load texture image!");
	}

	auto texture = new ::VulkanTexture(pixels, width, height, channels);
	Textures.push_back(texture);
	return texture;
}
