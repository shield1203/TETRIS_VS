#pragma once

enum class USER_LOBBY : unsigned int { LOBBY_IDLE, LOBBY_CREATE_ROOM, LOBBY_ENTER_ROOM };

struct LobbyPacket
{
	bool b_enterRoom = true;
	USER_LOBBY userReq = USER_LOBBY::LOBBY_IDLE;
	int n_roomNum = 0;
	int n_roomCount = 0;
};

struct GameRoom
{
	int m_roomNum;
	int m_userCount = 0;
};

struct RoomPacket
{
	int m_roomNum;
	bool bOn = false;
	bool bOwner = false;
	bool bReady = false;
	bool bGameStart = false;
};

class PacketManager
{
private:
	static PacketManager* Inst;
	PacketManager();
public:
	LobbyPacket* m_lobbyPacket = nullptr;
	list<GameRoom*>m_roomList;

	RoomPacket* m_1PGameRoomPacket = nullptr;
	RoomPacket* m_2PGameRoomPacket = nullptr;
public:
	static PacketManager* getInstance();

	void ClearRoomList();

	~PacketManager();
};