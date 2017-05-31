#pragma once

#include "Scene.h"
#include "TileType.h"

class Tile
{
public:
	Tile(Scene& scene, TileType type, uint32_t x, uint32_t y, uint32_t z);
	virtual ~Tile();

	void SetType(TileType type);

private:
	Scene& Scene;
	Actor* Actor = nullptr;
	uint32_t X = 0, Y = 0, Z = 0;
};
