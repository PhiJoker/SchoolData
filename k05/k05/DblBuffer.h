#ifndef _DBLBUFFER_H
#define _DBLBUFFER_H
#pragma once
//=============================================
//	C言語　ダブルバッファ(DoubleBuffer)
//  コンソールサイズは 160px * 100px
//　フォントサイズは18、1文字は 9px * 18px
//
//	OH_AT51A715_09_彭 海涛(ホウ	カイトウ)
//								2017-11-01
//	SuperDoubleBuffer		
//	画面解像度を固定した！！！
//								2017-11-17	
//=============================================
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

//	マクロの定義
//	Windowsサイズ
#define SCREEN_SIZE_X 400
#define SCREEN_SIZE_Y 320
 
enum COLORSC {
	BLACK = 0,			//	黒		
	BLUE = 1,			//	濃い青	
	GREEN = 2,			//	緑		
	CYAN = 3, 			//	青緑		
	RED = 4,			//	濃い赤	
	MAGENTA = 5,		//	紫		
	BROWN = 6,			//	濃い黄	
	LIGHTGRAY = 7,		//	25%灰色	
	GRAY = 8,			//	50%灰色	
	LIGHTBLUE = 9,		//	青		
	LIGHTGREEN = 10,	//	明るい緑	
	LIGHTCYAN = 11,		//	水色		
	LIGHTRED = 12,		//	 赤		
	LIGHTMAGENTA = 13,	//	マゼンタ	
	YELLOW = 14,		//	黄	
	WHITE = 15,			//	白		
	INTENSITY = 0x08,	//	高輝度マスク
	RED_MASK = 0x04,
	GREEN_MASK = 0x02,
	BLUE_MASK = 0x01,
};
//	ダブルバッファの構造体
typedef struct tagDblBuffer
{
	void(*CreatHandle)();
	void(*Close)();

	void(*SetColor)(int, int);
	void(*SetCursorPos)(int, int);
	void(*Write)(const char *);
	void(*ClearScreen)(int);
	void(*Swap)();
	HANDLE(*GetHandle)();
}*DblBuffer;

DblBuffer DblBufferObject();
  
#endif // _DBLBUFFER_H