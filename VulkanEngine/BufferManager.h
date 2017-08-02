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
	BufferManager(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, size_t commandBufferCount);
	virtual ~BufferManager();

	void Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, size_t commandBufferCount);
	Buffer Reserve(void* data, VkDeviceSize size);
	void Release(Buffer buffer);
	void Allocate();
	void Update(Buffer buffer);
	void Update(Buffer* buffers, size_t bufferCount);
	void UpdateReserved();
	void BeginUpdates();
	void EndUpdates();
	void SubmitUpdates();

private:
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkQueue GraphicsQueue = VK_NULL_HANDLE;
	FencedCommandBufferPool FencedCommandBufferPool;
	VkCommandBuffer RecordingCommandBuffer = VK_NULL_HANDLE;
	VkFence RecordingFence = VK_NULL_HANDLE;
	VkCommandBuffer ExecutableCommandBuffer = VK_NULL_HANDLE;
	VkFence ExecutableFence = VK_NULL_HANDLE;

	std::vector<Buffer> Reservations;
	std::vector<Buffer> Vacancies;
	DeviceBuffer DeviceBuffer;
	VkDeviceSize TotalBufferSize = 0;
	VkDeviceSize OffsetAlignment = 0;
};

