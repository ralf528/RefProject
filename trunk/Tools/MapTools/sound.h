#pragma once

#pragma comment(lib, "fmod_vc.lib")

#include "Singleton.h"

enum
{
	SOUND_CLIENT,
	SOUND_BGM
};

class SoundMgr
{
private:
	SoundMgr(void){}
	~SoundMgr(void){}

	SINGLETON(SoundMgr);

public:
	void initSound(void)
	{
		//���� ����
		volume = 0.5f;
		//�κ�
		FMOD_System_Create(&system);
		FMOD_System_Init(system,1,FMOD_INIT_NORMAL,NULL);
		FMOD_System_CreateSound(system,"Data/sound/[001]client.mp3",FMOD_LOOP_NORMAL,0,&sound[0]);
		//����
		FMOD_System_Create(&system);
		FMOD_System_Init(system,1,FMOD_INIT_NORMAL,NULL);
		FMOD_System_CreateSound(system,"Data/sound/[002]stage.mp3",FMOD_LOOP_NORMAL,0,&sound[1]);
	}
	//���� ����
	void releaseSound(void)
	{	
		FMOD_Channel_Stop(channel[0]);
		FMOD_Channel_Stop(channel[1]);
		FMOD_Sound_Release( sound[0] );
		FMOD_Sound_Release( sound[1] );
		FMOD_System_Close( system );
		FMOD_System_Release( system );
	}
	//���� ���
	void playSound(int channelNum)
	{
		FMOD_System_PlaySound(system,sound[channelNum],0, 0, &channel[channelNum]);
	}
	//���� ����
	void stopSound(int channelNum)
	{
		FMOD_Channel_Stop(channel[channelNum]);
	}

private:
	//����
	FMOD_SYSTEM *system;
	FMOD_SOUND *sound[2];
	FMOD_CHANNEL *channel[2];

	float volume;
	FMOD_BOOL IsPlaying;
};

#define SOUND_MGR Singleton<SoundMgr>::getInstance()