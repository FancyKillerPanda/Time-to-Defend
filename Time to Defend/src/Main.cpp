#include <iostream>

#include <SDL/SDL.h>


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		std::cout << "Could not initialise SDL." << std::endl;
		return 1;
	}

	std::cin.get();

	return 0;
}
