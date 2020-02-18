#pragma once
class ResourceManager;

enum MapEnum : unsigned int { MAP_LINE_CLEAR_SPEED = 120, BLINK_LINE_COUNT = 8 };

class Map
{
private:
	ResourceManager* m_resourceManager = nullptr;

	bool bClearLines = false;
	unsigned int m_LineclearSpeed = 0;
	unsigned __int64 m_time = 0;
	int nblinkCount = 0;

	vector<int> m_blockCount;
public:
	void Update();

	void CheckLines();
	void ClearLines();

	bool IsClearLines();

	Map();
	~Map();
};

