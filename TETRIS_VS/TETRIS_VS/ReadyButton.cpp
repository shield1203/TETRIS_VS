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

	if (m_inputSystem->IsEnterPressed())
	{
		PlayerReady();
	}

	if (m_inputSystem->IsLeftArrowPressed())
	{
		PlayerReady();
	}
}

void ReadyButton::BackLobby()
{
	m_packetManager->m_1PGameRoomPacket->bOn = false;
	m_resourceManager->m_curGameStep = STEP_LOBBY;

	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
}

void ReadyButton::PlayerReady()
{
	if (!m_packetManager->m_1PGameRoomPacket->bReady)
	{
		m_packetManager->m_1PGameRoomPacket->bReady = true;

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
	else
	{
		if (m_packetManager->m_1PGameRoomPacket->bOwner &&
			m_packetManager->m_2PGameRoomPacket->bReady)
		{
			m_packetManager->m_1PGameRoomPacket->bGameStart = true;

			SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
		}
	}
}