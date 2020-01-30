#include "stdafx.h"
#include "SystemFrame.h"
#include "SinglePlaySystem.h"

#include "ResourceManager.h"
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

	m_block = new Block();
}

void SinglePlaySystem::Update()
{
	m_block->Update();
}

void SinglePlaySystem::Render()
{
	// Background
	for (auto i : m_resourceManager->m_background.textInfo)
	{
		WriteBuffer(i->xPos, i->yPos, i->strText, i->textColor);
	}

	for (auto i : m_resourceManager->m_block.blocks)
	{
		WriteBuffer(i.xPos + m_resourceManager->m_block.xPos, i.yPos + m_resourceManager->m_block.yPos, i.strText, i.textColor);
	}
}

void SinglePlaySystem::Release()
{
	m_resourceManager->ReleaseData(STEP_SINGLE_PLAY);
}