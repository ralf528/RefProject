#include "stdafx.h"
#include "sound.h"

//void SoundMgr::initSound(void)
//{
//	//음향 생성
//	volume = 0.5f;
//	FMOD_System_Create(&system);
//	FMOD_System_Init(system,1,FMOD_INIT_NORMAL,NULL);
//	FMOD_System_CreateSound(system,"Data/sound/[002]stage.mp3",FMOD_LOOP_NORMAL,0,&sound);
//}
//void SoundMgr::releaseSound(void)
//{
//	//사운드 해제
//	FMOD_Sound_Release( sound );
//	FMOD_System_Close( system );
//	FMOD_System_Release( system );
//}