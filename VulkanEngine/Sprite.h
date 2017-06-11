#pragma once

#include "Model.h"
#include "Texture.h"
#include "Rectangle.h"

class Sprite
{
public:
	Sprite(Model* model, Texture* texture, Rectangle bounds);
	virtual ~Sprite();

	Model* GetModel() const { return Model; }
	Texture* GetTexture() const { return Texture; }
	const Rectangle GetBounds() const { return Bounds; }

private:
	Model* Model;
	Texture* Texture;
	Rectangle Bounds;
};
