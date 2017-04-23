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
#include "BufferManager.h"
#include "VulkanModel.h"

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
	VDeleter<VkDescriptorSetLayout> DescriptorSetLayout{ Device, vkDestroyDescriptorSetLayout };
	VDeleter<VkPipelineLayout> PipelineLayout{ Device, vkDestroyPipelineLayout };
	VDeleter<VkPipeline> GraphicsPipeline{ Device, vkDestroyPipeline };

	VDeleter<VkCommandPool> CommandPool{ Device, vkDestroyCommandPool };

	VDeleter<VkImage> DepthImage{ Device, vkDestroyImage };
	VDeleter<VkDeviceMemory> DepthImageMemory{ Device, vkFreeMemory };
	VDeleter<VkImageView> DepthImageView{ Device, vkDestroyImageView };

	VDeleter<VkImage> TextureImage{ Device, vkDestroyImage };
	VDeleter<VkDeviceMemory> TextureImageMemory{ Device, vkFreeMemory };
	VDeleter<VkImageView> TextureImageView{ Device, vkDestroyImageView };
	VDeleter<VkSampler> TextureSampler{ Device, vkDestroySampler };

	//std::vector<Vertex> Vertices;
	//std::vector<uint32_t> Indices;
	BufferManager* BufferManager;
	VulkanModel* Model;
	/*
	VDeleter<VkBuffer> VertexBuffer{ Device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> VertexBufferMemory{ Device, vkFreeMemory };
	VDeleter<VkBuffer> IndexBuffer{ Device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> IndexBufferMemory{ Device, vkFreeMemory };
	*/
	VDeleter<VkBuffer> UniformStagingBuffer{ Device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> UniformStagingBufferMemory{ Device, vkFreeMemory };
	VDeleter<VkBuffer> UniformBuffer{ Device, vkDestroyBuffer };
	VDeleter<VkDeviceMemory> UniformBufferMemory{ Device, vkFreeMemory };

	VDeleter<VkDescriptorPool> DescriptorPool{ Device, vkDestroyDescriptorPool };
	VkDescriptorSet DescriptorSet;

	std::vector<VkCommandBuffer> CommandBuffers;

	VDeleter<VkSemaphore> ImageAvailableSemaphore{ Device, vkDestroySemaphore };
	VDeleter<VkSemaphore> RenderFinishedSemaphore{ Device, vkDestroySemaphore };
	

	void InitWindow();
	void InitVulkan();
	void MainLoop();
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
	void CreateDescriptorSetLayout();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateDepthResources();
	VkFormat FindDepthFormat();
	VkFormat FindSupportedFormat(const std::vector<VkFormat>& canditates, VkImageTiling tiling, VkFormatFeatureFlags features);
	bool HasStencilComponent(VkFormat format);
	void CreateTextureImage();
	void CreateTextureImageView();
	void CreateTextureSampler();
	void CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VDeleter<VkImageView>& imageView);
	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkImage>& image, VDeleter<VkDeviceMemory>& imageMemory);
	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void CopyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);
	//void CreateVertexBuffer();
	//void CreateIndexBuffer();
	void CreateUniformBuffer();
	void CreateDescriptorPool();
	void CreateDescriptorSet();
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
