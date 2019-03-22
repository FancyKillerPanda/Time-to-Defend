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

void Application::pushState(std::unique_ptr<GameState> state)
{
	m_GameStates.emplace_back(std::move(state));
	// Sets up the state
	m_GameStates.back()->onEnter();
}

void Application::popState()
{
	// Makes sure there is a state in the stack
	if (m_GameStates.empty())
	{
		LOG_WARNING("Tried to pop GameState off empty stack.");
	}

	else
	{
		// Cleans up the state before popping
		m_GameStates.back()->onExit();
		m_GameStates.pop_back();
	}
}
