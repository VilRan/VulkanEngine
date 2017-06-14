#pragma once
#include "Scene.h"
#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanActor.h"
#include "DynamicBufferPool.h"
#include "VulkanTexture.h"
#include "Camera3D.h"

class VulkanActor;

enum SceneStatus
{
	Changed,
	Ready
};

class VulkanScene :
	public Scene
{
public:
	VulkanScene(
		VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout,
		VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet,
		DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass, std::shared_ptr<ICamera> camera
	);
	VulkanScene(
		VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout,
		VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet,
		DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass, float aspectRatio
	);
	virtual ~VulkanScene();

	virtual Actor* AddActor(Sprite* sprite, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
	virtual Actor* AddActor(Model* model, Texture* texture, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
	virtual Label* AddLabel(const char* text, SpriteFont* font, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
	virtual void RemoveActor(Actor* actor);
	virtual int GetActorCount();
	virtual int GetVertexCount();
	virtual Scene* AddScene();
	virtual void RemoveScene(Scene* scene);
	virtual std::shared_ptr<ICamera> GetCamera();
	virtual void SetCamera(std::shared_ptr<ICamera> camera, bool passToChildScenes = true);
	void Reset(VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, float aspectRatio);
	void BuildSecondaryCommandBuffer();
	void BuildPrimaryCommandBuffer(VkCommandBuffer commandBuffer);
	void Update();

protected:
	void BuildCommandBuffer(VkCommandBuffer commandBuffer);

private:
	std::vector<VulkanScene*> ChildScenes;
	std::unordered_map<VulkanModel*, std::unordered_map<VulkanTexture*, std::vector<VulkanActor*>>> GroupedActors;
	std::vector<VulkanActor*> VacantActors;
	std::vector<Label*> Labels;
	std::shared_ptr<ICamera> Camera;
	glm::mat4 ViewProjection;
	DynamicBuffer ViewProjectionBuffer;
	SceneStatus Status = Changed;
	size_t ActorCount = 0;
	size_t VertexCount = 0;
	DynamicBufferPool& DynamicBufferPool;
	std::vector<VkCommandBuffer> CommandBuffers;
	VkDevice Device = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkPipeline GraphicsPipeline = VK_NULL_HANDLE;
	VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
	VkDescriptorSet ViewProjectionDescriptorSet = VK_NULL_HANDLE;
	VkDescriptorSet ModelDescriptorSet = VK_NULL_HANDLE;
	VkRenderPass RenderPass = VK_NULL_HANDLE;
	uint32_t LastCommandBufferIndex;

	VulkanScene(
		VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout,
		VkDescriptorSet viewProjectionDescriptorSet, VkDescriptorSet modelDescriptorSet,
		::DynamicBufferPool& dynamicBufferPool, VkRenderPass renderPass
	);

	void AllocateCommandBuffers();
	void FreeCommandBuffers();
	std::shared_ptr<Camera3D> CreateDefaultCamera(float aspectRatio);
};
