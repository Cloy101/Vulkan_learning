// Setup.cpp

#include "Setup.h"

Setup::Setup()
{
	Screen screen;

	gameLoop(screen);
	
}

void Setup::gameLoop(Screen& screen)
{
	screen.drawFrame();

	//int temp;
	//std::cin >> temp;
	
	while (true)
	{
		screen.drawFrame();

		input();
	}
	
	vkDeviceWaitIdle(screen.get_device());
	
}

void Setup::input()
{
	while (SDL_PollEvent(&eventSDL))
	{
		switch (eventSDL.type)
		{
		case SDL_QUIT:
			//SDL_Quit();
			exit(0);
			break;

		case SDL_KEYDOWN:
			//value.keys[event.key.keysym.sym] = true;
			//if (value.keys[SDLK_ESCAPE])
			//{
			//	//SDL_Quit();
			//	exit(0);
			//}
			break;

		case SDL_KEYUP:
			//value.keys[event.key.keysym.sym] = false;
			//break;

		default:
			break;
		}


	}
}
