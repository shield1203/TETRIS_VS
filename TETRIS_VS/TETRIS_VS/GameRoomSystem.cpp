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

	m_socketManager->Communication(m_resourceManager->m_curGameStep);

	m_readyButton->Update();
}

void GameRoomSystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	WriteBuffer(ROOM_NUM_XPOS, ROOM_NUM_YPOS, to_string(m_packetManager->m_1PGameRoomPacket->m_roomNum), WHITE);

	// 1 Player
	if (m_packetManager->m_1PGameRoomPacket->bOn)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P1]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 1P Ready
	if (m_packetManager->m_1PGameRoomPacket->bReady)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P1_READY]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 2P
	if (m_packetManager->m_2PGameRoomPacket->bOn)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P2]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 2P Ready
	if (m_packetManager->m_2PGameRoomPacket->bReady)
	{
		for (auto i : m_resourceManager->m_sprite[ROOM_P2_READY]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// ¹æÀå
	if (m_packetManager->m_1PGameRoomPacket->bOwner)
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
	if (m_packetManager->m_1PGameRoomPacket->bReady && 
		m_packetManager->m_2PGameRoomPacket->bReady)
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
}