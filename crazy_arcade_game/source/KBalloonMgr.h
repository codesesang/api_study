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
	vector<KBalloon> m_Balloons;						//��ǳ�� ����
	void Draw(HDC hdc, KPlayer* player);				//��ǳ�� �׸���
	void WaveDraw(HDC hdc, KPlayer* player);			//������ ��ǳ�� �׸���
	void CheckSetBalloon(KPlayer* player, int x, int y);//�÷��̾��� ��ġ�� ���ؼ� ��ǳ���� �� �� �ִ��� üũ
	bool IncreaseBalloon(KPlayer* player);				
	void Animation();									//��ǳ�� �ִϸ��̼�
	//void AfterBomb();
};