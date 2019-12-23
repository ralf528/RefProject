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
	return true;
}
//����
void cProjectile::release(void)
{
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
#ifdef _DEBUG
	if( true == m_flag )
	{
		Rectangle( hdc, m_rect.left - CAMERA->getX(), m_rect.top - CAMERA->getY(), m_rect.right - CAMERA->getX(), m_rect.bottom - CAMERA->getY() );
	}
#endif
}

//< �߻� (���� ����)
void cProjectile::shoot( POINT &startPoint, POINT &destPos )
{
 	if( false == m_flag )
	{				
		//��ġ ����
		m_pos = m_startPos = startPoint;
		//��ǥ ���� ����
		m_destPos = destPos;
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