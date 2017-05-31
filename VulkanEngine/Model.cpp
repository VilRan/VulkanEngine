#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	: Vertices(vertices), Indices(indices)
{

}

Model::~Model()
{
}

Vertex* Model::GetVertexData()
{
	return Vertices.data();
}

size_t Model::GetVertexCount()
{
	return Vertices.size();
}

uint32_t* Model::GetIndexData()
{
	return Indices.data();
}

size_t Model::GetIndexCount()
{
	return Indices.size();
}

size_t Model::GetVertexBufferSize()
{
	return sizeof(Vertices[0]) * Vertices.size();
}

size_t Model::GetIndexBufferSize()
{
	return sizeof(Indices[0]) * Indices.size();
}
