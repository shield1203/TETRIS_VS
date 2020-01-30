#pragma once
class ResourceManager;

class Map
{
private:
	ResourceManager* m_resourceManager = nullptr;
public:
	void Update();

	Map();
	~Map();
};

