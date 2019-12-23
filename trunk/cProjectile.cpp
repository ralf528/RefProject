#include "stdafx.h"
#include "sphereObject.h"

//������ �Ҹ���
cProjectile::cProjectile( int damage, int range, int speed )
	:m_flag(false)
{
	init(damage,range,speed);
}
cProjectile::~cProjectile(void)
{
	release();
}

//< �������̽�	
//�ʱ�ȭ
bool cProjectile::init(int damage, int range, int speed)
{
	m_speed = speed;
	m_range = range;
	m_damage = damage;
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