// SDLLibrary.h
#include "SDLLibrary.h"

SDLLibrary::SDLLibrary()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "ERROR::SDL_Library is undefined" << std::endl;
	}
}
