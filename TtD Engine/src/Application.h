#pragma once

#include "pch.h"


class GameState;
struct GameSettings;


class Application
{
protected:
	bool m_Running = true;

	// Window properties
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	const char* m_WindowTitle;

	// SDL window and renderer
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	// Stack of the current game states
	std::vector<std::unique_ptr<GameState>> m_GameStates;

public:
	// Settings
	GameSettings* settings;

protected:
	virtual void handleEvents() = 0;
	virtual void update() {}
	virtual void draw() = 0;

	// Initialises SDL
	bool initSDL();
	// Initialises IMG
	bool initIMG();
	// Initialises TTF
	bool initTTF();

	// Creates the SDL window
	bool createWindow();
	// Creates the SDL renderer
	bool createRenderer();

	// Reads settings from file (or sets to default)
	virtual void readSettings() {}

public:
	Application(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle);
	~Application();

	// Runs the main game-loop
	void run();

	// Pushes a state onto the stack
	void pushState(std::unique_ptr<GameState> state);
	// Pops a state from the stack
	void popState();

	// Saves the current settings
	virtual void saveSettings() {}

	inline SDL_Renderer* const getRenderer() { return m_Renderer; }
	inline unsigned int getWindowWidth() { return m_WindowWidth; }
	inline unsigned int getWindowHeight() { return m_WindowHeight; }

	void setRunning(bool value) { m_Running = value; }
};
