#include "stdafx.h"
#include "KItemMgr.h"

extern HINSTANCE hInst;

KItemMgr::KItemMgr()
{
	Ini();
}


KItemMgr::~KItemMgr()
{
}

void KItemMgr::Draw(HDC hdc)
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		m_Items[i].Draw(hdc);

		if (0 == Map[(m_Items[i].m_y - 35) / 40][(m_Items[i].m_x - 10) / 40])
			m_Items.erase(m_Items.begin() + i);
	}
}


void KItemMgr::Ini()
{
	
	int temp[24][2];

	for (int i = 0; i < 24; i++)
	{
		int x = rand() % 15;
		int y = rand() % 13;

		temp[i][0] = x;
		temp[i][1] = y;

		for (int j = 0; j < i; j++)
		{
			if (temp[i][0] == temp[j][0] && temp[i][1] == temp[j][1])
				i--;
		}
	}

	int flag = 0;
	for (int i = 0; i < 24; i++)
	{
		Map[temp[i][1]][temp[i][0]] = flag + 3;												//풍선 -> 3, 물약 -> 4, 롤러 -> 5

		KItem KI;

		KI.Ini(temp[i][0] * 40 + 10, temp[i][1] * 40 + 35, flag);
		flag++;

		if (3 == flag)	flag = 0;

		m_Items.push_back(KI);
	}
}