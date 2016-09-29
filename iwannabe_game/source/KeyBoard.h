#pragma once

#define MAX_KEY 10

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();

	int m_KeyBuffer[MAX_KEY];

	int KeyDown(int key);
	int KeyUp(int key);
	int FindKey(int key);
	int FindKey2(int key);
};

