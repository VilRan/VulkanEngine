#pragma once

#include <unordered_map>
#include "Sprite.h"
#include "SpriteManager.h"

class SpriteFont
{
public:
	SpriteFont(Texture* texture, const char* metaPath, SpriteManager& spriteManager);
	virtual ~SpriteFont();

	Sprite* GetSprite(char c);
	const int GetSpaceWidth() const { return SpaceWidth; }

private:
	std::unordered_map<char, Sprite*> Sprites;
	int SpaceWidth = 0;
};

