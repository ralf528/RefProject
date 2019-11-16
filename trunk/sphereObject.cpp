#include "stdafx.h"
#include "sphereObject.h"

//������ �Ҹ���
sphereObject::sphereObject( int damage, int range, int speed )
	:m_flag(false)
{
	init(damage,range,speed);
}
sphereObject::~sphereObject(void)
{
	release();
}

//< �������̽�	
//�ʱ�ȭ
bool sphereObject::init(int damage, int range, int speed)
{
	m_speed = speed;
	m_range = range;
	m_damage = damage;
	return true;
}
//����
void sphereObject::release(void)
{
}
//������Ʈ
void sphereObject::update(void)
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
void sphereObject::render(HDC hdc)
{
#ifdef _DEBUG
	if( true == m_flag )
	{
		Rectangle( hdc, m_rect.left - CAMERA->getX(), m_rect.top - CAMERA->getY(), m_rect.right - CAMERA->getX(), m_rect.bottom - CAMERA->getY() );
	}
#endif
}

//< �߻� (���� ����)
void sphereObject::shoot( POINT &startPoint, POINT &destPos )
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
void sphereObject::setPos(POINT pos)
{
	m_pos = pos;
}
void sphereObject::setPos(LONG x, LONG y)
{
	m_pos.x = x;
	m_pos.y = y;
}

//< ���� �Լ�

//��Ʈ ����
void sphereObject::setRect(void)
{
	SetRect(&m_rect, 
		m_pos.x - 10, m_pos.y - 10,
		m_pos.x + 10, m_pos.y + 10);
}