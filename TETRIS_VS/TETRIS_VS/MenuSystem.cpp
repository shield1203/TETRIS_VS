#include "stdafx.h"
#include "SystemFrame.h"
#include "MenuSystem.h"

#include "ResourceManager.h"
#include "Title.h"

MenuSystem::MenuSystem()
{
}

MenuSystem::~MenuSystem()
{
}

void MenuSystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();

	m_consoleSize = m_resourceManager->m_menuBackground.consoleSize;
	m_sizeCommend = m_resourceManager->m_menuBackground.sizeCommend;
	
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_title = new Title();
}

void MenuSystem::Update()
{
	m_title->Update();

}

void MenuSystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_menuBackground.textInfo)
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