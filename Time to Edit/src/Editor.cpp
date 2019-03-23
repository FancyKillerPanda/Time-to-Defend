#include "pch.h"

#include "Editor.h"

#include "utils/Log.h"
#include "utils/Random.h"
#include "Settings.h"


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

#ifdef _DEBUG
	// Loads the information text
	m_InfoText.load(DEFAULT_FONT_PATH, "Time to Edit V0.1.0 | 0 FPS", 10, SDL_Color { 180, 180, 180, 255 }, m_Renderer);
#endif // _DEBUG
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
#ifdef _DEBUG
	m_FrameCount += 1;

	if (m_FrameTimer.getElapsed() >= 1000.0)
	{
		// Creates the text
		std::string text = "Time to Edit V0.1.0 | ";
		text += std::to_string(m_FrameCount);
		text += " FPS";

		// Sets the text
		m_InfoText.setText(text.c_str());

		// Resets the timer
		m_FrameTimer.reset();
		m_FrameCount = 0;
	}
#endif // _DEBUG
}

void Editor::draw()
{
	// Clears the screen
	SDL_RenderClear(m_Renderer);

#ifdef _DEBUG
	// Draws the information text
	m_InfoText.draw(m_WindowWidth - m_InfoText.getRect().w / 2 - 10, m_WindowHeight - m_InfoText.getRect().h / 2 - 10);
#endif // _DEBUG

	// Displays the screen
	SDL_RenderPresent(m_Renderer);
}
