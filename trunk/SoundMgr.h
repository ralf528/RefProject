#pragma once

#include "Singleton.h"
#include "FMOD/inc/fmod.hpp"

using namespace FMOD;
#define EXTRA_SOUND_CHANNEL 5

#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL

class SoundMgr
{
private:
	SoundMgr(void);
	~SoundMgr(void);

	SINGLETON(SoundMgr);

	System*		m_pSystem;
	Sound**		m_pSound;
	Channel**	m_pChannel;

	

public:

	//채널 카운트 만큼 채널 생성
	HRESULT init(void);

	//정리
	void release(void);
	//파일명 열거체에서 정해준 사운드 이름 ,반복재생여부
	void soundSetup(char* szFilename,int nSoundKind,bool bBackgrund=false, bool bSoundloop = false);
	//재생할 사운드 이름 (열거체에서 설정), 불륨
	void soundPlay(int nSoundKind,float fVolume = 1.0f);
	// 재생중인 사운드를 일시 정지 시킨다.
	void soundPause(int nSoundKind);
	//일시정지된 사운드를 다시 재생한다
	void soundResume(int nSoundKind);
	//일시 정지되었는지 확인
	bool isPausedsound(int nsSoundKind);
	//재생중인 사운드를 정지 시킨다
	void soundStop(int nSoundKind);
	//재생중인지 확인
	bool isPlaySound(int nSoundKind);
	//FMOD 시스템 갱신
	void soundUpdate(void);
	//객체내부에서 생성한다
	void createSystem(void);
	//사운드를 한번만 발생시켜주는 함수
	void soundButton(void);


	Channel* getChannel(int nSoundKind)
	{
		return this->m_pChannel[nSoundKind];
	}
};
#define SOUND_MGR Singleton<SoundMgr>::getInstance()