#include "SoundManager.h"


CSoundManager::CSoundManager()
{
	System_Create(&pSystem);

	pSystem->init(1, FMOD_INIT_NORMAL, NULL);
}


CSoundManager::~CSoundManager()
{
}

void CSoundManager::InsertSound(const char* str, int soundidx, bool IsLoop)
{
	if (IsLoop)
		pSystem->createSound(
			str,
			FMOD_HARDWARE | FMOD_LOOP_NORMAL,	//	�������Ͽɼ�
			NULL,			//	Ȯ�嵥����(��������)
			&pSound[soundidx]		//	������ ���� ������
		);
	else
		pSystem->createSound(
			str,
			FMOD_HARDWARE | FMOD_DEFAULT,	//	�������Ͽɼ�
			NULL,			//	Ȯ�嵥����(��������)
			&pSound[soundidx]		//	������ ���� ������
		);

}

void CSoundManager::SoundPlay(int soundidx, int channelidx)
{
	//pChannel[0]->isPlaying((bool*)true);
	pSystem->playSound(FMOD_CHANNEL_REUSE, pSound[soundidx], false, &pChannel[channelidx]);
}

void CSoundManager::StopPlay(int channelidx)
{
	pChannel[0]->stop();
	//pSystem->release();
	//pSystem->close();
}
