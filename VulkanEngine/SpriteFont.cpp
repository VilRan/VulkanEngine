#include "SpriteFont.h"

#include <fstream>
#include <sstream>

SpriteFont::SpriteFont(Texture* texture, const char* metaPath, SpriteManager& spriteManager)
{
	std::ifstream file(metaPath);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open font meta file!");
	}

	std::string line;
	std::getline(file, line);

	if (line == "monospace")
	{
		std::getline(file, line);
		std::istringstream iss(line);
		int left, top, width, height;
		if (!(iss >> left >> top >> width >> height))
		{
			file.close();
			throw std::runtime_error("Failed to read monospace character width and/or height!");
		}

		SpaceWidth = width;

		int y = 0;
		while (std::getline(file, line))
		{
			iss = std::istringstream(line);
			char c;
			int x = 0;
			while (iss >> c)
			{
				Rectangle charArea(x, y, width, height);
				Sprite* sprite = spriteManager.Create(texture, charArea);
				Sprites.emplace(c, sprite);
				x += width;
			}

			y += height;
		}
	}

	file.close();
}

SpriteFont::~SpriteFont()
{
}

Sprite* SpriteFont::GetSprite(char c)
{
	return Sprites[c];
}
