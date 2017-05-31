#pragma once
#include "Actor.h"

#include "VulkanModel.h"
#include "DynamicBufferPool.h"
#include "VulkanScene.h"

class VulkanScene;

class VulkanActor :
	public Actor
{
public:
	VulkanActor(VulkanModel* model, ::Texture* texture, VulkanScene& scene, DynamicBufferPool& dynamicBufferPool);
	virtual ~VulkanActor();

	inline const DynamicBuffer GetDynamicBuffer() const { return DynamicBuffer; }
	virtual void SetPosition(glm::vec3 position);
	virtual void SetRotation(glm::quat rotation);
	virtual void SetScale(glm::vec3 scale);
	virtual void SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

private:
	VulkanScene& Scene;
	DynamicBufferPool& DynamicBufferPool;
	DynamicBuffer DynamicBuffer;

	void UpdateBuffer();
};

