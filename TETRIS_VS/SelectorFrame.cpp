#include "stdafx.h"
#include "SelectorFrame.h"

SelectorFrame::SelectorFrame()
{
}

SelectorFrame::~SelectorFrame()
{
	SafeDelete(m_inputSystem);
}