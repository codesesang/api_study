#pragma once
#include "KObject.h"
#include "Resource.h"
#include "Define.h"
#include "KBalloon.h"
#include "KPlayer.h"
#include "KMedia.h"
#include <vector>

using namespace std;

class KPlayer;

class KBalloonMgr :
	public KObject
{
public:
	KBalloonMgr();
	~KBalloonMgr();
	KMedia m_Media;
	vector<KBalloon> m_Balloons;						//물풍선 벡터
	void Draw(HDC hdc, KPlayer* player);				//물풍선 그리기
	void WaveDraw(HDC hdc, KPlayer* player);			//터지는 물풍선 그리기
	void CheckSetBalloon(KPlayer* player, int x, int y);//플러이어의 위치를 통해서 물풍선을 둘 수 있는지 체크
	bool IncreaseBalloon(KPlayer* player);				
	void Animation();									//물풍선 애니메이션
	//void AfterBomb();
};