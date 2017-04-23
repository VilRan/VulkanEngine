#include "BufferManager.h"

#include "VulkanHelper.h"

BufferManager::BufferManager(VkPhysicalDevice& physicalDevice, VkDevice& device, VkCommandPool commandPool, VkQueue graphicsQueue)
	: PhysicalDevice(physicalDevice), Device(device), CommandPool(commandPool), GraphicsQueue(graphicsQueue)
{
}

BufferManager::~BufferManager()
{
}

void BufferManager::AllocateMemory()
{
	VulkanHelper::CreateBuffer(
		PhysicalDevice, Device, TotalSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		StagingBuffer, StagingBufferMemory
	);

	for (auto reservation : Reservations)
	{
		void* data;
		vkMapMemory(Device, StagingBufferMemory, reservation.GetOffset(), reservation.GetSize(), 0, &data);
		memcpy(data, reservation.GetData(), (size_t)reservation.GetSize());
		vkUnmapMemory(Device, StagingBufferMemory);
	}

	VulkanHelper::CreateBuffer(
		PhysicalDevice, Device, TotalSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		DeviceBuffer, DeviceBufferMemory
	);

	VulkanHelper::CopyBuffer(Device, CommandPool, GraphicsQueue, StagingBuffer, DeviceBuffer, TotalSize);
}

Buffer BufferManager::Reserve(void* data, VkDeviceSize size)
{
	auto buffer = Buffer(data, DeviceBuffer.GetPointer(), TotalSize, size);
	TotalSize += size;
	Reservations.push_back(buffer);
	return buffer;
}
