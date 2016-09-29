#include "stdafx.h"
#include "My.h"
#include "resource.h"
#include "Image.h"
#include "KeyBoard.h"
#include "Jump.h"
#include "iMusic.h"

#pragma comment(lib,"MSimg32.lib")

#define MAPSIZE 3
#define WALKSIZE 12
#define STOPSIZE 12
#define GUYSIZE 30
#define FLOOR 500
#define JUMPSPEED 10
#define GRAVITY 2
#define ELEMENTSIZE 8
#define ELEMENTHEIGHT 32
#define ELEMENTWIDTH 32
#define MAPWIDTH 1024
#define MAPHEIGHT 768
#define YSTART 82
#define XSTART 23

#define NIDDLESIZE 2



RECT rect;
HDC MemDC;
HBITMAP MyBitmap, OldBitmap;
HBITMAP Map[MAPSIZE];
HBITMAP WalkPlayer[WALKSIZE];
HBITMAP mWalkPlayer[WALKSIZE];
HBITMAP StopPlayer[STOPSIZE];
HBITMAP mStopPlayer[STOPSIZE];
HBITMAP Element[ELEMENTSIZE];
HBITMAP Bullet[3];
HBITMAP Niddle[NIDDLESIZE];



extern HINSTANCE hInst;

Image img;
KeyBoard key;
Jump jum;


int tmp1 = 5;
int tmp2 = 0;
int tmp3 = 0;

int g_GuyFlag = 0;	// 0=stop 1=walk 2=jump
int g_Ani = 0;		// Animation
int g_oAni = 0;		//opening Animation
int g_stage = 0;	// game flag
int g_xPlayer = XSTART;
int g_yPlayer = YSTART;
int g_KeyUp = 0;	// Key입력 찾기
int g_mirror = 0;	//오른쪽=0, 왼쪽=1
bool JUMP = false;
int g_JumpFlag = 0;
int g_JumpSpeed = JUMPSPEED;
int g_Gravity = GRAVITY;
bool g_JUMP = true;
int g_BulletFlag = -1;
int g_xBullet[3];
int g_yBullet[3];
int g_i = -1;
int g_GaveOver = 0;

int NW = 5;
int NiddleFlag = 0;
int x_Niddle = ELEMENTWIDTH;			//1x
int y_Niddle = ELEMENTHEIGHT * 5;		//1y
int x1_Niddle = MAPWIDTH - ELEMENTWIDTH;//2x
int y1_Niddle = ELEMENTHEIGHT * 9;		//2y
int x2_Niddle = ELEMENTWIDTH;			//3x
int y2_Niddle = ELEMENTHEIGHT * 13;		//3y
int x3_Niddle = MAPWIDTH - ELEMENTWIDTH;//4x
int y3_Niddle = ELEMENTHEIGHT * 17;		//4y

int Saver_x = ELEMENTWIDTH*20;
int Saver_y = ELEMENTHEIGHT*2;
int Save_xPlayer = XSTART;
int Save_yPlayer = YSTART;
int SaveFlag = 0;
int DeathFlag = 0;


int a;
int b;
int c;
int d;
int e;
int f;



void MyCreate(HWND hWnd)
{
	SetTimer(hWnd, 1, 30, NULL);	// Player Stop Walk
	SetTimer(hWnd, 2, 500, NULL);	// operning
	SetTimer(hWnd, 3, 10, NULL);
	SetTimer(hWnd, 4, 6, NULL); //가시

	TCHAR temp[20];

	for (int i = 0; i < MAPSIZE; i++)	// Player Stop LoadImage
	{
		wsprintf(temp, TEXT("Map%d.bmp"), i);

		Map[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < 3; i++)	// Player Stop LoadImage
	{
		wsprintf(temp, TEXT("Bullet%d.bmp"), i);

		Bullet[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < ELEMENTSIZE; i++)	// Element LoadImage
	{
		wsprintf(temp, TEXT("Element%d.bmp"), i);

		Element[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < STOPSIZE; i++)	// Player Stop LoadImage
	{
		wsprintf(temp, TEXT("mStop%d.bmp"), i);

		mStopPlayer[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < STOPSIZE; i++)	// Player Stop LoadImage
	{
		wsprintf(temp, TEXT("Stop%d.bmp"), i);

		StopPlayer[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < WALKSIZE; i++)	// Player Walk LoadImage
	{
		wsprintf(temp, TEXT("Walk%d.bmp"), i);

		WalkPlayer[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < WALKSIZE; i++)	// Player Walk LoadImage
	{
		wsprintf(temp, TEXT("mWalk%d.bmp"), i);

		mWalkPlayer[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	for (int i = 0; i < NIDDLESIZE; i++)	// Niddle LoadImage
	{
		wsprintf(temp, TEXT("Niddle%d.bmp"), i);

		Niddle[i] = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

}

void MyPaint(HWND hWnd, HDC hdc)
{
	GetClientRect(hWnd, &rect);

	MemDC = CreateCompatibleDC(hdc);
	MyBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

	
	//Rectangle(hdc, g_xPlayer + 5, g_yPlayer + 10, g_xPlayer + 25, g_yPlayer + 30);
	//Rectangle(hdc, 0, 0, 1100, 31);

	if (0 == g_stage)	// 게임 시작
	{
		img.ImageBitMap(MemDC, 0, 0, 1024, 768, Map[g_oAni], 0, 0, 1024, 768);
		StartMusic1(hWnd);

	}
	
	if (1 == g_stage)
	{
		img.ImageBitMap(MemDC, 0, 0, MAPWIDTH, MAPHEIGHT, Map[2], 0, 0, MAPWIDTH, MAPHEIGHT);//stage

		img.ImageBitMapTrans(MemDC, x_Niddle, y_Niddle, 28, 97, Niddle[1], 0, 0, 28, 97, RGB(255, 255, 255));//NiddleRight
		img.ImageBitMapTrans(MemDC, x1_Niddle, y1_Niddle, 28, 97, Niddle[0], 0, 0, 28, 97, RGB(255, 255, 255));//NiddleLeft
		img.ImageBitMapTrans(MemDC, x2_Niddle, y2_Niddle, 28, 97, Niddle[1], 0, 0, 28, 97, RGB(255, 255, 255));//NiddleRight
		img.ImageBitMapTrans(MemDC, x3_Niddle, y3_Niddle, 28, 97, Niddle[0], 0, 0, 28, 97, RGB(255, 255, 255));//NiddleLeft

		if (0 == SaveFlag)
		{
			img.ImageBitMap(MemDC, Saver_x, Saver_y, ELEMENTWIDTH, ELEMENTHEIGHT, Element[5], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//노세이브
		}
		else
		{
			img.ImageBitMap(MemDC, Saver_x, Saver_y, ELEMENTWIDTH, ELEMENTHEIGHT, Element[6], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//세이브
		}

		if (1 == DeathFlag)
		{
			img.ImageBitMap(MemDC, ELEMENTWIDTH * 4, ELEMENTHEIGHT * 4, 800, 200, Element[7], 0, 0, 800, 200);//게임오버

		}


		if (1 == g_GaveOver)
		{
			img.ImageBitMap(MemDC, 0, 0, MAPWIDTH, MAPHEIGHT, Element[7], 0, 0, MAPWIDTH, MAPHEIGHT);
		}


		if (g_xBullet[0] < 1000)
		{
			img.ImageBitMap(MemDC, g_xBullet[0], g_yBullet[0], 4, 4, Bullet[0], 0, 0, 4, 4);

		}
		if (g_xBullet[1] < 1000)
		{
			img.ImageBitMap(MemDC, g_xBullet[1], g_yBullet[1], 4, 4, Bullet[1], 0, 0, 4, 4);
		}
		if (g_xBullet[2] < 1000)
		{
			img.ImageBitMap(MemDC, g_xBullet[2], g_yBullet[2], 4, 4, Bullet[2], 0, 0, 4, 4);
		}

		for (int i = 0; i < MAPHEIGHT; i++)
		{
			img.ImageBitMap(MemDC, 0, ELEMENTHEIGHT * i, ELEMENTWIDTH, ELEMENTHEIGHT, Element[0], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측벽
		}
		for (int i = 0; i < MAPHEIGHT; i++)
		{
			img.ImageBitMap(MemDC, MAPWIDTH, ELEMENTHEIGHT * i, ELEMENTWIDTH, ELEMENTHEIGHT, Element[0], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//우측벽
		}
		for (int i = 1; i < 32; i++)
		{
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, 0, ELEMENTWIDTH, ELEMENTHEIGHT, Element[0], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//천장
		}
		for (int i = 1; i < 28; i++)
		{
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 4, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측 1 번째
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 12, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측 3 번째
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 20, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측 5 번째
		}
		for (int i = 30; i < 32; i++)
		{
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 4, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//우측 1 번째
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 12, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//우측 3 번째
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 20, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측 5 번째
		}
		for (int i = 1; i < 3; i++)
		{
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 8, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측 2 번째
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 16, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//좌측 4 번째
		}
		for (int i = 5; i < 32; i++)
		{
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 8, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//우측 2 번째
			img.ImageBitMap(MemDC, ELEMENTHEIGHT * i, ELEMENTHEIGHT * 16, ELEMENTWIDTH, ELEMENTHEIGHT, Element[1], 0, 0, ELEMENTWIDTH, ELEMENTHEIGHT);//우측 4 번째
		}

		if (0 == g_GuyFlag)		//정지
		{
			if (0 == g_mirror)		//오른쪽
			{
				img.ImageBitMapTrans(MemDC, g_xPlayer, g_yPlayer, GUYSIZE, GUYSIZE, StopPlayer[g_Ani], 0, 0, 100, 100, RGB(255, 255, 255));
			}

			if (1 == g_mirror)	// 왼쪽
			{
				img.ImageBitMapTrans(MemDC, g_xPlayer, g_yPlayer, GUYSIZE, GUYSIZE, mStopPlayer[g_Ani], 0, 0, 100, 100, RGB(255, 255, 255));
			}
		}

		if (1 == g_GuyFlag)		//움직임
		{
			if (0 == g_mirror)		//오른쪽
			{
				img.ImageBitMapTrans(MemDC, g_xPlayer, g_yPlayer, GUYSIZE, GUYSIZE, WalkPlayer[g_Ani], 0, 0, 100, 100, RGB(255, 255, 255));
			}

			if (1 == g_mirror)		//왼쪽
			{
				img.ImageBitMapTrans(MemDC, g_xPlayer, g_yPlayer, GUYSIZE, GUYSIZE, mWalkPlayer[g_Ani], 0, 0, 100, 100, RGB(255, 255, 255));
			}
		}
	}

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteObject(OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

void MyLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

}

void MyTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 1:								// STOP TIMER, WALK TIMER
		if(0==g_GuyFlag || 1 == g_GuyFlag)
		{ 
			g_Ani++;
			g_Ani %= STOPSIZE;
		}
									
		if (-1 == jum.DownJumpCheck(&g_xPlayer, &g_yPlayer))
		{
			jum.DownJump(&g_JumpSpeed, g_Gravity, &g_xPlayer, &g_yPlayer, &g_JUMP);
		}

		jum.UpJump(&g_JumpSpeed, g_Gravity, &g_xPlayer, &g_yPlayer, &g_JUMP);
		
		//if (-1 == g_JumpFlag)
		//{
		//	g_JumpSpeed = JUMPSPEED;

		//	jum.DownJump(&g_JumpSpeed, g_Gravity, &g_yPlayer);

		//	if (0 < g_JumpSpeed)				//점프 한계
		//	{
		//		g_JumpFlag = 0;
		//	}
		//}
		break;
	case 2:
		if (0 == g_stage)
		{
			g_oAni++;
			g_oAni %= MAPSIZE - 1;
		}
		break;
	case 3:
		
		if (-1 < g_i)
		{
			//g_BulletFlag = -1;

			if (0 < g_i)
			{
				if (1 < g_i)
				{
					
					if (0 == g_mirror)
					{
						g_xBullet[2] += 15;
					}

					else
					{
						g_xBullet[2] -= 15;
					}


						if (1050 < g_xBullet[2] || 50 > g_xBullet[2])
						{
							g_yBullet[2] = g_yPlayer + 17;
							g_xBullet[2] = g_xPlayer + 8;

							g_i--;

							//	(g_i + 3) % 3;

							//g_BulletFlag = -1;
						}
					

				}

				if (0 == g_mirror)
				{
					g_xBullet[1] += 15;
				}

				else
				{
					g_xBullet[1] -= 15;
				}

				if (1050 < g_xBullet[1] || 50 > g_xBullet[1])
				{
					g_yBullet[1] = g_yPlayer + 17;
					g_xBullet[1] = g_xPlayer + 8;

					g_i--;

					//(g_i + 3) % 3;

					//g_BulletFlag = -1;
				}
			}

			if (0 == g_mirror)
			{
				g_xBullet[0] += 15;
			}

			else
			{
				g_xBullet[0] -= 15;
			}

			if (1050 < g_xBullet[0] || 50 > g_xBullet[0])
			{
				g_yBullet[0] = g_yPlayer + 17;
				g_xBullet[0] = g_xPlayer + 8;

				g_i--;

				//(g_i + 3) % 3;

				//g_BulletFlag = -1;
			}

		}
		break;
	case 4:
		if (1 == g_stage && 0 == DeathFlag)
		{
			if (tmp2 < 180) 
			{
				x_Niddle += tmp1;
				x1_Niddle -= tmp1;
				x2_Niddle += tmp1;
				x3_Niddle -= tmp1;
				tmp2++;
				tmp3 = 0;
			}
			else if (tmp2 == 180 && tmp3 < 180)
			{
				x_Niddle -= tmp1;
				x1_Niddle += tmp1;
				x2_Niddle -= tmp1;
				x3_Niddle += tmp1;
				tmp3++;
				if (tmp3 == 180) 
				{
					tmp2 = 0;
				}
			}
		}
		
		
		break;
	default:
		break;
	}


	if (-1 != key.FindKey('X'))		//움직일떄
	{
			if (-1 == g_BulletFlag)
			{
				g_yBullet[0] = g_yPlayer + 17;
				g_xBullet[0] = g_xPlayer + 8;
				g_yBullet[1] = g_yPlayer + 17;
				g_xBullet[1] = g_xPlayer + 8;
				g_yBullet[2] = g_yPlayer + 17;
				g_xBullet[2] = g_xPlayer + 8;

				g_BulletFlag = 0;
			}
			if (0 == g_BulletFlag && g_i!=2)
			{
				g_i++;
				g_i %= 3;


				g_KeyUp = 'X';
			}	
	}
	


	if (1 == jum.LocationFlag && 98 == g_yPlayer)
	{
		if (885 < g_xPlayer && 940 > g_xPlayer)
		{
			jum.LocationFlag = 2;
		}
	}

	if (2 == jum.LocationFlag && 226 == g_yPlayer)
	{
		if (85 < g_xPlayer && 140 > g_xPlayer)
		{
			jum.LocationFlag = 3;
		}
	}

	if (3 == jum.LocationFlag && 354 == g_yPlayer)
	{
		if (885 < g_xPlayer && 940 > g_xPlayer)
		{
			jum.LocationFlag = 4;
		}
	}

	if (4 == jum.LocationFlag && 482 == g_yPlayer)
	{
		if (85 < g_xPlayer && 140 > g_xPlayer)
		{
			jum.LocationFlag = 5;
		}
	}

	if (5 == jum.LocationFlag && 610 == g_yPlayer)
	{
		if (885 < g_xPlayer && 940 > g_xPlayer)
		{
			jum.LocationFlag = 6;
		}
	}
	if (0 == DeathFlag)
	{
		if (-1 != key.FindKey(VK_RIGHT))		//움직일떄
		{
			if (1000 != g_xPlayer)
			{
				g_xPlayer += 5;
				g_GuyFlag = 1;
				g_mirror = 0;
				g_KeyUp = VK_RIGHT;

			}
		}

		if (-1 != key.FindKey(VK_LEFT))			// 움직일떄
		{
			if (25 != g_xPlayer)
			{
				g_xPlayer -= 5;
				g_GuyFlag = 1;
				g_mirror = 1;
				g_KeyUp = VK_LEFT;

			}
		}

		if (-1 != key.FindKey('Z'))			// Z키 눌렀을때
		{
			if (0 == g_stage)
			{
				g_stage = 1;
				StopMusic1(hWnd);
				StartMusic2(hWnd);
				g_KeyUp = 'Z';
			}
		}

		if (-1 != key.FindKey(VK_SHIFT))			// shift키 눌렀을때
		{


			if (2 != g_JumpFlag)
			{
				g_JumpFlag++;
				g_JUMP = true;
				g_JumpSpeed = JUMPSPEED;
			}
			else
			{
				g_JumpFlag = 0;
			}
		}

		if (-1 == key.FindKey(VK_RIGHT))		// 움직이지 않을때
		{
			if (-1 == key.FindKey(VK_LEFT))		// 움직이지 않을때
			{
				g_GuyFlag = 0;
			}
		}
	}
	if (-1 != key.FindKey('R'))
	{

		if (1 == g_stage)
		{
			g_xPlayer = Save_xPlayer;
			g_yPlayer = Save_yPlayer;
			g_KeyUp = 'R';
			jum.LocationFlag = 1;
		}

		if (DeathFlag == 1)
		{
			DeathFlag == 0;
			StopMusic3(hWnd);
			StartMusic2(hWnd);
		}

	}
	if ((Saver_x - 20 <= g_xPlayer && g_xPlayer <= Saver_x + 20) && (Saver_y - 20 <= g_yPlayer && g_yPlayer <= Saver_y + 20))	//저장검사
	{
		SaveFlag = 1;
		Save_xPlayer = Saver_x;
		Save_yPlayer = Saver_y;
	}
	else
	{
		SaveFlag = 0;
	}

	if (0 == DeathFlag && (x_Niddle <= g_xPlayer && g_xPlayer <= x_Niddle + ELEMENTWIDTH) && (y_Niddle <= g_yPlayer && g_yPlayer <= y_Niddle + ELEMENTHEIGHT * 3)) //가시검사
	{
		DeathFlag = 1;
		StopMusic2(hWnd);
		StartMusic3(hWnd);

	}

	if (0 == DeathFlag && (x1_Niddle - ELEMENTWIDTH <= g_xPlayer && g_xPlayer <= x1_Niddle) && (y1_Niddle <= g_yPlayer && g_yPlayer <= y1_Niddle + ELEMENTHEIGHT * 3)) //가시검사
	{
		DeathFlag = 1;
		StopMusic2(hWnd);
		StartMusic3(hWnd);

	}

	if (0 == DeathFlag && (x2_Niddle <= g_xPlayer && g_xPlayer <= x2_Niddle + ELEMENTWIDTH) && (y2_Niddle <= g_yPlayer && g_yPlayer <= y2_Niddle + ELEMENTHEIGHT * 3)) //가시검사
	{
		DeathFlag = 1;
		StopMusic2(hWnd);
		StartMusic3(hWnd);

	}

	if (0 == DeathFlag && (x3_Niddle - ELEMENTWIDTH <= g_xPlayer && g_xPlayer <= x3_Niddle) && (y3_Niddle <= g_yPlayer && g_yPlayer <= y3_Niddle + ELEMENTHEIGHT * 3)) //가시검사
	{
		DeathFlag = 1;
		StopMusic2(hWnd);
		StartMusic3(hWnd);

	}

	


	InvalidateRect(hWnd, NULL, FALSE);
}


void MyKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	key.KeyDown(wParam);
}

void MyKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	key.KeyUp(wParam);
}