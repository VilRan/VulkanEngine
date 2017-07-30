#pragma once
#include "ModelManager.h"

#include "OpenGLModel.h"

class OpenGLModelManager :
	public ModelManager
{
public:
	OpenGLModelManager();
	virtual ~OpenGLModelManager();

	virtual Model* Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

private:
	std::vector<OpenGLModel*> Models;
};
