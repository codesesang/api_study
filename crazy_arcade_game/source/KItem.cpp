#include "stdafx.h"
#include "Resource.h"
#include "KItem.h"

extern HINSTANCE hInst;

KItem::KItem()
{
	m_x = 0;
	m_y = 0;
	m_w = 60;
	m_h = 60;

	image_x = 0;
	image_y = 0;
	image_w = 73;
	image_h = 73;

	for (int i = 0; i < ITEM_SIZE; i++)												//풍선,물약,롤러
		m_item[i] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(itemName[i]), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}


KItem::~KItem()
{
}

void KItem::Draw(HDC hdc)
{
	
	HDC myDC = CreateCompatibleDC(hdc);

	SelectObject(myDC, m_item[m_choice]);
	TransparentBlt(hdc, m_x, m_y, m_w, m_h, myDC, image_x, image_y, image_w, image_h, RGB(255,255,255));

	DeleteDC(myDC);
}

void KItem::Ini(int x, int y, int choice)
{
	m_x = x;
	m_y = y;
	m_choice = choice;
}