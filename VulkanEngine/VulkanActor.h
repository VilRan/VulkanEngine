#pragma once
#include "Actor.h"

#include "VulkanModel.h"
#include "DynamicBuffer.h"
#include "VulkanScene.h"

class VulkanScene;

class VulkanActor :
	public Actor
{
public:
	VulkanActor(VulkanModel* model, ::Texture* texture, DynamicBuffer dynamicBuffer, VulkanScene* scene);
	virtual ~VulkanActor();

	inline const DynamicBuffer GetDynamicBuffer() const { return DynamicBuffer; }
	inline virtual void SetPosition(glm::vec3 position);
	inline virtual void SetRotation(glm::quat rotation);
	inline virtual void SetScale(glm::vec3 scale);
	inline virtual void SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

private:
	DynamicBuffer DynamicBuffer;
	VulkanScene* Scene;

	void UpdateBuffer();
};

