#include "stdafx.h"
#include "sphereObject.h"

//생성자 소멸자
sphereObject::sphereObject( int damage, int range, int speed )
	:m_flag(false)
{
	init(damage,range,speed);
}
sphereObject::~sphereObject(void)
{
	release();
}

//< 인터페이스	
//초기화
bool sphereObject::init(int damage, int range, int speed)
{
	m_speed = speed;
	m_range = range;
	m_damage = damage;
	return true;
}
//해제
void sphereObject::release(void)
{
}
//업데이트
void sphereObject::update(void)
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
}
//그리기
void sphereObject::render(HDC hdc)
{
#ifdef _DEBUG
	if( true == m_flag )
	{
		Rectangle( hdc, m_rect.left - CAMERA->getX(), m_rect.top - CAMERA->getY(), m_rect.right - CAMERA->getX(), m_rect.bottom - CAMERA->getY() );
	}
#endif
}

//< 발사 (방향 지정)
void sphereObject::shoot( POINT &startPoint, POINT &destPos )
{
 	if( false == m_flag )
	{				
		//위치 설정
		m_pos = m_startPos = startPoint;
		//목표 방향 설정
		m_destPos = destPos;
		//구체 살리기
		m_flag = true;
	}
}

//위치 설정
void sphereObject::setPos(POINT pos)
{
	m_pos = pos;
}
void sphereObject::setPos(LONG x, LONG y)
{
	m_pos.x = x;
	m_pos.y = y;
}

//< 내부 함수

//렉트 설정
void sphereObject::setRect(void)
{
	SetRect(&m_rect, 
		m_pos.x - 10, m_pos.y - 10,
		m_pos.x + 10, m_pos.y + 10);
}