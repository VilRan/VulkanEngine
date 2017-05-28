#include "VulkanModelManager.h"

VulkanModelManager::VulkanModelManager()
{
}

VulkanModelManager::VulkanModelManager(::BufferManager* bufferManager)
{
	Initialize(bufferManager);
}

VulkanModelManager::~VulkanModelManager()
{
	for (auto model : Models)
	{
		BufferManager->Release(model->GetVertexBuffer());
		BufferManager->Release(model->GetIndexBuffer());
		delete model;
	}
}

void VulkanModelManager::Initialize(::BufferManager* bufferManager)
{
	BufferManager = bufferManager;
}

Model* VulkanModelManager::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
	auto model = new VulkanModel(vertices, indices);
	model->ReserveBuffers(*BufferManager);
	Models.push_back(model);
	return model;
}
