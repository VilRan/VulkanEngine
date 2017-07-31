#include "Projectile.h"

#include "GameMap.h"

Projectile::Projectile()
{
}

Projectile::Projectile(GameMap* map, ::Scene* scene, ProjectileType type, glm::vec3 position)
	: Map(map), Scene(scene)
{
	Position = position;
	Velocity = { 0.0f, 0.0f, 0.0f };
	Actor = Scene->AddActor(type.GetModel(), type.GetTexture(), Position);
}

Projectile::~Projectile()
{
	Destroy();
}

void Projectile::Update(UpdateEvent update)
{
	if (Actor == nullptr)
	{
		return;
	}

	float time = (float)update.GetDeltaTime();
	glm::vec3 acceleration(0.0f, -9.81f, 0.0f);
	Position += Velocity * time + 0.5f * acceleration * time * time;
	Velocity += acceleration * time;
	Actor->SetPosition(Position);

	if (Position.y < 0)
	{
		Destroy();
	}
}

void Projectile::Destroy()
{
	if (Actor != nullptr)
	{
		Scene->RemoveActor(Actor);
		Actor = nullptr;
	}
}
