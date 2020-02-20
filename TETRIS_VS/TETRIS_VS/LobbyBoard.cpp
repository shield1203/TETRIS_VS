#include "stdafx.h"
#include "LobbyBoard.h"

#include "InputSystem.h"
#include "PacketManager.h"

LobbyBoard::LobbyBoard()
{
	m_packetManager = PacketManager::getInstance();
	m_inputSystem = new InputSystem();
}

LobbyBoard::~LobbyBoard()
{
	SafeDelete(m_inputSystem);
}

void LobbyBoard::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (m_inputSystem->IsEnterPressed())
	{
		m_packetManager->m_lobbyPacket->b_enterRoom = true;
	}
}