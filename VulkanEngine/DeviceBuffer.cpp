#include "DeviceBuffer.h"

#include "VulkanHelper.h"

DeviceBuffer::DeviceBuffer()
{
}

DeviceBuffer::~DeviceBuffer()
{
	Free();
}

void DeviceBuffer::Create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
	Free();
	PhysicalDevice = physicalDevice;
	Device = device;
	Size = size;
	VulkanHelper::CreateBuffer(PhysicalDevice, Device, size, usage, properties, &Buffer, &Memory);
}

void DeviceBuffer::Update(::Buffer buffer)
{
	if (buffer.GetData() == nullptr)
	{
		return;
	}

	void* data;
	vkMapMemory(Device, Memory, buffer.GetOffset(), buffer.GetSize(), 0, &data);
	memcpy(data, buffer.GetData(), (size_t)buffer.GetSize());
	vkUnmapMemory(Device, Memory);
}

void DeviceBuffer::CopyTo(DeviceBuffer& destination, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	VulkanHelper::CopyBuffer(Device, commandPool, graphicsQueue, Buffer, destination.GetHandle(), Size);
}

void DeviceBuffer::CopyTo(DeviceBuffer& destination, ::Buffer* regions, size_t regionCount, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	VulkanHelper::CopyBuffer(Device, commandPool, graphicsQueue, Buffer, destination.GetHandle(), regions, regionCount);
}

void DeviceBuffer::Free()
{
	if (Device == VK_NULL_HANDLE)
	{
		return;
	}

	if (Buffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(Device, Buffer, nullptr);
	}
	Buffer = VK_NULL_HANDLE;

	if (Memory != VK_NULL_HANDLE)
	{
		vkFreeMemory(Device, Memory, nullptr);
	}
	Memory = VK_NULL_HANDLE;

	Size = 0;
}

VkBuffer DeviceBuffer::GetHandle()
{
	return Buffer;
}

VkBuffer* DeviceBuffer::GetHandlePointer()
{
	return &Buffer;
}
