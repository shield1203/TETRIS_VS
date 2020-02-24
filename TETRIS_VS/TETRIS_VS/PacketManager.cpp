#include "stdafx.h"
#include "PacketManager.h"

PacketManager* PacketManager::Inst = nullptr;

PacketManager* PacketManager::getInstance()
{
	if (Inst == nullptr) {
		Inst = new PacketManager();
	}

	return Inst;
}

PacketManager::PacketManager()
{
	m_lobbyPacket = new LobbyPacket;
	m_lobbySendPacket = new LobbySendPacket;

	m_1PGameRoomPacket = new GameRoomPacket;
	m_2PGameRoomPacket = new GameRoomPacket;
}

PacketManager::~PacketManager()
{
	SafeDelete(m_lobbyPacket);
	ClearRoomList();

	SafeDelete(m_1PGameRoomPacket);
	SafeDelete(m_2PGameRoomPacket);

	Inst = nullptr;
}

void PacketManager::ClearRoomList()
{
	for (auto i : m_roomList)
	{
		SafeDelete(i);
	}
	m_roomList.clear();
}

void PacketManager::SetLobbySendPacket(LobbySendPacket* lobbySendPacket)
{
	m_lobbySendPacket->lobbyPacket.b_enterRoom = lobbySendPacket->lobbyPacket.b_enterRoom;
	m_lobbySendPacket->lobbyPacket.n_roomCount = lobbySendPacket->lobbyPacket.n_roomCount;
	m_lobbySendPacket->lobbyPacket.n_roomNum = lobbySendPacket->lobbyPacket.n_roomNum;
	m_lobbySendPacket->lobbyPacket.userReq = lobbySendPacket->lobbyPacket.userReq;

	for (int i = 0; i < m_lobbySendPacket->lobbyPacket.n_roomCount; i++)
	{
		m_lobbySendPacket->gameRoom_lobby[i].m_roomNum = lobbySendPacket->gameRoom_lobby[i].m_roomNum;
		m_lobbySendPacket->gameRoom_lobby[i].m_userCount = lobbySendPacket->gameRoom_lobby[i].m_userCount;
	}

	SetLobbyPacket();
	SetRoomList();
}

void PacketManager::SetLobbyPacket()
{
	m_lobbyPacket->b_enterRoom = m_lobbySendPacket->lobbyPacket.b_enterRoom;
	m_lobbyPacket->n_roomCount = m_lobbySendPacket->lobbyPacket.n_roomCount;
	m_lobbyPacket->n_roomNum = m_lobbySendPacket->lobbyPacket.n_roomNum;
	m_lobbyPacket->userReq = m_lobbySendPacket->lobbyPacket.userReq;
}

void PacketManager::SetRoomList()
{
	for (int i = 0; i < m_lobbyPacket->n_roomCount; i++)
	{
		GameRoom_Lobby* room = new GameRoom_Lobby;
		room->m_roomNum = m_lobbySendPacket->gameRoom_lobby[i].m_roomNum;
		room->m_userCount = m_lobbySendPacket->gameRoom_lobby[i].m_userCount;

		m_roomList.push_back(room);
	}
}

void PacketManager::SetGameRoomPacket(GameRoomPacket* gameRoomPacket)
{
	m_2PGameRoomPacket->bGameStart = gameRoomPacket->bGameStart;
	m_2PGameRoomPacket->bOn = gameRoomPacket->bOn;
	m_2PGameRoomPacket->bOwner = gameRoomPacket->bOwner;
	m_2PGameRoomPacket->bReady = gameRoomPacket->bReady;
	m_2PGameRoomPacket->userNum = gameRoomPacket->userNum;
	m_2PGameRoomPacket->userReq = gameRoomPacket->userReq;
}