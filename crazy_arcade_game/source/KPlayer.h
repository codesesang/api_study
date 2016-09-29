#pragma once
#include "KObject.h"
#include "Define.h"
class KPlayer :
	public KObject
{
public:
	KPlayer();
	~KPlayer();
	void Draw(HDC hdc);															//ĳ���� ���
	void Move(int dir);															//ĳ���� ������
	void Ini(int location, int choice, int number, int maxNumber, int range);	//ó�� ĳ���� ��ġ
	HBITMAP m_character[CHARACTER_SIZE];										//ĳ���� �̹���
	int m_speed;																//���ǵ�
	int WallCollisionCheck();													//�ܺ� �浹üũ
	int Animation(int dir);														//�ִϸ��̼� ȿ��
	int m_choice;																//ĳ���� ����
	int m_number;																//��ǳ�� ����
	int m_maxNumber;															//�ִ� ��ǳ�� ����
	int m_range;																//��ǳ�� ����
	int GetArrXPos(int xPos);													//�÷��̾��� ��ǥ�� �迭�� ��ȯ
	int GetArrYPos(int yPos);
};