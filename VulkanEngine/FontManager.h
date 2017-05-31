#pragma once

#include "SpriteFont.h"
#include "TextureManager.h"
#include "SpriteManager.h"

class FontManager
{
public:
	FontManager();
	FontManager(SpriteManager* spriteManager);
	virtual ~FontManager();

	void Initialize(SpriteManager* spriteManager);
	SpriteFont* Load(Texture* texture, const char* metaPath);

private:
	std::vector<SpriteFont*> Fonts;
	SpriteManager* SpriteManager;
};

