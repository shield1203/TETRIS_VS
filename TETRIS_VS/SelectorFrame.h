#pragma once
class ResourceManager;
class InputSystem;

class SelectorFrame
{
public:
	ResourceManager* m_resourceManager = nullptr;
	InputSystem* m_inputSystem = nullptr;
public:
	virtual void Init() {};
	virtual void Update() {};

	virtual void MoveUp() {};
	virtual void MoveDown() {};
	virtual void Select() {};

	SelectorFrame();
	~SelectorFrame();
};

