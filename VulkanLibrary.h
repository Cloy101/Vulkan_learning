// VulkanLibrary.h
#ifndef VULKANLIBRARY_H
#define VULKANLIBRARY_H

#include "SDLLibrary.h"
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>



class VulkanLibrary
{
public:
	VulkanLibrary();

	~VulkanLibrary() 
	{ 
		std::cout << "~Destructor of Screen" << std::endl;
		SDL_Vulkan_UnloadLibrary(); 
	};


};

#endif // VULKANLIBRARY_H