// main.cpp

#include "Test.cpp"
#include "Setup.h"

int SDL_main(int argc, char* argv[])
{
	//Test test;
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