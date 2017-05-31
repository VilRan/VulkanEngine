#pragma once

#include "Model.h"
#include "Texture.h"

class ProjectileType
{
public:
	ProjectileType();
	ProjectileType(Model* model, Texture* texture);
	virtual ~ProjectileType();

	Model* GetModel() const { return Model; }
	Texture* GetTexture() const { return Texture; }

private:
	Model* Model = nullptr;
	Texture* Texture = nullptr;
};

