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
}

PacketManager::~PacketManager()
{
	SafeDelete(m_lobbyPacket);
	ClearRoomList();
}

void PacketManager::ClearRoomList()
{
	for (auto i : m_roomList)
	{
		SafeDelete(i);
	}
	m_roomList.clear();
}