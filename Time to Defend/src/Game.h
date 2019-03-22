#pragma once

#include "pch.h"

#include "BaseApplication.h"

#include "state/BaseGameState.h"
#include "utils/Timer.h"
#include "gfx/Text.h"


class Game : public Application
{
private:
#ifdef _DEBUG
	// Frame rate timer
	Timer m_FrameTimer;
	// Counter of number of frames since timer reset
	unsigned int m_FrameCount;

	// Text containing debug information
	Text m_InfoText;
#endif // _DEBUG

private:
	void handleEvents() override;
	void update() override;
	void draw() override;

public:
	Game();
};
