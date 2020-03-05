#pragma once
class ResourceManager;
class SocketManager;
class PacketManager;

class ReadyButton;

enum ROOM_NUM { ROOM_NUM_YPOS = 2, ROOM_NUM_XPOS = 10 };

class GameRoomSystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;
	SocketManager* m_socketManager = nullptr;
	PacketManager* m_packetManager = nullptr;

	ReadyButton* m_readyButton = nullptr;
public:
	virtual void Init();
	virtual void Update();
	void CheckPacket();
	virtual void Render();
	virtual void Release();

	GameRoomSystem();
	~GameRoomSystem();
};