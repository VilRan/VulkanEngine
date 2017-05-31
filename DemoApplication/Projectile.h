#pragma once

#include "Scene.h"
#include "UpdateEvent.h"
#include "ProjectileType.h"

class GameMap;

class Projectile
{
public:
	Projectile();
	Projectile(GameMap* map, Scene* scene, ProjectileType type, glm::vec3 position);
	virtual ~Projectile();

	void Update(UpdateEvent update);
	void Destroy();
	const bool IsDestroyed() const { return Actor == nullptr; }

private:
	GameMap* Map;
	Scene* Scene;
	Actor* Actor = nullptr;
	glm::vec3 Position;
	glm::vec3 Velocity;
};

