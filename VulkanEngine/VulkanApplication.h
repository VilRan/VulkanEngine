#pragma once
#include "IApplication.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <functional>
#include <vector>
#include <array>
#include "VDeleter.h"
#include "DebugReportCallback.h"
#include "Vertex.h"
#include "Buffer.h"
#include "VulkanTextureManager.h"
#include "BufferManager.h"
#include "DynamicBufferPool.h"
#include "VulkanModel.h"
#include "Actor.h"
#include "VulkanScene.h"

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
	public IApplication
{
public:
	VulkanApplication();
	~VulkanApplication();

	virtual void Run();
	virtual Model* LoadModel(const char* path);
	virtual Texture* LoadTexture(const char* path);
	inline virtual Scene* GetRootScene() { return RootScene; }

private:
	GLFWwindow* Window;

	VDeleter<VkInstance> Instance{ vkDestroyInstance };
	VDeleter<VkDebugReportCallbackEXT> Callback{ Instance, DestroyDebugReportCallbackEXT };
	VDeleter<VkSurfaceKHR> Surface{ Instance, vkDestroySurfaceKHR };

	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VDeleter<VkDevice> Device{ vkDestroyDevice };

	VkQueue GraphicsQueue;
	VkQueue PresentQueue;

	VDeleter<VkSwapchainKHR> SwapChain{ Device, vkDestroySwapchainKHR };
	std::vector<VkImage> SwapChainImages;
	VkFormat SwapChainImageFormat;
	VkExtent2D SwapChainExtent;
	std::vector<VDeleter<VkImageView>> SwapChainImageViews;
	std::vector<VDeleter<VkFramebuffer>> SwapChainFramebuffers;

	VDeleter<VkRenderPass> RenderPass{ Device, vkDestroyRenderPass };
	VDeleter<VkDescriptorSetLayout> ViewProjectionLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkDescriptorSetLayout> ModelLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkDescriptorSetLayout> ImageLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkPipelineLayout> PipelineLayout{ Device, vkDestroyPipelineLayout };
	VDeleter<VkPipeline> GraphicsPipeline{ Device, vkDestroyPipeline };

	VDeleter<VkCommandPool> CommandPool{ Device, vkDestroyCommandPool };

	VDeleter<VkImage> DepthImage{ Device, vkDestroyImage };
	VDeleter<VkDeviceMemory> DepthImageMemory{ Device, vkFreeMemory };
	VDeleter<VkImageView> DepthImageView{ Device, vkDestroyImageView };

	VulkanTextureManager Textures;
	//VulkanTexture* Texture;
	VDeleter<VkSampler> TextureSampler{ Device, vkDestroySampler };
	BufferManager BufferManager;
	DynamicBufferPool DynamicBufferPool;
	Buffer ViewProjectionUniformBuffer;

	VDeleter<VkDescriptorPool> DescriptorPool{ Device, vkDestroyDescriptorPool };
	VkDescriptorSet ViewProjectionDescriptorSet;
	VkDescriptorSet ModelDescriptorSet;
	//VkDescriptorSet ImageDescriptorSet;

	VulkanScene* RootScene;

	std::vector<VkCommandBuffer> CommandBuffers;

	VDeleter<VkSemaphore> ImageAvailableSemaphore{ Device, vkDestroySemaphore };
	VDeleter<VkSemaphore> RenderFinishedSemaphore{ Device, vkDestroySemaphore };
	
	void InitWindow();
	void InitVulkan();
	static void OnWindowResized(GLFWwindow* window, int width, int height);
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
	void CreateUniformBuffer();
	void CreateDescriptorPool();
	void CreateDescriptorSets();
	void CreateCommandBuffers();
	void CreateSemaphores();
	void UpdateUniformBuffer();
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
