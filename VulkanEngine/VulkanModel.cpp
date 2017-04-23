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

Buffer VulkanModel::GetVertexBuffer()
{
	return VertexBuffer;
}

Buffer VulkanModel::GetIndexBuffer()
{
	return IndexBuffer;
}
