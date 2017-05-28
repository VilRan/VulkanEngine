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

glm::vec3 Actor::GetPosition()
{
	return Position;
}

void Actor::SetPosition(glm::vec3 position)
{
	Position = position;
	UpdateTransform();
}

glm::quat Actor::GetRotation()
{
	return Rotation;
}

void Actor::SetRotation(glm::quat rotation)
{
	Rotation = rotation;
	UpdateTransform();
}

glm::vec3 Actor::GetScale()
{
	return Scale;
}

void Actor::SetScale(glm::vec3 scale)
{
	Scale = scale;
	UpdateTransform();
}

glm::mat4 Actor::GetTransform()
{
	return Transform;
}

void Actor::SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
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
