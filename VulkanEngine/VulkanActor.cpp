#include "VulkanActor.h"

VulkanActor::VulkanActor(VulkanModel* model, ::Texture* texture, ::DynamicBuffer dynamicBuffer, VulkanScene* scene)
	: Actor(model, texture)
{
	DynamicBuffer = dynamicBuffer;
	Scene = scene;
}

VulkanActor::~VulkanActor()
{
}

inline void VulkanActor::SetPosition(glm::vec3 position)
{
	Actor::SetPosition(position);
	UpdateBuffer();
}

inline void VulkanActor::SetRotation(glm::quat rotation)
{
	Actor::SetRotation(rotation);
	UpdateBuffer();
}

inline void VulkanActor::SetScale(glm::vec3 scale)
{
	Actor::SetScale(scale);
	UpdateBuffer();
}

inline void VulkanActor::SetTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	Actor::SetTransform(position, rotation, scale);
	UpdateBuffer();
}

void VulkanActor::UpdateBuffer()
{
	//TODO: Unite ViewProjection and Transform into a ModelViewProjection dynamic buffer.
	DynamicBuffer.SetData(&Transform);
	Scene->QueueBufferUpdate(DynamicBuffer);
}
