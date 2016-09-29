#pragma once
class Image
{
public:
	Image();
	~Image();
	int ImageBitMap(void);
	int ImageBitMap(HDC hdc, int x, int y, int w, int h, HBITMAP bitMap, int sx, int sy, int sw, int sh);
	int ImageBitMapTrans(HDC hdc, int x, int y, int w, int h, HBITMAP bitMap, int sx, int sy, int sw, int sh, COLORREF color);
	int ImageBrush(HDC hdc, int x, int y, int w, int h, int brushhatch, COLORREF brushcolor, int penstyle, int pensize, COLORREF pencolor);

};

