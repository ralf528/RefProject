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

//< �ʱ�ȭ
void Camera::init(void)
{
	m_shakeStart=0;
	prevPosX=0;
	prevPosY=0;
	m_viewOffSetY=0;
	m_viewOffSetX=0;
	m_shakeCount=false;
}
//< ī�޶� ����
void Camera::update(void)
{
	//< ī�޶� ����ŷ
	if( m_isShaking == true )
	{
		//< ����ŷ�� ������
		if( m_shakeStart + m_shakeCount <= GetTickCount() )
		{
			//< ���� ��ġ�� �ǵ�����		
			m_viewOffSetX = prevPosX;
			m_viewOffSetY = prevPosY;
			m_isShaking = false;
		}
		else
		{
			//< ī�޶� ��ġ �̵�
			m_viewOffSetX += rand()%30-15;
			m_viewOffSetY += rand()%30-15;			
		}
	}
}
//< ī�޶� �̵�
void Camera::moveCamera( LONG cx, LONG cy )
{
	m_viewOffSetX += cx;
	m_viewOffSetY += cy;
}
//< ��ġ ����
void Camera::setPosition( LONG x, LONG y )
{
	m_viewOffSetX = x;
	m_viewOffSetY = y;
}

//< ī�޶� ����
void Camera::cameraShaking( unsigned int count )
{
	if( m_isShaking == false )
	{
		//< ���� ��ġ ���
		prevPosX = m_viewOffSetX;
		prevPosY = m_viewOffSetY;
	}
	//< ���� ���·� �ٲٱ�
	m_isShaking = true;
	//�ߵ� �ð� ���
	m_shakeStart = GetTickCount();
	//< ī��Ʈ
	m_shakeCount = count;
}