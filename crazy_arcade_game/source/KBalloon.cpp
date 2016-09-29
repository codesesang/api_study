#include "stdafx.h"
#include "KBalloon.h"

extern HINSTANCE hInst;

KBalloon::KBalloon()
{
	//�̹�������
	image_x = 0;
	image_y = 0;
	image_w = WIDTH_BALLOON_IMAGE / WIDTH_BALLOON_SIZE;
	image_h = HEIGHT_BALLOON_IMAGE;

	//����� �̹��� ����
	m_w = WIDTH_BALLOON;
	m_h = HEIGHT_BALLOON;

	//�ִϸ��̼�
	m_animationFlag		= 0;
	m_waveAnimationFlag = 0;
	m_waveFlag			= 0;

	for (int i = 0; i < BALLOON_SIZE; i++)
		m_balloon[i] = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(balloonName[i]), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	m_waveBalloon = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(WAVE), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}


KBalloon::~KBalloon()
{
}


void KBalloon::Draw(HDC hdc)
{
	//������۸�
	HDC myDC = CreateCompatibleDC(hdc);

	SelectObject(myDC, m_balloon[m_choice]);
	TransparentBlt(hdc, m_x, m_y, m_w, m_h, myDC, image_x, image_y, image_w, image_h, CHARACTER_RGB);
	DeleteDC(myDC);
}


void KBalloon::WaveDraw(HDC hdc, KPlayer* player) //��ǳ�� ������ �̹��� �׸���
{
	HDC myDC = CreateCompatibleDC(hdc);

	SelectObject(myDC, m_waveBalloon);
	 
	//TCHAR msg[70];									//��ǳ�� ���� Ȯ��
	//wsprintf(msg, _T("%d"), player->m_range);
	//TextOut(hdc, 50, 10, msg, lstrlen(msg));

	//int xPos = player->GetArrXPos(m_x);					//�ʿ��� ��ǳ�� ���� �ٲ۴�
	//int yPos = player->GetArrYPos(m_y);
	//Map[yPos][xPos] = 0;

	//ǳ�� ������ ������
	//int aniArr[7] = { 3, 2, 1, 0, 1, 2, 3 };
	//for (int i = 0; i < 7; i++)
	//{
	//	TransparentBlt(hdc, m_x + 15, m_y + 15, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonCenter[aniArr[i] % 3][0], BalloonCenter[aniArr[i] % 3][1], WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);		//���� �̹���
	//	for (int j = 1; j < player->m_range; j++)
	//	{
	//		TransparentBlt(hdc, m_x + 15,                         m_y + 15 - WAVE_BALLOON_SIZE * j, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonUp[aniArr[i]][0],    BalloonUp[aniArr[i]][1],    WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);		//������
	//		TransparentBlt(hdc, m_x + 15,						  m_y + 15 + WAVE_BALLOON_SIZE * j, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonDown[aniArr[i]][0],  BalloonDown[aniArr[i]][1],  WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	//		TransparentBlt(hdc, m_x + 15 + WAVE_BALLOON_SIZE * j, m_y + 15,						    WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonRight[aniArr[i]][0], BalloonRight[aniArr[i]][1], WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	//		TransparentBlt(hdc, m_x + 15 - WAVE_BALLOON_SIZE * j, m_y + 15,							WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonLeft[aniArr[i]][0],  BalloonLeft[aniArr[i]][1],  WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	//	}
	//	//15�� ���� ĳ���� �̹����� ��ǳ�� �̹����� ��ġ ����
	//	TransparentBlt(hdc, m_x + 15,										m_y + 15 - WAVE_BALLOON_SIZE * player->m_range, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonUp[aniArr[i] + 4][0],    BalloonUp[aniArr[i] + 4][1],    WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);		//�����ڸ�
	//	TransparentBlt(hdc, m_x + 15,										m_y + 15 + WAVE_BALLOON_SIZE * player->m_range, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonDown[aniArr[i] + 4][0],  BalloonDown[aniArr[i] + 4][1],  WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	//	TransparentBlt(hdc, m_x + 15 + WAVE_BALLOON_SIZE * player->m_range, m_y + 15,										WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonRight[aniArr[i] + 4][0], BalloonRight[aniArr[i] + 4][1], WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	//	TransparentBlt(hdc, m_x + 15 - WAVE_BALLOON_SIZE * player->m_range, m_y + 15,										WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonLeft[aniArr[i] + 4][0],  BalloonLeft[aniArr[i] + 4][1],  WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	//}

	//ǳ�� ������ �̹��� �׸���
	TransparentBlt(hdc, m_x + 15, m_y + 15, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, BalloonCenter[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] % 3][0], BalloonCenter[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] % 3][1], WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);		//���� �̹���

	BltDraw(hdc, m_x, m_y, myDC, BalloonUp[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][0],    BalloonUp[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][1],    BalloonUp[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][0],    BalloonUp[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][1],    player->m_range, 0);
	BltDraw(hdc, m_x, m_y, myDC, BalloonDown[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][0],  BalloonDown[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][1],  BalloonDown[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][0],  BalloonDown[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][1],  player->m_range, 1);
	BltDraw(hdc, m_x, m_y, myDC, BalloonRight[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][0], BalloonRight[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][1], BalloonRight[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][0], BalloonRight[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][1], player->m_range, 2);
	BltDraw(hdc, m_x, m_y, myDC, BalloonLeft[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][0],  BalloonLeft[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE]][1],  BalloonLeft[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][0],  BalloonLeft[aniArr[m_waveAnimationFlag%WAVE_ANI_SIZE] + 4][1],  player->m_range, 3);
	
	DeleteDC(myDC);
}


void KBalloon::BltDraw(HDC hdc, int x, int y, HDC myDC, int image_x, int image_y, int image_xLast, int image_yLast, int range, int dir)
{
	int xPos = 0;											//��ǳ�� ���� ������ ���� ����
	int yPos = 0;

	int arrX = x + 10;										//ĳ���Ͷ� ��ǳ���� �̹��� ��ǥ���� ������.
	int arrY = y + 5;
	Map[GetArrYPos(arrY)][GetArrXPos(arrX)] = 2;			//�߾� ��ǳ�� �迭�� -> 2

	for (int i = 1; i <= range; i++)
	{
		if		(0 == dir)	yPos -= WAVE_BALLOON_SIZE;		//    �� ����	
		else if (1 == dir)	yPos += WAVE_BALLOON_SIZE;		//  �Ʒ� ����	
		else if (2 == dir)	xPos += WAVE_BALLOON_SIZE;		//������ ����
		else if (3 == dir)	xPos -= WAVE_BALLOON_SIZE;		//  ���� ����

		int arrX = x + 10 + xPos;
		int arrY = y + 5 + yPos;

		if (GetArrXPos(arrX) < 0 || GetArrYPos(arrY) < 0)			return;				//�ʹ迭 �����°��� ����
		if (15 == GetArrXPos(arrX) || 13 == GetArrYPos(arrY))		return;				//15�� ���� ĳ���� �̹����� ��ǳ�� �̹����� ��ġ����

		Map[GetArrYPos(arrY)][GetArrXPos(arrX)] = 2;		//������ ǳ���� -> 2
		TCHAR msg[80];										//�����
		wsprintf(msg, _T("(%d %d) -> %d\n"), GetArrXPos(arrX), GetArrYPos(arrY), Map[GetArrYPos(arrY)][GetArrXPos(arrX)]);
		OutputDebugString(msg);

		if (true == WallCollisionCheck(x + 10 + xPos, y + 5 + yPos))	return;  //�ܺ�üũ
		
		//15�� ���� ĳ���� �̹����� ��ǳ�� �̹����� ��ġ ����
		if (range == i)					//�����ڸ� ����
			TransparentBlt(hdc, x + 15 + xPos, y + 15 + yPos, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, image_xLast, image_yLast, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
		else							//���� ����
			TransparentBlt(hdc, x + 15 + xPos, y + 15 + yPos, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, myDC, image_x, image_y, WAVE_BALLOON_SIZE, WAVE_BALLOON_SIZE, CHARACTER_RGB);
	}
}

void KBalloon::Ini(int choice)
{
	m_choice = choice;
}

void KBalloon::SetLocation(int x, int y) //��ǳ���� ��ǥ�� ���� �ִ� �Լ�
{
	x *= MAP_XSPACE;             		//�� �迭 ��ǥ�� ��ġ��ǥ�� ��ȯ
	y *= MAP_XSPACE;

	x += 5;					//��ǳ���� ĳ������ ��ǥ�� �����ش�
	y += 30;

	m_x = x;
	m_y = y;
}

void KBalloon::Animation()						//�ִϸ��̼ǰ� ǳ�� �ð�üũ
{
	image_x = m_animationFlag * (WIDTH_BALLOON_IMAGE / WIDTH_BALLOON_SIZE);
	
	m_waveAnimationFlag++;
	m_animationFlag++;
	m_waveFlag++;

	if (3 == m_animationFlag)		m_animationFlag = 0;
	//if (20 == m_waveAnimationFlag)	m_waveAnimationFlag = 0;
}


bool KBalloon::WallCollisionCheck(int x, int y)	   //�ܺ� �浹 üũ
{
	if (x < chLocation[0][0])	return true;		
	if (y < chLocation[0][1])	return true;
	if (chLocation[3][0] < x)	return true;
	if (chLocation[3][1] < y)	return true;

	return false;
}

int KBalloon::GetArrXPos(int x)						//������ǥ�� �迭��ǥ��
{
	x -= START_XLOCATION;
	x /= MAP_XSPACE;

	return x;
}


int KBalloon::GetArrYPos(int y)
{
	y -= START_YLOCATION;
	y /= MAP_YSPACE;

	return y;
}
