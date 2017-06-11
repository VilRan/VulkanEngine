#pragma once

#include "BufferManager.h"
#include "DynamicBuffer.h"

class DynamicBufferPool
{
public:
	DynamicBufferPool();
	DynamicBufferPool(
		BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers,
		VkDevice device, VkDescriptorPool descriptorPool,
		VkDescriptorSetLayout viewProjectionDescriptorSetLayout,  VkDescriptorSet viewProjectionDescriptorSet,
		VkDescriptorSetLayout modelDescriptorSetLayout, VkDescriptorSet modelDescriptorset
	);
	virtual ~DynamicBufferPool();

	void Initialize(
		BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers, 
		VkDevice device, VkDescriptorPool descriptorPool, 
		VkDescriptorSetLayout viewProjectionDescriptorSetLayout, VkDescriptorSet viewProjectionDescriptorSet,
		VkDescriptorSetLayout modelDescriptorSetLayout, VkDescriptorSet modelDescriptorSet
	);
	DynamicBuffer Reserve(void* data);
	void Release(DynamicBuffer buffer);
	void Update(DynamicBuffer buffer);
	void Update(Buffer* buffers, size_t bufferCount);
	void UpdateDescriptorSets();
	const Buffer GetBuffer() const { return Buffer; }
	const size_t GetSizePerDynamicBuffer() const { return SizePerDynamicBuffer; }
	const bool HasResized() const { return Resized; }
	void SetResized(bool resized) { Resized = resized; }

private:
	std::vector<DynamicBuffer> Vacancies;
	BufferManager* BufferManager = nullptr;
	Buffer Buffer;
	size_t SizePerDynamicBuffer = 0;
	uint32_t DynamicOffsetCounter = 0;
	bool Resized = false;

	VkDevice Device = VK_NULL_HANDLE;
	VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;
	VkDescriptorSetLayout ViewProjectionDescriptorSetLayout = VK_NULL_HANDLE;
	VkDescriptorSet ViewProjectionDescriptorSet = VK_NULL_HANDLE;
	VkDescriptorSetLayout ModelDescriptorSetLayout = VK_NULL_HANDLE;
	VkDescriptorSet ModelDescriptorSet = VK_NULL_HANDLE;
};

