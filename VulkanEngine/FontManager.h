#pragma once

#include "SpriteFont.h"
#include "TextureManager.h"
#include "SpriteManager.h"

class FontManager
{
public:
	FontManager();
	FontManager(TextureManager* textureManager, SpriteManager* spriteManager);
	virtual ~FontManager();

	void Initialize(TextureManager* textureManager, SpriteManager* spriteManager);
	SpriteFont* Load(Texture* texture, const char* metaPath);
	SpriteFont* Load(const char* texturePath, const char* metaPath);

private:
	std::vector<SpriteFont*> Fonts;
	TextureManager* TextureManager;
	SpriteManager* SpriteManager;
};

