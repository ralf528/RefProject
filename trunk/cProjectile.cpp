#include "stdafx.h"
#include "cProjectile.h"

//생성자 소멸자
cProjectile::cProjectile( int damage, int range, int speed, float fPrefDelay)
	:m_flag(false), m_fPrevDelayCount(0.f)
{
	init(damage,range,speed, fPrefDelay);
}
cProjectile::~cProjectile(void)
{
	release();
}

//< 인터페이스	
//초기화
bool cProjectile::init(int damage, int range, int speed, float fPrevDelay)
{
	m_speed = speed;
	m_range = range;
	m_damage = damage;
    m_fPrevDelay = fPrevDelay;
    m_fPrevDelayCount = 0.f;
	m_dir = DIR_D;
	m_ImgID = imgID_NONID;

	return true;
}

//해제
void cProjectile::release(void)
{
	SAFE_DELETE(m_Animation);
}

//업데이트
void cProjectile::update(void)
{
	//< 충돌체가 활성화 된다면
	if( true == m_flag )
	{
		//< 충돌체 이동
		if( true==math::moveToPt( &m_pos, &m_destPos, static_cast<float>(m_speed) ) )
		{
			m_flag = false;
		}
		//< 범위 체크
		float dist = math::distancePtToPt( m_startPos , m_pos );
		if( dist >= m_range )
		{
			//< 멀어지면 비활성화
			m_flag = false;
		}
		//< 충돌체 업데이트
		setRect();
	}
    else if (m_fPrevDelay > 0.f && m_fPrevDelayCount > 0.f)
    {
        m_fPrevDelayCount -= FpsTime::getElapsedTime();
        if (m_fPrevDelayCount <= 0.f)
        {
            m_flag = true;
        }
    }
}

//그리기
void cProjectile::render(HDC hdc)
{
	if (m_Animation != nullptr)
	{
		if (m_flag == true)
		{
			AniMgr::Render(hdc, m_Animation, m_pos, m_dir, imgID_ARCHER_ARROW);
		}
	}
#ifdef _DEBUG
	else if( true == m_flag )
	{
		Rectangle( hdc, m_rect.left - CAMERA->getX(), m_rect.top - CAMERA->getY(), m_rect.right - CAMERA->getX(), m_rect.bottom - CAMERA->getY() );
	}
#endif	
}

//< 발사 (방향 지정)
void cProjectile::shoot( POINT &startPoint, POINT &destPos, int dir )
{
 	if( false == m_flag )
	{				
		//위치 설정
		m_pos = m_startPos = startPoint;
		//목표 방향 설정
		m_destPos = destPos;
		m_dir = dir;

		//구체 살리기
		m_flag = true;
        if (m_fPrevDelay > 0.f)
        {
            m_flag = false;
            m_fPrevDelayCount = m_fPrevDelay;
        }
        setRect();
	}
}

//위치 설정
void cProjectile::setPos(POINT pos)
{
	m_pos = pos;
}
void cProjectile::setPos(LONG x, LONG y)
{
	m_pos.x = x;
	m_pos.y = y;
}

//< 내부 함수

//렉트 설정
void cProjectile::setRect(void)
{
	SetRect(&m_rect, 
		m_pos.x - 10, m_pos.y - 10,
		m_pos.x + 10, m_pos.y + 10);
}

void cProjectile::SetImage(E_ImageID InImgID, string InPath)
{
	m_ImgID = InImgID;

	SAFE_DELETE(m_Animation);
	m_Animation = new ANI_INFO;
	RC_MGR->addImage(m_ImgID, InPath.c_str(), 0, 0, RM_TRANS);
	//< 이미지 사이즈
	SIZE idleAniSize = RC_MGR->findImage(m_ImgID)->getSize();
	//< 프레임 수
	m_Animation->frameCntX = 1;
	m_Animation->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_Animation->aniSize.cx = idleAniSize.cx / m_Animation->frameCntX;
	m_Animation->aniSize.cy = idleAniSize.cy / m_Animation->frameCntY;

	m_Animation->frameSpeed = 0;
	m_Animation->nowFrame = 0;
	m_Animation->nowFrameY = DIR_D;
	m_Animation->lastTime = GetTickCount();
	m_Animation->flag = false;
	m_Animation->loop = false;
	m_Animation->playAni = false;
}