// Screen.h

#ifndef SCREEN_H
#define SCREEN_H

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


#include "VulkanLibrary.h"
#include "Shaders.h"
#include <map>
#include <optional>
#include <set>
#include <array>
#include <limits> // Nesessary for std::numeric_limits
#include <algorithm> // Nesessary for std::clamp
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <chrono>
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


// The Struct that keeps the Families of Queues
struct QueueFamilyIndices
{
	// This Queue Family contains the queues of Graphics commands
	std::optional<uint32_t> graphicsFamily;
	// This Queue Family contains the queues of ______ commands
	std::optional<uint32_t> presentFamily;

	std::optional<uint32_t> transferFamily;

	bool isComplete() 
	{
		return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
	}
};

// The structure that contains information about SwapChain properties
struct SwapChainSupportDetails
{
	// min/max numbers of images in the SwapChain
	VkSurfaceCapabilitiesKHR capabilities;
	// Format of pixels and color space
	std::vector<VkSurfaceFormatKHR> formats;
	// Available operation modes
	std::vector<VkPresentModeKHR> presentModes;
};

// Function to create the debug messenger 
VkResult createDebugUtilsMessengerEXT(VkInstance instance,
										const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
										const VkAllocationCallbacks* pAllocator,
										VkDebugUtilsMessengerEXT* pDebugMessenger);

// Shaders
struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	// Function to get the Binding description between Shader and Vulkan
	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
		// Description of vertex attribute
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);
		// Description of color attribute
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		// Description of texture atribute
		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}
};

// Descriptors
struct UniformBufferObject
{
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};


class Screen
{
public:
	// This constant intended for enumeration of validation layers in Vulkan SDK
	const std::vector<const char*> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};
	// This constant intended for enumeration of required device extensions
	const std::vector<const char*> DEVICE_EXTENSIONS = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	// This constant to specifies the limit of simultaneous rendering of images
	const int MAX_FRAMES_IN_FLIGHT = 2;
	// Constant to specify the Vertex Shader Data
	const std::vector<Vertex> vertices = {   // Vertices        //Colors          //Textures
											{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
											{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
											{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
											{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
	};
	// Constant to specify the indices to represent the contents of the index buffer
	const std::vector<uint16_t> indices = { 0,1,2,2,3,0 };
	
	Screen();

	// 1. Functions of SDL2 library initialization
	void initSDL();
	void set_window(int width, int hight);
	SDL_Window* get_window() { return window; };

	// 2. Functions of Vulkan library initialization
	void initVulkanLib();

	/// 2.1. Functions for creating the Vulkan Instance
	void createInstance();
	///
	void availableExtensions();
	///
	std::vector<const char*> getRequiredExtensions();


	/// 2.2. Functions for creating the Vulkan SDK debug extension
	bool checkValidationLayerSupport();
	void setupDebugMessenger();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	
	/// 2.3. Function to call a bugs of Vulkan with using 
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
															VkDebugUtilsMessageTypeFlagsEXT messageType,
															const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
															void* pUserData);
	/// 2.4. Function to destroy the Debug messenger	
	static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
												VkDebugUtilsMessengerEXT debugMessenger,
												const VkAllocationCallbacks* pAllocator);

	// 3. Creating the surface
	void createSurface();

	// 4. Picking the available physical devices which support Vulkan features
	/// The implementation of function pickPhysicalDevise() in current code pick only one devise
	/// If you need to use more than one device you have to change the code in the function and find a right way to keep more the one VkPhysicalDevice variables
	void pickPhysicalDevise();
	/// 4.1 Verify that the physical device supports all necessary functions for the application
	bool isDeviceSuitable(VkPhysicalDevice device);
	/// 4.2. Optional function to rate the available physical devices with desired parameters 
	int rateDeviceSuitability(VkPhysicalDevice device);
		
	// 5. Creating the logical device
	/// 5.1. Function to find out the available and correct Queue Families in the Physical Device
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	/// 5.2. Function to create the Logical device that will be used to make the images
	void createLogicalDevice();

	// 6. Making Vulkan swap chain
	/// 6.1. Verify the support of required extensions in the Physical Device
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	/// 6.2. Function for filling the SwapChainSupportDetails structure
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	/// 6.3. Choosing the right setting of the Window Surface format for the SwapChain
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	/// 6.4. Choosing the right setting of the Presentation mode for the swap chain
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	/// 6.5. Choosing the swap extent
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	/// 6.6. Creating the Swap Chain
	void createSwapChain();
	/// 6.7. Function to recreate the Swap Chain when Window Size is changed
	void recreateSwapChain();
	///6.8. Function to clean the old FrameBuffer objects
	void cleanupSwapChain();
	
	// 7. Creating the Image Views
	void createImageViews();

	// 8. Creating the Vulkan Graphics Pipeline
	/// 8.1. Main function for creating the Pipeline
	void createGraphicsPipeline();
	/// 8.2. Function for creating the Shader module that wraps up the SPIR-V bitecode for the Graphics Pipeline
	VkShaderModule createShaderModule(const std::vector<char>& code);

	// 9. Creating the Render Pass
	/// 9.1. Main function for creating the Render Pass, that must be called right before the createGraphicsPipeline()
	void createRenderPass();
	
	// 10. Drawing
	/// 10.1. Function to create the Frame Buffers to each VkImageView of the SwapChain
	void createFramebuffers();
	/// 10.2. Creating the Command Pool that contains the commands to manage the memory which used to store the Buffers
	void createCommandPool();
	/// 10.3. Function to create the Vertex Buffer that contains the vertices
	void createVertexBuffer();
	/// 10.4. Function to create the VkBuffer
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	/// 10.5. Creating the Command Buffer that allocates the memory and records commands for each Image of the SwapChain
	void createCommandBuffer();
	/// 10.6. Function to writes the commands to execute into a command buffer
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	/// 10.7. Function to draw a frame of the scene with next steps
	//// 10.7.1. Getting the Image from the Swap Chain
	//// 10.7.2. Launch the compatible Command Buffer
	//// 10.7.3. Returning the image to the Swap Chain for output to screen
	void drawFrame();
	/// 10.7. Creating the Synchronization object like Semaphores and Fences
	void createSyncObjects();
	
	// 11. Find the memory type of the GPU
	/// 11.1. Function to determine the type of GPU memory
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	// 12. Function to copy VkBuffer
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, uint32_t indexBuffer, VkQueue queue);

	// 13. Function to create the IndexBuffer
	void createIndexBuffer();

	// 14. Descriptors
	/// 14.1. Function to create Descriptors
	void createDescriptorSetLayout();
	/// 14.2. Create the uniform buffers
	void createUniformBuffers();
	/// 14.3. Function to update the Uniform buffer
	void updateUniformBuffer(uint32_t currentImage);
	/// 14.4. Function to create a descriptor pool
	void createDescriptorPool();
	/// 14.5. Function to create the Descriptor Sets
	void createDescriptorSets();

	// 15. Texture mapping
	/// 15.1. Function to create Texture Image
	void createTextureImage();
	/// 15.2. Function to create image
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, 
						VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	/// 15.3. Function to start recording of the command buffer
	VkCommandBuffer beginSingleTimeCommands();
	/// 15.4. Function to end recording of the command buffer
	void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue queue);
	/// 15.5. Function to handle layout transitions
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	/// 15.6. Function to copy Buffer to Image
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	/// 15.7. Function to create the Texture Image View
	void createTextureImageView();
	/// 15.8 Abstract function to create imageViews
	VkImageView createImageView(VkImage image, VkFormat format);
	/// 15.9. Function to create the Texture Sampler
	void createTextureSampler();

	VkDevice get_device() { return device; };

	void resizeWindow(int width, int height);


	void cleanup();
	~Screen();
private:

	SDL_Window* window;
	VkInstance instanceVK;

	std::vector<VkExtensionProperties> extensions;
	//std::vector<const char*> extensionsSDL;

	std::vector<VkLayerProperties> availableLayers;
	VkDebugUtilsMessengerEXT debugMessenger;
	
	VkSurfaceKHR surface;
	VkQueue presentQueue;

	VkPhysicalDevice physicalDevice;
	std::vector<VkPhysicalDevice> devices;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	std::multimap<int, VkPhysicalDevice> ratingDevices;


	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue transferQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	
	std::vector<VkImageView> swapChainImageViews;

	//std::vector<VkDynamicState> dynamicStates;
	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	VkCommandPool commandPoolTransfer;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

	std::vector<VkCommandBuffer> commandBuffer;
	std::vector<VkCommandBuffer> commandBufferTransfer;


	std::vector<VkSemaphore> imageAvailableSemaphore;
	std::vector<VkSemaphore> renderFinishedSemaphore;
	std::vector<VkFence> inFlightFence;
	bool framebufferResized;
	uint32_t currentFrame;


};

#endif // SCREEN_H