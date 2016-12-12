#pragma once
#include "stdafx.h"

#pragma comment(lib, "winmm.lib" )
#include "FMOD\fmod.hpp"
#pragma	comment (lib, "FMOD/fmodex_vc.lib")


using namespace FMOD;

class CSoundManager
{
private:
	
	System*			pSystem;
	Sound*			pSound[5];					//	사운드의 개수만큼 필요
	Channel*		pChannel[5];				//	동시에 출력될 사운드 만큼 필요

	bool	bPlay = true;				// 플레이 관련 변수 -> 건들지 말기 이거 못고침~~~
	bool	IsBGPlaying = false;		// BGM 관련 재생 변수 -> 건들면 코드 버려야함~~~
		
public:
	CSoundManager();
	~CSoundManager();
	void InsertSound(const char* str, int soundidx, bool IsLoop = true);
	void SoundPlay(int soundidx, int channelidx);
	void StopPlay(int channelidx);
};

