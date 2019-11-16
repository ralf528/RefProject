#include "stdafx.h"
#include "AniMgr.h"
#include "ImageNode.h"
#include "ImageNode.h"

AniMgr::AniMgr(void)
	:m_isRender(true)
{
	init();
}

AniMgr::~AniMgr(void)
{
	release();
}

void AniMgr::render(HDC hdc,int ID, int cx, int cy)
{
	if(m_isRender == true)
	{
		 m_image[ID].render(hdc,
			cx - m_info[ID].aniSize.cx / 2,
			cy - m_info[ID].aniSize.cx / 2,
			m_info[ID].aniSize.cx,
			m_info[ID].aniSize.cy,
			m_info[ID].aniSize.cx * m_info[ID].nowFrame,
			0,
			m_info[ID].aniSize.cx,
			m_info[ID].aniSize.cy);
	}
}

//void AniMgr::animation(int ID)
//{
//	updateAni(&m_info[ID]);
//}

void AniMgr::animation(int ID)
{
	updateAni(&m_info[ID]);
}

void AniMgr::init(void)
{
	effectInit();
}

void AniMgr::effectInit(void)
{
	srand((unsigned)time(NULL));
	unsigned int flag=0;
	if(m_image != NULL)

	if(m_image != NULL)
	{
		release();
	}
	int frame = 0;
	// enum문으로 순서가 정해지면
	//const int EFFECT = 2;
	
	
	/*for (int i = EFFECT + ET_STR; i <= EFFECT + AckEffect::ET_END; i++)
	{
		m_image = new imageClass(i);
	}*/
	m_image = new ImageNode[AniEffect::ET_END];

	// 정보
	m_info = new ANI_INFO[AniEffect::ET_END];
	//고블린 이동 전진
	m_image[AniEffect::ET_STR].load("Data/resource/image/dd.bmp",0,0,RM_TRANS);
	SIZE aniSize = m_image[AniEffect::ET_STR].getSize();
	m_info[AniEffect::ET_STR].frameCntX = 14;
	m_info[AniEffect::ET_STR].frameCntY = 1;
	m_info[AniEffect::ET_STR].aniSize.cx = aniSize.cx / m_info[0].frameCntX ;
	m_info[AniEffect::ET_STR].aniSize.cy = aniSize.cy / m_info[0].frameCntY;
	m_info[AniEffect::ET_STR].frameSpeed = 80;
	m_info[AniEffect::ET_STR].lastTime = GetTickCount();
	m_info[AniEffect::ET_STR].loop = true;	
	m_info[AniEffect::ET_STR].nowFrame = (flag = rand()%14+1);
	m_info[AniEffect::ET_STR].playAni = true;
	
	//피 폭발
	m_image[AniEffect::ET_STR1].load("Data/Resource/Image/blood.bmp",0,0,RM_TRANS);
	SIZE aniSize1 = m_image[AniEffect::ET_STR1].getSize();
	m_info[AniEffect::ET_STR1].frameCntX = 6;
	m_info[AniEffect::ET_STR1].frameCntY = 1;
	m_info[AniEffect::ET_STR1].aniSize.cx = aniSize1.cx / m_info[AniEffect::ET_STR1].frameCntX;
	m_info[AniEffect::ET_STR1].aniSize.cy = aniSize1.cy / m_info[AniEffect::ET_STR1].frameCntY;
	m_info[AniEffect::ET_STR1].frameSpeed = 80;
	m_info[AniEffect::ET_STR1].lastTime = GetTickCount();
	m_info[AniEffect::ET_STR1].loop = true;
	m_info[AniEffect::ET_STR1].nowFrame = frame;
	m_info[AniEffect::ET_STR1].playAni = true;

	//화염 불꽃
	m_image[AniEffect::ET_STR2].load("Data/Resource/Image/effect.bmp",0,0,RM_TRANS);
	SIZE aniSize2 = m_image[AniEffect::ET_STR2].getSize();
	m_info[AniEffect::ET_STR2].frameCntX = 16;
	m_info[AniEffect::ET_STR2].frameCntY = 1;
	m_info[AniEffect::ET_STR2].aniSize.cx = aniSize2.cx / m_info[AniEffect::ET_STR2].frameCntX;
	m_info[AniEffect::ET_STR2].aniSize.cy = aniSize2.cy / m_info[AniEffect::ET_STR2].frameCntY;
	m_info[AniEffect::ET_STR2].frameSpeed = 80;
	m_info[AniEffect::ET_STR2].lastTime = GetTickCount();
	m_info[AniEffect::ET_STR2].loop = true;
	m_info[AniEffect::ET_STR2].nowFrame = frame;
	m_info[AniEffect::ET_STR2].playAni = true;
	//케릭터 애니메이션
	//공격 모션
	m_image[AniEffect::ET_STR3].load("Data/Resource/Image/ATK.bmp",0,0,RM_TRANS);
	 SIZE aniSize3 = m_image[AniEffect::ET_STR3].getSize();
	m_info[AniEffect::ET_STR3].frameCntX = 5;
	m_info[AniEffect::ET_STR3].frameCntY = 1;
	m_info[AniEffect::ET_STR3].aniSize.cx = aniSize3.cx / m_info[AniEffect::ET_STR3].frameCntX;
	m_info[AniEffect::ET_STR3].aniSize.cy = aniSize3.cy / m_info[AniEffect::ET_STR3].frameCntY;
	m_info[AniEffect::ET_STR3].frameSpeed = 40;
	m_info[AniEffect::ET_STR3].lastTime = GetTickCount();
	m_info[AniEffect::ET_STR3].loop = true;
	m_info[AniEffect::ET_STR3].nowFrame = 0;
	m_info[AniEffect::ET_STR3].playAni = true;
	//아래
	m_image[AniEffect::CHAR_D].load("Data/Resource/Image/walk/D_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize4 = m_image[AniEffect::CHAR_D].getSize();
	m_info[AniEffect::CHAR_D].frameCntX = 3;
	m_info[AniEffect::CHAR_D].frameCntY = 1;
	m_info[AniEffect::CHAR_D].aniSize.cx = aniSize4.cx / m_info[AniEffect::CHAR_D].frameCntX;
	m_info[AniEffect::CHAR_D].aniSize.cy = aniSize4.cy / m_info[AniEffect::CHAR_D].frameCntY;
	m_info[AniEffect::CHAR_D].frameSpeed = 120;
	m_info[AniEffect::CHAR_D].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_D].loop = true;
	m_info[AniEffect::CHAR_D].nowFrame = 0;
	m_info[AniEffect::CHAR_D].playAni = true;
	//위로
	m_image[AniEffect::CHAR_U].load("Data/Resource/Image/walk/U_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize5 = m_image[AniEffect::CHAR_U].getSize();
	m_info[AniEffect::CHAR_U].frameCntX = 3;
	m_info[AniEffect::CHAR_U].frameCntY = 1;
	m_info[AniEffect::CHAR_U].aniSize.cx = aniSize5.cx / m_info[AniEffect::CHAR_U].frameCntX;
	m_info[AniEffect::CHAR_U].aniSize.cy = aniSize5.cy / m_info[AniEffect::CHAR_U].frameCntY;
	m_info[AniEffect::CHAR_U].frameSpeed = 120;
	m_info[AniEffect::CHAR_U].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_U].loop = true;
	m_info[AniEffect::CHAR_U].nowFrame = 0;
	m_info[AniEffect::CHAR_U].playAni = true;
	//왼쪽
	m_image[AniEffect::CHAR_L].load("Data/Resource/Image/walk/L_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize6 = m_image[AniEffect::CHAR_L].getSize();
	m_info[AniEffect::CHAR_L].frameCntX = 3;
	m_info[AniEffect::CHAR_L].frameCntY = 1;
	m_info[AniEffect::CHAR_L].aniSize.cx = aniSize6.cx / m_info[AniEffect::CHAR_L].frameCntX;
	m_info[AniEffect::CHAR_L].aniSize.cy = aniSize6.cy / m_info[AniEffect::CHAR_L].frameCntY;
	m_info[AniEffect::CHAR_L].frameSpeed = 120;
	m_info[AniEffect::CHAR_L].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_L].loop = true;
	m_info[AniEffect::CHAR_L].nowFrame = 0;
	m_info[AniEffect::CHAR_L].playAni = true;
	//오른쪽
	m_image[AniEffect::CHAR_R].load("Data/Resource/Image/walk/R_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize7 = m_image[AniEffect::CHAR_R].getSize();
	m_info[AniEffect::CHAR_R].frameCntX = 3;
	m_info[AniEffect::CHAR_R].frameCntY = 1;
	m_info[AniEffect::CHAR_R].aniSize.cx = aniSize7.cx / m_info[AniEffect::CHAR_R].frameCntX;
	m_info[AniEffect::CHAR_R].aniSize.cy = aniSize7.cy / m_info[AniEffect::CHAR_R].frameCntY;
	m_info[AniEffect::CHAR_R].frameSpeed = 120;
	m_info[AniEffect::CHAR_R].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_R].loop = true;
	m_info[AniEffect::CHAR_R].nowFrame = 0;
	m_info[AniEffect::CHAR_R].playAni = true;
	//왼쪽위
	m_image[AniEffect::CHAR_LU].load("Data/Resource/Image/walk/UL_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize8 = m_image[AniEffect::CHAR_LU].getSize();
	m_info[AniEffect::CHAR_LU].frameCntX = 3;
	m_info[AniEffect::CHAR_LU].frameCntY = 1;
	m_info[AniEffect::CHAR_LU].aniSize.cx = aniSize8.cx / m_info[AniEffect::CHAR_LU].frameCntX;
	m_info[AniEffect::CHAR_LU].aniSize.cy = aniSize8.cy / m_info[AniEffect::CHAR_LU].frameCntY;
	m_info[AniEffect::CHAR_LU].frameSpeed = 120;
	m_info[AniEffect::CHAR_LU].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_LU].loop = true;
	m_info[AniEffect::CHAR_LU].nowFrame = 0;
	m_info[AniEffect::CHAR_LU].playAni = true;
		//오른쪽 위
	m_image[AniEffect::CHAR_RU].load("Data/Resource/Image/walk/UR_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize9 = m_image[AniEffect::CHAR_RU].getSize();
	m_info[AniEffect::CHAR_RU].frameCntX = 3;
	m_info[AniEffect::CHAR_RU].frameCntY = 1;
	m_info[AniEffect::CHAR_RU].aniSize.cx = aniSize9.cx / m_info[AniEffect::CHAR_RU].frameCntX;
	m_info[AniEffect::CHAR_RU].aniSize.cy = aniSize9.cy / m_info[AniEffect::CHAR_RU].frameCntY;
	m_info[AniEffect::CHAR_RU].frameSpeed = 120;
	m_info[AniEffect::CHAR_RU].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_RU].loop = true;
	m_info[AniEffect::CHAR_RU].nowFrame = 0;
	m_info[AniEffect::CHAR_RU].playAni = true;
	//왼쪽아래
	m_image[AniEffect::CHAR_LD].load("Data/Resource/Image/walk/DL_Walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize10 = m_image[AniEffect::CHAR_LD].getSize();
	m_info[AniEffect::CHAR_LD].frameCntX = 3;
	m_info[AniEffect::CHAR_LD].frameCntY = 1;
	m_info[AniEffect::CHAR_LD].aniSize.cx = aniSize10.cx / m_info[AniEffect::CHAR_LD].frameCntX;
	m_info[AniEffect::CHAR_LD].aniSize.cy = aniSize10.cy / m_info[AniEffect::CHAR_LD].frameCntY;
	m_info[AniEffect::CHAR_LD].frameSpeed = 120;
	m_info[AniEffect::CHAR_LD].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_LD].loop = true;
	m_info[AniEffect::CHAR_LD].nowFrame = 0;
	m_info[AniEffect::CHAR_LD].playAni = true;
	//오른쪽 아래
	m_image[AniEffect::CHAR_RD].load("Data/Resource/Image/DR_walk.bmp",0,0,RM_TRANS);
	 SIZE aniSize11 = m_image[AniEffect::CHAR_RD].getSize();
	m_info[AniEffect::CHAR_RD].frameCntX = 3;
	m_info[AniEffect::CHAR_RD].frameCntY = 1;
	m_info[AniEffect::CHAR_RD].aniSize.cx = aniSize11.cx / m_info[AniEffect::CHAR_RD].frameCntX;
	m_info[AniEffect::CHAR_RD].aniSize.cy = aniSize11.cy / m_info[AniEffect::CHAR_RD].frameCntY;
	m_info[AniEffect::CHAR_RD].frameSpeed = 120;
	m_info[AniEffect::CHAR_RD].lastTime = GetTickCount();
	m_info[AniEffect::CHAR_RD].loop = true;
	m_info[AniEffect::CHAR_RD].nowFrame = 0;
	m_info[AniEffect::CHAR_RD].playAni = true;

	m_image[AniEffect::ATK_L].load("Data/Resource/Image/ATK/attack-w.bmp",0,0,RM_TRANS);
	 SIZE aniSize12 = m_image[AniEffect::ATK_L].getSize();
	m_info[AniEffect::ATK_L].frameCntX = 18 ;
	m_info[AniEffect::ATK_L].frameCntY = 1;
	m_info[AniEffect::ATK_L].aniSize.cx = aniSize12.cx / m_info[AniEffect::ATK_L].frameCntX;
	m_info[AniEffect::ATK_L].aniSize.cy = aniSize12.cy / m_info[AniEffect::ATK_L].frameCntY;
	m_info[AniEffect::ATK_L].frameSpeed = 30;
	m_info[AniEffect::ATK_L].lastTime = GetTickCount();
	m_info[AniEffect::ATK_L].loop = true;
	m_info[AniEffect::ATK_L].nowFrame = 0;
	m_info[AniEffect::ATK_L].playAni = true;

	m_image[AniEffect::ATK_R].load("Data/Resource/Image/ATK/attack-e.bmp",0,0,RM_TRANS);
	 SIZE aniSize13 = m_image[AniEffect::ATK_R].getSize();
	m_info[AniEffect::ATK_R].frameCntX = 18;
	m_info[AniEffect::ATK_R].frameCntY = 1;
	m_info[AniEffect::ATK_R].aniSize.cx = aniSize13.cx / m_info[AniEffect::ATK_R].frameCntX;
	m_info[AniEffect::ATK_R].aniSize.cy = aniSize13.cy / m_info[AniEffect::ATK_R].frameCntY;
	m_info[AniEffect::ATK_R].frameSpeed = 30;
	m_info[AniEffect::ATK_R].lastTime = GetTickCount();
	m_info[AniEffect::ATK_R].loop = true;
	m_info[AniEffect::ATK_R].nowFrame = 0;
	m_info[AniEffect::ATK_R].playAni = true;

   m_image[AniEffect::ATK_U].load("Data/Resource/Image/ATK/attack-n.bmp",0,0,RM_TRANS);
	 SIZE aniSize14 = m_image[AniEffect::ATK_U].getSize();
	m_info[AniEffect::ATK_U].frameCntX = 18;
	m_info[AniEffect::ATK_U].frameCntY = 1;
	m_info[AniEffect::ATK_U].aniSize.cx = aniSize14.cx / m_info[AniEffect::ATK_U].frameCntX;
	m_info[AniEffect::ATK_U].aniSize.cy = aniSize14.cy / m_info[AniEffect::ATK_U].frameCntY;
	m_info[AniEffect::ATK_U].frameSpeed = 30;
	m_info[AniEffect::ATK_U].lastTime = GetTickCount();
	m_info[AniEffect::ATK_U].loop = true;
	m_info[AniEffect::ATK_U].nowFrame = 0;
	m_info[AniEffect::ATK_U].playAni = true;

   m_image[AniEffect::ATK_D].load("Data/Resource/Image/ATK/attack-s.bmp",0,0,RM_TRANS);
	 SIZE aniSize15 = m_image[AniEffect::ATK_D].getSize();
	m_info[AniEffect::ATK_D].frameCntX = 18;
	m_info[AniEffect::ATK_D].frameCntY = 1;
	m_info[AniEffect::ATK_D].aniSize.cx = aniSize15.cx / m_info[AniEffect::ATK_D].frameCntX;
	m_info[AniEffect::ATK_D].aniSize.cy = aniSize15.cy / m_info[AniEffect::ATK_D].frameCntY;
	m_info[AniEffect::ATK_D].frameSpeed = 30;
	m_info[AniEffect::ATK_D].lastTime = GetTickCount();
	m_info[AniEffect::ATK_D].loop = true;
	m_info[AniEffect::ATK_D].nowFrame = 0;
	m_info[AniEffect::ATK_D].playAni = true;

    m_image[AniEffect::ATK_LU].load("Data/Resource/Image/ATK/attack-nw.bmp",0,0,RM_TRANS);
	 SIZE aniSize16 = m_image[AniEffect::ATK_LU].getSize();
	m_info[AniEffect::ATK_LU].frameCntX = 18;
	m_info[AniEffect::ATK_LU].frameCntY = 1;
	m_info[AniEffect::ATK_LU].aniSize.cx = aniSize16.cx / m_info[AniEffect::ATK_LU].frameCntX;
	m_info[AniEffect::ATK_LU].aniSize.cy = aniSize16.cy / m_info[AniEffect::ATK_LU].frameCntY;
	m_info[AniEffect::ATK_LU].frameSpeed = 30;
	m_info[AniEffect::ATK_LU].lastTime = GetTickCount();
	m_info[AniEffect::ATK_LU].loop = true;
	m_info[AniEffect::ATK_LU].nowFrame = 0;
	m_info[AniEffect::ATK_LU].playAni = true;

    m_image[AniEffect::ATK_RU].load("Data/Resource/Image/ATK/attack-ne.bmp",0,0,RM_TRANS);
	 SIZE aniSize17 = m_image[AniEffect::ATK_RU].getSize();
	m_info[AniEffect::ATK_RU].frameCntX = 18;
	m_info[AniEffect::ATK_RU].frameCntY = 1;
	m_info[AniEffect::ATK_RU].aniSize.cx = aniSize17.cx / m_info[AniEffect::ATK_RU].frameCntX;
	m_info[AniEffect::ATK_RU].aniSize.cy = aniSize17.cy / m_info[AniEffect::ATK_RU].frameCntY;
	m_info[AniEffect::ATK_RU].frameSpeed = 30;
	m_info[AniEffect::ATK_RU].lastTime = GetTickCount();
	m_info[AniEffect::ATK_RU].loop = true;
	m_info[AniEffect::ATK_RU].nowFrame = 0;
	m_info[AniEffect::ATK_RU].playAni = true;

   m_image[AniEffect::ATK_LD].load("Data/Resource/Image/ATK/attack-sw.bmp",0,0,RM_TRANS);
	 SIZE aniSize18 = m_image[AniEffect::ATK_LD].getSize();
	m_info[AniEffect::ATK_LD].frameCntX = 18;
	m_info[AniEffect::ATK_LD].frameCntY = 1;
	m_info[AniEffect::ATK_LD].aniSize.cx = aniSize18.cx / m_info[AniEffect::ATK_LD].frameCntX;
	m_info[AniEffect::ATK_LD].aniSize.cy = aniSize18.cy / m_info[AniEffect::ATK_LD].frameCntY;
	m_info[AniEffect::ATK_LD].frameSpeed = 30;
	m_info[AniEffect::ATK_LD].lastTime = GetTickCount();
	m_info[AniEffect::ATK_LD].loop = true;
	m_info[AniEffect::ATK_LD].nowFrame = 0;                                                                             
	m_info[AniEffect::ATK_LD].playAni = true;

   m_image[AniEffect::ATK_RD].load("Data/Resource/Image/ATK/attack-se.bmp",0,0,RM_TRANS);
	 SIZE aniSize19 = m_image[AniEffect::ATK_RD].getSize();
	m_info[AniEffect::ATK_RD].frameCntX = 18;
	m_info[AniEffect::ATK_RD].frameCntY = 1;
	m_info[AniEffect::ATK_RD].aniSize.cx = aniSize19.cx / m_info[AniEffect::ATK_RD].frameCntX;
	m_info[AniEffect::ATK_RD].aniSize.cy = aniSize19.cy / m_info[AniEffect::ATK_RD].frameCntY;
	m_info[AniEffect::ATK_RD].frameSpeed = 30;
	m_info[AniEffect::ATK_RD].lastTime = GetTickCount();
	m_info[AniEffect::ATK_RD].loop = true;
	m_info[AniEffect::ATK_RD].nowFrame = 0;
	m_info[AniEffect::ATK_RD].playAni = true;

	m_image[AniEffect::GBL_ATK].load("Data/Resource/Image/monster/Gob_D_Atk.bmp",0,0,RM_TRANS);
	SIZE aniSize20 = m_image[AniEffect::ATK_RD].getSize();
	m_info[AniEffect::GBL_ATK].frameCntX = 17;
	m_info[AniEffect::GBL_ATK].frameCntY = 1;
	m_info[AniEffect::GBL_ATK].aniSize.cx = aniSize20.cx / m_info[AniEffect::GBL_ATK].frameCntX;
	m_info[AniEffect::GBL_ATK].aniSize.cy = aniSize20.cy / m_info[AniEffect::GBL_ATK].frameCntY;
	m_info[AniEffect::GBL_ATK].frameSpeed = 120;
	m_info[AniEffect::GBL_ATK].lastTime = GetTickCount();
	m_info[AniEffect::GBL_ATK].loop = true;
	m_info[AniEffect::GBL_ATK].nowFrame = 0;
	m_info[AniEffect::GBL_ATK].playAni = true;
	
}



void AniMgr::updateAni(LPANI_INFO aniInfo)
{
	//현대 시간을 얻는다
	if(aniInfo != NULL && aniInfo->playAni == true)
	{
		//현재시간을 얻는다
		DWORD curTime = GetTickCount();
		if(aniInfo->lastTime + aniInfo->frameSpeed <= curTime)
		{
			//갱신한다
			aniInfo->nowFrame++;
			//마지막을 갱신한다
			aniInfo->lastTime=curTime;

			//애니메이션 개수체크(인덱스)
			if(aniInfo->frameCntX<= aniInfo->nowFrame)
			{
				aniInfo->nowFrame=0;
				if(aniInfo->loop == false)
				{
					aniInfo->playAni = false;
					m_isRender = false;
				}
			}
		}
	}
}

void AniMgr::release(void)
{
	SAFE_DELETE_ARR( m_image );
	SAFE_DELETE_ARR( m_info);
}