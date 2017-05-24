#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

class ICamera
{
public:
	ICamera();
	virtual ~ICamera();

	virtual glm::mat4 GetViewProjection() = 0;
	inline const float GetAspectRatio() const { return AspectRatio; }
	inline void SetAspectRatio(float aspectRatio) { AspectRatio = aspectRatio; Changed = true; }
	inline const bool HasChanged() const { return Changed; }
	inline void SetChanged(bool changed) { Changed = changed; }

protected:
	float AspectRatio = 1.0f;
	bool Changed = false;
};
