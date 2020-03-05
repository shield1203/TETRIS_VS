#include "stdafx.h"
#include "SystemFrame.h"
#include "LobbySystem.h"

#include "ResourceManager.h"
#include "SocketManager.h"
#include "PacketManager.h"
#include "SoundSystem.h"

#include "SelectorFrame.h"
#include "LobbySelector.h"
#include "LobbyBoard.h"

LobbySystem::LobbySystem()
{
}

LobbySystem::~LobbySystem()
{
}

void LobbySystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_LOBBY);
 
	m_socketManager = SocketManager::getInstance();
	if (m_socketManager->m_userState != USER_STATE::CLOSE_CONNECT)
	{
		m_socketManager->m_userState = USER_STATE::USER_LOBBY;
	}

	m_packetManager = PacketManager::getInstance();

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_selector = new LobbySelector();
	m_selector->Init();
	m_lobbyboard = new LobbyBoard();

	SoundSystem::getInstance()->StopBGM();
	SoundSystem::getInstance()->StartBGM(LOBBY_BGM);
}

void LobbySystem::Update()
{
	SoundSystem::getInstance()->pSystem->update();

	m_socketManager->Communication();
	CheckPacket();

	if (m_resourceManager->m_curGameStep == GAME_STEP::STEP_LOBBY)
	{
		if (m_lobbyboard->m_on)
		{
			m_lobbyboard->Update();
		}
		else
		{
			m_selector->Update();
		}
	}
}

void LobbySystem::CheckPacket()
{
	if (m_socketManager->m_userState == USER_STATE::CLOSE_CONNECT)
	{
		m_packetManager->m_lobbyData->userReq = USER_LOBBY::LOBBY_BACK_MENU;
	}

	switch (m_packetManager->m_lobbyData->userReq)
	{
	case USER_LOBBY::LOBBY_BACK_MENU:
		m_resourceManager->m_curGameStep = GAME_STEP::STEP_MENU;
		break;
	case USER_LOBBY::LOBBY_CREATE_ROOM:
		m_packetManager->m_1PGameRoomData->userReq = USER_ROOM::ROOM_IDLE;
		m_packetManager->m_1PGameRoomData->bOn = true;
		m_packetManager->m_1PGameRoomData->bOwner = true;
		m_packetManager->m_1PGameRoomData->bReady = false;
		m_packetManager->m_1PGameRoomData->roomNum = m_packetManager->m_lobbyData->roomNum;

		m_resourceManager->m_curGameStep = GAME_STEP::STEP_ROOM;
		break;
	case USER_LOBBY::LOBBY_ENTER_ROOM:
		if (m_packetManager->m_lobbyData->bEnterRoom)
		{
			m_packetManager->m_1PGameRoomData->userReq = USER_ROOM::ROOM_IDLE;
			m_packetManager->m_1PGameRoomData->bOn = true;
			m_packetManager->m_1PGameRoomData->bOwner = false;
			m_packetManager->m_1PGameRoomData->bReady = false;
			m_packetManager->m_1PGameRoomData->roomNum = m_packetManager->m_lobbyData->roomNum;

			m_resourceManager->m_curGameStep = GAME_STEP::STEP_ROOM;
		}
		else
		{
			m_lobbyboard->m_on = false;
		}
		break;
	}

	m_packetManager->m_lobbyData->userReq = USER_LOBBY::LOBBY_IDLE;
}

void LobbySystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	if (!m_lobbyboard->m_on && !m_packetManager->m_roomList.empty())
	{
		for (auto i : m_resourceManager->m_sprite[LOBBY_SELECTOR]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}

		// RoomList
		unsigned int n_count = 0;
		for (auto i : m_packetManager->m_roomList)
		{
			LOBBY listState;
			if (i->userCount < 2)
			{
				listState = LOBBY::LOBBY_LIST_POSSIBLE;
			}
			else
			{
				listState = LOBBY::LOBBY_LIST_IMPOSSIBLE;
			}

			for (auto j : m_resourceManager->m_sprite[listState]->textInfo)
			{
				WriteBuffer(j->xPos, j->yPos + n_count, j->strText, j->textColor);
			}

			WriteBuffer(ROOM_LIST_XPOS, ROOM_LIST_YPOS + n_count, to_string(i->roomNum), WHITE);
			n_count++;
		}
	}
	
	if(m_lobbyboard->m_on)
	{
		for (auto i : m_resourceManager->m_sprite[LOBBY_FAIL_ENTER_ROOM]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}
}

void LobbySystem::Release()
{
	m_resourceManager->ReleaseData(STEP_LOBBY);

	SafeDelete(m_selector);
	SafeDelete(m_lobbyboard);

	if (m_resourceManager->m_curGameStep == STEP_MENU)
	{
		m_socketManager->CleanSocket();
		SafeDelete(m_socketManager);
		SafeDelete(m_packetManager);
	}
}