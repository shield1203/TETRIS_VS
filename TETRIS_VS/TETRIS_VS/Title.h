#pragma once
class ResourceManager;

enum SETTING : unsigned int { CHANGE_COLOR_TIME = 120 };

class Title
{
private:
	ResourceManager* m_resourceManager = nullptr;

	unsigned int m_time = 0;
	bool bChange = false;
public:
	void Update();
	void BlinkTitle();

	Title();
	~Title();
};