#pragma once
#include "KObject.h"
#include "Define.h"
class KPlayer :
	public KObject
{
public:
	KPlayer();
	~KPlayer();
	void Draw(HDC hdc);															//캐릭터 출력
	void Move(int dir);															//캐릭터 움직임
	void Ini(int location, int choice, int number, int maxNumber, int range);	//처음 캐릭터 위치
	HBITMAP m_character[CHARACTER_SIZE];										//캐릭터 이미지
	int m_speed;																//스피드
	int WallCollisionCheck();													//외벽 충돌체크
	int Animation(int dir);														//애니메이션 효과
	int m_choice;																//캐릭터 선택
	int m_number;																//물풍선 갯수
	int m_maxNumber;															//최대 물풍선 갯수
	int m_range;																//물풍선 범위
	int GetArrXPos(int xPos);													//플레이어의 좌표를 배열로 변환
	int GetArrYPos(int yPos);
};