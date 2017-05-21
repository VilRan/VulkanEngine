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
};
