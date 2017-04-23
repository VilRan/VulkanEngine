#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Model.h"
#include "Texture.h"

class Actor
{
public:
	Actor(Model* model, Texture* texture);
	virtual ~Actor();

	Model& GetModel();
	Texture& GetTexture();
	inline glm::vec3 GetPosition();
	inline void SetPosition(glm::vec3 position);
	inline glm::quat GetRotation();
	inline void SetRotation(glm::quat rotation);
	inline glm::vec3 GetScale();
	inline void SetScale(glm::vec3 scale);
	inline glm::mat4 GetTransform();

private:
	Model* Model;
	Texture* Texture;
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
};

