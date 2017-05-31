#include "GameMap.h"

GameMap::GameMap()
{
}

GameMap::GameMap(::Scene* scene, ::Ruleset* ruleset, uint32_t width, uint32_t height, uint32_t depth)
{
	Initialize(scene, ruleset);
}

GameMap::~GameMap()
{
}

void GameMap::Initialize(::Scene* scene, ::Ruleset* ruleset, uint32_t width, uint32_t height, uint32_t depth)
{
	Scene = scene;
	Ruleset = ruleset;
	Width = width;
	Height = height;
	Depth = depth;
	TileType empty = Ruleset->GetTileType("Empty");
	TileType block = Ruleset->GetTileType("Block");
	TileType colored = Ruleset->GetTileType("Colored");

	for (size_t y = 0; y < Height; y++)
	{
		for (size_t x = 0; x < Width; x++)
		{
			for (size_t z = 0; z < Depth; z++)
			{
				switch (y)
				{
				case 0:
					Terrain.emplace_back(*Scene, empty, x, y, z);
				case 4:
					Terrain.emplace_back(*Scene, block, x, y, z);
				default:
					Terrain.emplace_back(*Scene, colored, x, y, z);
					break;
				}
			}
		}
	}
}
