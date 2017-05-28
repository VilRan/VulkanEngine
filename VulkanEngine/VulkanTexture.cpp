#include "VulkanTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>
#include "VulkanHelper.h"

VulkanTexture::VulkanTexture(const char* path, VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	Device = device;
	Create(path, physicalDevice, device, commandPool, graphicsQueue);
}

VulkanTexture::~VulkanTexture()
{
	Destroy();
}

VkDeviceSize VulkanTexture::GetSize()
{
	return GetWidth() * GetHeight() * 4;
}

void VulkanTexture::Create(const char* path, VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	Destroy();

	stbi_uc* pixels = stbi_load(path, &Width, &Height, &Channels, STBI_rgb_alpha);
	if (!pixels)
	{
		throw std::runtime_error("Failed to load texture image!");
	}

	VkDeviceSize imageSize = GetSize();
	VkImage stagingImage;
	VkDeviceMemory stagingImageMemory;

	VulkanHelper helper(physicalDevice, device, commandPool, graphicsQueue);
	helper.CreateImage(
		Width, Height,
		VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&stagingImage, &stagingImageMemory
	);

	VkImageSubresource subresource = {};
	subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresource.mipLevel = 0;
	subresource.arrayLayer = 0;

	VkSubresourceLayout stagingImageLayout;
	vkGetImageSubresourceLayout(device, stagingImage, &subresource, &stagingImageLayout);

	void* data;
	vkMapMemory(device, stagingImageMemory, 0, imageSize, 0, &data);

	if (stagingImageLayout.rowPitch == Width * 4)
	{
		memcpy(data, pixels, (size_t)imageSize);
	}
	else
	{
		uint8_t* dataBytes = reinterpret_cast<uint8_t*>(data);

		for (int y = 0; y < Height; y++)
		{
			memcpy(&dataBytes[y * stagingImageLayout.rowPitch], &pixels[y * Width * 4], Height * 4);
		}
	}

	vkUnmapMemory(device, stagingImageMemory);

	stbi_image_free(pixels);

	helper.CreateImage(
		Width, Height,
		VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		&Image, &ImageMemory
	);
	helper.TransitionImageLayout(stagingImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
	helper.TransitionImageLayout(Image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	helper.CopyImage(stagingImage, Image, Width, Height);
	helper.TransitionImageLayout(Image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	helper.CreateImageView(Image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, &ImageView);

	vkFreeMemory(device, stagingImageMemory, nullptr);
	vkDestroyImage(device, stagingImage, nullptr);
}

void VulkanTexture::UpdateDescriptorSet(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorSetLayout imageDescriptorSetLayout, VkSampler sampler)
{
	if (DescriptorSet == VK_NULL_HANDLE)
	{
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &imageDescriptorSetLayout;

		if (vkAllocateDescriptorSets(device, &allocInfo, &DescriptorSet) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to allocate descriptor set!");
		}
	}

	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = ImageView;
	imageInfo.sampler = sampler;

	VkWriteDescriptorSet descriptorWrite;
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = DescriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pImageInfo = &imageInfo;
	descriptorWrite.pNext = NULL;

	vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
}

void VulkanTexture::Bind(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout)
{
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 2, 1, &DescriptorSet, 0, nullptr);
}

void VulkanTexture::Destroy()
{
	if (ImageView != VK_NULL_HANDLE)
	{
		vkDestroyImageView(Device, ImageView, nullptr);
		ImageView = VK_NULL_HANDLE;
	}
	if (ImageMemory != VK_NULL_HANDLE)
	{
		vkFreeMemory(Device, ImageMemory, nullptr);
		ImageMemory = VK_NULL_HANDLE;
	}
	if (Image != VK_NULL_HANDLE)
	{
		vkDestroyImage(Device, Image, nullptr);
		Image = VK_NULL_HANDLE;
	}
}
