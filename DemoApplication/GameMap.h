#pragma once

#include "Ruleset.h"
#include "Tile.h"
#include "Scene.h"
#include "Projectile.h"
#include "UpdateEvent.h"

class GameMap
{
public:
	GameMap();
	GameMap(Scene* scene, Ruleset* ruleset, uint32_t width = 100, uint32_t height = 10, uint32_t depth = 100);
	virtual ~GameMap();

	void Initialize(Scene* scene, Ruleset* ruleset, uint32_t width = 100, uint32_t height = 10, uint32_t depth = 100);
	void Update(UpdateEvent update);

private:
	std::vector<Tile> Terrain;
	std::vector<Projectile*> Projectiles;
	Scene* Scene;
	::Scene* ProjectileScene;
	Ruleset* Ruleset;
	uint32_t Width = 100;
	uint32_t Height = 10;
	uint32_t Depth = 100;
};

