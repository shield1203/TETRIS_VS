#include "stdafx.h"
#include "ReadyButton.h"

#include "ResourceManager.h"

#include "PacketManager.h"
#include "InputSystem.h"
#include "SoundSystem.h"

ReadyButton::ReadyButton()
{
	m_resourceManager = ResourceManager::getInstance();
	m_packetManager = PacketManager::getInstance();
	m_inputSystem = new InputSystem();
}

ReadyButton::~ReadyButton()
{
	SafeDelete(m_inputSystem);
}

void ReadyButton::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (!m_packetManager->m_2PGameRoomData->bOn)
	{
		m_packetManager->m_1PGameRoomData->bOwner = true;
	}

	if (m_inputSystem->IsEnterPressed())
	{
		PlayerReady();
	}

	if (m_inputSystem->IsLeftArrowPressed())
	{
		BackLobby();
	}
}

void ReadyButton::BackLobby()
{
	m_packetManager->m_1PGameRoomData->userReq = USER_ROOM::ROOM_BACK_LOBBY;

	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
}

void ReadyButton::PlayerReady()
{
	if (!m_packetManager->m_1PGameRoomData->bReady)
	{
		m_packetManager->m_1PGameRoomData->bReady = true;

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
	else
	{
		if (m_packetManager->m_1PGameRoomData->bOwner && m_packetManager->m_2PGameRoomData->bReady)
		{
			m_packetManager->m_1PGameRoomData->userReq = USER_ROOM::ROOM_GAME_START;
		}
		else
		{
			m_packetManager->m_1PGameRoomData->bReady = false;
		}

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
}