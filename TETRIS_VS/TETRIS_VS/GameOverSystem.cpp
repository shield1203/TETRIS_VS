#include "stdafx.h"
#include "SystemFrame.h"
#include "GameOverSystem.h"

#include "ResourceManager.h"
#include "Button.h"

GameOverSystem::GameOverSystem()
{
}

GameOverSystem::~GameOverSystem()
{
}

void GameOverSystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_GAMEOVER);

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_button = new Button();
}

void GameOverSystem::Update()
{
	m_button->Update();
}

void GameOverSystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	if (m_button->GetState())
	{
		for (auto i : m_resourceManager->m_GameOverSprite)
		{
			for (auto j : i->textInfo)
			{
				WriteBuffer(j->xPos, j->yPos, j->strText, j->textColor);
			}
		}
	}
}

void GameOverSystem::Release()
{
	m_resourceManager->ReleaseData(STEP_GAMEOVER);
}