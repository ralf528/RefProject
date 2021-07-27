#include "stdafx.h"
#include "skillWhole.h"

//������ �Ҹ���
skillWhole::skillWhole(void)
	: cProjectile( SCREEN_X/2 , 50 )
{
	RC_MGR->addImage( imgID_SKILL_SCREEN, L"Data/Resource/Image/skill/��ü��ų.bmp", 0, 0 , RM_TRANS );
	m_count = m_speed;
	m_AniFlag = false;
	setAniInfo();
}
skillWhole::~skillWhole(void)
{
	releaseAniInfo();
	release();
}

//< �������̽�	
//������Ʈ
void skillWhole::update(void)
{
	//< ��ų�� Ȱ��ȭ �ȴٸ�
	if( true == m_AniFlag )
	{
		//< ī��Ʈ (������ �������� �ߵ�)
		if(m_Ani_Info->flag == false)
		{
			
			//< ��ų Ȱ��ȭ
			m_flag = true;
			//< ī��Ʈ �ʱ�ȭ
			m_count = m_speed;
			
			//< �ִϸ��̼� ����
			m_AniFlag = false;
		}
		//< �浹ü ������Ʈ
		setRect();
	}
	else
	{
		//< �浹ü ��Ȱ��ȭ
		m_flag = false;
	}
	
	updateAni( m_Ani_Info );
}
//�׸���
void skillWhole::render(HDC hdc)
{
	//< �ִϸ��̼� ���̸�
	if( true == m_AniFlag )
	{
		//< ��ü ��ųȭ��
		RENDER_MGR->render( hdc, imgID_SKILL_SCREEN,
				m_pos.x - m_Ani_Info->aniSize.cx/2 - CAMERA->getX() +50, m_pos.y - m_Ani_Info->aniSize.cy/2 - RENDER_OFFSET_Y - CAMERA->getY()+50,
				m_Ani_Info->aniSize.cx, 	m_Ani_Info->aniSize.cy,
				m_Ani_Info->nowFrame * m_Ani_Info->aniSize.cx,	m_Ani_Info->nowFrameY * m_Ani_Info->aniSize.cy,
				m_Ani_Info->aniSize.cx, m_Ani_Info->aniSize.cy);
		//< ��ų ����
		//Rectangle(hdc, m_rect.left - CAMERA->getX() , m_rect.top - CAMERA->getY(), m_rect.right - CAMERA->getX(), m_rect. bottom - CAMERA->getY() );
	}
}

//< �߻� (���� ����)
void skillWhole::shoot( POINT &startPoint, POINT &destPos )
{
	if( false == m_AniFlag )
	{				
		//��ġ ����
		m_pos = m_startPos = startPoint;
		//��ǥ ���� ����
		m_destPos = destPos;
		//SOUND_MGR->soundPlay(SKILL_START);
		
		//�ִϸ��̼� ����
		m_AniFlag = true;		
		
		m_Ani_Info->flag = true;
	}
}

//< ���� �Լ�

//��Ʈ ����
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