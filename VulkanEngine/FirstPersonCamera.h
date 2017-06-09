#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "ICamera.h"

class FirstPersonCamera
	: public ICamera
{
public:
	FirstPersonCamera();
	virtual ~FirstPersonCamera();

	virtual glm::mat4 GetViewProjection();
	void MoveBy(glm::vec3 delta);
	void Rotate(float x, float y);
	void SetPosition(glm::vec3 position) { Position = position; }
	void MoveForward(float delta);
	void MoveBackward(float delta);
	void MoveRight(float delta);
	void MoveLeft(float delta);
	const float GetFieldOfView() const { return FieldOfView; }
	void SetFieldOfView(float fieldOfView) { FieldOfView = fieldOfView; }//Changed = true; }
	const float GetNear() const { return Near; }
	void SetNear(float near) { Near = near; }//Changed = true; }
	const float GetFar() const { return Far; }
	void SetFar(float far) { Far = far; }//Changed = true; }

private:
	glm::vec3 Position;
	glm::vec2 Angles;
	glm::quat Rotation;
	float FieldOfView = 60.0f;
	float Near = 0.1f;
	float Far = 10.0f;
};

