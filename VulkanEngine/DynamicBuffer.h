#pragma once
#include "Buffer.h"
class DynamicBuffer :
	public Buffer
{
public:
	DynamicBuffer();
	DynamicBuffer(void* data, VkBuffer* handlePointer, VkDeviceSize offset, VkDeviceSize size, uint32_t dynamicOffset);
	virtual ~DynamicBuffer();

	inline const uint32_t GetDynamicOffset() const { return DynamicOffset; }

private:
	uint32_t DynamicOffset = 0;
};

