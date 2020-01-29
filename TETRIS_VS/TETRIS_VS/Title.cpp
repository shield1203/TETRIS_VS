#include "stdafx.h"
#include "Title.h"

#include "ResourceManager.h"

Title::Title()
{
	m_resourceManager = ResourceManager::getInstance();
}

Title::~Title()
{
}

void Title::Update()
{
	BlinkTitle();
}

void Title::BlinkTitle()
{
	if (GetTickCount64() - m_time > 120)
	{
		m_time = GetTickCount64();

		if (bChange)
		{
			bChange = false;

			for (auto i : m_resourceManager->m_menuSprite[TITLE_T1]->textInfo)
			{
				i->textColor = DARK_BLUE;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_E]->textInfo)
			{
				i->textColor = DARK_RED;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_T2]->textInfo)
			{
				i->textColor = DARK_YELLOW;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_R]->textInfo)
			{
				i->textColor = DARK_SKY;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_I]->textInfo)
			{
				i->textColor = DARK_GREEN;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_S]->textInfo)
			{
				i->textColor = DARK_PURPLE;
			}
		}
		else
		{
			bChange = true;

			for (auto i : m_resourceManager->m_menuSprite[TITLE_T1]->textInfo)
			{
				i->textColor = BLUE;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_E]->textInfo)
			{
				i->textColor = RED;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_T2]->textInfo)
			{
				i->textColor = YELLOW;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_R]->textInfo)
			{
				i->textColor = SKY;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_I]->textInfo)
			{
				i->textColor = GREEN;
			}

			for (auto i : m_resourceManager->m_menuSprite[TITLE_S]->textInfo)
			{
				i->textColor = PURPLE;
			}
		}
	}
}