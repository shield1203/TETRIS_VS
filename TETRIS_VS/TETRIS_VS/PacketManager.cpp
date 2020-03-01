#include "stdafx.h"
#include "PacketManager.h"
#include "ResourceManager.h"

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
	m_1P_PlayGameData = new PlayGameData;
	m_2P_PlayGameData = new PlayGameData;
}

PacketManager::~PacketManager()
{
	SafeDelete(m_packetData);
	SafeDelete(m_lobbyData);
	SafeDelete(m_1PGameRoomData);
	SafeDelete(m_2PGameRoomData);
	SafeDelete(m_1P_PlayGameData);
	SafeDelete(m_2P_PlayGameData);

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

void PacketManager::ClearBlockList()
{
	for (auto i : m_2PBlockList)
	{
		SafeDelete(i);
	}
	m_2PBlockList.clear();
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
	case USER_STATE::USER_RESULT:
		SetPlayResultData();
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
	m_packetData->size = 0;

	memcpy(m_packetData->data, m_1P_PlayGameData, sizeof(PlayGameData));
	m_packetData->size += static_cast<unsigned short>(sizeof(PlayGameData));

	for (auto block : ResourceManager::getInstance()->m_block.blocks)
	{
		PlayGameData_Block* addBlock = new PlayGameData_Block;
		addBlock->xPos = ResourceManager::getInstance()->m_block.xPos + block.xPos;
		addBlock->yPos = ResourceManager::getInstance()->m_block.yPos + block.yPos;
		addBlock->textColor = block.textColor;
		memcpy(m_packetData->data + m_packetData->size, addBlock, sizeof(PlayGameData_Block));

		m_packetData->size += static_cast<unsigned short>(sizeof(PlayGameData_Block));

		SafeDelete(addBlock);
	}

	for (auto map : ResourceManager::getInstance()->m_map)
	{
		if (map->strText == "бс")
		{
			PlayGameData_Block* addBlock = new PlayGameData_Block;
			addBlock->xPos = map->xPos;
			addBlock->yPos = map->yPos;
			addBlock->textColor = map->textColor;
			memcpy(m_packetData->data + m_packetData->size, addBlock, sizeof(PlayGameData_Block));

			m_packetData->size += static_cast<unsigned short>(sizeof(PlayGameData_Block));

			SafeDelete(addBlock);
		}
	}
}

void PacketManager::SetPlayResultData()
{
	m_packetData->size = 0;

	memcpy(m_packetData->data, m_1P_PlayGameData, sizeof(PlayGameData));
	m_packetData->size += static_cast<unsigned short>(sizeof(PlayGameData));
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
		GetPlayGameData(); 
		break;
	case USER_STATE::USER_RESULT:
		GetPlayResultData();
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
	ZeroMemory(m_2P_PlayGameData, sizeof(PlayGameData));
	memcpy(m_2P_PlayGameData, m_packetData->data, sizeof(PlayGameData));

	int size = sizeof(PlayGameData);

	ClearBlockList();
	while (size < m_packetData->size)
	{
		PlayGameData_Block* block = new PlayGameData_Block;
		memcpy(block, m_packetData->data + size, sizeof(PlayGameData_Block));
		m_2PBlockList.push_back(block);

		size += sizeof(PlayGameData_Block);
	}
}

void PacketManager::GetPlayResultData()
{
	ZeroMemory(m_2P_PlayGameData, sizeof(PlayGameData));
	memcpy(m_2P_PlayGameData, m_packetData->data, sizeof(PlayGameData));
}