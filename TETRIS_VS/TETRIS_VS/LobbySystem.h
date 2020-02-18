#pragma once
class SystemFrame;
class ResourceManager;

class SelectorFrame;

class LobbySystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;

	SelectorFrame* m_selector = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	LobbySystem();
	~LobbySystem();
};