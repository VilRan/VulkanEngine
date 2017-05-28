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

void VulkanTextureManager::Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	PhysicalDevice = physicalDevice;
	Device = device;
	CommandPool = commandPool;
	GraphicsQueue = graphicsQueue;
}

void VulkanTextureManager::UpdateDescriptorSets(VkDescriptorPool descriptorPool, VkDescriptorSetLayout imageDescriptorSetLayout, VkSampler sampler)
{
	for (auto texture : Textures)
	{
		texture->UpdateDescriptorSet(Device, descriptorPool, imageDescriptorSetLayout, sampler);
	}
}

Texture* VulkanTextureManager::Load(const char* path)
{
	auto texture = new ::VulkanTexture(path, PhysicalDevice, Device, CommandPool, GraphicsQueue);
	Textures.push_back(texture);
	return texture;
}
