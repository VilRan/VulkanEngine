#include "Actor.h"

#include <glm/gtx/transform.hpp>

Actor::Actor(::Model* model, ::Texture* texture)
{
	Model = model;
	Texture = texture;
}


inline Actor::~Actor()
{
}

inline Model& Actor::GetModel()
{
	return *Model;
}

inline Texture& Actor::GetTexture()
{
	return *Texture;
}

inline glm::vec3 Actor::GetPosition()
{
	return Position;
}

inline void Actor::SetPosition(glm::vec3 position)
{
	Position = position;
}

inline glm::quat Actor::GetRotation()
{
	return Rotation;
}

inline void Actor::SetRotation(glm::quat rotation)
{
	Rotation = rotation;
}

inline glm::vec3 Actor::GetScale()
{
	return Scale;
}

inline void Actor::SetScale(glm::vec3 scale)
{
	Scale = scale;
}

inline glm::mat4 Actor::GetTransform()
{
	glm::mat4 translationMatrix = glm::translate(Position);
	glm::mat4 rotationMatrix = glm::toMat4(Rotation);
	glm::mat4 scaleMatrix = glm::scale(Scale);
	return translationMatrix * rotationMatrix * scaleMatrix;
}
