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
	Sound*			pSound[5];					//	������ ������ŭ �ʿ�
	Channel*		pChannel[5];				//	���ÿ� ��µ� ���� ��ŭ �ʿ�

	bool	bPlay = true;				// �÷��� ���� ���� -> �ǵ��� ���� �̰� ����ħ~~~
	bool	IsBGPlaying = false;		// BGM ���� ��� ���� -> �ǵ�� �ڵ� ��������~~~
		
public:
	CSoundManager();
	~CSoundManager();
	void InsertSound(const char* str, int soundidx, bool IsLoop = true);
	void SoundPlay(int soundidx, int channelidx);
	void StopPlay(int channelidx);
};

