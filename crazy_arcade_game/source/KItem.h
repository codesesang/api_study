#pragma once
#include "KObject.h"
#include "Define.h"
#include "Resource.h"
class KItem :
	public KObject
{
public:
	KItem();
	~KItem();
	HBITMAP m_item[ITEM_SIZE];
	int m_choice;
	void Draw(HDC hdc);
	void Ini(int x, int y, int choice);
};