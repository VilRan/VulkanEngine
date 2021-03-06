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
	for (auto projectile : Projectiles)
	{
		delete projectile;
	}
}

void GameMap::Initialize(::Scene* scene, ::Ruleset* ruleset, uint32_t width, uint32_t height, uint32_t depth)
{
	Scene = scene;
	Ruleset = ruleset;
	Width = width;
	Height = height;
	Depth = depth;
	TileType colored = Ruleset->GetTileType("Colored");
	TileType block = Ruleset->GetTileType("Block");
	TileType empty = Ruleset->GetTileType("Empty");
	
	for (uint32_t y = 0; y < Height; y++)
	{
		for (uint32_t x = 0; x < Width; x++)
		{
			for (uint32_t z = 0; z < Depth; z++)
			{
				int rn = rand() % 100;
				if (rn < 10)
				{
					Terrain.emplace_back(*Scene, colored, x, y, z);
				}
				else if (rn < 30)
				{
					Terrain.emplace_back(*Scene, block, x, y, z);
				}
				else
				{
					Terrain.emplace_back(*Scene, empty, x, y, z);
				}
			}
		}
	}
	
	ProjectileScene = Scene->AddScene();
	ProjectileSpawnTimer.SetEvent(std::bind(&GameMap::SpawnProjectile, this, std::placeholders::_1));
	ProjectileSpawnTimer.SetFrequency(1000);
	ProjectileSpawnTimer.Start();
}

void GameMap::Update(UpdateEvent update)
{
	for (size_t i = 0; i < Projectiles.size(); i++)
	{
		Projectile* projectile = Projectiles[i];
		projectile->Update(update);
		if (projectile->IsDestroyed())
		{
			Projectiles.erase(Projectiles.begin() + i);
			delete projectile;
			i--;
		}
	}

	ProjectileSpawnTimer.Update(update);
}

void GameMap::SpawnProjectile(TimerEvent timer)
{
	glm::vec3 position = {};
	position.x = (float)(rand() % Width);
	position.z = (float)(rand() % Depth);
	position.y = 100.0f;

	ProjectileType type;
	auto rn = rand() % 100;
	if (rn < 25)
	{
		type = Ruleset->GetProjectileType("Icosphere");
	}
	else if (rn < 50)
	{
		type = Ruleset->GetProjectileType("InverseIcosphere");
	}
	else if (rn < 75)
	{
		type = Ruleset->GetProjectileType("Torus");
	}
	else
	{
		type = Ruleset->GetProjectileType("InverseTorus");
	}

	Projectile* projectile = new Projectile(this, ProjectileScene, type, position);
	projectile->Update(UpdateEvent(timer.GetDeltaTime(), timer.GetDeltaTime()));
	Projectiles.push_back(projectile);
}
