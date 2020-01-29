#include "stdafx.h"
#include "SystemFrame.h"
#include "SinglePlaySystem.h"

#include "ResourceManager.h"

SinglePlaySystem::SinglePlaySystem()
{
}

SinglePlaySystem::~SinglePlaySystem()
{
}

void SinglePlaySystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_SINGLE_PLAY);

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);
}

void SinglePlaySystem::Update()
{
	
}

void SinglePlaySystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	/*for (auto i : m_resourceManager->m_menuSprite)
	{
		for (auto j : i->textInfo)
		{
			WriteBuffer(j->xPos, j->yPos, j->strText, j->textColor);
		}
	}*/
}

void SinglePlaySystem::Release()
{
	m_resourceManager->ReleaseData(STEP_SINGLE_PLAY);
}