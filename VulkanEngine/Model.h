#pragma once

#include <vector>
#include "Vertex.h"

class Model
{
public:
	Model(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
	virtual ~Model();

	Vertex* GetVertexData();
	size_t GetVertexCount();
	uint32_t* GetIndexData();
	size_t GetIndexCount();

	size_t GetVertexBufferSize();
	size_t GetIndexBufferSize();

private:
	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;
};

