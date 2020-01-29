#pragma once
class SystmeFrame;
class ResourceManager;
class Title;
class Selector;
class MenuList;

class MenuSystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;

	Title* m_title = nullptr;
	Selector* m_selector = nullptr;
	MenuList* m_menuList = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	MenuSystem();
	~MenuSystem();
};