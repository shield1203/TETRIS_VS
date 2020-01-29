#include "stdafx.h"
#include "MenuList.h"

#include "ResourceManager.h"

MenuList::MenuList()
{
	m_resourceManager = ResourceManager::getInstance();
}

MenuList::~MenuList()
{
}

void MenuList::Update()
{
	SelectorLocationCheck();
}

void MenuList::SelectorLocationCheck()
{
	auto selectorLocation = m_resourceManager->m_menuSprite[SELECTOR]->textInfo.front();

	for (int i = MODE_SINGLE_PLAY; i <= MODE_EXIT; i++)
	{
		auto listLocation = m_resourceManager->m_menuSprite[i]->textInfo.front();

		if (selectorLocation->yPos == listLocation->yPos)
		{
			for (auto j : m_resourceManager->m_menuSprite[i]->textInfo)
			{
				j->textColor = GREEN;
			}
		}
		else
		{
			for (auto j : m_resourceManager->m_menuSprite[i]->textInfo)
			{
				j->textColor = PURPLE;
			}
		}
	}
}