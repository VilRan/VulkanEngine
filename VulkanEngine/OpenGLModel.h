#pragma once
#include <glad/glad.h>
#include "Model.h"

class OpenGLModel :
	public Model
{
public:
	OpenGLModel(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
	virtual ~OpenGLModel();

	void Bind();

private:
	GLuint VertexArray;
	GLuint VertexBuffer;
	GLuint IndexBuffer;
};
