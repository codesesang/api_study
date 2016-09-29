#pragma once

#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

typedef struct {

	DWORD dwCallback;

	DWORD dwItem;

	DWORD dwValue;

	DWORD dwOver;

	LPSTR lpstrAlgorithm;

	LPSTR lpstrQuality;

} MCI_DGV_SETAUDIO_PARMS;

#define     MCI_SETAUDIO              0x0873 
#define     MCI_DGV_SETAUDIO_VOLUME    0x4002 
#define     MCI_DGV_SETAUDIO_ITEM      0x00800000 
#define     MCI_DGV_SETAUDIO_VALUE     0x01000000 
#define     MCI_DGV_STATUS_VOLUME  0x4019


class KMedia
{
public:
	KMedia(void);
	~KMedia(void);
private:
	MCI_OPEN_PARMS mciOpenParms;
	DWORD wDeviceID;
	LONG m_nTotalTime;
	MCI_PLAY_PARMS  mciPlayParms;

public:
	int   KMedia::GetVolume();
	void  KMedia::SetVolume(DWORD volume);

	DWORD  GetLength();
	DWORD  GetPosition();
	DWORD  GetMode();
	void  SetPosition(DWORD dwPos);
	BOOL  Stop();
	BOOL   Play();
	BOOL  Pause();
	void  Open(TCHAR* filename);

	////////////////////////for wave
private:
	UINT m_h1;
	UINT m_h2;
public:
	void PlayWave(TCHAR* filename, int ch);
};
