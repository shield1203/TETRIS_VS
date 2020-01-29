#pragma once

// SafeDelete
template<typename T>
static void SafeDelete(T*& p)
{
	if (p == nullptr) return;

	delete p;
	p = nullptr;
}

template<typename T>
static void SageDelete_Array(T*& p)
{
	if (p == nullptr) return;

	delete[] p;
	p = nullptr;
}

// Double Buffering
static void CreateBuffer(COORD size)
{
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = size.X - 1;
	rect.Top = 0;
	rect.Bottom = size.Y - 1;

	if (g_screenBuffer[0] != nullptr)
	{
		CloseHandle(g_screenBuffer[0]);
		g_screenBuffer[0] = nullptr;
	}

	if (g_screenBuffer[1] != nullptr)
	{
		CloseHandle(g_screenBuffer[1]);
		g_screenBuffer[1] = nullptr;
	}

	g_screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

static void WriteBuffer(short xPos, short yPos, string str, unsigned short text = WHITE, unsigned short back = DARK)
{
	DWORD dw;
	COORD cursorPosition = { xPos, yPos };
	SetConsoleTextAttribute(g_screenBuffer[g_bufferIndex], text | (back << 4));
	SetConsoleCursorPosition(g_screenBuffer[g_bufferIndex], cursorPosition);
	WriteFile(g_screenBuffer[g_bufferIndex], str.c_str(), str.size(), &dw, NULL);
}

static void FlippingBuffer()
{
	SetConsoleActiveScreenBuffer(g_screenBuffer[g_bufferIndex]);
	g_bufferIndex = !g_bufferIndex;
}

static void ClearBuffer(COORD size)
{
	COORD coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_screenBuffer[g_bufferIndex], ' ', size.X * size.Y, coor, &dw);
}