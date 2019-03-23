#include "pch.h"

#include "EditorState.h"


void EditorState::onEnter()
{
	m_MapEditing.load(s_Game, nullptr);
}

void EditorState::handleEvent(SDL_Event& event)
{
}

void EditorState::update()
{
}

void EditorState::draw()
{
	m_MapEditing.draw();
}
