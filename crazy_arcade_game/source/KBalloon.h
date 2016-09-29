#pragma once
#include "KObject.h"
#include "Resource.h"
#include "Define.h"
#include "KPlayer.h"

class KPlayer;

class KBalloon :
	public KObject
{
public:
	KBalloon();
	~KBalloon();
	HBITMAP m_balloon[BALLOON_SIZE];
	HBITMAP m_waveBalloon;
	int m_choice;							//물풍선 선택
	int m_animationFlag;					//물풍선 애니메이션
	int m_waveAnimationFlag;				//터지는 물풍선 애니메이션
	int m_waveFlag;							//물풍선 시간체크
	void Draw(HDC hdc);						//물풍선 그리기
	void Ini(int choice);					//물풍선 선택
	void SetLocation(int x, int y);			//물풍선의 좌표값을 넣음
	void Animation();						//애니메이션과 물풍선 체크
	void WaveDraw(HDC hdc, KPlayer* player);//물풍선 터지는 이미지 그리기
	void BltDraw(HDC hdc, int x, int y, HDC myDC, int image_x, int image_y, int image_xLast, int image_yLast, int range, int dir); //사용자가 먹는 물풍선 아이템에 따라서 물줄기 증가
	bool WallCollisionCheck(int x, int y);  //외벽충돌체크
	int GetArrXPos(int x);					//물리좌표를 배열좌표로 전환
	int GetArrYPos(int y);
};