#pragma once
class ResourceManager;
class SocketManager;
class PacketManager;

class GameRoomSystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;
	SocketManager* m_socketManager = nullptr;
	PacketManager* m_packetManager = nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	GameRoomSystem();
	~GameRoomSystem();
};

