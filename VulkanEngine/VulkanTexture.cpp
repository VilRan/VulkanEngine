#include "VulkanTexture.h"

VulkanTexture::VulkanTexture(stbi_uc* pixels, int width, int height, int channels)
	: Texture(pixels, width, height, channels)
{
}

VulkanTexture::~VulkanTexture()
{
}

VkDeviceSize VulkanTexture::GetSize()
{
	return GetWidth() * GetHeight() * 4;
}
