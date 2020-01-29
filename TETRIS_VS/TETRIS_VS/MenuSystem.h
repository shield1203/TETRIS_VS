#pragma once
class SystmeFrame;
class ResourceManager;
class Title;

class MenuSystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;

	Title* m_title = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	MenuSystem();
	~MenuSystem();
};