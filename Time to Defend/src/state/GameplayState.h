#pragma once

#include "BaseGameState.h"
#include "gfx/Map.h"
#include "gfx/Texture.h"


enum class GameLevel
{
	_1,
};


class GameplayState : public GameState
{
private:
	GameLevel m_GameLevel;

	Map m_CurrentMap;
	Texture m_TestTexture;

public:
	void onEnter() override;
	void onExit() override;

	void handleEvent(SDL_Event& event) override;
	void update() override;
	void draw() override;
};
