#pragma once

class SystemFrame;

class GameSystem
{
private:
	GAME_STEP m_CurGameStep, m_PrevGameStep;

	SystemFrame* m_systemFrame = nullptr;
public:
	void Process();
	void Init();
	void Update();
	void Render();

	GameSystem();
	~GameSystem();
};

