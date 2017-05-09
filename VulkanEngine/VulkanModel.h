#pragma once
#include "Model.h"

#include <vulkan/vulkan.h>
#include "Buffer.h"
#include "BufferManager.h"

class VulkanModel :
	public Model
{
public:
	VulkanModel(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
	virtual ~VulkanModel();

	void ReserveBuffers(BufferManager& bufferManager);
	void Bind(VkCommandBuffer commandBuffer);
	Buffer GetVertexBuffer();
	Buffer GetIndexBuffer();

private:
	Buffer VertexBuffer;
	Buffer IndexBuffer;
};

