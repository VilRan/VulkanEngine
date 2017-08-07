#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class CommandBufferPool
{
public:
	CommandBufferPool();
	virtual ~CommandBufferPool();

	virtual void Initialize(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level, size_t size);
	virtual void Destroy();
	const size_t Count() const { return CommandBuffers.size(); }

protected:
	std::vector<VkCommandBuffer> CommandBuffers;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;

private:
	void DestroyCommandBuffers();
};
