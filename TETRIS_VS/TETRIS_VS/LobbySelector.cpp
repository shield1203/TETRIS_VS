#include "stdafx.h"
#include "SelectorFrame.h"
#include "LobbySelector.h"

#include "ResourceManager.h"
#include "PacketManager.h"
#include "InputSystem.h"
#include "SoundSystem.h"

LobbySelector::LobbySelector()
{
}

LobbySelector::~LobbySelector()
{
	SafeDelete(m_inputSystem);
}

void LobbySelector::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_packetManager = PacketManager::getInstance();
	m_inputSystem = new InputSystem();
}

void LobbySelector::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (m_packetManager->m_roomList.size() != 0)
	{
		if (m_inputSystem->IsUpArrowPressed())
		{
			MoveUp();
		}

		if (m_inputSystem->IsDownArrowPressed())
		{
			MoveDown();
		}

		if (m_inputSystem->IsEnterPressed())
		{
			Select();
		}
	}
	else
	{
		ListEmpty();
	}

	if (m_inputSystem->IsLeftArrowPressed())
	{
		BackMenu();
	}

	if (m_inputSystem->IsKeySPressed())
	{
		ReqestCreateRoom();
	}
}
void LobbySelector::ListEmpty()
{
	m_selectedRoom = 0;
}

void LobbySelector::MoveUp()
{
	auto selector = m_resourceManager->m_sprite[LOBBY_SELECTOR]->textInfo.front();

	if (selector->yPos > ROOM_LIST_Y)
	{
		m_selectedRoom -= 1;

		for (auto i : m_resourceManager->m_sprite[LOBBY_SELECTOR]->textInfo)
		{
			i->yPos = m_selectedRoom + ROOM_LIST_Y;
		}

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
}

void LobbySelector::MoveDown()
{
	auto selector = m_resourceManager->m_sprite[LOBBY_SELECTOR]->textInfo.front();

	if (selector->yPos < ROOM_LIST_Y + m_packetManager->m_roomList.size())
	{
		m_selectedRoom += 1;

		for (auto i : m_resourceManager->m_sprite[LOBBY_SELECTOR]->textInfo)
		{
			i->yPos = m_selectedRoom + ROOM_LIST_Y;
		}

		SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
}

void LobbySelector::Select()
{
	ReqeatEnterRoom();

	SoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
}

void LobbySelector::BackMenu()
{
	m_resourceManager->m_curGameStep = STEP_MENU;
}

void LobbySelector::ReqeatEnterRoom()
{
	m_packetManager->m_lobbyPacket->userReq = USER_LOBBY::LOBBY_ENTER_ROOM;

	int roomNum = 0;
	for (auto i : m_packetManager->m_roomList)
	{
		if (roomNum == m_selectedRoom)
		{
			m_packetManager->m_lobbyPacket->n_roomNum = i->m_roomNum;
			break;
		}
		roomNum++;
	}
}

void LobbySelector::ReqestCreateRoom()
{
	m_packetManager->m_lobbyPacket->userReq = USER_LOBBY::LOBBY_CREATE_ROOM;
}