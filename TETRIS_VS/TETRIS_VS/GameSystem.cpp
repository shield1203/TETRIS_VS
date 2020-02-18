#include "stdafx.h"
#include "SystemFrame.h"
#include "GameSystem.h"

#include "MenuSystem.h"
#include "SinglePlaySystem.h"
#include "GameOverSystem.h"
#include "LobbySystem.h"

#include "ResourceManager.h"
#include "SoundSystem.h"


GameSystem::GameSystem()
{
	m_curGameStep = STEP_MENU;

	m_systemFrame = new MenuSystem();
	m_systemFrame->Init();

	m_resourceManager = ResourceManager::getInstance();
}

GameSystem::~GameSystem()
{
	SafeDelete(m_systemFrame);
	SafeDelete(m_resourceManager);
	SoundSystem::getInstance()->~SoundSystem();
}

void GameSystem::Process()
{
	while (m_resourceManager->m_curGameStep != STEP_EXIT)
	{
		Init();
		Update();
		Render();
	}
}

void GameSystem::Init()
{
	if (m_curGameStep != m_resourceManager->m_curGameStep)
	{
		m_systemFrame->Release();
		SafeDelete(m_systemFrame);

		m_curGameStep = m_resourceManager->m_curGameStep;

		switch (m_curGameStep)
		{
		case STEP_MENU:
			m_systemFrame = new MenuSystem();
			break;
		case STEP_SINGLE_PLAY:
			m_systemFrame = new SinglePlaySystem();
			break;
		case STEP_GAMEOVER:
			m_systemFrame = new GameOverSystem();
			break;
		case STEP_LOBBY:
			m_systemFrame = new LobbySystem();
			break;
		}

		m_systemFrame->Init();
	}
}

void GameSystem::Update()
{
	m_systemFrame->Update();
}

void GameSystem::Render()
{
	COORD size;
	m_systemFrame->GetConsoleSize(size);

	ClearBuffer(size);

	m_systemFrame->Render();

	FlippingBuffer();
}