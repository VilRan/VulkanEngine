#pragma once
#include "TextureManager.h"

#include <vector>
#include "OpenGLTexture.h"

class OpenGLTextureManager :
	public TextureManager
{
public:
	OpenGLTextureManager();
	virtual ~OpenGLTextureManager();

	virtual Texture* Load(const char* path);

private:
	std::vector<OpenGLTexture*> Textures;
};
