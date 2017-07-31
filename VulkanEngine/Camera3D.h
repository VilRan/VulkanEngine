#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "ICamera.h"

class Camera3D
	: public ICamera
{
public:
	Camera3D();
	Camera3D(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fieldOfView, float aspectRatio, float nearDistance, float farDistance);
	virtual ~Camera3D();

	virtual glm::mat4 GetViewProjection();
	void MoveBy(glm::vec3 delta);
	void Rotate(glm::quat rotation);
	glm::vec3 GetForward();
	glm::vec3 GetBackward();
	glm::vec3 GetRight();
	glm::vec3 GetLeft();
	const glm::vec3 GetPosition() const { return Position; }
	void SetPosition(glm::vec3 position) { Position = position; }
	const glm::vec3 GetTarget() const { return Target; }
	void SetTarget(glm::vec3 target) { Target = target; }
	const glm::vec3 GetUp() const { return Up; }
	void SetUp(glm::vec3 up) { Up = up; }
	const float GetFieldOfView() const { return FieldOfView; }
	void SetFieldOfView(float fieldOfView) { FieldOfView = fieldOfView; }
	const float GetNear() const { return Near; }
	void SetNear(float nearDistance) { Near = nearDistance; }
	const float GetFar() const { return Far; }
	void SetFar(float farDistance) { Far = farDistance; }

private:
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Up;
	float FieldOfView = 60.0f;
	float Near = 0.1f;
	float Far = 10.0f;
};

