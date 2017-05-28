#include "Sprite.h"

Sprite::Sprite(::Model* model, ::Texture* texture)
{
	Model = model;
	Texture = texture;
}

Sprite::~Sprite()
{
}
