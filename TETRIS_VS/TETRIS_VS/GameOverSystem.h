#pragma once
class SystemFrame;
class ResourceManager;
class Button;

class GameOverSystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;

	Button* m_button = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	GameOverSystem();
	~GameOverSystem();
};