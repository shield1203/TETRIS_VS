#include "stdafx.h"
#include "SystemFrame.h"
#include "LobbySystem.h"

#include "SelectorFrame.h"
#include "LobbySelector.h"

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

	//m_socketManager = SocketManager::getInstance();
	m_packetManager = PacketManager::getInstance();

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_selector = new LobbySelector();
	m_selector->Init();

	SoundSystem::getInstance()->StopBGM();
	SoundSystem::getInstance()->StartBGM(LOBBY_BGM);
}

void LobbySystem::Update()
{
	SoundSystem::getInstance()->pSystem->update();
	
	m_selector->Update();
}

void LobbySystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}
}

void LobbySystem::Release()
{
	m_resourceManager->ReleaseData(STEP_LOBBY);

	SafeDelete(m_selector);

	if (m_resourceManager->m_curGameStep == STEP_MENU)
	{
		SafeDelete(m_socketManager);
	}
}