#pragma once

#include <unordered_map>
#include "TileType.h"
#include "ProjectileType.h"

class DemoApplication;

class Ruleset
{
public:
	Ruleset();
	virtual ~Ruleset();

	void Initialize(DemoApplication& application);
	TileType GetTileType(const char* uid);
	ProjectileType GetProjectileType(const char* uid);

private:
	std::unordered_map<const char*, TileType> TileTypes;
	std::unordered_map<const char*, ProjectileType> ProjectileTypes;
};

