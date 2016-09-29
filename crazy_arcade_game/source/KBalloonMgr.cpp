#include "stdafx.h"
#include "KBalloonMgr.h"

KBalloonMgr::KBalloonMgr()
{
	
}


KBalloonMgr::~KBalloonMgr()
{
}


void KBalloonMgr::Draw(HDC hdc, KPlayer* player)
{
	for (int i = 0; i < m_Balloons.size(); i++)
	{
		m_Balloons[i].Draw(hdc);					//벡터에 들어있는 물풍선을 그린다

		//if (55 < m_Balloons[i].m_waveFlag)	//물풍선 타이머와 물풍선끼리의 충돌 체크
		//{
		//	Map[m_Balloons[i].GetArrYPos(m_Balloons[i].m_y + 5)][m_Balloons[i].GetArrXPos(m_Balloons[i].m_x + 10)] = 0;
		//	m_Balloons.erase(m_Balloons.begin() + i);
		//}	
	}
} 

void KBalloonMgr::WaveDraw(HDC hdc, KPlayer* player)
{
	for (int i = 0; i < m_Balloons.size(); i++)
	{
		//왜 50이냐면 시간을 맞춘것이다.(늘리면 느려지고, 줄이면 빨라지고 한다.)
		if (50 < m_Balloons[i].m_waveFlag || 2 == Map[m_Balloons[i].GetArrYPos(m_Balloons[i].m_y + 5)][m_Balloons[i].GetArrXPos(m_Balloons[i].m_x + 10)])	//물풍선 타이머와 물풍선끼리의 충돌 체크
		{
			m_Balloons[i].WaveDraw(hdc, player);								//벡터에 들어있는 물풍선을 그린다

			for (int j = 0; j < 3 * m_Balloons.size(); j += 3)					//터지는 물풍선의 위치를 저장
			{
				temp[j] = m_Balloons[i].GetArrXPos(m_Balloons[i].m_x + 10);
				temp[j + 1] = m_Balloons[i].GetArrYPos(m_Balloons[i].m_y + 5);
				temp[j + 2] = player->m_range;
			}

			m_Balloons.erase(m_Balloons.begin() + i);							//물풍선 제거
			
			m_Media.PlayWave(_T("WaterBoom.wav"), 0);							//음악

			player->m_number++;									
		}
		//if (3 < m_Balloons[i].flag)
		//{
		//	Map[m_Balloons[i].GetArrYPos(m_Balloons[i].m_y + 5)][m_Balloons[i].GetArrXPos(m_Balloons[i].m_x + 10)] = 0;

		//	int x = m_Balloons[i].GetArrXPos(m_Balloons[i].m_x + 10);
		//	int y = m_Balloons[i].GetArrYPos(m_Balloons[i].m_y + 5);

		//	for (int j = 1; j <= player->m_range; j++)
		//	{
		//		Map[y - j][x] = 0;
		//		Map[y + j][x] = 0;
		//		Map[y][x - j] = 0;
		//		Map[y][x + 1] = 0;
		//	}
		//	m_Balloons.erase(m_Balloons.begin() + i);
		//}
	}

	//for (int i = 0; i < 30; i+=3)
	//{
	//	for (int j = 1; j <= temp[i + 2]; j++)
	//	{
	//		Map[temp[i + 1] + j][temp[i]] = 0;
	//		Map[temp[i + 1] - j][temp[i]] = 0;
	//		Map[temp[i + 1]][temp[i] + j] = 0;
	//		Map[temp[i + 1]][temp[i] - j] = 0;
	//		Map[temp[i + 1]][temp[i]] = 0;
	//	}
	//}
}


void KBalloonMgr::CheckSetBalloon(KPlayer* player, int x, int y)		//플레이어의 위치를 통해서 물풍선을 둘수있는지 체크
{
	if (player->m_number <= player->m_maxNumber && 0 < player->m_number)	//플레이어의 물풍선 수와 현재 존재하는 물풍선 비교
	{
		int yPos = player->GetArrYPos(y);
		int xPos = player->GetArrXPos(x);

		if (0 == Map[yPos][xPos])										//0일때만 물풍선을 둘 수있다.
		{
			m_Media.PlayWave(_T("WaterPut.wav"), 0);  //////////두는음악

			Map[yPos][xPos] = 1;										//물풍선을 두면 1로 변한다.

			player->m_number--;

			KBalloon m_Balloon;

			m_Balloon.SetLocation(xPos, yPos);
			m_Balloon.Ini(0);

			m_Balloons.push_back(m_Balloon);
		}
	}
}

bool KBalloonMgr::IncreaseBalloon(KPlayer* player)
{
	if (player->m_number != player->m_maxNumber)
	{
		player->m_number--;

		return true;
	}
	return false;
}

void KBalloonMgr::Animation()
{
	for (int i = 0; i < m_Balloons.size(); i++)
		m_Balloons[i].Animation();
}

//void KBalloonMgr::AfterBomb()
//{
//	vector<KBalloon>::iterator it;
//
//	//for (it = Vector->begin(); it != Vector->end(); ++it)
//	//{
//	//	if (2 == Map[(it)->GetArrYPos((it)->m_y + 5)][(it)->GetArrXPos((it)->m_x + 10)])
//	//		Map[(it)->GetArrYPos((it)->m_y + 5)][(it)->GetArrXPos((it)->m_x + 10)] = 0;
//	//
//	//	TCHAR msg[80];										//디버깅
//	//	wsprintf(msg, _T("a(%d, %d) %d\n"), (it)->GetArrXPos((it)->m_x + 10), (it)->GetArrYPos((it)->m_y + 5),Map[(it)->GetArrYPos((it)->m_y + 5)][(it)->GetArrXPos((it)->m_x + 10)]);
//	//	OutputDebugString(msg);
//	//}
//
//	for (int y = 0; y < MAP_YSIZE; y++)
//	{
//		for (int x = 0; x < MAP_XSIZE; x++)
//		{
//			if (2 == Map[y][x])
//				Map[y][x] = 0;
//		}
//	}
//}
