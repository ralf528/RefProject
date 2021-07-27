#include "stdafx.h"
#include "ImageNode.h"

//#pragma comment( lib,"msimg32.lib")

ImageNode::ImageNode( void )
	: Object( imgID_NONID )
{
	//< 초기화
	init();
}

ImageNode::ImageNode( unsigned int id )
	: Object( id )
{
	//< 초기화
	init();
}


ImageNode::~ImageNode(void)
{
	//< 해제
	release();
}


//< 초기화
void ImageNode::init( void )
{
	//< 기존이미지 삭제 및 초기화
	release();

	//< 가로세로사이즈
	m_size.cx = 0;
	m_size.cy = 0;

	m_colorKey = RGB(255,0,255);
	//< 경로
	//memset( m_path , 0, sizeof( TCHAR) * _MAX_FNAME ) ;
	ZeroMemory( m_path , sizeof( TCHAR) * _MAX_FNAME );
}

//< 로딩
unsigned int  ImageNode::load( const TCHAR *imagePath , int cx , int cy , BYTE mode )
{
	if( NULL == imagePath )
	{
		//< 이미지 로딩 실패 메세지
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;
	}

	//< 로딩시작
	//< DC얻기
	HDC hdc = GetDC( g_hWnd );

	//< MemoryDC생성
	m_memDC = CreateCompatibleDC( hdc );

	//< 이미지 로드
	m_bit = (HBITMAP)LoadImage( g_hInst, 
		imagePath, 
		IMAGE_BITMAP, 
		cx,
		cy,
		LR_LOADFROMFILE );

	//< 모드설정
	m_renderMode = mode;

	//< 정보설정
	if( setImageInfo() == false )
	{
		return Object::EMPTYOBJ;;
	}

	//< 로딩실패
	if( NULL == m_bit )
	{
		//< 이미지 로딩 실패 메세지
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;;
	}

	//< 선택
	m_obit = (HBITMAP)SelectObject( m_memDC , m_bit );
	//DC 반환
	ReleaseDC( g_hWnd, hdc );
	
	return Object::getUID();
}

//< RC로딩
unsigned int ImageNode::load( const int resourceID , BYTE mode )
{
	//< 로딩시작
	//< DC얻기
	HDC hdc = GetDC( g_hWnd );

	//< MemoryDC생성
	m_memDC = CreateCompatibleDC( hdc );

	//< iamgeLoad
	m_bit = LoadBitmap( g_hInst, MAKEINTRESOURCE( resourceID ) );

	//< 모드설정
	m_renderMode = mode;

	//< 정보설정
	if( setImageInfo() == false )
	{
		return Object::EMPTYOBJ;;
	}

	//< 로딩실패
	if( NULL == m_bit )
	{
		//< 이미지 로딩 실패 메세지
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;;
	}

	//< 선택
	m_obit = (HBITMAP)SelectObject( m_memDC , m_bit );

	ReleaseDC( g_hWnd, hdc );
	return resourceID;
}

//< 빈이미지만들기(해당 크기로 빈이미지 만들기 )디폴트로 흰색으로 칠한다.
unsigned int ImageNode::load( int cx , int cy , BYTE mode )
{
	//< 로딩시작
	//< DC얻기
	HDC hdc = GetDC( g_hWnd );

	//< MemoryDC생성
	m_memDC = CreateCompatibleDC( hdc );

	//< iamgeLoad
	m_bit = CreateCompatibleBitmap( hdc, cx, cy );

	//< 모드설정
	m_renderMode = mode;

	//< 정보설정
	if( setImageInfo() == false )
	{
		return Object::EMPTYOBJ;;
	}

	//< 로딩실패
	if( NULL == m_bit )
	{
		//< 이미지 로딩 실패 메세지
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;;
	}

	//< 선택
	m_obit = (HBITMAP)SelectObject( m_memDC , m_bit );

	//< 흰색으로
	//< 백버퍼 DC를 초기화시킨다.
	RECT	winRect;
	GetClientRect( g_hWnd, &winRect );
	FillRect( m_memDC, &winRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	ReleaseDC( g_hWnd, hdc );
	
	return Object::getUID();
}

//< 렌더
void ImageNode::render( HDC hdc, int x , int y )
{
	switch( m_renderMode )
	{
	case RM_NORMAL:
		{
			BitBlt( hdc, x,y, m_size.cx, m_size.cy, m_memDC,0,0,SRCCOPY );
		}
		break;
	case RM_TRANS:
		{
			//WINGDIAPI BOOL WINAPI TransparentBlt(
			//	_In_ HDC hdcDest,		//< 렌더할 위치 대상의 DC
			//	_In_ int xoriginDest,	//< 렌더 시작점X
			//	_In_ int yoriginDest,	//< 렌더 시작점Y 
			//	_In_ int wDest,			//< 렌더 할 영역가로
			//	_In_ int hDest,			//< 렌더 할 영역 세로
			//	_In_ HDC hdcSrc,		//< 찍을 메모리DC(찍을이미지)
			//	_In_ int xoriginSrc,	//< 이지미의 시작점 X
			//	_In_ int yoriginSrc,	//< 이미지의 시작점 Y
			//	_In_ int wSrc,			//< 이미지의 찍을 영역의 가로
			//	_In_ int hSrc,			//< 이미지의 찍을 영역의 세로
			//	_In_ UINT crTransparent); //< 제외할 픽셀색상(RGB) 또는 0x~~
			GdiTransparentBlt( hdc, x, y , m_size.cx, m_size.cy, m_memDC,0,0,
				m_size.cx, m_size.cy,m_colorKey );			
		}
		break;
	case RM_ALPHA32:
		{
			static BLENDFUNCTION bf;
			bf.BlendOp = 0, bf.BlendFlags = 0, bf.AlphaFormat = AC_SRC_ALPHA;
			bf.SourceConstantAlpha = 250;

			GdiAlphaBlend( hdc, x, y , m_size.cx, m_size.cy, m_memDC, 0, 0,	m_size.cx, m_size.cy, bf );
		}
		break;
	}
	
}

void ImageNode::render( HDC hdc, int x , int y, int destCX , int destCY, 
						  int scrX , int srcY , int srcCX, int srcCY  )
{
	switch( m_renderMode )
	{
	case RM_NORMAL:
		{
			BitBlt( hdc, x,y, destCX, destCY, m_memDC,scrX,srcY, SRCCOPY );
		}
		break;
	case RM_TRANS:
		{
			GdiTransparentBlt( hdc, x, y , destCX, destCY, m_memDC,
				scrX,
				srcY,
				destCX, destCY, m_colorKey );
		}
		break;
	case RM_ALPHA32:
		{
			static BLENDFUNCTION bf;
			bf.BlendOp = 0, bf.BlendFlags = 0, bf.AlphaFormat = AC_SRC_ALPHA;
			bf.SourceConstantAlpha = 250;

			GdiAlphaBlend( hdc, x, y , m_size.cx, m_size.cy, m_memDC, 0, 0,	m_size.cx, m_size.cy, bf );
		}
		break;
	}
}

//< 알파 블렌드
void ImageNode::renderAlpha( HDC hdc, int x , int y, BYTE alpha )
{
	static BLENDFUNCTION bf;
	bf.BlendOp = 0, bf.BlendFlags = 0, bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	GdiAlphaBlend( hdc, x, y , m_size.cx, m_size.cy, m_memDC, 0, 0,	m_size.cx, m_size.cy, bf );
}

//< 크기수정용 랜더
void ImageNode::renderSize( HDC hdc, int x, int y, int width, int height )
{
	GdiTransparentBlt( hdc, x, y, width,height, m_memDC, 0,0,m_size.cx,m_size.cy, RGB(255,0,255) );
}

//< 해제
void ImageNode::release( void )
{
	//< 오브젝트 삭제 및 초기화
	if( NULL != m_bit )
	{
		DeleteObject( SelectObject( m_memDC, m_obit ));
	}
	m_bit = NULL;
	m_obit = NULL;

	//< DC삭제 및 초기화
	if( NULL != m_memDC )
	{
		DeleteDC( m_memDC );
	}
	m_memDC = NULL;
}

//< 지정색으로 DC초기화하기
void	ImageNode::clearDC( DWORD color )
{
	
		//< 렉트얻기
		RECT	imageRect;

		SetRect( &imageRect, 0,0, m_size.cx , m_size.cy );

		//< 브러쉬
		HBRUSH	brush,obrush;
		brush = CreateSolidBrush( color );
		obrush = (HBRUSH)SelectObject( m_memDC , brush );

		//< 화면백색으로 클리어
		FillRect( m_memDC , &imageRect, brush );

		DeleteObject( SelectObject( m_memDC, obrush) );
}

//< 정보설정
bool ImageNode::setImageInfo( void )
{
	//< bit확인
	if( NULL == m_bit )
	{
		return false;
	}

	//< 오브젝트 정보 설정
	BITMAP	bt;
	GetObject( m_bit , sizeof(BITMAP), &bt );

	//< 가로세로정보설정
	m_size.cx = bt.bmWidth;
	m_size.cy = bt.bmHeight;

	//< 결과 반환
	return true;
}
