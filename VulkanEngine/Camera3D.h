#pragma once

#include "ICamera.h"

class Camera3D
	: public ICamera
{
public:
	Camera3D();
	virtual ~Camera3D();

	inline const glm::vec3 GetPosition() const { return Position; }
	inline void SetPosition(glm::vec3 position) { Position = position; }
	inline const glm::vec3 GetTarget() const { return Target; }
	inline void SetTarget(glm::vec3 position) { Position = position; }
	inline const glm::vec3 GetUp() const { return Up; }
	inline void SetUp(glm::vec3 position) { Position = position; }
	inline const float GetFieldOfView() const { return FieldOfView; }
	inline void SetFieldOfView(float fieldOfView) { FieldOfView = fieldOfView; }
	inline const float GetAspectRatio() const { return AspectRatio; }
	inline void SetAspectRatio(float aspectRatio) { AspectRatio = aspectRatio; }
	inline const float GetNear() const { return Near; }
	inline void SetNear(float near) { Near = near; }
	inline const float GetFar() const { return Far; }
	inline void SetFar(float far) { Far = far; }
	virtual glm::mat4 GetViewProjection();

private:
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Up;
	float FieldOfView;
	float AspectRatio;
	float Near;
	float Far;
};

