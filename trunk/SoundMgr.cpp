#include "stdafx.h"
//#include "SoundMgr.h"
//
//
//
//SoundMgr::SoundMgr(void)
//	:m_pSound(NULL),m_pChannel(NULL),m_pSystem(NULL)
//{
//	init();
//}
//
//SoundMgr::~SoundMgr(void)
//{
//	release();
//}
//
//HRESULT SoundMgr::init(void)
//{
//	System_Create(&m_pSystem);
//
//	//m_pSystem->init(SOUND_END +1,FMOD_INIT_NORMAL,0);
//	
//	m_pSystem->init(SOUND_END,FMOD_INIT_NORMAL,0);
//
//	m_pSound = new Sound*[SOUND_END];
//	m_pChannel = new Channel *[SOUND_END];
//
//	memset(m_pSound,0,sizeof(Sound)*(SOUND_END));
//	memset(m_pChannel,0,sizeof(Channel*)*(SOUND_END));
//
//	//:�̰����� ���� ������ �ε��Ѵ�.
//	//�α׸�,Ÿ��Ʋ ����
//	soundSetup("Data/Resource/Sound/Title.mp3", SOUND_TITLE, true, true);
//	//�κ� ���� 
//	soundSetup("Data/Resource/Sound/Lobby.mp3", SOUND_LOBBY, true, true);
//	//���� ����
//	soundSetup("Data/Resource/Sound/Boss.mp3", SOUND_BOSS, true, true);
//	soundSetup("Data/Resource/Sound/Ingame.mp3", SOUND_INGAME, true, true);
//	//��ưŬ��,�˾� ����
//	soundSetup("Data/Resource/Sound/Popup.wav", SOUND_POPUP,true, false);
//	//�ɸ���----------------------------------------------------------------
//	//�ɸ��� ���� ����
//	soundSetup("Data/Resource/Sound/Character/PC_Attack.mp3",CHAR_ATK,true,false);
//	//�ɸ��� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Character/PC_Gethit.mp3",CHAR_HIT,true,false);
//	//�ɸ��� ��� ����
//	soundSetup("Data/Resource/Sound/Character/PC_Die.mp3",CHAR_DIE,true,false);
//
//	////���------------------------------------------------------------
//	//��� ���� ����
//	soundSetup("Data/Resource/Sound/goblin/Gob_Attack.wav",GLB_ATK,true,false);
//	//��� �ǰ� ����
//	soundSetup("Data/Resource/Sound/goblin/Gob_Gethit.wav",GLB_HIT,true,false);
//	//��� ��� ����
//	soundSetup("Data/Resource/Sound/goblin/Gob_Die.wav",GLB_DIE,true,false);
//	////����--------------------------------------------------------------
//	//���� ���� ����
//	soundSetup("Data/Resource/Sound/Bug/Bug_Attack.wav",BUG_ATK,true,false);
//	///���� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Bug/Bug_Gethit.wav",BUG_HIT,true,false);
//	//���� ��� ����
//	soundSetup("Data/Resource/Sound/Bug/Bug_Die.wav",BUG_DIE,true,false);
//	////����--------------------------------------------------------------
//	//���� ���� ����
//	soundSetup("Data/Resource/Sound/Ghoul/Ghl_Attack.wav",GUL_ATK,true,false);
//	///���� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Ghoul/Ghl_Gethit.wav",GUL_HIT,true,false);
//	//���� ��� ����
//	soundSetup("Data/Resource/Sound/Ghoul/Ghl_Die.wav",GUL_DIE,true,false);
//	////�����Ź�-----------------------------------------------------------
//	//�����Ź� ���� ����
//	soundSetup("Data/Resource/Sound/Darkspider/Spider_Attack.wav",SPIDER_ATK,true,false);
//	///�����Ź� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Darkspider/Spider_Gethit.wav",SPIDER_HIT,true,false);
//	//�����Ź� ��� ����
//	soundSetup("Data/Resource/Sound/Darkspider/Spider_Die.wav",SPIDER_DIE,true,false);
//	////����---------------------------------------------------------------
//	//���� ���� ����
//	soundSetup("Data/Resource/Sound/Spector/Spector_Attack.wav",STOR_ATK,true,false);
//	///���� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Spector/Spector_Gethit.wav",STOR_HIT,true,false);
//	//���� ��� ����
//	soundSetup("Data/Resource/Sound/Spector/Spector_Die.wav",STOR_DIE,true,false);
//	////�ΰ�����------------------------------------------------------------
//	//�ΰ����� ���� ����
//	soundSetup("Data/Resource/Sound/Warrior/Warrior_Attack.wav",WARRIOR_ATK,true,false);
//	///�ΰ����� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Warrior/Warrior_Gethit.wav",WARRIOR_HIT,true,false);
//	//�ΰ����� ��� ����
//	soundSetup("Data/Resource/Sound/Warrior/Warrior_Die.wav",WARRIOR_DIE,true,false);
//	////�ΰ�����------------------------------------------------------------
//	//�ΰ����� ���� ����
//	soundSetup("Data/Resource/Sound/Rogue/Rogue_Attack.wav",ROGUE_ATK,true,false);
//	///�ΰ����� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Rogue/Rogue_Gethit.wav",ROGUE_HIT,true,false);
//	//�ΰ����� ��� ����
//	soundSetup("Data/Resource/Sound/Rogue/Rogue_Die.wav",ROGUE_DIE,true,false);
//	////���̵�------------------------------------------------------------
//	//���̵� ���� ����
//	soundSetup("Data/Resource/Sound/Naid/Naid_Attack.wav",NAID_ATK,true,false);
//	///���̵� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Naid/Naid_Gethit.wav",NAID_HIT,true,false);
//	//���̵� ��� ����
//	soundSetup("Data/Resource/Sound/Naid/Naid_Die.wav",NAID_DIE,true,false);
//	//���� ����----------------------------------------------------------------
//	soundSetup("Data/Resource/Sound/boss/boss.mp3",BOSS_BGM,true,true);
//	//���� ���� ����
//	soundSetup("Data/Resource/Sound/boss/boss_Attack.wav",BOSS_ATK,true,false);
//	///���� �ǰ� ����
//	soundSetup("Data/Resource/Sound/boss/boss_Gethit.wav",BOSS_HIT,true,false);
//	//���� ��ų����1
//	soundSetup("Data/Resource/Sound/boss/Boss_Skill1.wav",BOSS_SKILL1,true,false);
//	//���� ��ų����2
//	soundSetup("Data/Resource/Sound/boss/Boss_Skill2.wav",BOSS_SKILL2,true,false);
//	//���� ��� ����
//	soundSetup("Data/Resource/Sound/boss/boss_Die.mp3",BOSS_DIE,true,false);
//
//
//	//��ų ����
//	soundSetup("Data/Resource/Sound/Skill_Start.mp3",SKILL_START,true,false);
//	soundSetup("Data/Resource/Sound/Skill_End.wav",SKILL_END,true,false);
//	//�ɸ��� �ǰ� ����
//	soundSetup("Data/Resource/Sound/Spider_Gethit.wav",CHAR_HIT,true,false);
////	soundSetup("Data/Resource/Sound/Sword flesh5.wav",SOUND_BGM4,true,false);
//	soundSetup("Data/Resource/Sound/swordclash1.mp3",SOUND_BGM5,true,false);
//	soundSetup("Data/Resource/Sound/blue2.wav",SOUND_BGM6,true,false);
//	//�α��� ���� ����
//	soundSetup("Data/Resource/Sound/baksu.mp3",SOUND_BGM7,true,false);
//	//�α��� ���� ����
//	soundSetup("Data/Resource/Sound/tting.mp3",SOUND_BGM8,true,false);
//	//���ǸԴ� ����
//	soundSetup("Data/Resource/Sound/potion.wav",SOUND_BGM9,true,false);
//	return S_OK;
//}
//
//void SoundMgr::release(void)
//{
//	if(m_pChannel != NULL || m_pSound != NULL)
//	{
//		for(int i = 0; i < SOUND_END; i++)
//		{
//			if(m_pChannel != NULL)
//			{
//				if(m_pChannel[i])
//				{
//					m_pChannel[i] ->stop();
//				}
//			}
//			if(m_pSound != NULL)
//			{
//				if(m_pSound != NULL)
//				{
//					m_pSound[i]->release();
//				}
//			}
//
//		}
//	}
//
//	SAFE_DELETE_ARR(m_pChannel);
//	m_pChannel = NULL;
//	SAFE_DELETE_ARR(m_pSound);
//	m_pSound = NULL;
//
//	if(m_pSystem != NULL)
//	{
//		m_pSystem->release();
//		m_pSystem->close();
//	}
//}
//
//void SoundMgr::soundSetup(char * szFilename, int nSoundKind,bool bBackground,bool bSoundloop)
//{
//	if(bSoundloop == true)
//	{
//		if(bBackground)
//		{
//			m_pSystem->createStream(szFilename,FMOD_LOOP_NORMAL,0,&m_pSound[nSoundKind]);
//
//		}
//		else
//		{
//			m_pSystem->createSound(szFilename,FMOD_LOOP_NORMAL,0,&m_pSound[nSoundKind]);
//		}
//	}
//	else
//	{
//		m_pSystem->createSound(szFilename,FMOD_DEFAULT,0,&m_pSound[nSoundKind]);
//	}
//}
//
//void SoundMgr::soundPlay(int nSoundKind, float fVolume)
//{
//	// ���� �÷���
//	m_pSystem->playSound(m_pSound[nSoundKind],NULL,false,&m_pChannel[nSoundKind]);
//	//���� ����
//	m_pChannel[nSoundKind]->setVolume ( fVolume );
//
//}
////���� ������� ���带 �Ͻ����� ��Ų��
//void SoundMgr::soundPause(int nSoundKind)
//{
//	m_pChannel[nSoundKind]->setPaused(false);
//}
//
////�Ͻ������� ���带 �ٽ� ����Ѵ�
//void SoundMgr::soundResume(int nSoundKind)
//{
//	m_pChannel[nSoundKind]->setPaused(false);
//}
////�Ͻ����� �Ǿ����� Ȯ���Ѵ�
//bool SoundMgr::isPausedsound(int nSoundKind)
//{
//	bool isPause;
//	m_pChannel[nSoundKind]->getPaused(&isPause);
//	return isPause;
//}
//
////���� ������� ���带 ���� ��Ų��
//void SoundMgr::soundStop(int nSoundKind)
//{
//	if(NULL == m_pChannel)
//	{return ;}
//	m_pChannel[nSoundKind]->stop();
//}
//
////���� ��������� Ȯ���Ѵ�
//bool SoundMgr::isPlaySound(int nSoundKind)
//{
//	bool isPlay;
//	m_pChannel [nSoundKind]->isPlaying(&isPlay);
//	return isPlay;
//}
//
////FMOD �ý����� �����Ѵ�
//void SoundMgr::soundUpdate(void)
//{
//	m_pSystem->update();
//}