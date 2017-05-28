#pragma once
#include "ICamera.h"
class Camera2D :
	public ICamera
{
public:
	Camera2D(glm::vec2 position, float width, float height, float rotation);
	virtual ~Camera2D();

	inline const glm::vec2 GetPosition() const { return Position; }
	inline void SetPosition(glm::vec2 position) { Position = position; }
	inline const float GetWidth() const { return Width; }
	inline void SetWidth(float width) { Width = width; }
	inline const float GetHeight() const { return Height; }
	inline void SetHeight(float height) { Height = height; }
	inline const float GetRotation() const { return Rotation; }
	inline void SetRotation(float rotation) { Rotation = rotation; }
	virtual glm::mat4 GetViewProjection();

private:
	glm::vec2 Position;
	float Width;
	float Height;
	float Rotation;
};