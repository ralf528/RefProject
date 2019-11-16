#include "stdafx.h"

#include "ImageNode.h"
#include "RenderMgr.h"

RenderMgr::RenderMgr(void)
	: m_imgBack(NULL)
{
}
RenderMgr::~RenderMgr(void)
{
}

//< �ʱ�ȭ
void RenderMgr::init( void )
{
	//������ ������ ����
	RC_MGR->removeRC( imgID_BACKBUFFER );
	//< ������ ũ�� ���
	GetClientRect( g_hWnd, &m_winRect );

	//< ����� �̹��� �߰�
	if( RC_MGR->addImage( imgID_BACKBUFFER, m_winRect.right, m_winRect.bottom )
		== Object::EMPTYOBJ )
	{
		//���� ó��
		return;
	}

	//< ����� �̹��� ������ ���
	m_imgBack = RC_MGR->findImage( imgID_BACKBUFFER );

	if( NULL != m_mainDC )
	{
		ReleaseDC( g_hWnd, m_mainDC );
	}

	//< ���� DC ���
	m_mainDC = GetDC( g_hWnd );
}

//< ������
//< �׳� ����
void RenderMgr::render( HDC hdc , const unsigned int UID, int x, int y )
{
	//< ã��
	Object *obj = RC_MGR->findRC( UID );
	//< �׸���
	if( obj != NULL )
	{
		obj->render( hdc, x, y );
	}
}
//< �������� ����
void RenderMgr::render( HDC hdc, const unsigned int UID, 
					   int x , int y, int destWidth, int destHeight, 
					   int srcX, int srcY, int srcWidth, int srcHeight,
					   BYTE alphaValue )
{
	//< ã��
	Object *obj = RC_MGR->findRC( UID );
	//< �׸���
	if( obj != NULL )
	{
		obj->render( hdc, x, y, destWidth, destHeight, srcX, srcY, srcWidth, srcHeight );
	}
}

//< ȭ�鿡 ���� ��� ( hdc �ʿ� ���� )
void RenderMgr::renderFrame( void )
{
	if( NULL != m_imgBack )
	{
		m_imgBack->render( m_mainDC, 0, 0 );
	}
}
//< ����� �ʱ�ȭ
void RenderMgr::clearBack( int brush )
{
	if( m_imgBack != NULL )
	{
		FillRect( m_imgBack->getMemDC(), &m_winRect, (HBRUSH)GetStockObject(brush));
	}
}
//< ����
void RenderMgr::release( void )
{
	//< ���� DC ��ȯ
	ReleaseDC( g_hWnd, m_mainDC );
}

//< ����DC���
HDC RenderMgr::getMainDC( void )
{
	return m_mainDC;
}
//< ��DC���
HDC RenderMgr::getBackDC( void )
{
	if( NULL != m_imgBack )
	{
		//< ����� �̹����� �޸�DC ����
		return m_imgBack->getMemDC();
	}
	return NULL;
}