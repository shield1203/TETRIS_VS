#include "stdafx.h"
#include "Block.h"

#include "ResourceManager.h"
#include "InputSystem.h"

Block::Block()
{
	m_resourceManager = ResourceManager::getInstance();
	m_inputSystem = new InputSystem();
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
	m_resourceManager->m_block.blockShape = rand() % BLOCK_SHAPE;
	m_resourceManager->m_block.blockType = 0;
	m_resourceManager->m_block.xPos = BLOCK_START_X;
	m_resourceManager->m_block.yPos = BLOCK_START_Y;
	COLOR randomColor = static_cast<COLOR>(rand() % WHITE);

	int num = 0;
	for (auto& i : m_resourceManager->m_block.blocks)
	{
		i.strText = "бс";
		i.xPos = m_Block[m_resourceManager->m_block.blockShape][m_resourceManager->m_block.blockType][num][0];
		i.yPos = m_Block[m_resourceManager->m_block.blockShape][m_resourceManager->m_block.blockType][num][1];
		i.textColor = randomColor;
		num++;
	}
}

void Block::MoveLeft()
{
	for (auto i : m_resourceManager->m_block.blocks)
	{
		if (i.xPos + m_resourceManager->m_block.xPos <= 2)
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
}

void Block::MoveRight()
{
	for (auto i : m_resourceManager->m_block.blocks)
	{
		if (i.xPos + m_resourceManager->m_block.xPos >= 20)
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
}

void Block::MoveDown()
{

}

bool Block::CollisionCheck()
{
	for (auto i : m_resourceManager->m_map)
	{
		if (1)
		{
			return true;
		}
	}

	return false;
}