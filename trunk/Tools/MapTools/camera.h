#pragma once

#include "singleton.h"

class Camera
{
private:
	Camera(void)
	{
	}
	~Camera(void)
	{
	}

	SINGLETON(Camera);
public:
	void init(void)
	{
		m_viewOffSetY=0;
		m_viewOffSetX=0;
	}
	void update( void )
	{
		if( keyInput::isKeyDown( VK_LEFT) )
		{
			moveCamera( -5, 0 );
		}
		if( keyInput::isKeyDown( VK_RIGHT ) )
		{
			moveCamera( 5, 0 );
		}
		if( keyInput::isKeyDown( VK_UP ) )
		{
			moveCamera( 0, -5 );
		}
		if( keyInput::isKeyDown( VK_DOWN ) )
		{
			moveCamera( 0, 5 );
		}
		if( keyInput::isKeyDown( VK_SPACE ) )
		{
			m_viewOffSetY=0;
			m_viewOffSetX=0;
		}
	}
	void moveCamera( LONG cx, LONG cy )
	{
		m_viewOffSetX += cx;
		m_viewOffSetY += cy;
	}

	LONG getX(void) { return m_viewOffSetX; }
	LONG getY(void) { return m_viewOffSetY; }

private:
	//< ºä ¿ÀÇÁ¼Â
	LONG m_viewOffSetX;
	LONG m_viewOffSetY;
};

#define CAMERA Singleton<Camera>::getInstance()