#pragma once

enum USER_LOBBY : unsigned int { LOBBY_IDLE, LOBBY_CREATE_ROOM, LOBBY_ENTER_ROOM };

struct LobbyPacket
{
	bool b_enterRoom;
	USER_LOBBY userReq;
	int n_roomNum;
	int n_roomCount;
};

struct GameRoom
{
	int m_roomNum;
	int m_userCount = 0;
};

class PacketManager
{
private:
	static PacketManager* Inst;
	PacketManager();
public:
	LobbyPacket* m_lobbyPacket = nullptr;
	list<GameRoom*>m_roomList;


public:
	static PacketManager* getInstance();

	void ClearRoomList();

	~PacketManager();
};