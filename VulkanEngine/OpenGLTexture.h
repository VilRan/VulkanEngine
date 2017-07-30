#pragma once
#include <glad/glad.h>
#include "Texture.h"
class OpenGLTexture :
	public Texture
{
public:
	OpenGLTexture(const char* path);
	virtual ~OpenGLTexture();

	void Bind();

private:
	GLuint Index;
};
