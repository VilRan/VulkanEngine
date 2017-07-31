#include "Camera3D.h"

#include <glm/gtc/matrix_transform.hpp>

Camera3D::Camera3D()
{
}

Camera3D::Camera3D(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fieldOfView, float aspectRatio, float nearDistance, float farDistance)
{
	Position = position;
	Target = target;
	Up = up;
	FieldOfView = fieldOfView;
	AspectRatio = aspectRatio;
	Near = nearDistance;
	Far = farDistance;
}

Camera3D::~Camera3D()
{
}

glm::mat4 Camera3D::GetViewProjection(bool invertY)
{
	glm::mat4 view = glm::lookAt(Position, Target, Up);
	glm::mat4 projection = glm::perspective(glm::radians(FieldOfView), AspectRatio, Near, Far);
	if (invertY)
	{
		projection[1][1] *= -1;
	}
	return projection * view;
}

void Camera3D::MoveBy(glm::vec3 delta)
{
	Position += delta;
	Target += delta;
}

void Camera3D::Rotate(glm::quat rotation)
{
	Target = Position + rotation * (Target - Position);
	Up = rotation * Up;
}

glm::vec3 Camera3D::GetForward()
{
	return glm::normalize(Target - Position);
}

glm::vec3 Camera3D::GetBackward()
{
	return -GetForward();
}

glm::vec3 Camera3D::GetRight()
{
	return glm::cross(GetForward(), Up);
}

glm::vec3 Camera3D::GetLeft()
{
	return -GetRight();
}
