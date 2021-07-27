#include "stdafx.h"
#include "ImageNode.h"

//#pragma comment( lib,"msimg32.lib")

ImageNode::ImageNode( void )
	: Object( imgID_NONID )
{
	//< �ʱ�ȭ
	init();
}

ImageNode::ImageNode( unsigned int id )
	: Object( id )
{
	//< �ʱ�ȭ
	init();
}


ImageNode::~ImageNode(void)
{
	//< ����
	release();
}


//< �ʱ�ȭ
void ImageNode::init( void )
{
	//< �����̹��� ���� �� �ʱ�ȭ
	release();

	//< ���μ��λ�����
	m_size.cx = 0;
	m_size.cy = 0;

	m_colorKey = RGB(255,0,255);
	//< ���
	//memset( m_path , 0, sizeof( TCHAR) * _MAX_FNAME ) ;
	ZeroMemory( m_path , sizeof( TCHAR) * _MAX_FNAME );
}

//< �ε�
unsigned int  ImageNode::load( const TCHAR *imagePath , int cx , int cy , BYTE mode )
{
	if( NULL == imagePath )
	{
		//< �̹��� �ε� ���� �޼���
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;
	}

	//< �ε�����
	//< DC���
	HDC hdc = GetDC( g_hWnd );

	//< MemoryDC����
	m_memDC = CreateCompatibleDC( hdc );

	//< �̹��� �ε�
	m_bit = (HBITMAP)LoadImage( g_hInst, 
		imagePath, 
		IMAGE_BITMAP, 
		cx,
		cy,
		LR_LOADFROMFILE );

	//< ��弳��
	m_renderMode = mode;

	//< ��������
	if( setImageInfo() == false )
	{
		return Object::EMPTYOBJ;;
	}

	//< �ε�����
	if( NULL == m_bit )
	{
		//< �̹��� �ε� ���� �޼���
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;;
	}

	//< ����
	m_obit = (HBITMAP)SelectObject( m_memDC , m_bit );
	//DC ��ȯ
	ReleaseDC( g_hWnd, hdc );
	
	return Object::getUID();
}

//< RC�ε�
unsigned int ImageNode::load( const int resourceID , BYTE mode )
{
	//< �ε�����
	//< DC���
	HDC hdc = GetDC( g_hWnd );

	//< MemoryDC����
	m_memDC = CreateCompatibleDC( hdc );

	//< iamgeLoad
	m_bit = LoadBitmap( g_hInst, MAKEINTRESOURCE( resourceID ) );

	//< ��弳��
	m_renderMode = mode;

	//< ��������
	if( setImageInfo() == false )
	{
		return Object::EMPTYOBJ;;
	}

	//< �ε�����
	if( NULL == m_bit )
	{
		//< �̹��� �ε� ���� �޼���
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;;
	}

	//< ����
	m_obit = (HBITMAP)SelectObject( m_memDC , m_bit );

	ReleaseDC( g_hWnd, hdc );
	return resourceID;
}

//< ���̹��������(�ش� ũ��� ���̹��� ����� )����Ʈ�� ������� ĥ�Ѵ�.
unsigned int ImageNode::load( int cx , int cy , BYTE mode )
{
	//< �ε�����
	//< DC���
	HDC hdc = GetDC( g_hWnd );

	//< MemoryDC����
	m_memDC = CreateCompatibleDC( hdc );

	//< iamgeLoad
	m_bit = CreateCompatibleBitmap( hdc, cx, cy );

	//< ��弳��
	m_renderMode = mode;

	//< ��������
	if( setImageInfo() == false )
	{
		return Object::EMPTYOBJ;;
	}

	//< �ε�����
	if( NULL == m_bit )
	{
		//< �̹��� �ε� ���� �޼���
		MessageBox( g_hWnd, L"imageLoadFail", L"ImageError",MB_OK );
		return Object::EMPTYOBJ;;
	}

	//< ����
	m_obit = (HBITMAP)SelectObject( m_memDC , m_bit );

	//< �������
	//< ����� DC�� �ʱ�ȭ��Ų��.
	RECT	winRect;
	GetClientRect( g_hWnd, &winRect );
	FillRect( m_memDC, &winRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	ReleaseDC( g_hWnd, hdc );
	
	return Object::getUID();
}

//< ����
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
			//	_In_ HDC hdcDest,		//< ������ ��ġ ����� DC
			//	_In_ int xoriginDest,	//< ���� ������X
			//	_In_ int yoriginDest,	//< ���� ������Y 
			//	_In_ int wDest,			//< ���� �� ��������
			//	_In_ int hDest,			//< ���� �� ���� ����
			//	_In_ HDC hdcSrc,		//< ���� �޸�DC(�����̹���)
			//	_In_ int xoriginSrc,	//< �������� ������ X
			//	_In_ int yoriginSrc,	//< �̹����� ������ Y
			//	_In_ int wSrc,			//< �̹����� ���� ������ ����
			//	_In_ int hSrc,			//< �̹����� ���� ������ ����
			//	_In_ UINT crTransparent); //< ������ �ȼ�����(RGB) �Ǵ� 0x~~
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

//< ���� ����
void ImageNode::renderAlpha( HDC hdc, int x , int y, BYTE alpha )
{
	static BLENDFUNCTION bf;
	bf.BlendOp = 0, bf.BlendFlags = 0, bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	GdiAlphaBlend( hdc, x, y , m_size.cx, m_size.cy, m_memDC, 0, 0,	m_size.cx, m_size.cy, bf );
}

//< ũ������� ����
void ImageNode::renderSize( HDC hdc, int x, int y, int width, int height )
{
	GdiTransparentBlt( hdc, x, y, width,height, m_memDC, 0,0,m_size.cx,m_size.cy, RGB(255,0,255) );
}

//< ����
void ImageNode::release( void )
{
	//< ������Ʈ ���� �� �ʱ�ȭ
	if( NULL != m_bit )
	{
		DeleteObject( SelectObject( m_memDC, m_obit ));
	}
	m_bit = NULL;
	m_obit = NULL;

	//< DC���� �� �ʱ�ȭ
	if( NULL != m_memDC )
	{
		DeleteDC( m_memDC );
	}
	m_memDC = NULL;
}

//< ���������� DC�ʱ�ȭ�ϱ�
void	ImageNode::clearDC( DWORD color )
{
	
		//< ��Ʈ���
		RECT	imageRect;

		SetRect( &imageRect, 0,0, m_size.cx , m_size.cy );

		//< �귯��
		HBRUSH	brush,obrush;
		brush = CreateSolidBrush( color );
		obrush = (HBRUSH)SelectObject( m_memDC , brush );

		//< ȭ�������� Ŭ����
		FillRect( m_memDC , &imageRect, brush );

		DeleteObject( SelectObject( m_memDC, obrush) );
}

//< ��������
bool ImageNode::setImageInfo( void )
{
	//< bitȮ��
	if( NULL == m_bit )
	{
		return false;
	}

	//< ������Ʈ ���� ����
	BITMAP	bt;
	GetObject( m_bit , sizeof(BITMAP), &bt );

	//< ���μ�����������
	m_size.cx = bt.bmWidth;
	m_size.cy = bt.bmHeight;

	//< ��� ��ȯ
	return true;
}
