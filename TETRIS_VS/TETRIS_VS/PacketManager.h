#pragma once

// Lobby
enum class USER_LOBBY : unsigned int { LOBBY_IDLE, LOBBY_CREATE_ROOM, LOBBY_ENTER_ROOM };

struct LobbyPacket
{
	bool b_enterRoom = true;
	USER_LOBBY userReq = USER_LOBBY::LOBBY_IDLE;
	int n_roomNum = 0;
	int n_roomCount = 0;
};

struct GameRoom_Lobby
{
	int m_roomNum;
	int m_userCount = 0;
};

struct LobbySendPacket
{
	LobbyPacket lobbyPacket;
	GameRoom_Lobby gameRoom_lobby[20];
};

// GameRoom
enum class USER_ROOM : unsigned int { ROOM_IDLE, ROOM_BACK_LOBBY, ROOM_GAME_START };

struct GameRoomPacket
{
	USER_ROOM userReq = USER_ROOM::ROOM_IDLE;
	int userNum = 0;
	bool bOn = false;
	bool bOwner = false;
	bool bReady = false;
	bool bGameStart = false;
};

struct PlayGamePacket
{
	
};

class PacketManager
{
private:
	static PacketManager* Inst;
	PacketManager();
public:
	LobbyPacket* m_lobbyPacket = nullptr;
	LobbySendPacket* m_lobbySendPacket = nullptr;
	list<GameRoom_Lobby*>m_roomList;

	GameRoomPacket* m_1PGameRoomPacket = nullptr;
	GameRoomPacket* m_2PGameRoomPacket = nullptr;

	//PlayGamePacket* m_1PGamePacket = nullptr;
	//PlayGamePacket* m_2PGamePacket = nullptr;
public:
	static PacketManager* getInstance();

	void ClearRoomList();

	void SetLobbySendPacket(LobbySendPacket*);
	void SetLobbyPacket();
	void SetRoomList();
	void SetGameRoomPacket(GameRoomPacket*);

	~PacketManager();
};