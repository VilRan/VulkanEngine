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
	Velocity.y -= (float)update.GetDeltaTime() * 9.81f;
	Position += Velocity;
	Actor->SetPosition(Position);

	if (Position.y < 0)
	{
		Destroy();
	}
}

void Projectile::Destroy()
{
	Scene->RemoveActor(Actor);
	Actor = nullptr;
}
