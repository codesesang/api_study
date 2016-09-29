#include "stdafx.h"
#include "KBrickMgr.h"


KBrickMgr::KBrickMgr()
{
	for (int y = 0; y < MAP_YSIZE; y++)
	{
		for (int x = 0; x < MAP_XSIZE; x++)
		{
			if (3 == Map[y][x])
			{
				KBrick KB;

				KB.Ini(x * 40, y * 40, 1);

				m_Bricks.push_back(KB);
			}
		}
	}
}


KBrickMgr::~KBrickMgr()
{
}


void KBrickMgr::Draw(HDC hdc)
{
	for (int i = 0; i < m_Bricks.size(); i++)
		m_Bricks[i].Draw(hdc);
}