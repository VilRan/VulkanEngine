#include "DynamicBufferPool.h"

DynamicBufferPool::DynamicBufferPool()
{
}

DynamicBufferPool::DynamicBufferPool(::BufferManager* bufferManager, size_t sizePerBuffer, size_t numberOfBuffers)
{
	Initialize(bufferManager, sizePerBuffer, numberOfBuffers);
}

DynamicBufferPool::~DynamicBufferPool()
{
}

void DynamicBufferPool::Initialize(::BufferManager* bufferManager, size_t sizePerBuffer, size_t numberOfBuffers)
{
	BufferManager = bufferManager;
	SizePerBuffer = sizePerBuffer;

	size_t totalSize = sizePerBuffer * numberOfBuffers;
	Buffer = BufferManager->Reserve(nullptr, totalSize);
}

DynamicBuffer DynamicBufferPool::Reserve(void* data)
{
	DynamicBuffer buffer(data, Buffer.GetHandlePointer(), Buffer.GetOffset() + DynamicOffsetCounter, SizePerBuffer, DynamicOffsetCounter);
	DynamicOffsetCounter += SizePerBuffer;
	return buffer;
}

void DynamicBufferPool::Release(DynamicBuffer buffer)
{
}
