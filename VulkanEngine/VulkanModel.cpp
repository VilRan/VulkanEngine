#include "VulkanModel.h"

VulkanModel::VulkanModel(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	: Model(vertices, indices)
{

}

VulkanModel::~VulkanModel()
{
}

void VulkanModel::ReserveBuffers(BufferManager& bufferManager)
{
	VertexBuffer = bufferManager.Reserve(GetVertexData(), GetVertexBufferSize());
	IndexBuffer = bufferManager.Reserve(GetIndexData(), GetIndexBufferSize());
}

void VulkanModel::Bind(VkCommandBuffer commandBuffer)
{
	VkBuffer vertexBuffer = VertexBuffer.GetDeviceBuffer();
	VkDeviceSize vertexBufferOffset = VertexBuffer.GetOffset();
	VkBuffer vertexBuffers[] = { vertexBuffer };
	VkDeviceSize offsets[] = { vertexBufferOffset };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

	VkBuffer indexBuffer = IndexBuffer.GetDeviceBuffer();
	VkDeviceSize indexBufferOffset = IndexBuffer.GetOffset();
	vkCmdBindIndexBuffer(commandBuffer, indexBuffer, indexBufferOffset, VK_INDEX_TYPE_UINT32);
}

Buffer VulkanModel::GetVertexBuffer()
{
	return VertexBuffer;
}

Buffer VulkanModel::GetIndexBuffer()
{
	return IndexBuffer;
}
