#pragma once
#include "KObject.h"
#include "Define.h"
#include "Resource.h"
#include "KBrick.h"
#include <vector>

using namespace std;

class KBrickMgr :
	public KObject
{
public:
	KBrickMgr();
	~KBrickMgr();
	vector<KBrick> m_Bricks;
	void Draw(HDC hdc);
};

