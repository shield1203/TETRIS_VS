#pragma once

class SystemFrame;
class ResourceManager;

class GameSystem
{
private:
	GAME_STEP m_curGameStep, m_prevGameStep;

	SystemFrame* m_systemFrame = nullptr;
	ResourceManager* m_resourceManager = nullptr;
public:
	void Process();
	void Init();
	void Update();
	void Render();

	GameSystem();
	~GameSystem();
};

