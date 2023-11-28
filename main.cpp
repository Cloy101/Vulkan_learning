// main.cpp

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "Setup.h"

int SDL_main(int argc, char* argv[])
{
	try
	{
		Setup setup;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		
	}
	return 0;
}

