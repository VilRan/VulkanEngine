#pragma once

#include <vector>
#include "Buffer.h"
#include "Vertex.h"
#include "VDeleter.h"

class BufferManager
{
public:
	BufferManager(VkPhysicalDevice& physicalDevice, VkDevice& device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual ~BufferManager();

	Buffer Reserve(void* data, VkDeviceSize size);
	void AllocateMemory();
	void UpdateBuffers(Buffer* buffers, size_t bufferCount);

private:
	std::vector<Buffer> Reservations;
	VkDeviceSize TotalBufferSize = 0;
	VDeleter<VkBuffer> StagingBuffer;
	VDeleter<VkDeviceMemory> StagingBufferMemory;
	VDeleter<VkBuffer> DeviceBuffer;
	VDeleter<VkDeviceMemory> DeviceBufferMemory;

	VkPhysicalDevice& PhysicalDevice;
	VkDevice& Device;
	VkCommandPool CommandPool;
	VkQueue GraphicsQueue;
};

