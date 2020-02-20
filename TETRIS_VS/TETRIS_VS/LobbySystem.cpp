#include "stdafx.h"
#include "SystemFrame.h"
#include "LobbySystem.h"

#include "SelectorFrame.h"
#include "LobbySelector.h"
#include "LobbyBoard.h"

#include "ResourceManager.h"
#include "SocketManager.h"
#include "PacketManager.h"
#include "SoundSystem.h"

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

	m_socketManager->Communication(m_resourceManager->m_curGameStep);
	
	if (m_packetManager->m_1PGameRoomPacket->bOn)
	{
		m_resourceManager->m_curGameStep = STEP_ROOM;
		return;
	}

	if (m_packetManager->m_lobbyPacket->b_enterRoom)
	{
		m_selector->Update();
	}
	else
	{
		m_lobbyboard->Update();
	}
}

void LobbySystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Sprite
	if (m_packetManager->m_lobbyPacket->b_enterRoom && !m_packetManager->m_roomList.empty())
	{
		for (auto i : m_resourceManager->m_sprite[LOBBY_SELECTOR]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}
	
	if(!m_packetManager->m_lobbyPacket->b_enterRoom)
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
		SocketManager::getInstance()->CleanSocket();
		SafeDelete(m_socketManager);
	}
}