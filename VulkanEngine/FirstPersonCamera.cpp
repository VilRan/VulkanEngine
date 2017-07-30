#include "FirstPersonCamera.h"

#include <glm/gtc/matrix_transform.hpp>

FirstPersonCamera::FirstPersonCamera()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	Angles = glm::vec2(0.0f, 0.0f);
}

FirstPersonCamera::~FirstPersonCamera()
{
}

glm::mat4 FirstPersonCamera::GetViewProjection()
{
	glm::vec3 target = Position + Rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(Position, target, up);
	glm::mat4 projection = glm::perspective(glm::radians(FieldOfView), AspectRatio, Near, Far);
	projection[1][1] *= -1;
	return projection * view;
}

void FirstPersonCamera::MoveBy(glm::vec3 delta)
{
	Position += delta;
}

void FirstPersonCamera::Rotate(float x, float y)
{
	Angles.x += x;
	Angles.y += y;

	float yLimit = glm::pi<float>() / 3;
	if (Angles.y > yLimit)
	{
		Angles.y = yLimit;
	}
	else if (Angles.y < -yLimit)
	{
		Angles.y = -yLimit;
	}

	glm::quat q1 = glm::angleAxis(Angles.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat q2 = glm::angleAxis(Angles.y, glm::vec3(0.0f, 0.0f, -1.0f));
	Rotation = q1 * q2;
}

void FirstPersonCamera::MoveForward(float delta)
{
	Position += glm::angleAxis(Angles.x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec3(delta, 0.0f, 0.0f);
}

void FirstPersonCamera::MoveBackward(float delta)
{
	MoveForward(-delta);
}

void FirstPersonCamera::MoveRight(float delta)
{
	Position += glm::angleAxis(Angles.x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec3(0.0f, 0.0f, delta);
}

void FirstPersonCamera::MoveLeft(float delta)
{
	MoveRight(-delta);
}


