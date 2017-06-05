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

	inline Model* GetModel() { return Model; }
	virtual void SetModel(Model* model) { Model = model; }
	inline Texture* GetTexture() { return Texture; }
	virtual void SetTexture(Texture* texture) { Texture = texture; }
	glm::vec3 GetPosition();
	virtual void SetPosition(glm::vec3 position);
	glm::quat GetRotation();
	virtual void SetRotation(glm::quat rotation);
	glm::vec3 GetScale();
	virtual void SetScale(glm::vec3 scale);
	glm::mat4 GetTransform();
	virtual void SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

protected:
	Model* Model;
	Texture* Texture;
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
	glm::mat4 Transform;

	void UpdateTransform();
};

