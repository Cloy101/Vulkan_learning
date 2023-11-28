// SDLLibrary.h
#ifndef SDLLIBRARY_H
#define SDLLIBRARY_H

#include <SDL.h>
#include <iostream>
#include <exception>

class SDLLibrary
{
public:
	SDLLibrary();
	~SDLLibrary() 
	{ 
		std::cout << "~Destructor of SDLLibrary" << std::endl;
		SDL_Quit(); 
	};

};

#endif // SDLLIBRARY_H
