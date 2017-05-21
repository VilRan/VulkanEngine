#include "Actor.h"

#include <glm/gtx/transform.hpp>

Actor::Actor(::Model* model, ::Texture* texture)
{
	Model = model;
	Texture = texture;
}

Actor::~Actor()
{
}

inline glm::vec3 Actor::GetPosition()
{
	return Position;
}

inline void Actor::SetPosition(glm::vec3 position)
{
	Position = position;
	UpdateTransform();
}

inline glm::quat Actor::GetRotation()
{
	return Rotation;
}

inline void Actor::SetRotation(glm::quat rotation)
{
	Rotation = rotation;
	UpdateTransform();
}

inline glm::vec3 Actor::GetScale()
{
	return Scale;
}

inline void Actor::SetScale(glm::vec3 scale)
{
	Scale = scale;
	UpdateTransform();
}

glm::mat4 Actor::GetTransform()
{
	return Transform;
}

inline void Actor::SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	Position = position;
	Rotation = rotation;
	Scale = scale;
	UpdateTransform();
}

void Actor::UpdateTransform()
{
	glm::mat4 translationMatrix = glm::translate(Position);
	glm::mat4 rotationMatrix = glm::toMat4(Rotation);
	glm::mat4 scaleMatrix = glm::scale(Scale);
	Transform = translationMatrix * rotationMatrix * scaleMatrix;
}
