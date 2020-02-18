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

	for (int i = 0; i < 2; i++)
	{
		if (g_screenBuffer[i] != nullptr)
		{
			CloseHandle(g_screenBuffer[i]);
			g_screenBuffer[i] = nullptr;
		}
		g_screenBuffer[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	}
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

static void FlippingSTDBuffer()
{
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}

static void ClearBuffer(COORD size)
{
	COORD coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_screenBuffer[g_bufferIndex], ' ', size.X * size.Y, coor, &dw);
}