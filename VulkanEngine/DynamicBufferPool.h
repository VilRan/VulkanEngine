#pragma once

#include "BufferManager.h"
#include "DynamicBuffer.h"

class DynamicBufferPool
{
public:
	DynamicBufferPool();
	DynamicBufferPool(BufferManager* bufferManager, size_t sizePerBuffer, size_t numberOfBuffers);
	virtual ~DynamicBufferPool();

	void Initialize(BufferManager* bufferManager, size_t sizePerBuffer, size_t numberOfBuffers);
	DynamicBuffer Reserve(void* data);
	void Release(DynamicBuffer buffer);
	const Buffer GetBuffer() const { return Buffer; }

private:
	BufferManager* BufferManager = nullptr;
	Buffer Buffer;
	size_t SizePerBuffer = 0;
	uint32_t DynamicOffsetCounter = 0;
};

