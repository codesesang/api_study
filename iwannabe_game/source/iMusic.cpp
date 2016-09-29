#include "stdafx.h"
#include "mmsystem.h"	//For sound (Use iMusic)
#include "iMusic.h"

MCI_OPEN_PARMS mciOpen;	//Load Music File
MCI_PLAY_PARMS mciPlay;	//Music Play
MCI_STATUS_PARMS mciStatus;	//File State

//파일을 DWORD 변수에 로드하는 함수 만들기
UINT wDeviceID = 0;

DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD Result;

	

	mciOpen.lpstrDeviceType = L"MPEGVideo";
	//mciOpen.lpstrDeviceType = L"WaveAudio";
	//MPEGVideo대신 WaveAudio를 사용하면 wav형식 지원

	mciOpen.lpstrElementName = lpszWave;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)
		(LPVOID)&mciOpen);

	if (Result)
	{
		return Result;
	}

	wDeviceID = mciOpen.wDeviceID;
	
	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
	{
		return Result;
	}

	return 0;
}

void StartMusic1(HWND hWnd)
{
	DWORD Sound1 = LoadWAV(hWnd, L"sound_opening.mp3");

	Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}

void StopMusic1(HWND hWnd)
{
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}

void StartMusic2(HWND hWnd)
{
	DWORD Sound1 = LoadWAV(hWnd, L"sound_stage.mp3");

	Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}

void StopMusic2(HWND hWnd)
{
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}

void StartMusic3(HWND hWnd)
{
	DWORD Sound3 = LoadWAV(hWnd, L"sound_gameover.mp3");

	Sound3 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}

void StopMusic3(HWND hWnd)
{
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}

void StartMusic4(HWND hWnd)
{
	DWORD Sound1 = LoadWAV(hWnd, L"sound_endgame.mp3");

	Sound1 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}

void StopMusic4(HWND hWnd)
{
	mciSendCommand(4, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}