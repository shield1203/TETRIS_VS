#include "stdafx.h"
#include "Selector.h"

#include "ResourceManager.h"

Selector::Selector()
{
	m_resourceManager = ResourceManager::getInstance();
}

Selector::~Selector()
{
}

void Selector::Update()
{
	PressKeyCheck();
}

void Selector::PressKeyCheck()
{
	if (_kbhit()) {
		int nKey = _getch();

		auto selector = m_resourceManager->m_menuSprite[SELECTOR]->textInfo.front();

		switch (nKey)
		{
		case UP:
			if (selector->yPos > SINGLE_PLAY)
			{
				for (auto i : m_resourceManager->m_menuSprite[SELECTOR]->textInfo)
				{
					i->yPos -= SELECTOR_Y;
				}
			}
			break;
		case DOWN:
			if (selector->yPos < EXIT)
			{
				for (auto i : m_resourceManager->m_menuSprite[SELECTOR]->textInfo)
				{
					i->yPos += SELECTOR_Y;
				}
			}
			break;
		case ENTER:
			if (selector->yPos == SINGLE_PLAY)
			{
				m_resourceManager->m_curGameStep = STEP_SINGLE_PLAY;
			}
			else if (selector->yPos == VERSUS_PLAY)
			{

			}
			else if (selector->yPos == EXIT)
			{
				m_resourceManager->m_curGameStep = STEP_EXIT;
			}
			break;
		}
	}
}