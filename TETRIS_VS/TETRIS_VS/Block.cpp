#include "stdafx.h"
#include "Block.h"

#include "ResourceManager.h"
#include "SoundSystem.h"
#include "InputSystem.h"

Block::Block()
{
	m_resourceManager = ResourceManager::getInstance();
	m_inputSystem = new InputSystem();

	m_blockSpeed = INIT_SPEED;

	srand((unsigned)time(NULL));
	m_resourceManager->m_nextBlock.blockShape = rand() % BLOCK_SHAPE;
	m_resourceManager->m_nextBlock.xPos = NEXT_BLOCK_X;
	m_resourceManager->m_nextBlock.yPos = NEXT_BLOCK_Y;
}

Block::~Block()
{
	SafeDelete(m_inputSystem);
}

void Block::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (bBlock)
	{
		// 블록 이동, 회전
		if (m_inputSystem->IsLeftArrowPressed())
		{
			MoveLeft();
		}

		if (m_inputSystem->IsRightArrowPressed())
		{
			MoveRight();
		}

		if (m_inputSystem->IsDownArrowPressed())
		{
			MoveDown();

			SoundSystem::getInstance()->StartEffect(SOUND_BLOCK);
		}

		if (m_inputSystem->IsUpArrowPressed())
		{
			TurnBlock();
		}

		// 블록 드랍
		if (m_inputSystem->IsSpacebarPressed())
		{
			MoveStraightDwon();
		}

		// 일정 스피드로 내려오는 블록
		if (GetTickCount64() - m_time > m_blockSpeed)
		{
			m_time = GetTickCount64();

			MoveDown();
		}
	}
	else {
		CreateBlock();
	}
}

void Block::CreateBlock()
{
	bBlock = true;

	srand((unsigned)time(NULL));
	m_resourceManager->m_block.blockShape = m_resourceManager->m_nextBlock.blockShape;
	m_resourceManager->m_block.blockType = 0;
	m_resourceManager->m_block.xPos = BLOCK_START_X;
	m_resourceManager->m_block.yPos = BLOCK_START_Y;
	COLOR randomColor = static_cast<COLOR>((rand() % DARK_YELLOW) + BLUE);

	// 현재 블록
	int num = 0;
	for (auto& i : m_resourceManager->m_block.blocks)
	{
		i.strText = "■";
		i.xPos = m_Block[m_resourceManager->m_block.blockShape][m_resourceManager->m_block.blockType][num][0];
		i.yPos = m_Block[m_resourceManager->m_block.blockShape][m_resourceManager->m_block.blockType][num][1];
		i.textColor = randomColor;
		num++;
	}

	// 다음 블록
	m_resourceManager->m_nextBlock.blockShape = rand() % BLOCK_SHAPE;
	num = 0;
	for (auto& i : m_resourceManager->m_nextBlock.blocks)
	{
		i.strText = "■";
		i.xPos = m_Block[m_resourceManager->m_nextBlock.blockShape][0][num][0]; // x
		i.yPos = m_Block[m_resourceManager->m_nextBlock.blockShape][0][num][1]; // y
		num++;
	}
}

void Block::MoveLeft()
{
	for (auto i : m_resourceManager->m_block.blocks)
	{
		if (i.xPos + m_resourceManager->m_block.xPos -2 <= 0)
		{
			return;
		}

		for (auto j : m_resourceManager->m_map)
		{
			if (j->strText != "  " && i.xPos + m_resourceManager->m_block.xPos - 2 == j->xPos &&
				i.yPos + m_resourceManager->m_block.yPos == j->yPos)
			{
				return;
			}
		}
	}

	m_resourceManager->m_block.xPos -= 2;

	SoundSystem::getInstance()->StartEffect(SOUND_BLOCK);
}

void Block::MoveRight()
{
	for (auto i : m_resourceManager->m_block.blocks)
	{
		if (i.xPos + m_resourceManager->m_block.xPos >= MAP_WIDTH * 2)
		{
			return;
		}

		for (auto j : m_resourceManager->m_map)
		{
			if (j->strText != "  " && i.xPos + m_resourceManager->m_block.xPos + 2 == j->xPos &&
				i.yPos + m_resourceManager->m_block.yPos == j->yPos)
			{
				return;
			}
		}
	}

	m_resourceManager->m_block.xPos += 2;

	SoundSystem::getInstance()->StartEffect(SOUND_BLOCK);
}

void Block::MoveDown()
{
	for (auto i : m_resourceManager->m_block.blocks)
	{
		if (i.yPos + m_resourceManager->m_block.yPos >= MAP_HIGH - 1)
		{
			ApplyToMap();
			return;
		}

		for (auto j : m_resourceManager->m_map)
		{
			if (j->strText != "  " && i.xPos + m_resourceManager->m_block.xPos == j->xPos &&
				i.yPos + m_resourceManager->m_block.yPos + 1 == j->yPos)
			{
				ApplyToMap();
				return;
			}
		}
	}

	m_resourceManager->m_block.yPos += 1;
}

void Block::TurnBlock()
{
	unsigned int blockType = (m_resourceManager->m_block.blockType + 1) % BLOCK_TYPE;

	int num = 0;
	for (auto i : m_resourceManager->m_block.blocks)
	{
		i.xPos = m_Block[m_resourceManager->m_block.blockShape][blockType][num][0];
		i.yPos = m_Block[m_resourceManager->m_block.blockShape][blockType][num][1];

		if (i.xPos + m_resourceManager->m_block.xPos <= 0 || i.xPos + m_resourceManager->m_block.xPos > MAP_WIDTH * 2)
		{
			return;
		}

		if (i.yPos + m_resourceManager->m_block.yPos < 0 || i.yPos + m_resourceManager->m_block.yPos > MAP_HIGH - 1)
		{
			return;
		}

		for (auto j : m_resourceManager->m_map)
		{
			if (j->strText != "  " && i.xPos + m_resourceManager->m_block.xPos == j->xPos &&
				i.yPos + m_resourceManager->m_block.yPos == j->yPos)
			{
				return;
			}
		}

		num++;
	}

	num = 0;
	m_resourceManager->m_block.blockType = blockType;
	for (auto& i : m_resourceManager->m_block.blocks)
	{
		i.xPos = m_Block[m_resourceManager->m_block.blockShape][blockType][num][0];
		i.yPos = m_Block[m_resourceManager->m_block.blockShape][blockType][num][1];

		num++;
	}

	SoundSystem::getInstance()->StartEffect(SOUND_BLOCK);
}

void Block::MoveStraightDwon()
{
	while (bBlock)
	{
		MoveDown();
	}

	SoundSystem::getInstance()->StartEffect(SOUND_DROP_BLOCK);
}

void Block::ApplyToMap()
{
	for (auto i : m_resourceManager->m_map)
	{
		for (auto j : m_resourceManager->m_block.blocks)
		{
			if (i->xPos == j.xPos + m_resourceManager->m_block.xPos && 
				i->yPos == j.yPos + m_resourceManager->m_block.yPos)
			{
				i->strText = j.strText;
				i->textColor = j.textColor;
			}
		}
	}

	m_blockSpeed -= UP_SPEED;
	bBlock = false;
}