#include "ProjectileType.h"

ProjectileType::ProjectileType()
{
}

ProjectileType::ProjectileType(::Model* model, ::Texture* texture)
{
	Model = model;
	Texture = texture;
}

ProjectileType::~ProjectileType()
{
}
