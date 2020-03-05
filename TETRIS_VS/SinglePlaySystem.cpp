#include "stdafx.h"
#include "SystemFrame.h"
#include "SinglePlaySystem.h"

#include "ResourceManager.h"
#include "SoundSystem.h"

#include "Map.h"
#include "Block.h"

SinglePlaySystem::SinglePlaySystem()
{
}

SinglePlaySystem::~SinglePlaySystem()
{
}

void SinglePlaySystem::Init()
{
	m_resourceManager = ResourceManager::getInstance();
	m_resourceManager->LoadGameData(STEP_SINGLE_PLAY);

	m_consoleSize = m_resourceManager->m_background.consoleSize;
	m_sizeCommend = m_resourceManager->m_background.sizeCommend;

	FlippingSTDBuffer();
	system(m_sizeCommend.c_str());

	CreateBuffer(m_consoleSize);

	m_map = new Map();
	m_block = new Block();

	SoundSystem::getInstance()->StopBGM();
	SoundSystem::getInstance()->StartBGM(GAME_BGM);
}

void SinglePlaySystem::Update()
{
	SoundSystem::getInstance()->pSystem->update();

	if (!m_map->IsClearLines())
	{
		m_block->Update();
	}

	m_map->Update();
}

void SinglePlaySystem::Render()
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
}

void SinglePlaySystem::Release()
{
	m_resourceManager->ReleaseData(STEP_SINGLE_PLAY);
	SafeDelete(m_block);
	SafeDelete(m_map);
}