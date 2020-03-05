#include "stdafx.h"
#include "Result.h"

#include "PacketManager.h"
#include "InputSystem.h"

Result::Result()
{
	m_packetManager = PacketManager::getInstance();
	m_inputSystem = new InputSystem();
}

Result::~Result()
{
	SafeDelete(m_inputSystem);
}

void Result::Update()
{
	m_inputSystem->CheckKeyboardPressed();

	if (m_inputSystem->IsEnterPressed())
	{
		BackRoom();
	}
}

void Result::BackRoom()
{
	if (m_win || m_lose)
	{
		m_packetManager->m_1P_PlayGameData->userReq = USER_PLAY::RESULT_BACK_ROOM;
	}
}