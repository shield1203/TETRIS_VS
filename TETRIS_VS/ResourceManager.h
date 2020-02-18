#pragma once

struct TextInfo
{
	string strText;
	int xPos = 0;
	int yPos = 0;
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

struct BlockInfo
{
	unsigned int blockShape = 0;
	unsigned int blockType = 0;
	int xPos = 0;
	int yPos = 0;

	vector<TextInfo> blocks;
};

class ResourceManager
{
private:
	static ResourceManager* Inst;
	ResourceManager();
public:
	GAME_STEP m_curGameStep;

	Background m_background;

	vector<Sprite*> m_sprite;

	// SinglePlay

	// Game
	BlockInfo m_block;
	BlockInfo m_nextBlock;
	list<TextInfo*> m_map;
public:
	static ResourceManager* getInstance();

	void LoadGameData(GAME_STEP);
	void LoadBackgroundData(GAME_STEP);
	void LoadSpriteData(GAME_STEP);

	void InitMap();

	void ReleaseData(GAME_STEP);

	~ResourceManager();
};

