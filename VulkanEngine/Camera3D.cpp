#include "Camera3D.h"

#include <glm/gtc/matrix_transform.hpp>

Camera3D::Camera3D()
{
}

Camera3D::Camera3D(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fieldOfView, float aspectRatio, float near, float far)
{
	Position = position;
	Target = target;
	Up = up;
	FieldOfView = fieldOfView;
	AspectRatio = aspectRatio;
	Near = near;
	Far = far;
	Changed = true;
}

Camera3D::~Camera3D()
{
}

glm::mat4 Camera3D::GetViewProjection()
{
	glm::mat4 view = glm::lookAt(Position, Target, Up);
	glm::mat4 projection = glm::perspective(glm::radians(FieldOfView), AspectRatio, Near, Far);
	projection[1][1] *= -1;
	return projection * view;
}
