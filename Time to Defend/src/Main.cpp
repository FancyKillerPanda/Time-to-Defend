#include "pch.h"

#include "Game.h"


int main(int argc, char* argv[])
{
	Game* timeToDefend = new Game();
	timeToDefend->run();
	delete timeToDefend;

#ifdef _DEBUG
	system("PAUSE");
#endif

	return 0;
}
