#pragma once
#include "ICamera.h"
class Camera2D :
	public ICamera
{
public:
	Camera2D(glm::vec2 position, float width, float height, float rotation);
	virtual ~Camera2D();

	inline const glm::vec2 GetPosition() const { return Position; }
	inline void SetPosition(glm::vec2 position) { Position = position; Changed = true; }
	inline const float GetWidth() const { return Width; }
	inline void SetWidth(float width) { Width = width; Changed = true; }
	inline const float GetHeight() const { return Height; }
	inline void SetHeight(float height) { Height = height; Changed = true; }
	inline const float GetRotation() const { return Rotation; }
	inline void SetRotation(float rotation) { Rotation = rotation; Changed = true; }
	virtual glm::mat4 GetViewProjection();

private:
	glm::vec2 Position;
	float Width;
	float Height;
	float Rotation;
};
