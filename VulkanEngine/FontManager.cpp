#include "FontManager.h"

#include <fstream>
#include <sstream>

FontManager::FontManager()
{
}

FontManager::FontManager(::TextureManager* textureManager, ::SpriteManager* spriteManager)
{
	Initialize(textureManager, spriteManager);
}

FontManager::~FontManager()
{
	for (auto font : Fonts)
	{
		delete font;
	}
}

void FontManager::Initialize(::TextureManager* textureManager, ::SpriteManager* spriteManager)
{
	TextureManager = textureManager;
	SpriteManager = spriteManager;
}

SpriteFont* FontManager::Load(Texture* texture, const char* metaPath)
{
	auto font = new SpriteFont(texture, metaPath, *SpriteManager);
	Fonts.push_back(font);
	return font;
}

SpriteFont* FontManager::Load(const char* texturePath, const char* metaPath)
{
	auto texture = TextureManager->Load(texturePath);
	return Load(texture, metaPath);
}
