#include "stdafx.h"
#include "SystemFrame.h"
#include "MenuSystem.h"

#include "ResourceManager.h"
#include "SoundSystem.h"

#include "Title.h"
#include "SelectorFrame.h"
#include "MenuSelector.h"
#include "MenuList.h"

MenuSystem::MenuSystem()
{
}

MenuSystem::~MenuSystem()
{
}

void MenuSystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_MENU);

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;
	
	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_title = new Title();
	m_selector = new MenuSelector();
	m_menuList = new MenuList();

	m_selector->Init();

	SoundSystem::getInstance()->StopBGM();
	SoundSystem::getInstance()->StartBGM(MENU_BGM);
}

void MenuSystem::Update()
{
	SoundSystem::getInstance()->pSystem->update();

	m_title->Update();
	m_selector->Update();
	m_menuList->Update();
}

void MenuSystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	for (auto i : m_resourceManager->m_sprite)
	{
		for (auto j : i->textInfo)
		{
			WriteBuffer(j->xPos, j->yPos, j->strText, j->textColor);
		}
	}
}

void MenuSystem::Release()
{
	m_resourceManager->ReleaseData(STEP_MENU);

	SafeDelete(m_title);
	SafeDelete(m_selector);
	SafeDelete(m_menuList);
}