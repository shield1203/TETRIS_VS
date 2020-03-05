#pragma once
struct PacketData
{
	USER_STATE userState = USER_STATE::USER_LOBBY;
	unsigned short size = 0;
	char data[MAX_DATA_LEN] = "";
};

// Lobby
enum class USER_LOBBY : unsigned int { LOBBY_IDLE, LOBBY_CREATE_ROOM, LOBBY_ENTER_ROOM, LOBBY_BACK_MENU };

struct LobbyData
{
	USER_LOBBY userReq = USER_LOBBY::LOBBY_IDLE;
	bool bEnterRoom = true;
	int roomNum = 0;
};

struct LobbyData_GameRoom
{
	int roomNum;
	int userCount = 0;
};

// GameRoom
enum class USER_ROOM : unsigned int { ROOM_IDLE, ROOM_BACK_LOBBY, ROOM_GAME_START, ROOM_BACK_MENU };

struct GameRoomData
{
	USER_ROOM userReq = USER_ROOM::ROOM_IDLE;
	int roomNum = 0;
	bool bOn = false;
	bool bOwner = false;
	bool bReady = false;
};

// PlayGame
enum class USER_PLAY : unsigned int { PLAY_IDLE, PLAY_LOSE, PLAY_WIN, RESULT_BACK_ROOM };

struct PlayGameData
{
	USER_PLAY userReq = USER_PLAY::PLAY_IDLE;
};

struct PlayGameData_Block
{
	int xPos = 0;
	int yPos = 0;
	COLOR textColor = WHITE;
};

class PacketManager
{
private:
	static PacketManager* Inst;
	PacketManager();
public:
	PacketData* m_packetData = nullptr;

	LobbyData* m_lobbyData = nullptr;
	GameRoomData* m_1PGameRoomData = nullptr;
	GameRoomData* m_2PGameRoomData = nullptr;
	PlayGameData* m_1P_PlayGameData = nullptr;
	PlayGameData* m_2P_PlayGameData = nullptr;

	list<PlayGameData_Block*> m_2PBlockList;

	list<LobbyData_GameRoom*>m_roomList;
public:
	static PacketManager* getInstance();

	void ClearRoomList();
	void ClearBlockList();

	// Send
	void SetPacket(USER_STATE);
	void SetLobbyData();
	void SetGameRoomData();
	void SetPlayGameData();
	void SetPlayResultData();

	// Recv
	void CopyPacket(PacketData*);
	void GetData(USER_STATE);
	void GetLobbyData();
	void GetGameRoomData();
	void GetPlayGameData();
	void GetPlayResultData();

	~PacketManager();
};