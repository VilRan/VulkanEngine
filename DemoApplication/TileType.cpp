#include "TileType.h"

TileType::TileType()
{
}

TileType::TileType(::Model* model, ::Texture* texture)
{
	Model = model;
	Texture = texture;
}

TileType::~TileType()
{
}
