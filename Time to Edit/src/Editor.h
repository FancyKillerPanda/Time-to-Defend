#pragma once

#include "pch.h"

#include "Application.h"


class Editor : public Application
{
private:
	void handleEvents() override;
	void update() override;
	void draw() override;

public:
	Editor();
};
