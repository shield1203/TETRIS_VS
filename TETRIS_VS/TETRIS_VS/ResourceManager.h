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
	GAME_STEP m_curGameStep;

	Background m_background;

	// Menu
	vector<Sprite*> m_menuSprite;

	// SinglePlay
	vector<Sprite*> m_block;
	vector<Sprite*> m_map;

public:
	static ResourceManager* getInstance();

	void LoadGameData(GAME_STEP);
	
	void LoadMenuData();
	void LoadSinglePlayData();
	void LoadSingleResultData();

	void ReleaseData(GAME_STEP);

	~ResourceManager();
};

