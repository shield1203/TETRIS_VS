#include "stdafx.h"
#include "SocketManager.h"
#include "PacketManager.h"
#include "ResourceManager.h"

SocketManager* SocketManager::Inst = nullptr;

SocketManager* SocketManager::getInstance()
{
	if (Inst == nullptr) {
		Inst = new SocketManager();
	}

	return Inst;
}

SocketManager::SocketManager()
{
	m_packetManager = PacketManager::getInstance();

	WSAStartup(MAKEWORD(2, 2), &wsadata);

	m_sock = SetTCPClient();

	m_connect = connect(m_sock, (struct sockaddr*) & m_servaddr, sizeof(m_servaddr));//楷搬 夸没
	if (m_connect == -1) 
	{
		ResourceManager::getInstance()->m_curGameStep = GAME_STEP::STEP_MENU;
	}
}

SocketManager::~SocketManager()
{
	SafeDelete(m_packetManager);
}

SOCKET SocketManager::SetTCPClient()
{
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//家南 积己

	if (sock == -1)
	{
		return -1;
	}

	m_servaddr = { 0 };//家南 林家
	m_servaddr.sin_family = AF_INET;
	m_servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	m_servaddr.sin_port = htons(PORT_NUM);

	return sock;
}

void SocketManager::Communication(GAME_STEP gameStep)
{
	Send(gameStep);
	Recv(gameStep);
	CheckPacket(gameStep);
}

void SocketManager::Recv(GAME_STEP gameStep)
{
	char msg[MAX_MSG_LEN] = "";
	recv(m_sock, msg, sizeof(msg), 0); 

	switch (gameStep)
	{
	case GAME_STEP::STEP_LOBBY:
	{
		msg[sizeof(LobbySendPacket)] = '\0';

		LobbySendPacket* lobbySendPacket = (LobbySendPacket*)msg;

		m_packetManager->ClearRoomList();
		m_packetManager->SetLobbySendPacket(lobbySendPacket);

		/*LobbyPacket* lobbyPacket = (LobbyPacket*)msg;
		m_packetManager->SetLobbyPacket(lobbyPacket);

		m_packetManager->ClearRoomList();
		for (int i = 0; i < m_packetManager->m_lobbyPacket->n_roomCount; i++)
		{
			char roomData[MAX_MSG_LEN] = "";

			recv(m_sock, roomData, sizeof(roomData), 0);
			roomData[sizeof(GameRoom_Lobby)] = '\0';

			GameRoom_Lobby* roomPacket = (GameRoom_Lobby*)roomData;

			GameRoom_Lobby* room = new GameRoom_Lobby;
			room->m_roomNum = roomPacket->m_roomNum;
			room->m_userCount = roomPacket->m_userCount;

			m_packetManager->m_roomList.push_back(room);
		}*/
	}
		break;
	case GAME_STEP::STEP_ROOM:
	{
		msg[sizeof(GameRoomPacket)] = '\0';

		GameRoomPacket* gameRoomPacket = (GameRoomPacket*)msg;
		m_packetManager->SetGameRoomPacket(gameRoomPacket);
	}
		break;
	case GAME_STEP::STEP_VERSUS_PLAY:
	{
		
	}
		break;
	}
}

void SocketManager::Send(GAME_STEP gameStep)
{
	switch (gameStep)
	{
	case STEP_LOBBY:
		send(m_sock, (char*)m_packetManager->m_lobbyPacket, sizeof(LobbyPacket), 0);
		break;
	case STEP_ROOM:
		send(m_sock, (char*)m_packetManager->m_1PGameRoomPacket, sizeof(GameRoomPacket), 0);
		break;
	case STEP_VERSUS_PLAY:

		break;
	}
}

void SocketManager::CheckPacket(GAME_STEP gameStep)
{
	switch (gameStep)
	{
	case GAME_STEP::STEP_LOBBY:
		CheckLobbyPacket();
		break;
	case GAME_STEP::STEP_ROOM:
		CheckRoomPacket();
		break;
	case GAME_STEP::STEP_VERSUS_PLAY:

		break;
	}
}

void SocketManager::CheckLobbyPacket()
{
	switch (m_packetManager->m_lobbyPacket->userReq)
	{
	case USER_LOBBY::LOBBY_CREATE_ROOM:
		ResourceManager::getInstance()->m_curGameStep = GAME_STEP::STEP_ROOM;
		m_packetManager->m_1PGameRoomPacket->bOn = true;
		m_packetManager->m_1PGameRoomPacket->bOwner = true;
		break;
	case USER_LOBBY::LOBBY_ENTER_ROOM:
		if (m_packetManager->m_lobbyPacket->b_enterRoom)
		{
			m_packetManager->m_1PGameRoomPacket->bOn = true;
		}
		break;
	}

	m_packetManager->m_lobbyPacket->userReq = USER_LOBBY::LOBBY_IDLE;
}

void SocketManager::CheckRoomPacket()
{
	switch (m_packetManager->m_1PGameRoomPacket->userReq)
	{
	case USER_ROOM::ROOM_BACK_LOBBY:
		m_packetManager->m_1PGameRoomPacket->bOwner = false;
		m_packetManager->m_1PGameRoomPacket->bReady = false;
		m_packetManager->m_lobbyPacket->userReq = USER_LOBBY::LOBBY_IDLE;
		ResourceManager::getInstance()->m_curGameStep  = GAME_STEP::STEP_LOBBY;
		break;
	case USER_ROOM::ROOM_GAME_START:
		// 霸烙矫累
		break;
	}

	m_packetManager->m_1PGameRoomPacket->userReq = USER_ROOM::ROOM_IDLE;
}

void SocketManager::CleanSocket()
{
	closesocket(m_sock);
	WSACleanup();

	Inst = nullptr;
}