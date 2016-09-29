#include "stdafx.h"
#include "Image.h"


Image::Image()
{
}


Image::~Image()
{
}

int Image::ImageBitMap(void)
{
	return 0;
}

int Image::ImageBitMap(HDC hdc, int x, int y, int w, int h, HBITMAP bitMap, int sx, int sy, int sw, int sh)
{
	HDC memDC = CreateCompatibleDC(hdc);

	HBITMAP pOld = (HBITMAP)SelectObject(memDC, bitMap);

	StretchBlt(hdc, x, y, w, h, memDC, sx, sy, sw, sh, SRCCOPY);

	SelectObject(memDC, pOld);
	DeleteDC(memDC);

	return 0;
}

int Image::ImageBitMapTrans(HDC hdc, int x, int y, int w, int h, HBITMAP bitMap, int sx, int sy, int sw, int sh, COLORREF color)
{
	HDC memDC = CreateCompatibleDC(hdc);

	HBITMAP pOld = (HBITMAP)SelectObject(memDC, bitMap);

	TransparentBlt(hdc, x, y, w, h, memDC, sx, sy, sw, sh, color);

	SelectObject(memDC, pOld);
	DeleteDC(memDC);

	return 0;
}

int Image::ImageBrush(HDC hdc, int x, int y, int w, int h, int brushhatch, COLORREF brushcolor, int penstyle, int pensize, COLORREF pencolor)
{
	HBRUSH hBrush = CreateHatchBrush(brushhatch, brushcolor);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	HPEN hPen = CreatePen(penstyle, pensize, pencolor);

	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, w, h);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	return 0;
}
