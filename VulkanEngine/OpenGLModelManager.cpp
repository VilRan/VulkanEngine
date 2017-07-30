#include "OpenGLModelManager.h"

#include "OpenGLModel.h"

OpenGLModelManager::OpenGLModelManager()
{
}

OpenGLModelManager::~OpenGLModelManager()
{
	for (auto model : Models)
	{
		delete model;
	}
}

Model* OpenGLModelManager::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
	auto model = new OpenGLModel(vertices, indices);
	Models.push_back(model);
	return model;
}
