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
	VulkanActor(VulkanModel* model, ::Texture* texture, VkDescriptorSet descriptorSet, DynamicBuffer dynamicBuffer, VulkanScene* scene);
	virtual ~VulkanActor();

	inline const VkDescriptorSet GetDescriptorSet() const { return DescriptorSet; }
	inline const DynamicBuffer GetDynamicBuffer() const { return DynamicBuffer; }
	inline virtual void SetPosition(glm::vec3 position);
	inline virtual void SetRotation(glm::quat rotation);
	inline virtual void SetScale(glm::vec3 scale);
	inline virtual void SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

private:
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
	DynamicBuffer DynamicBuffer;
	VulkanScene* Scene;

	void UpdateBuffer();
};

