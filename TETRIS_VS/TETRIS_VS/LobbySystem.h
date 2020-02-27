#pragma once
class ResourceManager;
class SocketManager;
class PacketManager;

class SelectorFrame;
class LobbyBoard;

enum  ROOM_LIST : unsigned int { ROOM_LIST_YPOS = 4, ROOM_LIST_XPOS = 12 };

class LobbySystem : public SystemFrame
{
private:
	ResourceManager* m_resourceManager = nullptr;
	SocketManager* m_socketManager = nullptr;
	PacketManager* m_packetManager = nullptr;

	SelectorFrame* m_selector = nullptr;
	LobbyBoard* m_lobbyboard = nullptr;
public:
	virtual void Init();
	virtual void Update();
	void CheckPacket();
	virtual void Render();
	virtual void Release();

	LobbySystem();
	~LobbySystem();
};