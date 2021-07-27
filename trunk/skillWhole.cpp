#include "stdafx.h"
#include "skillWhole.h"

//생성자 소멸자
skillWhole::skillWhole(void)
	: cProjectile( SCREEN_X/2 , 50 )
{
	RC_MGR->addImage( imgID_SKILL_SCREEN, L"Data/Resource/Image/skill/전체스킬.bmp", 0, 0 , RM_TRANS );
	m_count = m_speed;
	m_AniFlag = false;
	setAniInfo();
}
skillWhole::~skillWhole(void)
{
	releaseAniInfo();
	release();
}

//< 인터페이스	
//업데이트
void skillWhole::update(void)
{
	//< 스킬이 활성화 된다면
	if( true == m_AniFlag )
	{
		//< 카운트 (마지막 순간에만 발동)
		if(m_Ani_Info->flag == false)
		{
			
			//< 스킬 활성화
			m_flag = true;
			//< 카운트 초기화
			m_count = m_speed;
			
			//< 애니메이션 종료
			m_AniFlag = false;
		}
		//< 충돌체 업데이트
		setRect();
	}
	else
	{
		//< 충돌체 비활성화
		m_flag = false;
	}
	
	updateAni( m_Ani_Info );
}
//그리기
void skillWhole::render(HDC hdc)
{
	//< 애니메이션 중이면
	if( true == m_AniFlag )
	{
		//< 전체 스킬화면
		RENDER_MGR->render( hdc, imgID_SKILL_SCREEN,
				m_pos.x - m_Ani_Info->aniSize.cx/2 - CAMERA->getX() +50, m_pos.y - m_Ani_Info->aniSize.cy/2 - RENDER_OFFSET_Y - CAMERA->getY()+50,
				m_Ani_Info->aniSize.cx, 	m_Ani_Info->aniSize.cy,
				m_Ani_Info->nowFrame * m_Ani_Info->aniSize.cx,	m_Ani_Info->nowFrameY * m_Ani_Info->aniSize.cy,
				m_Ani_Info->aniSize.cx, m_Ani_Info->aniSize.cy);
		//< 스킬 영역
		//Rectangle(hdc, m_rect.left - CAMERA->getX() , m_rect.top - CAMERA->getY(), m_rect.right - CAMERA->getX(), m_rect. bottom - CAMERA->getY() );
	}
}

//< 발사 (방향 지정)
void skillWhole::shoot( POINT &startPoint, POINT &destPos )
{
	if( false == m_AniFlag )
	{				
		//위치 설정
		m_pos = m_startPos = startPoint;
		//목표 방향 설정
		m_destPos = destPos;
		//SOUND_MGR->soundPlay(SKILL_START);
		
		//애니메이션 시작
		m_AniFlag = true;		
		
		m_Ani_Info->flag = true;
	}
}

//< 내부 함수

//렉트 설정
void skillWhole::setRect(void)
{
	SetRect(&m_rect, 
		m_pos.x - SCREEN_X/2, m_pos.y - SCREEN_Y/2,
		m_pos.x + SCREEN_X/2, m_pos.y + SCREEN_Y/2);
}

void skillWhole::setAniInfo( void )
{
	SAFE_DELETE( m_Ani_Info );
	m_Ani_Info = new ANI_INFO;
	m_Ani_Info->aniSize.cx = 1280;
	m_Ani_Info->aniSize.cy = 720;
	m_Ani_Info->frameCntX = 23;
	m_Ani_Info->frameCntY = 1;
	m_Ani_Info->frameSpeed = 100;
	m_Ani_Info->nowFrame = 0;
	m_Ani_Info->nowFrameY = 0;
	m_Ani_Info->lastTime = GetTickCount();
	m_Ani_Info->flag=false;
	m_Ani_Info->playAni=false;
}

void skillWhole::updateAni( LPANI_INFO info )
{
	if(NULL!=info && true == info->flag)
	{
		DWORD curTime = GetTickCount();

		if( info->lastTime + info->frameSpeed <= curTime )
		{
			info->nowFrame++;

			info->lastTime=curTime;

			if(info->frameCntX <= info->nowFrame)
			{
				info->nowFrame=0;
				if( info->playAni == false )
				{
					info->flag=false;
				}
			}
		}
	}
}
void skillWhole::releaseAniInfo(void)
{
	SAFE_DELETE( m_Ani_Info );
}