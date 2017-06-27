#include "DeviceBuffer.h"

#include "VulkanHelper.h"

DeviceBuffer::DeviceBuffer()
{
}

DeviceBuffer::~DeviceBuffer()
{
	Destroy();
}

void DeviceBuffer::Initialize
(
	VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, 
	VkBufferUsageFlags usage, VkMemoryPropertyFlags properties
)
{
	Destroy();
	PhysicalDevice = physicalDevice;
	Device = device;
	CommandPool = commandPool;
	GraphicsQueue = graphicsQueue;
	Usage = usage;
	Properties = properties;
}

void DeviceBuffer::Resize(VkDeviceSize newSize)
{
	VkBuffer newBuffer;
	VkDeviceMemory newMemory;
	VulkanHelper::CreateBuffer(PhysicalDevice, Device, newSize, Usage, Properties, &newBuffer, &newMemory);
	VulkanHelper::CopyBuffer(Device, CommandPool, GraphicsQueue, Buffer, newBuffer, Size);

	//TODO: This is here because a command buffer may be in the middle of using the old buffer when memory is reallocated. Look into better ways to solve this.
	vkDeviceWaitIdle(Device);

	Destroy();

	Buffer = newBuffer;
	Memory = newMemory;
	Size = newSize;
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
