#include "BufferManager.h"
#include "VulkanHelper.h"

BufferManager::BufferManager(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
	: PhysicalDevice(physicalDevice), Device(device), CommandPool(commandPool), GraphicsQueue(graphicsQueue)
{
}

BufferManager::~BufferManager()
{
}

Buffer BufferManager::Reserve(void* data, VkDeviceSize size)
{
	Buffer reservation(data, LocalBuffer.GetHandlePointer(), TotalBufferSize, size);
	Reservations.push_back(reservation);
	TotalBufferSize += size;
	return reservation;
}

void BufferManager::AllocateMemory()
{
	StagingBuffer.Create(PhysicalDevice, Device, TotalBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	LocalBuffer.Create(PhysicalDevice, Device, TotalBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	UpdateBuffers(Reservations.data(), Reservations.size());
}

void BufferManager::UpdateBuffers(Buffer* buffers, size_t bufferCount)
{
	for (size_t i = 0; i < bufferCount; i++)
	{
		StagingBuffer.Update(buffers[i]);
	}
	
	if (bufferCount == Reservations.size())
	{
		StagingBuffer.CopyTo(LocalBuffer, CommandPool, GraphicsQueue);
	}
	else
	{
		StagingBuffer.CopyTo(LocalBuffer, buffers, bufferCount, CommandPool, GraphicsQueue);
	}
}
