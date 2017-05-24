#pragma once

#include "ICamera.h"

class Camera3D
	: public ICamera
{
public:
	Camera3D();
	Camera3D(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fieldOfView, float aspectRatio, float near, float far);
	virtual ~Camera3D();

	inline const glm::vec3 GetPosition() const { return Position; }
	inline void SetPosition(glm::vec3 position) { Position = position; Changed = true; }
	inline const glm::vec3 GetTarget() const { return Target; }
	inline void SetTarget(glm::vec3 position) { Position = position; Changed = true; }
	inline const glm::vec3 GetUp() const { return Up; }
	inline void SetUp(glm::vec3 position) { Position = position; Changed = true; }
	inline const float GetFieldOfView() const { return FieldOfView; }
	inline void SetFieldOfView(float fieldOfView) { FieldOfView = fieldOfView; Changed = true; }
	inline const float GetNear() const { return Near; }
	inline void SetNear(float near) { Near = near; Changed = true; }
	inline const float GetFar() const { return Far; }
	inline void SetFar(float far) { Far = far; Changed = true; }
	virtual glm::mat4 GetViewProjection();

private:
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Up;
	float FieldOfView = 60.0f;
	float Near = 0.1f;
	float Far = 10.0f;
};

