#pragma once

#include "pch.h"

#include "Application.h"
#include "gfx/Text.h"
#include "utils/Timer.h"


class Editor : public Application
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

	// Reads settings from file (or sets to default)
	void readSettings() override;

private:
	void handleEvents() override;
	void update() override;
	void draw() override;

public:
	Editor();
	~Editor();

	// Saves the current settings
	void saveSettings() override;
};
