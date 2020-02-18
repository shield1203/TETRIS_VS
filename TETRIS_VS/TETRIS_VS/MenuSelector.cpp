#include "stdafx.h"
#include "SelectorFrame.h"
#include "MenuSelector.h"

#include "ResourceManager.h"
#include "InputSystem.h"
#include "SoundSystem.h"

MenuSelector::MenuSelector()
{
}

MenuSelector::~MenuSelector()
{
}

void MenuSelector::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_inputSystem = new InputSystem();
}

void MenuSelector::Update()
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
		Select();
	}
}

void MenuSelector::MoveUp()
{
	auto selector = m_resourceManager->m_sprite[MENU_SELECTOR]->textInfo.front();

	if (selector->yPos > SINGLE_PLAY)
	{
		for (auto i : m_resourceManager->m_sprite[MENU_SELECTOR]->textInfo)
		{
			i->yPos -= SELECTOR_Y;
		}

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
}

void MenuSelector::MoveDown()
{
	auto selector = m_resourceManager->m_sprite[MENU_SELECTOR]->textInfo.front();

	if (selector->yPos < EXIT)
	{
		for (auto i : m_resourceManager->m_sprite[MENU_SELECTOR]->textInfo)
		{
			i->yPos += SELECTOR_Y;
		}

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
}

void MenuSelector::Select()
{
	auto selector = m_resourceManager->m_sprite[MENU_SELECTOR]->textInfo.front();

	switch (selector->yPos)
	{
	case SINGLE_PLAY:
		m_resourceManager->m_curGameStep = STEP_SINGLE_PLAY;
		break;
	case VERSUS_PLAY:
		m_resourceManager->m_curGameStep = STEP_LOBBY;
		break;
	case EXIT:
		m_resourceManager->m_curGameStep = STEP_EXIT;
		break;
	}

	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
}