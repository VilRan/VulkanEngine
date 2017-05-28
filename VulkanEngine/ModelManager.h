#pragma once

#include "Model.h"

class ModelManager
{
public:
	ModelManager();
	virtual ~ModelManager();

	virtual Model* Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) = 0;
	virtual Model* Load(const char* path);
};
