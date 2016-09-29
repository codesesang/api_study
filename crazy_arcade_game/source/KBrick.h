#pragma once
#include "KObject.h"
#include "Define.h"
#include "Resource.h"
class KBrick :
	public KObject
{
public:
	KBrick();
	~KBrick();
	HBITMAP m_Brick[BRICK_SIZE];
	int m_choice;
	void Draw(HDC hdc);
	void Ini(int x, int y, int choice);
};

