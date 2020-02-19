#pragma once
class ResourceManager;
class SocketManager;
class PacketManager;
class SelectorFrame;

class LobbySystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;
	SocketManager* m_socketManager = nullptr;
	PacketManager* m_packetManager = nullptr;

	SelectorFrame* m_selector = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	LobbySystem();
	~LobbySystem();
};