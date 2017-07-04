#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#define GLFW_INCLUDE_VULKAN

#include <functional>
#include <vector>
#include <array>
#include "GlfwApplication.h"
#include "VDeleter.h"
#include "DebugReportCallback.h"
#include "Vertex.h"
#include "Buffer.h"
#include "VulkanTextureManager.h"
#include "VulkanModelManager.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "BufferManager.h"
#include "DynamicBufferPool.h"
#include "VulkanModel.h"
#include "Actor.h"
#include "VulkanScene.h"
//#include "Timer.h"

struct QueueFamilyIndices {
	int GraphicsFamily = -1;
	int PresentFamily = -1;

	bool IsComplete() 
	{
		return GraphicsFamily >= 0 && PresentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR Capabilities;
	std::vector<VkSurfaceFormatKHR> Formats;
	std::vector<VkPresentModeKHR> PresentModes;
};

class VulkanApplication :
	public GlfwApplication
{
public:
	VulkanApplication();
	~VulkanApplication();

	virtual Model* CreateModel(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	virtual Model* LoadModel(const char* path);
	virtual Texture* LoadTexture(const char* path);
	virtual Sprite* CreateSprite(Texture* texture);
	virtual Sprite* CreateSprite(Texture* texture, Rectangle area);
	virtual SpriteFont* LoadFont(Texture* texture, const char* metaPath);
	virtual SpriteFont* LoadFont(const char* texturePath, const char* metaPath);
	virtual Scene* GetRootScene() { return RootScene; }

protected:
	virtual void BeginRun();
	virtual void BeginUpdate(UpdateEvent update);
	virtual void EndUpdate(UpdateEvent update);
	virtual void EndRun();
	virtual void OnWindowResized();

private:
	VDeleter<VkInstance> Instance{ vkDestroyInstance };
	VDeleter<VkDebugReportCallbackEXT> Callback{ Instance, DestroyDebugReportCallbackEXT };
	VDeleter<VkSurfaceKHR> Surface{ Instance, vkDestroySurfaceKHR };

	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VDeleter<VkDevice> Device{ vkDestroyDevice };

	VkQueue GraphicsQueue = VK_NULL_HANDLE;
	VkQueue PresentQueue = VK_NULL_HANDLE;

	VDeleter<VkSwapchainKHR> SwapChain{ Device, vkDestroySwapchainKHR };
	std::vector<VkImage> SwapChainImages;
	VkFormat SwapChainImageFormat;
	VkExtent2D SwapChainExtent;
	std::vector<VDeleter<VkImageView>> SwapChainImageViews;
	std::vector<VDeleter<VkFramebuffer>> SwapChainFramebuffers;

	VDeleter<VkRenderPass> RenderPass{ Device, vkDestroyRenderPass };
	VDeleter<VkDescriptorSetLayout> ViewProjectionDescriptorSetLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkDescriptorSetLayout> ModelDescriptorSetLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkDescriptorSetLayout> ImageDescriptorSetLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkPipelineLayout> PipelineLayout{ Device, vkDestroyPipelineLayout };
	VDeleter<VkPipeline> GraphicsPipeline{ Device, vkDestroyPipeline };

	VDeleter<VkCommandPool> CommandPool{ Device, vkDestroyCommandPool };

	VDeleter<VkImage> DepthImage{ Device, vkDestroyImage };
	VDeleter<VkDeviceMemory> DepthImageMemory{ Device, vkFreeMemory };
	VDeleter<VkImageView> DepthImageView{ Device, vkDestroyImageView };
	VDeleter<VkSampler> TextureSampler{ Device, vkDestroySampler };

	BufferManager BufferManager;
	VulkanModelManager Models;
	VulkanTextureManager Textures;
	SpriteManager Sprites;
	FontManager Fonts;
	DynamicBufferPool DynamicBufferPool;
	VDeleter<VkDescriptorPool> DescriptorPool{ Device, vkDestroyDescriptorPool };
	VkDescriptorSet ViewProjectionDescriptorSet;
	VkDescriptorSet ModelDescriptorSet;

	//Timer DrawTimer;
	FencedCommandBufferPool FencedCommandBufferPool;
	VkCommandBuffer NextImageCommandBuffer;
	VkFence NextImageFence;
	uint32_t NextImageIndex;

	VDeleter<VkSemaphore> ImageAvailableSemaphore{ Device, vkDestroySemaphore };
	VDeleter<VkSemaphore> RenderFinishedSemaphore{ Device, vkDestroySemaphore };

	VulkanScene* RootScene;

	void LoadContent();
	void RecreateSwapChain();
	void CreateInstance();
	void SetupDebugCallback();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateDescriptorSetLayouts();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateDepthResources();
	VkFormat FindDepthFormat();
	VkFormat FindSupportedFormat(const std::vector<VkFormat>& canditates, VkImageTiling tiling, VkFormatFeatureFlags features);
	void CreateTextureSampler();
	void CreateDescriptorPool();
	void CreateDescriptorSets();
	void CreateSemaphores();
	//void Draw(TimerEvent timer);
	void AcquireNextImage();
	void RecordDrawCommandBuffer();
	void DrawFrame();
	void CreateShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	std::vector<const char*> GetRequiredExtensions();
	bool CheckValidationLayerSupport();
	static std::vector<char> ReadFile(const std::string& filename);
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
};
