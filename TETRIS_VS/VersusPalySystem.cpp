#include "stdafx.h"
#include "SystemFrame.h"
#include "VersusPalySystem.h"

#include "ResourceManager.h"
#include "SocketManager.h"
#include "PacketManager.h"
#include "SoundSystem.h"

#include "Map.h"
#include "Block.h"
#include "Result.h"

VersusPalySystem::VersusPalySystem()
{
}

VersusPalySystem::~VersusPalySystem()
{
}

void VersusPalySystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_VERSUS_PLAY);

	m_socketManager = SocketManager::getInstance();
	if (m_socketManager->m_userState != USER_STATE::CLOSE_CONNECT)
	{
		m_socketManager->m_userState = USER_STATE::USER_PLAY_GAME;
	}

	m_packetManager = PacketManager::getInstance();

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_map = new Map();
	m_block = new Block();
	m_result = new Result();

	SoundSystem::getInstance()->StopBGM();
	SoundSystem::getInstance()->StartBGM(GAME_BGM);
}

void VersusPalySystem::Update()
{
	SoundSystem::getInstance()->pSystem->update();

	m_socketManager->Communication();
	CheckPacket();

	if (m_resourceManager->m_curGameStep == GAME_STEP::STEP_VERSUS_PLAY)
	{
		if (m_result->m_win || m_result->m_lose)
		{
			m_result->Update();
		}
		else
		{
			if (!m_map->IsClearLines())
			{
				m_block->Update();
			}

			m_map->Update();
		}
	}
}

void VersusPalySystem::CheckPacket()
{
	if (m_socketManager->m_userState == USER_STATE::CLOSE_CONNECT)
	{
		m_resourceManager->m_curGameStep = GAME_STEP::STEP_MENU;
	}

	if (m_socketManager->m_userState == USER_STATE::USER_PLAY_GAME)
	{
		switch (m_packetManager->m_2P_PlayGameData->userReq)
		{
		case USER_PLAY::PLAY_LOSE:
			m_result->m_lose = true;
			m_socketManager->m_userState = USER_STATE::USER_RESULT;
			break;
		case USER_PLAY::PLAY_WIN:
			m_result->m_win = true;
			m_socketManager->m_userState = USER_STATE::USER_RESULT;
			break;
		}
	}
	else if (m_socketManager->m_userState == USER_STATE::USER_RESULT)
	{
		if (m_packetManager->m_1P_PlayGameData->userReq == USER_PLAY::RESULT_BACK_ROOM)
		{
			m_resourceManager->m_curGameStep = GAME_STEP::STEP_ROOM;
		}
	}

	m_packetManager->m_1P_PlayGameData->userReq = USER_PLAY::PLAY_IDLE;
}

void VersusPalySystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	// Block
	for (auto i : m_resourceManager->m_block.blocks)
	{
		WriteBuffer(i.xPos + m_resourceManager->m_block.xPos, i.yPos + m_resourceManager->m_block.yPos, i.strText, i.textColor);
	}

	// Next Block
	for (auto i : m_resourceManager->m_nextBlock.blocks)
	{
		WriteBuffer(i.xPos + m_resourceManager->m_nextBlock.xPos, i.yPos + m_resourceManager->m_nextBlock.yPos, i.strText, i.textColor);
	}

	// Map
	for (auto i : m_resourceManager->m_map)
	{
		if (i->strText != "  ")
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}

	// 상대 플레이어
	for (auto i : m_packetManager->m_2PBlockList)
	{
		WriteBuffer(i->xPos + VERSUS_XPOS, i->yPos, "■", i->textColor);
	}

	// 결과
	if (m_result->m_win)
	{
		for (auto i : m_resourceManager->m_sprite[VERSUS_WIN]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}
	else if(m_result->m_lose)
	{
		for (auto i : m_resourceManager->m_sprite[VERSUS_LOSE]->textInfo)
		{
			WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
		}
	}
}

void VersusPalySystem::Release()
{
	m_resourceManager->ReleaseData(STEP_VERSUS_PLAY);
	SafeDelete(m_block);
	SafeDelete(m_map);
	SafeDelete(m_result);

	if (m_resourceManager->m_curGameStep == STEP_MENU)
	{
		SocketManager::getInstance()->CleanSocket();
		SafeDelete(m_socketManager);
	}
}