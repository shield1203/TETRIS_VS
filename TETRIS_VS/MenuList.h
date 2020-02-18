#pragma once
class ResourceManager;

enum ModeEnum : unsigned int {  };

class MenuList
{
private:
	ResourceManager* m_resourceManager = nullptr;
public:
	void Update();
	void SelectorLocationCheck();

	MenuList();
	~MenuList();
};

