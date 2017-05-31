#pragma once

#include "Ruleset.h"
#include "Tile.h"
#include "Scene.h"

class GameMap
{
public:
	GameMap();
	GameMap(Scene* scene, Ruleset* ruleset, uint32_t width = 100, uint32_t height = 10, uint32_t depth = 100);
	virtual ~GameMap();

	void Initialize(Scene* scene, Ruleset* ruleset, uint32_t width = 100, uint32_t height = 10, uint32_t depth = 100);

private:
	std::vector<Tile> Terrain;
	Scene* Scene;
	Ruleset* Ruleset;
	uint32_t Width = 100;
	uint32_t Height = 10;
	uint32_t Depth = 100;
};

