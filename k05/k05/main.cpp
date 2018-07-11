#pragma warning (disable:4996)
#define _MAIN_MODULE

#include <time.h>
#include "DblBuffer.h"
#include "conioex.h"

//**********************************************************************
//	定体定義
//**********************************************************************
#define  PI			3.1415926f			//	円周率
#define  CON_WIDTH	(SCREEN_SIZE_X)		//	コンソール幅
#define  CON_HEIGHT (SCREEN_SIZE_Y/2)	//	コンソール高さ

#define  AIR_REGIST 0.95f				//	空気抵抗値
#define  GRAVITY	0.3					//	落下速度
#define  MIN_LIFE_CNT (100)			//	最短生存期間
#define  RAND_LIFE_CNT 10				//	生存期間乱数分
#define  EXP_SPEED	5.5f

#define  MAX_FIREWORKS 60				//　粒子の数
#define  MAX_TREE 128

#define  POSX		(CON_WIDTH/2)		//	パーティクル発生位置X座標
#define  POSY		(CON_HEIGHT/2)		//	パーティクル発生位置Y座標
//**********************************************************************
//	構造体定義
//**********************************************************************
typedef struct _TFirework
{
	int bAvctive;
	float fPosX, fPosY;		  //	現在座標
	float fDirection;		  //	移動方向
	float angle;
	float fVx, fVy;				
	int nLifeCnt;			  //	生存期間
}TFIREWORK;

typedef struct TagFractalTree
{
	int bAvctive;
	int level;
	float fPosX, fPosY;		  //	現在座標
	float fDirection;		  //	移動方向
	float fVx, fVy;
	float angle;
	int fStart, fEnd;
	int nLifeCnt;			  //	生存期間
}FractalTree;
//**********************************************************************
//	グローバル変数
//**********************************************************************
//	パーティクル用構造体変数
TFIREWORK g_fireworks[MAX_FIREWORKS];
TFIREWORK g_fireworks1[MAX_FIREWORKS*3];
TFIREWORK g_snow[MAX_FIREWORKS];
FractalTree g_tree[MAX_TREE];
int g_nTimeCount = 0;
int g_fireCnt = 0;

//**********************************************************************
//	プロトタイプ宣言
//**********************************************************************
int Init(int);
int InitFire(int);
int InitTree(int);
int InitSnow(int);
void Draw(int,int,int);
int Move(void);
float FractalBinaryTree(int, int, float);
//**********************************************************************
//	プログラム
//**********************************************************************
int main()
{
	DblBufferObject()->CreatHandle();
	//	画面初期化
	CLS();							//	画面クリア
	CUROFF();						//	カーソル非表示

	//	初期値設定
	srand((unsigned)time(NULL));	//	乱数初期化
	int nColor = Init(0);			//	各パーティクルを初期化
	int fColor = InitFire(g_fireCnt);
	int tColor = InitTree(0);
	InitSnow(0);
	int cnt = 0;
	//	メインループ
	while (1)
	{
		//CLS();						//	画面クリア
		DblBufferObject()->ClearScreen(BLACK);

		if (!Move())
		{
			g_fireCnt++;
			if (g_fireCnt==3)
			{
				g_fireCnt = 0;
			}
			fColor = InitFire(g_fireCnt);
		}
	    Draw(nColor,fColor, tColor);
		if ((g_nTimeCount % 2) == 0) {
			for (int i = 0; i < MAX_FIREWORKS; i++) {
				if (g_fireworks[i].bAvctive == false) {
					if (i == 0)
					{
						nColor = Init(i);
					}
					else
					{
						Init(i);
					}
					break;
				}
			}
			for (int i = 0; i < MAX_FIREWORKS; i++) {
				if (g_snow[i].bAvctive == false) {
					InitSnow(i);
					break;
				}
			}
			for (int i = 0; i < MAX_TREE; i++) {
				if (g_tree[i].bAvctive == false) {
					if (i == 0)
					{
						tColor = InitTree(i);
					}
					else
					{
						InitTree(i);
					}
					break;
				}
			}
		}
		g_nTimeCount++;
		
		if (kbhit())
		{
			if (getch()==0x1b)		//	ESCキーで終了
				break;
		}
		DblBufferObject()->Swap();
		cnt++;
		//WAIT(20);
	}
	//	画面の復帰
	LOCATE(1, 24);	//	カーソル位置を設定
	//COLOR(WHITE);
	CURON();
	DblBufferObject()->Close();
	return EXIT_SUCCESS;
}

//======================================================================
//	パーティクルの初期化
//　引数:i	配列のインデクス
//	戻り値:表示色(番号)
//======================================================================
int Init(int i)
{
	float fposX = POSX;
	float fposY = CON_HEIGHT - 10;
	float fRand_r, fRand_t;
	g_fireworks[i].fPosX = fposX;
	g_fireworks[i].fPosY = fposY;
	g_fireworks[i].bAvctive = true;
	fRand_r = sqrtf(-2.0f * logf((float)(rand() + 1) / (RAND_MAX + 1)));
	fRand_t = 2.0f * PI * (float)rand() / RAND_MAX;
	g_fireworks[i].fVx = (fRand_r * cosf(fRand_t)) * 3;
	g_fireworks[i].fVy = (fRand_r * sinf(fRand_t)) - 9;
	g_fireworks[i].nLifeCnt = MIN_LIFE_CNT;

	return rand() % 6 + 9;
}

//======================================================================
//	パーティクルの初期化
//　引数:n	回数
//	戻り値:表示色(番号)
//======================================================================
int InitFire(int n)
{
	float fposX = POSX;
	float fposY = CON_HEIGHT - 10;
	float fRand_r, fRand_t;
	for (int i = MAX_FIREWORKS*n; i < MAX_FIREWORKS*(n + 1); i++)
	{
		g_fireworks1[i].fPosX = fposX;
		g_fireworks1[i].fPosY = fposY;
		g_fireworks1[i].bAvctive = true;
		fRand_r = sqrtf(-2.0f * logf((float)(rand() + 1) / (RAND_MAX + 1)));
		fRand_t = 2.0f * PI * (float)rand() / RAND_MAX;
		g_fireworks1[i].fVx = (fRand_r * cosf(fRand_t)) * 3;
		g_fireworks1[i].fVy = (fRand_r * sinf(fRand_t)) - 8;
		g_fireworks1[i].nLifeCnt = MIN_LIFE_CNT;

	}
	return rand() % 6 + 9;
}

//======================================================================
//	パーティクルの初期化
//　引数:i	配列のインデクス
//	戻り値:表示色(番号)
//======================================================================
int InitTree(int i)
{
	float fposX = POSX;
	float fposY = CON_HEIGHT - 10;
	g_tree[i].level = 0;
	g_tree[i].fPosX = fposX;
	g_tree[i].fPosY = fposY;
	g_tree[i].nLifeCnt = MIN_LIFE_CNT * 3;
	g_tree[i].fStart = 0;
	g_tree[i].fEnd = 64;
	g_tree[i].angle = 90;
	g_tree[i].fDirection = g_tree[i].angle*PI / 180;
	g_tree[i].fVx = cos(g_tree[i].fDirection) * 2;
	g_tree[i].fVy = sin(g_tree[i].fDirection);
	g_tree[i].bAvctive = true;
	return rand() % 6 + 9;
}

int InitSnow(int i)
{
	float fRand_r, fRand_t;
	g_snow[i].fPosX = rand() % (CON_WIDTH-3) + 3;
	
	g_snow[i].fPosY = 0 - rand() % 10;
	g_snow[i].bAvctive = true;
	g_snow[i].angle = 0;
	g_snow[i].fDirection = g_snow[i].angle*PI / 180;
	g_snow[i].fVx = cosf(g_snow[i].fDirection) * 1.5;
	g_snow[i].fVy = 1;
	g_snow[i].nLifeCnt = MIN_LIFE_CNT-10;

	return 15;
}

//======================================================================
//	パーティクルの描画
//　引数:nColor　fColor 　tColor　表示色(０～１５)
//	戻り値:なし
//======================================================================
void Draw(int nColor,int fColor,int tColor)
{
	
	int nPosX, nPoxY, oPosX, oPosY;
	
	//	無限発射
	for (int i = 0; i < MAX_FIREWORKS; i++)
	{
		nPosX = (int)g_fireworks[i].fPosX;
		nPoxY = (int)g_fireworks[i].fPosY;
	
		if (nPosX < 1 || nPosX >= CON_WIDTH-1 || nPoxY < 0 || nPoxY >= CON_HEIGHT-1)
		{
			continue;
		}
		DblBufferObject()->SetColor(nColor, BLACK);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("M");
		DblBufferObject()->SetCursorPos(nPosX-1, nPoxY+1);
		DblBufferObject()->Write("MMM");
		
	}

	//	二分木
	for (int i = 0; i < MAX_TREE; i++)
	{
		nPosX = (int)g_tree[i].fPosX;
		nPoxY = (int)g_tree[i].fPosY;

		if (nPosX < 0 || nPosX >= CON_WIDTH || nPoxY < 0 || nPoxY >= CON_HEIGHT)
		{
			continue;
		}
		DblBufferObject()->SetColor(tColor, tColor);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("  ");
	}

	//	爆弾
	for (int i = 0; i < MAX_FIREWORKS*(g_fireCnt+1); i++)
	{
		nPosX = (int)g_fireworks1[i].fPosX;
		nPoxY = (int)g_fireworks1[i].fPosY;

		if (nPosX < 0 || nPosX >= CON_WIDTH || nPoxY < 0 || nPoxY >= CON_HEIGHT)
		{
			continue;
		}
		DblBufferObject()->SetColor(fColor, BLACK);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("-oOMOo-");
	}

	//	雪
	for (int i = 0; i < MAX_FIREWORKS; i++)
	{
		nPosX = (int)g_snow[i].fPosX;
		nPoxY = (int)g_snow[i].fPosY;


		if (nPosX < 0 || nPosX >= CON_WIDTH - 1 || nPoxY < 0 || nPoxY >= CON_HEIGHT - 2)
		{
			continue;
		}
		DblBufferObject()->SetColor(WHITE, BLACK);
		DblBufferObject()->SetCursorPos(nPosX, nPoxY);
		DblBufferObject()->Write("*");
		DblBufferObject()->SetCursorPos(nPosX - 1, nPoxY + 1);
		DblBufferObject()->Write("* *");
		DblBufferObject()->SetCursorPos(nPosX, nPoxY + 2);
		DblBufferObject()->Write("*");

	}
}

//======================================================================
//	パーティクルの移動処理
//　引数:なし
//	戻り値:生存しているパーティクルの数
//======================================================================
int Move()
{
	int nLife = MAX_FIREWORKS;
	for (int i = 0; i < MAX_FIREWORKS; i++)
	{
		////////////////////////////////////	
		if (g_fireworks[i].bAvctive)
		{
			if (g_fireworks[i].fVy < 3)
			{
				g_fireworks[i].fPosX += g_fireworks[i].fVx;
				g_fireworks[i].fPosY += g_fireworks[i].fVy;
				g_fireworks[i].fVy += GRAVITY;
			}
			g_fireworks[i].nLifeCnt--;
			if (g_fireworks[i].nLifeCnt == 0)
			{
				g_fireworks[i].bAvctive = false;

			}
		}
		/////////////////////////////////////
		if (g_snow[i].bAvctive)
		{
			g_snow[i].angle += 10;
			g_snow[i].fPosX += cosf(g_snow[i].angle*PI / 180) * 1.5;
				g_snow[i].fPosY += g_snow[i].fVy;
				//g_snow[i].fVy += GRAVITY;
			g_snow[i].nLifeCnt--;
			if (g_snow[i].nLifeCnt == 0)
			{
				g_snow[i].bAvctive = false;

			}
		}
	}
	for (int i = 0; i < MAX_TREE; i++)
	{
		////////////////////////////////////
		if (g_tree[i].bAvctive)
		{
			if (g_tree[i].fStart == g_tree[i].fEnd)
			{
				g_tree[i].fEnd = g_tree[i].fEnd / 2;
				g_tree[i].fStart = 0;
				g_tree[i].level++;
				g_tree[i].angle = FractalBinaryTree(i, g_tree[i].level, g_tree[i].angle);
				g_tree[i].fDirection = g_tree[i].angle*PI / 180;
				g_tree[i].fVx = cos(g_tree[i].fDirection)*2;
				g_tree[i].fVy = sin(g_tree[i].fDirection);
			}
			g_tree[i].fPosX -= g_tree[i].fVx;
			g_tree[i].fPosY -= g_tree[i].fVy;
			g_tree[i].fStart++;

			g_tree[i].nLifeCnt--;
			if (g_tree[i].nLifeCnt == 0)
			{
				g_tree[i].bAvctive = false;

			}
		}
	}
	for (int i = MAX_FIREWORKS*g_fireCnt; i < MAX_FIREWORKS*(g_fireCnt + 1); i++)
	{
		////////////////////////////////////	
		if (!g_fireworks1[i].nLifeCnt)
		{
			nLife--;
			continue;
		}
		if (g_fireworks1[i].fVy < 2)
		{

			g_fireworks1[i].fPosX += g_fireworks1[i].fVx;
			g_fireworks1[i].fPosY += g_fireworks1[i].fVy;
			g_fireworks1[i].fVy += GRAVITY;
		}
		g_fireworks1[i].nLifeCnt--;
	}
	return nLife > 0;
}

//======================================================================
//	二分木
//　引数:n		粒子のインデクス
//		 lv		深さ
//		 angle　角度
//	戻り値:次の角度
//======================================================================
float FractalBinaryTree(int n, int lv,float angle)
{
	//	分ける
	int tmpi = n &(1 << lv - 1);
	if (tmpi==0)
	{
		angle -= 45;
	}
	else
	{ 
		angle += 45;
	}
	return angle;
}

