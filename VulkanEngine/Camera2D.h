#pragma once
#include "ICamera.h"
class Camera2D :
	public ICamera
{
public:
	Camera2D(glm::vec2 position, float width, float height, float rotation);
	virtual ~Camera2D();

	const glm::vec2 GetPosition() const { return Position; }
	void SetPosition(glm::vec2 position) { Position = position; }
	const float GetWidth() const { return Width; }
	void SetWidth(float width) { Width = width; }
	const float GetHeight() const { return Height; }
	void SetHeight(float height) { Height = height; }
	const float GetRotation() const { return Rotation; }
	void SetRotation(float rotation) { Rotation = rotation; }
	virtual glm::mat4 GetViewProjection();

private:
	glm::vec2 Position;
	float Width;
	float Height;
	float Rotation;
};
