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
	LoadGameData();
}

ResourceManager::~ResourceManager()
{
	ReleaseData();
}

void ResourceManager::LoadGameData()
{
	LoadMenuData();
	LoadSinglePlayData();
	LoadSingleResultData();
}

void ResourceManager::LoadMenuData()
{
	TiXmlDocument doc;
	doc.LoadFile("ResourceData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Resource");
	if (!pRoot) return;

	TiXmlElement* pElem = nullptr;
	TiXmlElement* pSubElem = nullptr;
	TiXmlAttribute* pAttrib = nullptr;

	// Menu /////////////////////////////////////////////////////////

	pElem = pRoot->FirstChildElement("MenuSystem")->FirstChildElement("BackgroundData");
	pAttrib = pElem->FirstAttribute();

	m_menuBackground.consoleSize.X = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	m_menuBackground.consoleSize.Y = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	m_menuBackground.sizeCommend = pAttrib->Value();

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
		m_menuBackground.textInfo.push_back(addInfo);

		pSubElem = pSubElem->NextSiblingElement();
	}

	pElem = pRoot->FirstChildElement("MenuSystem")->FirstChildElement("SpriteData");
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

void ResourceManager::LoadSinglePlayData()
{

}

void ResourceManager::LoadSingleResultData()
{

}

void ResourceManager::ReleaseData()
{
	// Menu /////////////////////////////////////

	for (auto i : m_menuBackground.textInfo)
	{
		SafeDelete(i);
	}
	m_menuBackground.textInfo.clear();

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

	// Single Play ///////////////////////////////

}