#include "stdafx.h"
#include "ResourceManager.h"
#include "tinyxml.h"

ResourceManager* ResourceManager::Inst = nullptr;

ResourceManager* ResourceManager::getInstance()
{
	if (Inst == nullptr) {
		Inst = new ResourceManager();
	}

	return Inst;
}

ResourceManager::ResourceManager()
{
	m_curGameStep = STEP_MENU;
	m_block.blocks.resize(4);
}

ResourceManager::~ResourceManager()
{
	ReleaseData(m_curGameStep);
}

void ResourceManager::LoadGameData(GAME_STEP curGameStep)
{
	LoadBackgroundData(curGameStep);
	LoadSpriteData(curGameStep);
}

void ResourceManager::LoadBackgroundData(GAME_STEP gameStep)
{
	string strElemnt;

	switch (gameStep)
	{
	case STEP_MENU:
		strElemnt = "MenuSystem";
		break;
	case STEP_SINGLE_PLAY:
		strElemnt = "SinglePlaySystem";
		break;
	}

	TiXmlDocument doc;
	doc.LoadFile("ResourceData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Resource");
	if (!pRoot) return;

	TiXmlElement* pElem = nullptr;
	TiXmlElement* pSubElem = nullptr;
	TiXmlAttribute* pAttrib = nullptr;

	pElem = pRoot->FirstChildElement(strElemnt.c_str())->FirstChildElement("BackgroundData");
	pAttrib = pElem->FirstAttribute();

	m_background.consoleSize.X = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	m_background.consoleSize.Y = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	m_background.sizeCommend = pAttrib->Value();

	pSubElem = pElem->FirstChildElement("TextInfo");
	while (pSubElem != nullptr)
	{
		pAttrib = pSubElem->FirstAttribute();

		TextInfo* addInfo = new TextInfo();

		addInfo->xPos = pAttrib->IntValue();
		pAttrib = pAttrib->Next();

		addInfo->yPos = pAttrib->IntValue();
		pAttrib = pAttrib->Next();

		addInfo->textColor = static_cast<COLOR>(pAttrib->IntValue());
		pAttrib = pAttrib->Next();

		addInfo->strText = pSubElem->GetText();
		m_background.textInfo.push_back(addInfo);

		pSubElem = pSubElem->NextSiblingElement();
	}
}

void ResourceManager::LoadSpriteData(GAME_STEP gameStep)
{
	string strElemnt;

	switch (gameStep)
	{
	case STEP_MENU:
		strElemnt = "MenuSystem";
		break;
	case STEP_SINGLE_PLAY:
		InitMap();
		return;
		//strElemnt = "SinglePlaySystem";
		break;
	}

	TiXmlDocument doc;
	doc.LoadFile("ResourceData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Resource");
	if (!pRoot) return;

	TiXmlElement* pElem = nullptr;
	TiXmlElement* pSubElem = nullptr;
	TiXmlAttribute* pAttrib = nullptr;

	pElem = pRoot->FirstChildElement(strElemnt.c_str())->FirstChildElement("SpriteData");
	while (pElem != nullptr)
	{
		pSubElem = pElem->FirstChildElement("TextInfo");

		Sprite* addSprite = new Sprite();

		while (pSubElem != nullptr)
		{
			pAttrib = pSubElem->FirstAttribute();

			TextInfo* addTextInfo = new TextInfo();

			addTextInfo->xPos = pAttrib->IntValue();
			pAttrib = pAttrib->Next();

			addTextInfo->yPos = pAttrib->IntValue();
			pAttrib = pAttrib->Next();

			addTextInfo->textColor = static_cast<COLOR>(pAttrib->IntValue());
			pAttrib = pAttrib->Next();

			addTextInfo->strText = pSubElem->GetText();

			addSprite->textInfo.push_back(addTextInfo);

			pSubElem = pSubElem->NextSiblingElement();
		}

		m_menuSprite.push_back(addSprite);

		pElem = pElem->NextSiblingElement();
	}
}

void ResourceManager::InitMap()
{
	for (int i = 0; i < MAP_HIGH; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			TextInfo* mapBlock = new TextInfo;

			mapBlock->strText = "  ";
			mapBlock->xPos = (2 * (j+1));
			mapBlock->yPos = i;
		}
	}
}

void ResourceManager::ReleaseData(GAME_STEP prevGameStep)
{
	for (auto i : m_background.textInfo)
	{
		SafeDelete(i);
	}
	m_background.textInfo.clear();

	switch (prevGameStep)
	{
	case STEP_MENU:
		// Menu /////////////////////////////////////

		for (auto i : m_menuSprite)
		{
			for (auto j : i->textInfo)
			{
				SafeDelete(j);
			}
			i->textInfo.clear();
			SafeDelete(i);
		}
		m_menuSprite.clear();
		break;
	case STEP_SINGLE_PLAY:
		// Single Play ///////////////////////////////
		
		for (auto i : m_map)
		{
			SafeDelete(i);
		}
		m_map.clear();
		break;
	case STEP_SINGLE_RESULT:
		// Single Play Result

		break;
	}
}