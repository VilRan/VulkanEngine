#pragma once

#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	virtual Texture* Load(const char* path) = 0;
};

