#pragma once
#define MAX_KEY 100

class KKeyBoard
{

public:

	KKeyBoard(void);
	~KKeyBoard(void);
	int m_KeyBuf[MAX_KEY];
	int OnKeyDown(int key);
	int OnKeyUp(int key);
	int FindKey(int key);
};