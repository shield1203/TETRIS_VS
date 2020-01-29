#pragma once
class ResourceManager;

enum SelectorEnum : unsigned int { SINGLE_PLAY = 11, VERSUS_PLAY = 14, EXIT = 17, SELECTOR_Y = 3 };

class Selector
{
private:
	ResourceManager* m_resourceManager = nullptr;
public:
	void Update();
	void PressKeyCheck();

	Selector();
	~Selector();
};

