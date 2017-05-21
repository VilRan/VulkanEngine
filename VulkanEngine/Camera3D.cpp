#include "Camera3D.h"

#include <glm/gtc/matrix_transform.hpp>

Camera3D::Camera3D()
{
}

Camera3D::~Camera3D()
{
}

glm::mat4 Camera3D::GetViewProjection()
{
	glm::mat4 view = glm::lookAt(Position, Target, Up);
	glm::mat4 projection = glm::perspective(glm::radians(FieldOfView), AspectRatio, 0.1f, 10.0f);
	projection[1][1] *= -1;
	return projection * view;
}
