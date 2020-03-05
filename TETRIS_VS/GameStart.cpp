#include "stdafx.h"
#include "GameSystem.h"

HANDLE g_screenBuffer[2] = { nullptr, nullptr };
short g_bufferIndex = 0;

int main()
{
	system("title KJH's TETRIS");

	GameSystem* pGameSystem = new GameSystem();

	pGameSystem->Process();

	SafeDelete(pGameSystem);

	exit(1);
}