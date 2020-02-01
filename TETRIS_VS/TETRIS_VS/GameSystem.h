#pragma once

class SystemFrame;
class ResourceManager;
class SoundSystem;

class GameSystem
{
private:
	GAME_STEP m_curGameStep;

	SystemFrame* m_systemFrame = nullptr;
	ResourceManager* m_resourceManager = nullptr;
	SoundSystem* m_soundSystem = nullptr;
public:
	void Process();
	void Init();
	void Update();
	void Render();

	GameSystem();
	~GameSystem();
};

