#pragma once
#include "KObject.h"
#include "Resource.h"
#include "KItem.h"
#include <vector>

using namespace std;

class KItemMgr :
	public KObject
{
public:
	KItemMgr();
	~KItemMgr();
	vector<KItem> m_Items;
	void Draw(HDC hdc);
	void Ini();
};

