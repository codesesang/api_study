#include "stdafx.h"
#include "KPlayer.h"

KPlayer::KPlayer()
{
	image_x = 2 * (WIDTH_CHARACTER_IMAGE / WIDTH_CHARACTER_SIZE);				//�̹��� �ʱ�ȭ
	image_y = 0;
	image_w = WIDTH_CHARACTER_IMAGE / WIDTH_CHARACTER_SIZE;
	image_h = HEIGHT_CHARACTER_IMAGE / HEIGHT_CHARACTER_SIZE;

	m_speed  = 5;			//���ǵ�
	m_number = 0;			//��ǳ�� ����
	m_range  = 0;			//��ǳ�� ����
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


void KPlayer::Move(int dir)			//ĳ���� ������
{
	switch (dir)
	{
	case VK_LEFT:	
		if (1 == Map[GetArrYPos(m_y)][GetArrXPos(m_x) - 1])		break;		//��ֹ��� ������ ��������	   
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
	if (3 == Map[GetArrYPos(m_y)][GetArrXPos(m_x)])			//ǳ�� -> 3, ���� -> 4, �ѷ� -> 5
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

	Animation(dir);					//�ִϸ��̼�
	WallCollisionCheck();			//�ܺ� �浹 üũ
}


void KPlayer::Ini(int location, int choice, int number, int maxNumber, int range)		//ĳ���� ��ġ ����, ĳ���� ����
{
	m_x = chLocation[location][0];
	m_y = chLocation[location][1];
	m_w = WIDTH_CHARACTER;
	m_h = HEIGHT_CHARACTER;

	m_number	= number;			//��ǳ�� ����
	m_maxNumber = maxNumber;		//�ִ� ��ǳ�� ����
	m_range		= range;			//��ǳ�� ����

	m_choice	= choice;
}

//int chLocation[4][2] = { { 15, 35 }, { 575, 35 }, { 15, 515 }, { 575, 515 } };	//ĳ���� ��ġ(4������)

int KPlayer::WallCollisionCheck()		//�ܺ� �浹 üũ
{
	if (m_x < chLocation[0][0])		m_x = chLocation[0][0];
	if (m_y < chLocation[0][1])		m_y = chLocation[0][1];
	if (chLocation[3][0] < m_x)		m_x = chLocation[3][0];
	if (chLocation[3][1] < m_y)		m_y = chLocation[3][1];
	
	return 0;
}

int KPlayer::Animation(int dir)			//�ִϸ��̼� ȿ��
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



int KPlayer::GetArrXPos(int xPos)		//�÷��̾��� �߾� ������ǥ�� ���� �迭��ǥ�� ��ȯ
{
	xPos += MAP_XSPACE / 2;							//�÷��̾��� �߾� ������ǥ
	xPos -= START_XLOCATION;						//�� ������ǥ ����
	xPos /= MAP_XSPACE;								//�� �迭��ǥ�� ��ȯ

	return xPos;
}


int KPlayer::GetArrYPos(int yPos)		//�÷��̾��� �߾� ������ǥ�� ���� �迭��ǥ�� ��ȯ
{
	yPos += MAP_YSPACE / 2;							//�÷��̾��� �߾� ������ǥ
	yPos -= START_YLOCATION;						//�� ������ǥ ����
	yPos /= MAP_YSPACE;								//�� �迭��ǥ�� ��ȯ

	return yPos;
}