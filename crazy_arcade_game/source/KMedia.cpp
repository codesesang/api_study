
#include "StdAfx.h"
#include "KMedia.h"


KMedia::KMedia(void)
{
	m_h1 = -1;
	m_h2 = -1;

}

KMedia::~KMedia(void)
{
}


void KMedia::Open(TCHAR* filename)

{

	mciOpenParms.lpstrElementName = filename;                           //화일 설정

	mciOpenParms.lpstrDeviceType = _T("MPEGVideo");                     //디바이스 를 waveaudio로

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,

		(DWORD)(LPVOID)&mciOpenParms);          //MCI_OPEN 명령을 준다.

	wDeviceID = mciOpenParms.wDeviceID;                     //열린 디바이스 아이디를 받느다.



	MCI_STATUS_PARMS mciStatusParms;

	mciStatusParms.dwItem = MCI_STATUS_LENGTH;



	mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

	m_nTotalTime = (LONG)mciStatusParms.dwReturn;

}



BOOL KMedia::Pause()

{

	mciSendCommand(wDeviceID, MCI_PAUSE, MCI_NOTIFY,

		(DWORD)(LPVOID)&mciPlayParms);

	return TRUE;

}



BOOL KMedia::Play()

{

	mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY,

		(DWORD)(LPVOID)&mciPlayParms);

	return TRUE;

}



BOOL KMedia::Stop()

{

	mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);



	return TRUE;

}



void KMedia::SetPosition(DWORD dwPos)

{

	MCI_SEEK_PARMS mciSeekParms;

	mciSeekParms.dwTo = dwPos;



	mciSendCommand(wDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeekParms);

	Play();

}



DWORD KMedia::GetMode()

{

	DWORD dwMode;



	MCI_STATUS_PARMS mciStatusParms;

	mciStatusParms.dwItem = MCI_STATUS_MODE;



	mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

	dwMode = (LONG)mciStatusParms.dwReturn;



	return dwMode;

}



DWORD KMedia::GetPosition()

{

	DWORD nTime;



	MCI_STATUS_PARMS mciStatusParms;

	mciStatusParms.dwItem = MCI_STATUS_POSITION;



	mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

	nTime = (LONG)mciStatusParms.dwReturn;



	return nTime;

}



DWORD KMedia::GetLength()

{

	DWORD nTime;



	MCI_STATUS_PARMS mciStatusParms;

	mciStatusParms.dwItem = MCI_STATUS_LENGTH;



	mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

	nTime = (LONG)mciStatusParms.dwReturn;



	return nTime;

}



void KMedia::SetVolume(DWORD volume)
{    //Volume: 0 - 1000 
	MCI_DGV_SETAUDIO_PARMS  p;

	if (volume>100) volume = 100;
	if (volume<0) volume = 0;

	volume *= 10;

	p.dwCallback = 0;
	p.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	p.dwValue = volume;
	p.dwOver = 0;
	p.lpstrAlgorithm = NULL;
	p.lpstrQuality = NULL;

	mciSendCommand(wDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&p);
}

int KMedia::GetVolume()
{
	MCI_STATUS_PARMS p;

	p.dwCallback = 0;
	p.dwItem = MCI_DGV_STATUS_VOLUME;
	mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&p);

	return (int)(p.dwReturn / 10);  // Volume: 0 - 1000  
}

void KMedia::PlayWave(TCHAR* filename, int ch)
{
	if (0 == ch)
	{
		if (-1 != m_h1)
		{
			//0번채널 사운드 디바이스가 열려있다면 닫는다.
			mciSendCommand(m_h1, MCI_CLOSE, 0, (DWORD)NULL);
		}
	}
	else
	{
		if (-1 != m_h2)
		{
			//1번채널 사운드 디바이스가 열려있다면 닫는다.
			mciSendCommand(m_h2, MCI_CLOSE, 0, (DWORD)NULL);
		}
	}

	MCI_OPEN_PARMS a;
	MCI_PLAY_PARMS b;
	DWORD r;
	a.lpstrDeviceType = _T("WaveAudio");
	a.lpstrElementName = filename;
	// 사운드 카드를 열어 핸들을 확보
	r = mciSendCommand(ch, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&a);
	//if( r )
	//{
	//}
	UINT chid;
	chid = a.wDeviceID; //채널번호를 넘겨준다.
	//핸들을 이용해 플레이 명령을 내린다.
	mciSendCommand(chid, MCI_PLAY, 0, (DWORD)(LPVOID)&b);
	// 정지 명령도 여러가지가 있을수있으나 가장 확실한것은 디바이스를 닫는것이다.
	if (0 == ch) //0번 채널
	{
		m_h1 = chid;
	}
	else //1번 채널
	{
		m_h2 = chid;
	}
}