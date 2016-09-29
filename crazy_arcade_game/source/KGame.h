#pragma once
#include "KPlayer.h"
#include "KKeyBoard.h"
#include "KBalloon.h"
#include "KBalloonMgr.h"
#include "KItem.h"
#include "KItemMgr.h"
#include <vector>
#include "KBrickMgr.h"
#include "KBrick.h"
#include "KMedia.h"

using namespace std;

class KGame
{
public:
	KGame();
	~KGame();
	HWND m_hWnd;
	HBITMAP m_Bitmap;
	KPlayer m_Player;
	KPlayer m_Player2;
	KKeyBoard m_Key;
	KBalloonMgr m_BalloonMgr;
	KBalloonMgr m_BalloonMgr2;
	KBalloon m_Balloon;
	KItem m_Item;
	KItemMgr m_ItemMgr;
	KBrickMgr m_BrickMgr;
	KBrick m_Brick;
	KMedia m_Media;
	void OnCreate(HWND hWnd);
	void OnDraw(HDC hdc);
	void OnKeyDown(int key);
	void OnKeyUp(int key);
	void OnTimer(int id);
	void IniBitmap();
	void DrawBG(HDC hdc);
};