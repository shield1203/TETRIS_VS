#pragma once
class InputSystem
{
private:
	int m_inputKey = 1;
	bool m_pressedKey = false;
public:
	void CheckKeyboardPressed();

	bool IsLeftArrowPressed();
	bool IsRightArrowPressed();
	bool IsUpArrowPressed();
	bool IsDownArrowPressed();
	bool IsEnterPressed();

	InputSystem();
	~InputSystem();
};

