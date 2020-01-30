#pragma once
class SystemFrame;
class ResourceManager;
class Map;
class Block;

class SinglePlaySystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;

	Map* m_map = nullptr;
	Block* m_block = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	SinglePlaySystem();
	~SinglePlaySystem();
};

