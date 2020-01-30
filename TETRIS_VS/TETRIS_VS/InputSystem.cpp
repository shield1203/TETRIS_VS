#include "stdafx.h"
#include "InputSystem.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::CheckKeyboardPressed()
{
	if (kbhit())
	{
		m_inputKey = getch();

		if (m_inputKey == 224)
		{
			m_inputKey = getch();
		}

		m_pressedKey = true;
	}
}

bool InputSystem::IsLeftArrowPressed()
{
	if (m_pressedKey && m_inputKey == LEFT)
	{
		m_pressedKey = false;

		return true;
	}

	return false;
}

bool InputSystem::IsRightArrowPressed()
{
	if (m_pressedKey && m_inputKey == RIGHT)
	{
		m_pressedKey = false;

		return true;
	}

	return false;
}

bool InputSystem::IsUpArrowPressed()
{
	if (m_pressedKey && m_inputKey == UP)
	{
		m_pressedKey = false;

		return true;
	}

	return false;
}

bool InputSystem::IsDownArrowPressed()
{
	if (m_pressedKey && m_inputKey == DOWN)
	{
		m_pressedKey = false;

		return true;
	}

	return false;
}

bool InputSystem::IsEnterPressed()
{
	if (m_pressedKey && m_inputKey == ENTER)
	{
		m_pressedKey = false;

		return true;
	}

	return false;
}