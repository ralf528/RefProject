#include "stdafx.h"
#include "camera.h"


Camera::Camera(void)
	: m_isShaking(false)
{
	init();
}
Camera::~Camera(void)
{
}

//< 초기화
void Camera::init(void)
{
	m_shakeStart=0;
	prevPosX=0;
	prevPosY=0;
	m_viewOffSetY=0;
	m_viewOffSetX=0;
	m_shakeCount=false;
}
//< 카메라 갱신
void Camera::update(void)
{
	//< 카메라 셰이킹
	if( m_isShaking == true )
	{
		//< 셰이킹이 지나면
		if( m_shakeStart + m_shakeCount <= GetTickCount() )
		{
			//< 이전 위치로 되돌리기		
			m_viewOffSetX = prevPosX;
			m_viewOffSetY = prevPosY;
			m_isShaking = false;
		}
		else
		{
			//< 카메라 위치 이동
			m_viewOffSetX += rand()%30-15;
			m_viewOffSetY += rand()%30-15;			
		}
	}
}
//< 카메라 이동
void Camera::moveCamera( LONG cx, LONG cy )
{
	m_viewOffSetX += cx;
	m_viewOffSetY += cy;
}
//< 위치 설정
void Camera::setPosition( LONG x, LONG y )
{
	m_viewOffSetX = x;
	m_viewOffSetY = y;
}

//< 카메라 진동
void Camera::cameraShaking( unsigned int count )
{
	if( m_isShaking == false )
	{
		//< 이전 위치 기억
		prevPosX = m_viewOffSetX;
		prevPosY = m_viewOffSetY;
	}
	//< 진동 상태로 바꾸기
	m_isShaking = true;
	//발동 시간 기억
	m_shakeStart = GetTickCount();
	//< 카운트
	m_shakeCount = count;
}