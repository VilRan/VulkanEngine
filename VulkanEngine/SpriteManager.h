#pragma once

#include "Sprite.h"
#include "Rectangle.h"
#include "ModelManager.h"

class SpriteManager
{
public:
	SpriteManager();
	SpriteManager(ModelManager* modelManager);
	virtual ~SpriteManager();

	virtual void Initialize(ModelManager* modelManager);
	virtual Sprite* Create(Texture* texture);
	virtual Sprite* Create(Texture* texture, Engine::Rectangle area);

private:
	std::vector<Sprite*> Sprites;
	ModelManager* ModelManager = nullptr;
};
