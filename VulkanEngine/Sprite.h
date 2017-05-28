#pragma once

#include "Model.h"
#include "Texture.h"

class Sprite
{
public:
	Sprite(Model* model, Texture* texture);
	virtual ~Sprite();

	inline Model* GetModel() const { return Model; }
	inline Texture* GetTexture() const { return Texture; }

private:
	Model* Model;
	Texture* Texture;
};
