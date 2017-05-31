#include "FontManager.h"

#include <fstream>
#include <sstream>

FontManager::FontManager()
{
}

FontManager::FontManager(::SpriteManager* spriteManager)
{
	Initialize(spriteManager);
}

FontManager::~FontManager()
{
	for (auto font : Fonts)
	{
		delete font;
	}
}

void FontManager::Initialize(::SpriteManager* spriteManager)
{
	SpriteManager = spriteManager;
}

SpriteFont * FontManager::Load(Texture* texture, const char* metaPath)
{
	auto font = new SpriteFont(texture, metaPath, *SpriteManager);
	Fonts.push_back(font);
	return font;
}

