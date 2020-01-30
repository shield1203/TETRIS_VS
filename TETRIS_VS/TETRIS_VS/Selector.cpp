#include "stdafx.h"
#include "Selector.h"

#include "ResourceManager.h"
#include "InputSystem.h"

Selector::Selector()
{
	m_resourceManager = ResourceManager::getInstance();
	m_inputSystem = new InputSystem();
}

Selector::~Selector()
{
	SafeDelete(m_inputSystem);
}

void Selector::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (m_inputSystem->IsUpArrowPressed())
	{
		MoveUp();
	}

	if (m_inputSystem->IsDownArrowPressed())
	{
		MoveDown();
	}

	if (m_inputSystem->IsEnterPressed())
	{
		SetSelectedMode();
	}
}

void Selector::MoveUp()
{
	auto selector = m_resourceManager->m_menuSprite[SELECTOR]->textInfo.front();

	if (selector->yPos > SINGLE_PLAY)
	{
		for (auto i : m_resourceManager->m_menuSprite[SELECTOR]->textInfo)
		{
			i->yPos -= SELECTOR_Y;
		}
	}
}

void Selector::MoveDown()
{
	auto selector = m_resourceManager->m_menuSprite[SELECTOR]->textInfo.front();

	if (selector->yPos < EXIT)
	{
		for (auto i : m_resourceManager->m_menuSprite[SELECTOR]->textInfo)
		{
			i->yPos += SELECTOR_Y;
		}
	}
}

void Selector::SetSelectedMode()
{
	auto selector = m_resourceManager->m_menuSprite[SELECTOR]->textInfo.front();

	switch (selector->yPos)
	{
	case SINGLE_PLAY:
		m_resourceManager->m_curGameStep = STEP_SINGLE_PLAY;
		break;
	case VERSUS_PLAY:

		break;
	case EXIT:
		m_resourceManager->m_curGameStep = STEP_EXIT;
		break;
	}
}