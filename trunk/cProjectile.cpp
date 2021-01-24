#include "stdafx.h"
#include "cProjectile.h"

//������ �Ҹ���
cProjectile::cProjectile( int damage, int range, int speed, float fPrefDelay)
	:m_flag(false), m_fPrevDelayCount(0.f)
{
	init(damage,range,speed, fPrefDelay);
}
cProjectile::~cProjectile(void)
{
	release();
}

//< �������̽�	
//�ʱ�ȭ
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

//����
void cProjectile::release(void)
{
	SAFE_DELETE(m_Animation);
}

//������Ʈ
void cProjectile::update(void)
{
	//< �浹ü�� Ȱ��ȭ �ȴٸ�
	if( true == m_flag )
	{
		//< �浹ü �̵�
		if( true==math::moveToPt( &m_pos, &m_destPos, static_cast<float>(m_speed) ) )
		{
			m_flag = false;
		}
		//< ���� üũ
		float dist = math::distancePtToPt( m_startPos , m_pos );
		if( dist >= m_range )
		{
			//< �־����� ��Ȱ��ȭ
			m_flag = false;
		}
		//< �浹ü ������Ʈ
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

//�׸���
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

//< �߻� (���� ����)
void cProjectile::shoot( POINT &startPoint, POINT &destPos, int dir )
{
 	if( false == m_flag )
	{				
		//��ġ ����
		m_pos = m_startPos = startPoint;
		//��ǥ ���� ����
		m_destPos = destPos;
		m_dir = dir;

		//��ü �츮��
		m_flag = true;
        if (m_fPrevDelay > 0.f)
        {
            m_flag = false;
            m_fPrevDelayCount = m_fPrevDelay;
        }
        setRect();
	}
}

//��ġ ����
void cProjectile::setPos(POINT pos)
{
	m_pos = pos;
}
void cProjectile::setPos(LONG x, LONG y)
{
	m_pos.x = x;
	m_pos.y = y;
}

//< ���� �Լ�

//��Ʈ ����
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
	//< �̹��� ������
	SIZE idleAniSize = RC_MGR->findImage(m_ImgID)->getSize();
	//< ������ ��
	m_Animation->frameCntX = 1;
	m_Animation->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
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