#pragma once

#include <vector>
#include "Buffer.h"
#include "Vertex.h"
#include "DeviceBuffer.h"

class BufferManager
{
public:
	BufferManager();
	BufferManager(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual ~BufferManager();

	void Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	Buffer Reserve(void* data, VkDeviceSize size);
	void Release(Buffer buffer);
	void AllocateMemory();
	void UpdateBuffers(Buffer* buffers, size_t bufferCount);

private:
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkQueue GraphicsQueue = VK_NULL_HANDLE;

	std::vector<Buffer> Reservations;
	std::vector<Buffer> Vacancies;
	VkDeviceSize TotalBufferSize = 0;
	VkDeviceSize OffsetAlignment = 0;

	DeviceBuffer StagingBuffer;
	DeviceBuffer LocalBuffer;
};

