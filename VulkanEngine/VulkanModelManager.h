#pragma once

#include "ModelManager.h"
#include "BufferManager.h"
#include "VulkanModel.h"

class VulkanModelManager
	: public ModelManager
{
public:
	VulkanModelManager();
	VulkanModelManager(BufferManager* bufferManager);
	virtual ~VulkanModelManager();

	void Initialize(BufferManager* bufferManager);
	Model* CreateModel(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

private:
	std::vector<VulkanModel*> Models;
	BufferManager* BufferManager = nullptr;
};
