#include "stdafx.h"
#include "SocketManager.h"
#include "PacketManager.h"

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

	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	m_servaddr.sin_family = AF_INET;
	m_servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	m_servaddr.sin_port = htons(PORT_NUM);
}

SocketManager::~SocketManager()
{
	CleanSocket();
	SafeDelete(m_packetManager);
}

void SocketManager::Recv(GAME_STEP gameStep)
{
	switch (gameStep)
	{
	case STEP_LOBBY:

		break;
	case STEP_ROOM:

		break;
	case STEP_VERSUS_PLAY:

		break;
	}
}

void SocketManager::Send(GAME_STEP gameStep)
{
	switch (gameStep)
	{
	case STEP_LOBBY:

		break;
	case STEP_ROOM:

		break;
	case STEP_VERSUS_PLAY:

		break;
	}
}

void SocketManager::CleanSocket()
{
	closesocket(m_sock);
	WSACleanup();
}