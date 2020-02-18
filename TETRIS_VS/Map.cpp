#include "stdafx.h"
#include "Map.h"

#include "ResourceManager.h"
#include "SoundSystem.h"

Map::Map()
{
	m_resourceManager = ResourceManager::getInstance();

	m_resourceManager->InitMap();

	m_LineclearSpeed = MAP_LINE_CLEAR_SPEED;
	m_blockCount.resize(MAP_HIGH, 0);
	nblinkCount = BLINK_LINE_COUNT;
}

Map::~Map()
{
}

void Map::Update()
{
	if (!bClearLines)
	{
		CheckLines();
	}

	if (bClearLines) 
	{
		ClearLines();
	}
}

void Map::CheckLines()
{
	// ��� ī��Ʈ �ʱ�ȭ
	for (auto& i : m_blockCount)
	{
		i = 0;
	}

	for (auto i : m_resourceManager->m_map)
	{
		if (i->strText == "��")
		{
			m_blockCount[i->yPos]++;
		}
	}

	for (auto i : m_blockCount)
	{
		if (i == MAP_WIDTH)
		{
			bClearLines = true;
			nblinkCount = BLINK_LINE_COUNT;

			break;
		}
	}

	// ���ӿ��� �˻�
	if (m_blockCount[OVER_LINE])
	{
		m_resourceManager->m_curGameStep = STEP_GAMEOVER;
	}
}

void Map::ClearLines()
{
	// ���� ������
	if (GetTickCount64() - m_time > m_LineclearSpeed)
	{
		m_time = GetTickCount64();
		nblinkCount--;

		for (auto i : m_resourceManager->m_map)
		{
			if (m_blockCount[i->yPos] == MAP_WIDTH)
			{
				if (i->textColor != DARK)
				{
					i->textColor = DARK;
				}
				else
				{
					i->textColor = GRAY;
				}
			}
		}
	}

	// ��� ����, ����
	if (!nblinkCount)
	{
		// ��� ����
		for (auto i = m_resourceManager->m_map.begin(); i != m_resourceManager->m_map.end();)
		{
			if (m_blockCount[(*i)->yPos] == MAP_WIDTH)
			{
				i = m_resourceManager->m_map.erase(i++);
			}
			else
			{
				i++;
			}
		}

		// ���� ����
		for (auto i : m_blockCount)
		{
			if (i == MAP_WIDTH)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					TextInfo* mapBlock = new TextInfo;

					mapBlock->strText = "  ";

					m_resourceManager->m_map.push_front(mapBlock);
				}
			}
		}

		// ��ǥ �缳��
		auto iter = m_resourceManager->m_map.begin();
		for (int i = 0; i < MAP_HIGH; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				(*iter)->xPos = (2 * (j + 1));
				(*iter)->yPos = i;

				iter++;
			}
		}

		bClearLines = false;

		SoundSystem::getInstance()->StartEffect(SOUND_CLEAR_LINE);
	}


}

bool Map::IsClearLines()
{
	return bClearLines;
}