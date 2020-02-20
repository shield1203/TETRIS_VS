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

	m_1PGameRoomPacket = new RoomPacket;
	m_2PGameRoomPacket = new RoomPacket;
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