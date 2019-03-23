#include "pch.h"

#include "Editor.h"

#include "utils/Log.h"
#include "utils/Random.h"


Editor::Editor()
	: Application(960, 540, "Time to Edit!")
{
	// Initialises other parts of the editor
	Log::init("TTELOG");
	Random::init();

	if (!(
		initSDL() &&
		initIMG() &&
		initTTF() &&
		createWindow() &&
		createRenderer()
		))
	{
		return;
	}

	// Sets the clear colour
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
}


void Editor::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_Running = false;
			break;
		}
	}
}

void Editor::update()
{
}

void Editor::draw()
{
	// Clears the screen
	SDL_RenderClear(m_Renderer);

	// Displays the screen
	SDL_RenderPresent(m_Renderer);
}
