#include "VulkanTextureManager.h"

VulkanTextureManager::VulkanTextureManager()
{
}

VulkanTextureManager::~VulkanTextureManager()
{
	for (auto texture : Textures)
	{
		texture->Destroy(Device);
		delete texture;
	}
}

void VulkanTextureManager::Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	PhysicalDevice = physicalDevice;
	Device = device;
	CommandPool = commandPool;
	GraphicsQueue = graphicsQueue;
}

Texture* VulkanTextureManager::Load(const char* path)
{
	auto texture = new ::VulkanTexture();
	texture->Create(path, PhysicalDevice, Device, CommandPool, GraphicsQueue);
	Textures.push_back(texture);
	return texture;
}
