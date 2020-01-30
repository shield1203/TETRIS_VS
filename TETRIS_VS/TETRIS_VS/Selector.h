#pragma once
class ResourceManager;
class InputSystem;

enum SelectorEnum : unsigned int { SINGLE_PLAY = 11, VERSUS_PLAY = 14, EXIT = 17, SELECTOR_Y = 3 };

class Selector
{
private:
	ResourceManager* m_resourceManager = nullptr;
	InputSystem* m_inputSystem = nullptr;
public:
	void Update();

	void MoveUp();
	void MoveDown();
	void SetSelectedMode();

	Selector();
	~Selector();
};

