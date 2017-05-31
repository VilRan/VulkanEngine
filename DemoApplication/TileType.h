#pragma once

#include "Model.h"
#include "Texture.h"

class TileType
{
public:
	TileType();
	TileType(Model* model, Texture* texture);
	virtual ~TileType();

	inline Model* GetModel() const { return Model; }
	inline Texture* GetTexture() const { return Texture; }

private:
	Model* Model = nullptr;
	Texture* Texture = nullptr;
};

