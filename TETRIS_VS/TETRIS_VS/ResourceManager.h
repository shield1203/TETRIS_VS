#pragma once

struct TextInfo
{
	string strText;
	short xPos = 0;
	short yPos = 0;
	COLOR textColor = WHITE;
};

struct Background
{
	COORD consoleSize;
	string sizeCommend;
	list<TextInfo*> textInfo;
};

struct Sprite
{
	list<TextInfo*> textInfo;
};

class ResourceManager
{
private:
	static ResourceManager* Inst;
	ResourceManager();
public:
	// Menu
	Background m_menuBackground;
	vector<Sprite*> m_menuSprite;

	// SinglePlay
public:
	static ResourceManager* getInstance();

	void LoadGameData();
	
	void LoadMenuData();
	void LoadSinglePlayData();
	void LoadSingleResultData();

	void ReleaseData();

	~ResourceManager();
};

