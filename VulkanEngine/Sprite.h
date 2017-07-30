#pragma once

#include "Model.h"
#include "Texture.h"
#include "Rectangle.h"

class Sprite
{
public:
	Sprite(Model* model, Texture* texture, Engine::Rectangle bounds);
	virtual ~Sprite();

	Model* GetModel() const { return Model; }
	Texture* GetTexture() const { return Texture; }
	const Engine::Rectangle GetBounds() const { return Bounds; }

private:
	Model* Model;
	Texture* Texture;
	Engine::Rectangle Bounds;
};
