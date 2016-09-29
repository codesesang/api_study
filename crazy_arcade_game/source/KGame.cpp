#include "stdafx.h"
#include "KGame.h"
#include "Define.h"
#include "Resource.h"
#include <time.h>

extern HINSTANCE hInst;

KGame::KGame()
{
	srand(time(NULL));

	int location[2]; 		//ĳ���� ���� ��ġ
	int choice[2];			//ĳ���� ���� ����
	
	for (int i = 0; i < 2; i++)
	{
		location[i] = rand() % CHARACTER_SIZE;;
		choice[i] = rand() % CHARACTER_SIZE;
		for (int j = 0; j < i; j++)
		{
			if (location[i] == location[j] || choice[i] == choice[j])
				i--;
		}
	}

	m_Player.Ini(location[0], choice[0], 1, 5, 2);
	m_Player2.Ini(location[1], choice[1], 1, 5, 2);
}


KGame::~KGame()
{

}


void KGame::OnCreate(HWND hWnd)
{
	m_hWnd = hWnd;

	m_Media.Open(_T("GameStart.mp3"));											//����
	m_Media.Play();

	m_Media.Open(_T("MapBGM.mp3"));
	m_Media.Play();

	IniBitmap();																//��Ʈ�� �ε�

	SetTimer(m_hWnd, 1, 83, NULL);												//Ű���� Ÿ�̸�
	SetTimer(m_hWnd, 2, 450, NULL);												//��ǳ�� �迭���� �ٲٴ� Ÿ�̸�
}


void KGame::OnDraw(HDC hdc)														//������۸�
{
	HBITMAP bufBitmap = CreateCompatibleBitmap(hdc, WIDTH_MAP, HEIGHT_MAP);
	HDC		bufDC	  = CreateCompatibleDC(hdc);

	SelectObject(bufDC, bufBitmap);
	{
		DrawBG(bufDC);															//�ʱ׸���

		m_BalloonMgr.WaveDraw(bufDC, &m_Player);
		m_BalloonMgr2.WaveDraw(bufDC, &m_Player2);
		
		m_BalloonMgr.Draw(bufDC, &m_Player);									//��ǳ�� �׸���
		m_BalloonMgr2.Draw(bufDC, &m_Player2);

		m_Player.Draw(bufDC);//�÷��̾� �׸���
		m_Player2.Draw(bufDC);

		m_ItemMgr.Draw(bufDC);													//������ �׸���

		TCHAR msg[80];																										//�÷��̾��� ��ġ�� �迭��ǥ�� ��ȯ Ȯ��
		wsprintf(msg, _T("x : %d, y : %d"), m_Player.GetArrXPos(m_Player.m_x), m_Player.GetArrYPos(m_Player.m_y));
		TextOut(bufDC, 10, 10, msg, lstrlen(msg));
	}	
	
	StretchBlt(hdc, 0, 0, WIDTH_MAP, HEIGHT_MAP, bufDC, 0, 0, WIDTH_MAP, HEIGHT_MAP, SRCCOPY);
	DeleteObject(bufBitmap);
	DeleteDC(bufDC);

	TCHAR temp[10];																											//��ǳ�� �迭�� Ȯ��
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			wsprintf(temp, _T("%d "), Map[i][j]);
			TextOut(hdc, 900 + (20 * j), 10 + (20 * i), temp, lstrlen(temp));
		}
	}

	TCHAR msg[80];
	wsprintf(msg, _T("num : %d range : %d m_speed : %d"), m_Player.m_number, m_Player.m_range, m_Player.m_speed);
	TextOut(hdc, 100,10, msg, lstrlen(msg));
}


void KGame::OnKeyDown(int key)
{
	m_Key.OnKeyDown(key);
}


void KGame::OnKeyUp(int key)		
{
	m_Key.OnKeyUp(key);
}


void KGame::OnTimer(int id)			//Ÿ�̸�
{
	if (1 == id)
	{	
		if (2 == Map[m_Player.GetArrYPos(m_Player.m_y)][m_Player.GetArrXPos(m_Player.m_x)])		//���ӿ��� üũ
		{
			m_Media.Stop();

			m_Media.Open(_T("Lose.mp3"));
			m_Media.Play();

			KillTimer(m_hWnd, 1);
			MessageBox(m_hWnd, _T("PLAYER2 WIN"), _T("INFORMATION"), MB_OK);
		}
		if (2 == Map[m_Player2.GetArrYPos(m_Player2.m_y)][m_Player2.GetArrXPos(m_Player2.m_x)])		//���ӿ��� üũ
		{
			m_Media.Stop();

			m_Media.Open(_T("Lose.mp3"));
			m_Media.Play();

			KillTimer(m_hWnd, 1);
			MessageBox(m_hWnd, _T("PLAYER1 WIN"), _T("INFORMATION"), MB_OK);
		}
																									//player1
		if (-1 != m_Key.FindKey(VK_RIGHT))	m_Player.Move(VK_RIGHT);
		if (-1 != m_Key.FindKey(VK_LEFT))	m_Player.Move(VK_LEFT);
		if (-1 != m_Key.FindKey(VK_UP))		m_Player.Move(VK_UP);
		if (-1 != m_Key.FindKey(VK_DOWN))	m_Player.Move(VK_DOWN);
		          
		if (-1 != m_Key.FindKey(VK_SPACE))
			m_BalloonMgr.CheckSetBalloon(&m_Player, m_Player.m_x, m_Player.m_y);		//��ǳ���� �Ѽ� �ִ��� üũ


																								//player2
		if (-1 != m_Key.FindKey(VK_NUMPAD6))	m_Player2.Move(VK_RIGHT);
		if (-1 != m_Key.FindKey(VK_NUMPAD4))	m_Player2.Move(VK_LEFT);
		if (-1 != m_Key.FindKey(VK_NUMPAD8))	m_Player2.Move(VK_UP);
		if (-1 != m_Key.FindKey(VK_NUMPAD5))	m_Player2.Move(VK_DOWN);
		
		if (-1 != m_Key.FindKey(VK_NUMPAD0))
			m_BalloonMgr2.CheckSetBalloon(&m_Player2, m_Player2.m_x, m_Player2.m_y);		//��ǳ���� �Ѽ� �ִ��� üũ


		m_BalloonMgr.Animation();	//��ǳ�� �ִϸ��̼�
		m_BalloonMgr2.Animation();

		InvalidateRect(m_hWnd, NULL, FALSE);
	}

	if (2 == id)																		//��ǳ�� �迭���� ��ȯ
	{
		for (int i = 0; i < 30; i += 3)
		{
			for (int j = 1; j <= temp[i + 2]; j++)
			{
				if (1 != Map[temp[i + 1]][temp[i]])
				{
					if (12 >= (temp[i + 1] + j))
						Map[temp[i + 1] + j][temp[i]] = 0;
					if (0 <= (temp[i + 1] - j))
						Map[temp[i + 1] - j][temp[i]] = 0;
					if (14 >= (temp[i] + j))
						Map[temp[i + 1]][temp[i] + j] = 0;
					if (0 <= (temp[i] - j))
						Map[temp[i + 1]][temp[i] - j] = 0;
					Map[temp[i + 1]][temp[i]] = 0;
				}
			}
		}
		InvalidateRect(m_hWnd, NULL, FALSE);
	}

	
}


void KGame::IniBitmap()		//�̹��� �ε�
{
	m_Bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(BackGround), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	for (int i = 0; i < CHARACTER_SIZE; i++)
		m_Player.m_character[i] = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(chName[i]), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	for (int i = 0; i < CHARACTER_SIZE; i++)
		m_Player2.m_character[i] = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(chName[i]), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}


void KGame::DrawBG(HDC hdc)		//�ʱ׸���
{
	HDC myDC = CreateCompatibleDC(hdc);

	SelectObject(myDC, m_Bitmap);
	StretchBlt(hdc, 0, 0, WIDTH_MAP, HEIGHT_MAP, myDC, 0, 0, WIDTH_MAP, HEIGHT_MAP, SRCCOPY);
	DeleteDC(myDC);
}