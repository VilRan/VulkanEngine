#include "Tile.h"

Tile::Tile(::Scene& scene, TileType type, uint32_t x, uint32_t y, uint32_t z)
	: Scene(scene)
{
	X = x;
	Y = y;
	Z = z;
	SetType(type);
}

Tile::~Tile()
{
}

void Tile::SetType(TileType type)
{
	if (Actor != nullptr)
	{
		Scene.RemoveActor(Actor);
	}

	Model* model = type.GetModel();
	Texture* texture = type.GetTexture();

	if (model == nullptr || texture == nullptr)
	{
		return;
	}

	Scene.AddActor(model, texture, glm::vec3(X, Y, Z), glm::vec3(0.0f), glm::vec3(1.0f));
}
