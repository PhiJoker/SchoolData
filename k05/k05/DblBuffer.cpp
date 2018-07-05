#include "DblBuffer.h"

//	フォントサイズ
#define FONT_SIZE_X 2
#define FONT_SIZE_Y 4

static DblBuffer m_dblBuffer;
static 	bool		m_swapped;
static HANDLE		m_hCons1;		//	コンソールハンドルその１
static HANDLE		m_hCons2;		//	コンソールハンドルその２
static CONSOLE_SCREEN_BUFFER_INFO  m_screenInfo;

static void _creatHandle();
static void _close();

static void _setColor(int fg, int bg);
static void _setCursorPos(int x, int y);
static void _write(const char *ptr);
static void _clearScreen(int);
static void _swap();
static HANDLE _getHandle();

DblBuffer DblBufferObject()
{
	if (!m_dblBuffer)
	{
		m_dblBuffer = (DblBuffer)malloc(sizeof(*m_dblBuffer));
		m_dblBuffer->CreatHandle = _creatHandle;
		m_dblBuffer->SetColor = _setColor;
		m_dblBuffer->SetCursorPos = _setCursorPos;
		m_dblBuffer->Write = _write;
		m_dblBuffer->ClearScreen = _clearScreen;
		m_dblBuffer->Swap = _swap;
		m_dblBuffer->Close = _close;
		m_dblBuffer->GetHandle = _getHandle;
	}
	return m_dblBuffer;
}

void _creatHandle()
{
	m_swapped = false;

	m_hCons1 = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hCons2 = GetStdHandle(STD_OUTPUT_HANDLE);

	//フォントサイズ設定( Xpx * Ypx)
	CONSOLE_FONT_INFOEX font_size = { sizeof font_size };
	font_size.dwFontSize.X = FONT_SIZE_X;
	font_size.dwFontSize.Y = FONT_SIZE_Y;
	SetCurrentConsoleFontEx(m_hCons1, 0, &font_size);
	SetCurrentConsoleFontEx(m_hCons2, 0, &font_size);

	//コンソールウインドウズサイズ設定()
	COORD win_size = { SCREEN_SIZE_X,SCREEN_SIZE_Y / 2 };
	SetConsoleScreenBufferSize(m_hCons1, win_size);
	SetConsoleScreenBufferSize(m_hCons2, win_size);
	SMALL_RECT win_sr = { 0,0,SCREEN_SIZE_X - 1,SCREEN_SIZE_Y / 2 - 1 };
	SetConsoleWindowInfo(m_hCons1, TRUE, &win_sr);
	SetConsoleWindowInfo(m_hCons2, TRUE, &win_sr);


	m_hCons1 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hCons2 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_hCons1);
	_clearScreen(BLACK);
}

void _close()
{
	CloseHandle(m_hCons1);
	CloseHandle(m_hCons2);
}

void _setColor(int fg, int bg)
{
	WORD attr = 0;
	if (fg & INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if (fg & RED_MASK)
		attr |= FOREGROUND_RED;
	if (fg & GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (fg & BLUE_MASK)
		attr |= FOREGROUND_BLUE;

	if (bg & INTENSITY)
		attr |= BACKGROUND_INTENSITY;
	if (bg & RED_MASK)
		attr |= BACKGROUND_RED;
	if (bg & GREEN_MASK)
		attr |= BACKGROUND_GREEN;
	if (bg & BLUE_MASK)
		attr |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(m_swapped ? m_hCons1 : m_hCons2, attr);
}

void _setCursorPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(m_swapped ? m_hCons1 : m_hCons2, pos);
}

void _write(const char * ptr)
{
	DWORD len = strlen(ptr);
	WriteConsoleA(m_swapped ?m_hCons1 : m_hCons2, ptr, len, &len, 0);
	//printf(ptr);
}

void _clearScreen(int col)
{
	/*for (int cnt = 0; cnt < 2; cnt++)
	{
		_setColor(col, col);
		for (int i = 0; i < SCREEN_SIZE_Y; i++)
		{
			for (int j = 0; j < SCREEN_SIZE_X / 10; j++)
			{
				_setCursorPos(j * 10, i);
				_write("                    ");
			}
		}
		_swap();
	}*/
	DWORD dwNumberOfCharsWritten;
	COORD coord = { 0,0 };
	GetConsoleScreenBufferInfo(_getHandle(), &m_screenInfo);
	FillConsoleOutputAttribute(_getHandle(),
		WHITE + (BLACK << 4),
		m_screenInfo.dwSize.X * m_screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
	);
	FillConsoleOutputCharacter(
		_getHandle(),
		' ',
		m_screenInfo.dwSize.X * m_screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
	);
}

void _swap()
{
	if ((m_swapped = !m_swapped)) {
		SetConsoleActiveScreenBuffer(m_hCons2);
	}
	else {
		SetConsoleActiveScreenBuffer(m_hCons1);
	}
}

HANDLE _getHandle()
{
	return m_swapped ? m_hCons1 : m_hCons2;
}