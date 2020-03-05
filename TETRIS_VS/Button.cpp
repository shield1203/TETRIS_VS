#include "stdafx.h"
#include "Button.h"

#include "ResourceManager.h"
#include "InputSystem.h"

Button::Button()
{
	m_resourceManager = ResourceManager::getInstance();
	m_inputSystem = new InputSystem();
}

Button::~Button()
{
	SafeDelete(m_inputSystem);
}

void Button::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (m_inputSystem->IsEnterPressed())
	{
		m_resourceManager->m_curGameStep = STEP_MENU;
	}

	CheckBlink();
}

void Button::CheckBlink()
{
	if (GetTickCount64() - m_time > BlINK_TIME)
	{
		m_time = GetTickCount64();
		m_state = m_state ? false : true;
	}
}

bool Button::GetState()
{
	return m_state;
}