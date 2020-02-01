#pragma once
class ResourceManager;
class InputSystem;

enum ButtonEnum { BlINK_TIME = 400 };

class Button
{
private:
	ResourceManager* m_resourceManager = nullptr;
	InputSystem* m_inputSystem = nullptr;

	bool m_state = true;
	unsigned __int64 m_time = 0;

public:
	void Update();

	void CheckBlink();
	bool GetState();

	Button();
	~Button();
};

