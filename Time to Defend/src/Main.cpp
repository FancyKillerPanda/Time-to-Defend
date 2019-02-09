#include <SDL/SDL.h>

#include "utils/Log.h"


int main(int argc, char *argv[])
{
	Log::init();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		LOG_FATAL("Could not initialise SDL.");
		return 1;
	}

	LOG_INFO("SDL initialised.");

	system("PAUSE");

	return 0;
}
