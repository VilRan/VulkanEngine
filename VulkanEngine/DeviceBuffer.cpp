#include "DeviceBuffer.h"

#include "VulkanHelper.h"

DeviceBuffer::DeviceBuffer()
{
}

DeviceBuffer::~DeviceBuffer()
{
	Destroy();
}

void DeviceBuffer::Create
(
	VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, 
	VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties
)
{
	Destroy();
	PhysicalDevice = physicalDevice;
	Device = device;
	CommandPool = commandPool;
	GraphicsQueue = graphicsQueue;
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

void DeviceBuffer::CopyTo(DeviceBuffer& destination)
{
	VulkanHelper::CopyBuffer(Device, CommandPool, GraphicsQueue, Buffer, destination.GetHandle(), Size);
}

void DeviceBuffer::CopyTo(DeviceBuffer& destination, ::Buffer* regions, size_t regionCount)
{
	VulkanHelper::CopyBuffer(Device, CommandPool, GraphicsQueue, Buffer, destination.GetHandle(), regions, regionCount);
}

void DeviceBuffer::Destroy()
{
	if (Device == VK_NULL_HANDLE)
	{
		return;
	}

	if (Buffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(Device, Buffer, nullptr);
		Buffer = VK_NULL_HANDLE;
	}

	if (Memory != VK_NULL_HANDLE)
	{
		vkFreeMemory(Device, Memory, nullptr);
		Memory = VK_NULL_HANDLE;
	}

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
