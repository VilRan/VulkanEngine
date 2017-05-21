#include "DynamicBufferPool.h"

DynamicBufferPool::DynamicBufferPool()
{
}

DynamicBufferPool::DynamicBufferPool(::BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers)
{
	Initialize(bufferManager, sizePerDynamicBuffer, numberOfDynamicBuffers);
}

DynamicBufferPool::~DynamicBufferPool()
{
}

void DynamicBufferPool::Initialize(::BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers)
{
	BufferManager = bufferManager;
	SizePerDynamicBuffer = sizePerDynamicBuffer;

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
		BufferManager->AllocateMemory();
		//TODO: Handle memory allocation failures.
		//TODO: If buffer offset changes, move the offset of existing dynamic buffers.
	}

	DynamicBuffer buffer(data, Buffer.GetHandlePointer(), Buffer.GetOffset() + DynamicOffsetCounter, SizePerDynamicBuffer, DynamicOffsetCounter);
	DynamicOffsetCounter += SizePerDynamicBuffer;
	return buffer;
}

void DynamicBufferPool::Release(DynamicBuffer buffer)
{
	Vacancies.push_back(buffer);
}

void DynamicBufferPool::UpdateBuffers(::Buffer* buffers, size_t bufferCount)
{
	BufferManager->UpdateBuffers(buffers, bufferCount);
}
