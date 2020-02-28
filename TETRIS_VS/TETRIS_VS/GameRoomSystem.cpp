#include "stdafx.h"
#include "SystemFrame.h"
#include "GameRoomSystem.h"

#include "ReadyButton.h"

#include "ResourceManager.h"
#include "SocketManager.h"
#include "PacketManager.h"
#include "SoundSystem.h"

GameRoomSystem::GameRoomSystem()
{
}

GameRoomSystem::~GameRoomSystem()
{
}

void GameRoomSystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_ROOM);

	m_socketManager = SocketManager::getInstance();
	if (m_socketManager->m_userState != USER_STATE::CLOSE_CONNECT)
	{
		m_socketManager->m_userState = USER_STATE::USER_GAME_ROOM;
	}

	m_packetManager = PacketManager::getInstance();

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_readyButton = new ReadyButton();
}

void GameRoomSystem::Update()
{
	SoundSystem::getInstance()->pSystem->update();

	m_socketManager->Communication();
	CheckPacket();

	if (m_resourceManager->m_curGameStep == GAME_STEP::STEP_ROOM)
	{
		m_readyButton->Update();
	}
}

void GameRoomSystem::CheckPacket()
{
	if (m_socketManager->m_userState == USER_STATE::CLOSE_CONNECT)
	{
		m_packetManager->m_1PGameRoomData->userReq = USER_ROOM::ROOM_BACK_MENU;
	}

	switch (m_packetManager->m_1PGameRoomData->userReq)
	{
	case USER_ROOM::ROOM_BACK_MENU:
		m_resourceManager->m_curGameStep = GAME_STEP::STEP_MENU;
		break;
	case USER_ROOM::ROOM_BACK_LOBBY:
		m_packetManager->m_lobbyData->userReq = USER_LOBBY::LOBBY_IDLE;
		m_packetManager->m_lobbyData->roomNum = 0;
		m_packetManager->m_lobbyData->bEnterRoom = true;

		m_resourceManager->m_curGameStep = GAME_STEP::STEP_LOBBY;
		break;
	}

	if (m_packetManager->m_2PGameRoomData->userReq == USER_ROOM::ROOM_GAME_START)
	{
		m_resourceManager->m_curGameStep = GAME_STEP::STEP_VERSUS_PLAY;
	}

	m_packetManager->m_1PGameRoomData->userReq = USER_ROOM::ROOM_IDLE;
}

void GameRoomSystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	WriteBuffer(ROOM_NUM_XPOS, ROOM_NUM_YPOS, to_string(m_packetManager->m_lobbyData->roomNum), WHITE);

	// 1 Player
	if (m_packetManager->m_1PGameRoomData->bOn)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P1]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 1P Ready
	if (m_packetManager->m_1PGameRoomData->bReady)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P1_READY]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 2P
	if (m_packetManager->m_2PGameRoomData->bOn)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P2]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 2P Ready
	if (m_packetManager->m_2PGameRoomData->bReady)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P2_READY]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// ¹æÀå
	if (m_packetManager->m_1PGameRoomData->bOwner)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_1P_OWNER]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}
	else
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_2P_OWNER]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// Start
	if (m_packetManager->m_1PGameRoomData->bReady && 
		m_packetManager->m_2PGameRoomData->bReady)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_GAME_START]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}
}

void GameRoomSystem::Release()
{
	m_resourceManager->ReleaseData(STEP_ROOM);

	SafeDelete(m_readyButton);

	if (m_resourceManager->m_curGameStep == STEP_MENU)
	{
		SocketManager::getInstance()->CleanSocket();
		SafeDelete(m_socketManager);
	}
}