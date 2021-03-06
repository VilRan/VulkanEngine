#include "Camera2D.h"

#include <glm/gtx/transform.hpp>

Camera2D::Camera2D(glm::vec2 position, float width, float height, float rotation)
{
	Position = position;
	Width = width;
	Height = height;
	Rotation = rotation;
}

Camera2D::~Camera2D()
{
}

glm::mat4 Camera2D::GetViewProjection(bool invertY)
{
	float yScale = -2.0f;
	if (invertY)
	{
		yScale = 2.0f;
	}

	glm::vec3 scale(2.0f / Width, yScale / Height, 1.0f);
	glm::mat4 scaleMatrix = glm::scale(scale);
	glm::vec3 translation(Position.x, Position.y, 0.0f);
	glm::mat4 translationMatrix = glm::translate(translation);
	glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);
	glm::mat4 rotationMatrix = glm::rotate(Rotation, rotationAxis);
	return scaleMatrix * translationMatrix * rotationMatrix;
}
