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
	/*m_inputSystem->CheckKeyboardPressed();

	if (!m_packetManager->m_2PGameRoomPacket->bOn)
	{
		m_packetManager->m_1PGameRoomPacket->bOwner = true;
	}

	if (!m_packetManager->m_1PGameRoomPacket->bReady ||
		!m_packetManager->m_2PGameRoomPacket->bReady)
	{
		m_packetManager->m_1PGameRoomPacket->bGameStart = false;
	}

	if (m_inputSystem->IsEnterPressed())
	{
		PlayerReady();
	}

	if (m_inputSystem->IsLeftArrowPressed())
	{
		BackLobby();
	}*/
}

void ReadyButton::BackLobby()
{
	/*m_packetManager->m_1PGameRoomPacket->userReq = USER_ROOM::ROOM_BACK_LOBBY;
	m_packetManager->m_1PGameRoomPacket->bOn = false;*/

	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
}

void ReadyButton::PlayerReady()
{
	//if (!m_packetManager->m_1PGameRoomPacket->bReady)
	//{
	//	m_packetManager->m_1PGameRoomPacket->bReady = true;

	//	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	//}
	//else
	//{
	//	m_packetManager->m_1PGameRoomPacket->bReady = false;

	//	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	//}
	///*else
	//{
	//	if (m_packetManager->m_1PGameRoomPacket->bOwner &&
	//		m_packetManager->m_2PGameRoomPacket->bReady)
	//	{
	//		m_packetManager->m_1PGameRoomPacket->bGameStart = true;

	//		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	//	}
	//}*/
}