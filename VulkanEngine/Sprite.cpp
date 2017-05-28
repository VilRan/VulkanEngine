#include "Sprite.h"

Sprite::Sprite(::Model* model, ::Texture* texture, Rectangle bounds)
{
	Model = model;
	Texture = texture;
	Bounds = bounds;
}

Sprite::~Sprite()
{
}
