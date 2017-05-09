#pragma once

#include <vector>
#include "Buffer.h"
#include "Vertex.h"
#include "DeviceBuffer.h"

class BufferManager
{
public:
	BufferManager(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual ~BufferManager();

	Buffer Reserve(void* data, VkDeviceSize size);
	void AllocateMemory();
	void UpdateBuffers(Buffer* buffers, size_t bufferCount);

private:
	VkPhysicalDevice PhysicalDevice;
	VkDevice Device;
	VkCommandPool CommandPool;
	VkQueue GraphicsQueue;

	std::vector<Buffer> Reservations;
	VkDeviceSize TotalBufferSize = 0;

	DeviceBuffer StagingBuffer;
	DeviceBuffer LocalBuffer;
};

