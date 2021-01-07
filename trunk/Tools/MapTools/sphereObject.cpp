#include "stdafx.h"
#include "ImageNode.h"
#include "sphereObject.h"

//������ �Ҹ���
sphereObject::sphereObject(void)
	:m_flag(false)
{
	init();
}
sphereObject::~sphereObject(void)
{
	release();
}

//< �������̽�	
//�ʱ�ȭ
bool sphereObject::init(void)
{
	m_speed = 5;
	m_img = new ImageNode(imgID_SPHERE);
	m_img->load("Data/sphere.bmp",0,0,RM_TRANS);

	return true;
}
//����
void sphereObject::release(void)
{
	SAFE_DELETE( m_img );
}
//������Ʈ
void sphereObject::update(void)
{
	if( true == m_flag )
	{
		switch( m_dir )
		{
		case 0:
			m_pos.x -= m_speed;
			break;
		case 1:
			m_pos.x -= m_speed;
			m_pos.y -= m_speed;
			break;
		case 2:
			m_pos.y -= m_speed;
			break;
		case 3:
			m_pos.x += m_speed;
			m_pos.y -= m_speed;
			break;
		case 4:
			m_pos.x += m_speed;
			break;
		case 5:
			m_pos.x += m_speed;
			m_pos.y += m_speed;
			break;
		case 6:
			m_pos.y += m_speed;
			break;
		case 7:
			m_pos.x -= m_speed;
			m_pos.y += m_speed;
			break;
		}
		if( myUTIL::math::distancePtToPt( m_startPos , m_pos ) > 100.0f )
		{
			m_flag = false;
		}
	}
}
//�׸���
void sphereObject::render(HDC hdc)
{
	if( true == m_flag )
	{
		m_img->render( hdc, m_pos.x - m_img->getSize().cx/2 , m_pos.y - m_img->getSize().cy/2 );
	}
}

//�߻�
void sphereObject::shoot( POINT &startPoint, int dir )
{
	if( false == m_flag )
	{
		//��ġ ����
		m_pos = m_startPos = startPoint;
		//���� ����
		m_dir = dir;
		//��ü �츮��
		m_flag = true;
	}
}
//

//��ġ ����
void sphereObject::setPos(POINT pos)
{
}
void sphereObject::setPos(LONG x, LONG y)
{
}

//< ���� �Լ�
//��Ʈ ����
void sphereObject::setRect(void)
{
}