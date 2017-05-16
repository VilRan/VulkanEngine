#pragma once

#include "Actor.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual Actor* AddActor(Model* model, Texture* texture) = 0;
	virtual void RemoveActor(Actor* actor) = 0;
};

