#pragma once

#include "BufferManager.h"
#include "DynamicBuffer.h"

class DynamicBufferPool
{
public:
	DynamicBufferPool();
	DynamicBufferPool(BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers);
	virtual ~DynamicBufferPool();

	void Initialize(BufferManager* bufferManager, size_t sizePerDynamicBuffer, size_t numberOfDynamicBuffers);
	DynamicBuffer Reserve(void* data);
	void Release(DynamicBuffer buffer);
	void UpdateBuffers(Buffer* buffers, size_t bufferCount);
	inline const Buffer GetBuffer() const { return Buffer; }
	inline const size_t GetSizePerDynamicBuffer() const { return SizePerDynamicBuffer; }

private:
	std::vector<DynamicBuffer> Vacancies;
	BufferManager* BufferManager = nullptr;
	Buffer Buffer;
	size_t SizePerDynamicBuffer = 0;
	uint32_t DynamicOffsetCounter = 0;
};

