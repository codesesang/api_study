#include "stdafx.h"
#include "KBrick.h"
#include "Resource.h"

extern HINSTANCE hInst;

KBrick::KBrick()
{
	m_x = 100;
	m_y = 100;
	m_w = MAP_XSPACE;
	m_h = MAP_YSPACE;

	image_x = 0;
	image_y = 0;
	image_w = 73;
	image_h = 73;

	m_Brick[0] = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(130), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_Brick[1] = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(130), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}



KBrick::~KBrick()
{
}


void KBrick::Draw(HDC hdc)
{
	HDC myDC = CreateCompatibleDC(hdc);

	SelectObject(myDC, (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(143), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION));
	//TransparentBlt(hdc, m_x, m_y, m_w, m_h, myDC, image_x, image_y, image_w, image_h, CHARACTER_RGB);
	TransparentBlt(hdc, 100, 100, 150, 150, myDC, 0, 0, 70, 70, CHARACTER_RGB);
	DeleteDC(myDC);
}

void KBrick::Ini(int x, int y, int choice)
{
	m_x = x;
	m_y = y;
	m_choice = choice;
}