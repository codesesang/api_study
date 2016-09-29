#include "stdafx.h"
#include "kKeyBoard.h"

KKeyBoard::KKeyBoard(void)
{
	for (int i = 0; i<MAX_KEY; i++)
		m_KeyBuf[i] = -1;
}


KKeyBoard::~KKeyBoard(void)
{
}


int KKeyBoard::OnKeyDown(int key)
{
	if (-1 == FindKey(key))
	{
		for (int i = 0; i<MAX_KEY; i++)
		{
			if (-1 == m_KeyBuf[i])
			{
				m_KeyBuf[i] = key;

				return 0;
			}
		}
	}
	return 0;
}


int KKeyBoard::OnKeyUp(int key)
{
	int index = FindKey(key);

	if (-1 != index)
		m_KeyBuf[index] = -1;

	return 0;
}


int KKeyBoard::FindKey(int key)
{
	for (int i = 0; i<MAX_KEY; i++)
	{
		if (key == m_KeyBuf[i])
			return i;
	}
	return -1;
}