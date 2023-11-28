#include "VulkanLibrary.h"

VulkanLibrary::VulkanLibrary()
{
	if (SDL_Vulkan_LoadLibrary(nullptr) == -1)
	{
		std::cout << "ERROR::VulkanLibrary::SDL_Vulkan_LoadLibrary is undefined" << std::endl;
	}
}
