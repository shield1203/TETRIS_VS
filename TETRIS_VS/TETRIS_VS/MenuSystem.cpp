#include "stdafx.h"
#include "SystemFrame.h"
#include "MenuSystem.h"

#include "ResourceManager.h"
#include "Title.h"
#include "Selector.h"
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
	m_selector = new Selector();
	m_menuList = new MenuList();
}

void MenuSystem::Update()
{
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
	for (auto i : m_resourceManager->m_menuSprite)
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
}