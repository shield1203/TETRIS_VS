#include "stdafx.h"
#include "GameSystem.h"

#include "SystemFrame.h"
#include "MenuSystem.h"


GameSystem::GameSystem()
{
	m_CurGameStep = m_PrevGameStep = STEP_MENU;

	m_systemFrame = new MenuSystem();
}

GameSystem::~GameSystem()
{

}

void GameSystem::Process()
{
	while (true)
	{
		Init();
		Update();
		Render();
	}
}

void GameSystem::Init()
{

}

void GameSystem::Update()
{

}

void GameSystem::Render()
{

}