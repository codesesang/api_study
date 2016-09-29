#include "stdafx.h"
#include "mmsystem.h"	//For sound (Use iMusic)

#pragma once
#pragma comment(lib, "winmm.lib")	//For sound

DWORD LoadWAV(HWND, LPCTSTR);
void StartMusic1(HWND);
void StopMusic1(HWND);
void StartMusic2(HWND);
void StopMusic2(HWND);
void StartMusic3(HWND);
void StopMusic3(HWND);
void StartMusic4(HWND);
void StopMusic4(HWND);
//DWORD Sound1(HWND);



