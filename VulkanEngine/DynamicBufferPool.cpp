#include "DynamicBufferPool.h"

DynamicBufferPool::DynamicBufferPool()
{
}

DynamicBufferPool::DynamicBufferPool
(
	::BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers, 
	VkDevice device, VkDescriptorPool descriptorPool, 
	VkDescriptorSetLayout viewProjectionDescriptorSetLayout, VkDescriptorSet viewProjectionDescriptorSet,
	VkDescriptorSetLayout modelDescriptorSetLayout, VkDescriptorSet modelDescriptorSet
)
{
	Initialize(
		bufferManager, sizePerDynamicBuffer, numberOfDynamicBuffers, device, descriptorPool, 
		viewProjectionDescriptorSetLayout, viewProjectionDescriptorSet, modelDescriptorSetLayout, modelDescriptorSet
	);
}

DynamicBufferPool::~DynamicBufferPool()
{
}

void DynamicBufferPool::Initialize
(
	::BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers, 
	VkDevice device, VkDescriptorPool descriptorPool, 
	VkDescriptorSetLayout viewProjectionDescriptorSetLayout, VkDescriptorSet viewProjectionDescriptorSet,
	VkDescriptorSetLayout modelDescriptorSetLayout, VkDescriptorSet modeDescriptorSet
)
{
	BufferManager = bufferManager;
	SizePerDynamicBuffer = sizePerDynamicBuffer;
	Device = device;
	DescriptorPool = descriptorPool;
	ViewProjectionDescriptorSetLayout = viewProjectionDescriptorSetLayout;
	ViewProjectionDescriptorSet = viewProjectionDescriptorSet;
	ModelDescriptorSetLayout = modelDescriptorSetLayout;
	ModelDescriptorSet = modeDescriptorSet;

	size_t totalSize = sizePerDynamicBuffer * numberOfDynamicBuffers;
	Buffer = BufferManager->Reserve(nullptr, totalSize);
}

DynamicBuffer DynamicBufferPool::Reserve(void* data)
{
	if (Vacancies.size() > 0)
	{
		DynamicBuffer vacancy = Vacancies.back();
		Vacancies.pop_back();
		return vacancy;
	}

	if (DynamicOffsetCounter >= Buffer.GetSize() - SizePerDynamicBuffer)
	{
		VkDeviceSize newSize = Buffer.GetSize() * 2;
		BufferManager->Release(Buffer);
		Buffer = BufferManager->Reserve(nullptr, newSize);
		BufferManager->AllocateReserved();
		//TODO: Handle memory allocation failures.
		//TODO: If buffer offset changes, move the offset of existing dynamic buffers.
		UpdateDescriptorSets();
	}

	DynamicBuffer buffer(data, Buffer.GetHandlePointer(), Buffer.GetOffset() + DynamicOffsetCounter, SizePerDynamicBuffer, DynamicOffsetCounter);
	DynamicOffsetCounter += SizePerDynamicBuffer;
	return buffer;
}

void DynamicBufferPool::Release(DynamicBuffer buffer)
{
	Vacancies.push_back(buffer);
}

void DynamicBufferPool::Stage(DynamicBuffer buffer)
{
	BufferManager->Stage(buffer);
}

void DynamicBufferPool::UpdateBuffers(::Buffer* buffers, size_t bufferCount)
{
	BufferManager->Update(buffers, bufferCount);
}

void DynamicBufferPool::UpdateDescriptorSets()
{
	//TODO: Add support for arbitrary number of descriptor sets.

	VkDescriptorBufferInfo viewProjectionUniformBufferInfo = {};
	viewProjectionUniformBufferInfo.buffer = Buffer.GetHandle();
	viewProjectionUniformBufferInfo.offset = Buffer.GetOffset();
	viewProjectionUniformBufferInfo.range = SizePerDynamicBuffer;

	VkDescriptorBufferInfo modelUniformBufferInfo = {};
	modelUniformBufferInfo.buffer = Buffer.GetHandle();
	modelUniformBufferInfo.offset = Buffer.GetOffset();
	modelUniformBufferInfo.range = SizePerDynamicBuffer;

	std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

	descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[0].dstSet = ViewProjectionDescriptorSet;
	descriptorWrites[0].dstBinding = 0;
	descriptorWrites[0].dstArrayElement = 0;
	descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
	descriptorWrites[0].descriptorCount = 1;
	descriptorWrites[0].pBufferInfo = &viewProjectionUniformBufferInfo;

	descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[1].dstSet = ModelDescriptorSet;
	descriptorWrites[1].dstBinding = 0;
	descriptorWrites[1].dstArrayElement = 0;
	descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
	descriptorWrites[1].descriptorCount = 1;
	descriptorWrites[1].pBufferInfo = &modelUniformBufferInfo;

	vkUpdateDescriptorSets(Device, descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}
