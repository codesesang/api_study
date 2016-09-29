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
	int m_choice;							//��ǳ�� ����
	int m_animationFlag;					//��ǳ�� �ִϸ��̼�
	int m_waveAnimationFlag;				//������ ��ǳ�� �ִϸ��̼�
	int m_waveFlag;							//��ǳ�� �ð�üũ
	void Draw(HDC hdc);						//��ǳ�� �׸���
	void Ini(int choice);					//��ǳ�� ����
	void SetLocation(int x, int y);			//��ǳ���� ��ǥ���� ����
	void Animation();						//�ִϸ��̼ǰ� ��ǳ�� üũ
	void WaveDraw(HDC hdc, KPlayer* player);//��ǳ�� ������ �̹��� �׸���
	void BltDraw(HDC hdc, int x, int y, HDC myDC, int image_x, int image_y, int image_xLast, int image_yLast, int range, int dir); //����ڰ� �Դ� ��ǳ�� �����ۿ� ���� ���ٱ� ����
	bool WallCollisionCheck(int x, int y);  //�ܺ��浹üũ
	int GetArrXPos(int x);					//������ǥ�� �迭��ǥ�� ��ȯ
	int GetArrYPos(int y);
};