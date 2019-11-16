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

//< 초기화
void RenderMgr::init( void )
{
	//기존에 있으면 삭제
	RC_MGR->removeRC( imgID_BACKBUFFER );
	//< 윈도우 크기 얻기
	GetClientRect( g_hWnd, &m_winRect );

	//< 백버퍼 이미지 추가
	if( RC_MGR->addImage( imgID_BACKBUFFER, m_winRect.right, m_winRect.bottom )
		== Object::EMPTYOBJ )
	{
		//에러 처리
		return;
	}

	//< 백버퍼 이미지 포인터 백업
	m_imgBack = RC_MGR->findImage( imgID_BACKBUFFER );

	if( NULL != m_mainDC )
	{
		ReleaseDC( g_hWnd, m_mainDC );
	}

	//< 메인 DC 얻기
	m_mainDC = GetDC( g_hWnd );
}

//< 렌더링
//< 그냥 랜더
void RenderMgr::render( HDC hdc , const unsigned int UID, int x, int y )
{
	//< 찾기
	Object *obj = RC_MGR->findRC( UID );
	//< 그리기
	if( obj != NULL )
	{
		obj->render( hdc, x, y );
	}
}
//< 영역지정 랜더
void RenderMgr::render( HDC hdc, const unsigned int UID, 
					   int x , int y, int destWidth, int destHeight, 
					   int srcX, int srcY, int srcWidth, int srcHeight,
					   BYTE alphaValue )
{
	//< 찾기
	Object *obj = RC_MGR->findRC( UID );
	//< 그리기
	if( obj != NULL )
	{
		obj->render( hdc, x, y, destWidth, destHeight, srcX, srcY, srcWidth, srcHeight );
	}
}

//< 화면에 최종 출력 ( hdc 필요 없음 )
void RenderMgr::renderFrame( void )
{
	if( NULL != m_imgBack )
	{
		m_imgBack->render( m_mainDC, 0, 0 );
	}
}
//< 백버퍼 초기화
void RenderMgr::clearBack( int brush )
{
	if( m_imgBack != NULL )
	{
		FillRect( m_imgBack->getMemDC(), &m_winRect, (HBRUSH)GetStockObject(brush));
	}
}
//< 삭제
void RenderMgr::release( void )
{
	//< 메인 DC 반환
	ReleaseDC( g_hWnd, m_mainDC );
}

//< 메인DC얻기
HDC RenderMgr::getMainDC( void )
{
	return m_mainDC;
}
//< 백DC얻기
HDC RenderMgr::getBackDC( void )
{
	if( NULL != m_imgBack )
	{
		//< 백버퍼 이미지의 메모리DC 리턴
		return m_imgBack->getMemDC();
	}
	return NULL;
}