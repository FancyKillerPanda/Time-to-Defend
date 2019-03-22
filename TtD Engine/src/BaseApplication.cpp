#include "pch.h"

#include "BaseApplication.h"

#include "state/BaseGameState.h"


Application::Application(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle)
	: m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_WindowTitle(windowTitle)
{
}


void Application::run()
{
	// Main game-loop
	while (m_Running)
	{
		handleEvents();
		update();
		draw();
	}
}
