#include "stdafx.h"
#include "ImageNode.h"
#include "sphereObject.h"

//생성자 소멸자
sphereObject::sphereObject(void)
	:m_flag(false)
{
	init();
}
sphereObject::~sphereObject(void)
{
	release();
}

//< 인터페이스	
//초기화
bool sphereObject::init(void)
{
	m_speed = 5;
	m_img = new ImageNode(imgID_SPHERE);
	m_img->load("Data/sphere.bmp",0,0,RM_TRANS);

	return true;
}
//해제
void sphereObject::release(void)
{
	SAFE_DELETE( m_img );
}
//업데이트
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
//그리기
void sphereObject::render(HDC hdc)
{
	if( true == m_flag )
	{
		m_img->render( hdc, m_pos.x - m_img->getSize().cx/2 , m_pos.y - m_img->getSize().cy/2 );
	}
}

//발사
void sphereObject::shoot( POINT &startPoint, int dir )
{
	if( false == m_flag )
	{
		//위치 설정
		m_pos = m_startPos = startPoint;
		//방향 설정
		m_dir = dir;
		//구체 살리기
		m_flag = true;
	}
}
//

//위치 설정
void sphereObject::setPos(POINT pos)
{
}
void sphereObject::setPos(LONG x, LONG y)
{
}

//< 내부 함수
//렉트 설정
void sphereObject::setRect(void)
{
}