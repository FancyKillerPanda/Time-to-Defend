#pragma once

#include "BaseGameState.h"


enum class GameLevel
{
	_1,
};


class GameplayState : public GameState
{
private:
	GameLevel m_GameLevel;

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event &event);
	void update();
	void draw();
};
