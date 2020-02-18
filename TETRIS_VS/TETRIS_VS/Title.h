#pragma once
class ResourceManager;

enum TitleEnum : unsigned int { CHANGE_COLOR_TIME = 120 };

class Title
{
private:
	ResourceManager* m_resourceManager = nullptr;

	unsigned __int64 m_time = 0;
	bool bChange = false;
public:
	void Update();
	void BlinkTitle();

	Title();
	~Title();
};