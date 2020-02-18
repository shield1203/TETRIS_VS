#include "stdafx.h"
#include "SystemFrame.h"

SystemFrame::SystemFrame()
{

}

SystemFrame::~SystemFrame()
{

}

void SystemFrame::GetConsoleSize(COORD& size)
{
	size = m_consoleSize;
}