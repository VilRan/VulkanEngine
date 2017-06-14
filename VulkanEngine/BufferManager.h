#pragma once

#include <vector>
#include "Buffer.h"
#include "Vertex.h"
#include "DeviceBuffer.h"
#include "FencedCommandBufferPool.h"

class BufferManager
{
public:
	BufferManager();
	BufferManager(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	virtual ~BufferManager();

	void Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);
	Buffer Reserve(void* data, VkDeviceSize size);
	void Release(Buffer buffer);
	void AllocateReserved();
	void Update(Buffer buffer);
	void Update(Buffer* buffers, size_t bufferCount);
	void BeginUpdates();
	void EndUpdates();

private:
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkQueue GraphicsQueue = VK_NULL_HANDLE;
	FencedCommandBufferPool FencedCommandBufferPool;
	VkCommandBuffer ActiveCommandBuffer = VK_NULL_HANDLE;
	VkFence ActiveFence = VK_NULL_HANDLE;

	std::vector<Buffer> Reservations;
	std::vector<Buffer> Vacancies;
	std::vector<Buffer> Staged;
	DeviceBuffer StagingBuffer;
	DeviceBuffer LocalBuffer;
	VkDeviceSize TotalBufferSize = 0;
	VkDeviceSize OffsetAlignment = 0;

	void CopyFromStagingToLocal(Buffer* buffers, size_t bufferCount);
};

