#include "stdafx.h"
#include "KPlayer.h"

KPlayer::KPlayer()
{
	image_x = 2 * (WIDTH_CHARACTER_IMAGE / WIDTH_CHARACTER_SIZE);				//이미지 초기화
	image_y = 0;
	image_w = WIDTH_CHARACTER_IMAGE / WIDTH_CHARACTER_SIZE;
	image_h = HEIGHT_CHARACTER_IMAGE / HEIGHT_CHARACTER_SIZE;

	m_speed  = 5;			//스피드
	m_number = 0;			//물풍선 갯수
	m_range  = 0;			//물풍선 범위
}


KPlayer::~KPlayer()
{
}


void KPlayer::Draw(HDC hdc)
{
	HDC myDC = CreateCompatibleDC(hdc);

	SelectObject(myDC, m_character[m_choice]);
	TransparentBlt(hdc, m_x, m_y, m_w, m_h, myDC, image_x, image_y, image_w, image_h, CHARACTER_RGB);
	DeleteDC(myDC);
}


void KPlayer::Move(int dir)			//캐릭터 움직임
{
	switch (dir)
	{
	case VK_LEFT:	
		if (1 == Map[GetArrYPos(m_y)][GetArrXPos(m_x) - 1])		break;		//장애물에 있으면 못지나감	   
		m_x -= m_speed;		                        
		break;
	case VK_RIGHT:	
		if (1 == Map[GetArrYPos(m_y)][GetArrXPos(m_x) + 1])		break;	
		m_x += m_speed;		                        
		break;
	case VK_UP:		
		if (1 == Map[GetArrYPos(m_y) - 1][GetArrXPos(m_x)])		break;
		m_y -= m_speed;								
		break;
	case VK_DOWN:
		if (1 == Map[GetArrYPos(m_y) + 1][GetArrXPos(m_x)])		break; 
		m_y += m_speed;								
		break;
	}
	if (3 == Map[GetArrYPos(m_y)][GetArrXPos(m_x)])			//풍선 -> 3, 물약 -> 4, 롤러 -> 5
	{
		m_number++;
		Map[GetArrYPos(m_y)][GetArrXPos(m_x)] = 0;
	}
	if (4 == Map[GetArrYPos(m_y)][GetArrXPos(m_x)])
	{
		m_range++;
		Map[GetArrYPos(m_y)][GetArrXPos(m_x)] = 0;
	}
	if (5 == Map[GetArrYPos(m_y)][GetArrXPos(m_x)])
	{
		m_speed++;
		Map[GetArrYPos(m_y)][GetArrXPos(m_x)] = 0;
	}

	Animation(dir);					//애니메이션
	WallCollisionCheck();			//외벽 충돌 체크
}


void KPlayer::Ini(int location, int choice, int number, int maxNumber, int range)		//캐릭터 위치 설정, 캐릭터 설정
{
	m_x = chLocation[location][0];
	m_y = chLocation[location][1];
	m_w = WIDTH_CHARACTER;
	m_h = HEIGHT_CHARACTER;

	m_number	= number;			//물풍선 갯수
	m_maxNumber = maxNumber;		//최대 물풍선 갯수
	m_range		= range;			//물풍선 범위

	m_choice	= choice;
}

//int chLocation[4][2] = { { 15, 35 }, { 575, 35 }, { 15, 515 }, { 575, 515 } };	//캐릭터 위치(4꼭지점)

int KPlayer::WallCollisionCheck()		//외벽 충돌 체크
{
	if (m_x < chLocation[0][0])		m_x = chLocation[0][0];
	if (m_y < chLocation[0][1])		m_y = chLocation[0][1];
	if (chLocation[3][0] < m_x)		m_x = chLocation[3][0];
	if (chLocation[3][1] < m_y)		m_y = chLocation[3][1];
	
	return 0;
}

int KPlayer::Animation(int dir)			//애니메이션 효과
{
	static int animationFlag = 0;

	switch (dir)
	{
	case VK_LEFT:	image_y = 1 * (HEIGHT_CHARACTER_IMAGE / HEIGHT_CHARACTER_SIZE);	break;
	case VK_RIGHT:	image_y = 2 * (HEIGHT_CHARACTER_IMAGE / HEIGHT_CHARACTER_SIZE);	break;
	case VK_UP:		image_y = 3 * (HEIGHT_CHARACTER_IMAGE / HEIGHT_CHARACTER_SIZE);	break;
	case VK_DOWN:	image_y = 0 * (HEIGHT_CHARACTER_IMAGE / HEIGHT_CHARACTER_SIZE);	break;
	}
	image_x = animationFlag * (WIDTH_CHARACTER_IMAGE / WIDTH_CHARACTER_SIZE);
	animationFlag++;

	if (4 == animationFlag)	animationFlag = 0;

	return 0;
}



int KPlayer::GetArrXPos(int xPos)		//플레이어의 중앙 물리좌표를 맵의 배열좌표로 변환
{
	xPos += MAP_XSPACE / 2;							//플레이어의 중앙 물리좌표
	xPos -= START_XLOCATION;						//맵 시작좌표 빼기
	xPos /= MAP_XSPACE;								//맵 배열좌표로 변환

	return xPos;
}


int KPlayer::GetArrYPos(int yPos)		//플레이어의 중앙 물리좌표를 맵의 배열좌표로 변환
{
	yPos += MAP_YSPACE / 2;							//플레이어의 중앙 물리좌표
	yPos -= START_YLOCATION;						//맵 시작좌표 빼기
	yPos /= MAP_YSPACE;								//맵 배열좌표로 변환

	return yPos;
}