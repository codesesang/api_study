#include "stdafx.h"
#include "KeyBoard.h"


KeyBoard::KeyBoard()
{
	for (int i = 0; i<MAX_KEY; i++)
	{
		m_KeyBuffer[i] = -1;
	}
}


KeyBoard::~KeyBoard()
{
}


int KeyBoard::KeyDown(int key)
{
	if (-1 == FindKey(key))
	{
		for (int i = 0; i<MAX_KEY; i++)
		{
			if (-1 == m_KeyBuffer[i])
			{
				m_KeyBuffer[i] = key;
				return 0;
			}
		}
	}
	return 0;
}


int KeyBoard::KeyUp(int key)
{
	int index = FindKey(key);

	if (-1 != index)
	{
		m_KeyBuffer[index] = -1;
	}
	return 0;
}


int KeyBoard::FindKey(int key)
{
	for (int i = 0; i<MAX_KEY; i++)
	{
		if (key == m_KeyBuffer[i])
		{
			return i;
		}

	}
	return -1;
}

int KeyBoard::FindKey2(int key)
{
	for (int i = 0; i<10; i++)
	{
		if (key == m_KeyBuffer[i])
		{
			return i;
		}

	}
	return -1;
}
