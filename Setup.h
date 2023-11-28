// Setup.h

#ifndef SETUP_H
#define SETUP_H

//#include <vector>
#include "Screen.h"

class Setup
{
public:
	Setup();

	void gameLoop(Screen &screen);
	
	void input();

	~Setup() { std::cout << "~Destructor of Setup" << std::endl; }

private:
	SDL_Event eventSDL;
};

#endif // SETUP_H
