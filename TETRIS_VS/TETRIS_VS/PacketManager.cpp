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
	m_packetData = new PacketData;
	m_lobbyData = new LobbyData;
	m_1PGameRoomData = new GameRoomData;
	m_2PGameRoomData = new GameRoomData;
	//m_1P_PlayGameData = new PlayGameData;
	//m_2P_PlayGameData = new PlayGameData;
}

PacketManager::~PacketManager()
{
	SafeDelete(m_packetData);
	SafeDelete(m_lobbyData);
	SafeDelete(m_1PGameRoomData);
	SafeDelete(m_2PGameRoomData);
	//SafeDelete(m_1P_PlayGameData);
	//SafeDelete(m_2P_PlayGameData);

	ClearRoomList();

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

void PacketManager::SetPacket(USER_STATE userState)
{
	m_packetData->userState = userState;

	switch (userState)
	{
	case USER_STATE::USER_LOBBY:
		SetLobbyData();
		break;
	case USER_STATE::USER_GAME_ROOM:
		SetGameRoomData();
		break;
	case USER_STATE::USER_PLAY_GAME:
		SetPlayGameData();
		break;
	}
}

void PacketManager::SetLobbyData()
{
	m_packetData->size = 0;

	memcpy(m_packetData->data, m_lobbyData, sizeof(LobbyData));
	m_packetData->size += static_cast<unsigned short>(sizeof(LobbyData));
}

void PacketManager::SetGameRoomData()
{
	m_packetData->size = 0;

	memcpy(m_packetData->data, m_1PGameRoomData, sizeof(GameRoomData));
	m_packetData->size += static_cast<unsigned short>(sizeof(GameRoomData));
}

void PacketManager::SetPlayGameData()
{

}

void PacketManager::CopyPacket(PacketData* packetData)
{
	memcpy(m_packetData, packetData, sizeof(PacketData));
}

void PacketManager::GetData(USER_STATE userState)
{
	switch (userState)
	{
	case USER_STATE::USER_LOBBY:
		GetLobbyData();
		break;
	case USER_STATE::USER_GAME_ROOM:
		GetGameRoomData();
		break;
	case USER_STATE::USER_PLAY_GAME:
		GetPlayGameData(); // ¾ÆÁ÷
		break;
	}
}

void PacketManager::GetLobbyData()
{
	ZeroMemory(m_lobbyData, sizeof(LobbyData));
	memcpy(m_lobbyData, m_packetData->data, sizeof(LobbyData));

	int size = sizeof(LobbyData);

	ClearRoomList();
	while (size < m_packetData->size)
	{
		LobbyData_GameRoom* room = new LobbyData_GameRoom;
		memcpy(room, m_packetData->data + size, sizeof(LobbyData_GameRoom));
		m_roomList.push_back(room);

		size += sizeof(LobbyData_GameRoom);
	}
}

void PacketManager::GetGameRoomData()
{
	ZeroMemory(m_2PGameRoomData, sizeof(GameRoomData));
	memcpy(m_2PGameRoomData, m_packetData->data, sizeof(GameRoomData));
}

void PacketManager::GetPlayGameData()
{
	//ZeroMemory(m_gameRoomData, sizeof(GameRoomData));
}