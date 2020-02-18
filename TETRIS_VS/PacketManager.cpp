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
}

PacketManager::~PacketManager()
{
}

void PacketManager::ClearRoomList()
{
	for (auto i : m_roomList)
	{
		SafeDelete(i);
	}
	m_roomList.clear();
}