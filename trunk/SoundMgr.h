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

	//ä�� ī��Ʈ ��ŭ ä�� ����
	HRESULT init(void);

	//����
	void release(void);
	//���ϸ� ����ü���� ������ ���� �̸� ,�ݺ��������
	void soundSetup(char* szFilename,int nSoundKind,bool bBackgrund=false, bool bSoundloop = false);
	//����� ���� �̸� (����ü���� ����), �ҷ�
	void soundPlay(int nSoundKind,float fVolume = 1.0f);
	// ������� ���带 �Ͻ� ���� ��Ų��.
	void soundPause(int nSoundKind);
	//�Ͻ������� ���带 �ٽ� ����Ѵ�
	void soundResume(int nSoundKind);
	//�Ͻ� �����Ǿ����� Ȯ��
	bool isPausedsound(int nsSoundKind);
	//������� ���带 ���� ��Ų��
	void soundStop(int nSoundKind);
	//��������� Ȯ��
	bool isPlaySound(int nSoundKind);
	//FMOD �ý��� ����
	void soundUpdate(void);
	//��ü���ο��� �����Ѵ�
	void createSystem(void);
	//���带 �ѹ��� �߻������ִ� �Լ�
	void soundButton(void);


	Channel* getChannel(int nSoundKind)
	{
		return this->m_pChannel[nSoundKind];
	}
};
#define SOUND_MGR Singleton<SoundMgr>::getInstance()