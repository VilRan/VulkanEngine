#include "VulkanActor.h"

VulkanActor::VulkanActor(VulkanModel* model, ::Texture* texture, VulkanScene& scene, ::DynamicBufferPool& dynamicBufferPool)
	: Actor(model, texture), Scene(scene), DynamicBufferPool(dynamicBufferPool)
{
	DynamicBuffer = DynamicBufferPool.Reserve(&Transform);
}

VulkanActor::~VulkanActor()
{
	DynamicBufferPool.Release(DynamicBuffer);
}

void VulkanActor::SetPosition(glm::vec3 position)
{
	Actor::SetPosition(position);
	UpdateBuffer();
}

void VulkanActor::SetRotation(glm::quat rotation)
{
	Actor::SetRotation(rotation);
	UpdateBuffer();
}

void VulkanActor::SetScale(glm::vec3 scale)
{
	Actor::SetScale(scale);
	UpdateBuffer();
}

void VulkanActor::SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	Actor::SetTransform(position, rotation, scale);
	UpdateBuffer();
}

void VulkanActor::UpdateBuffer()
{
	//TODO: Maybe unite ViewProjection and Transform into a ModelViewProjection dynamic buffer.
	//Scene.QueueBufferUpdate(DynamicBuffer);
	DynamicBufferPool.Stage(DynamicBuffer);
}
