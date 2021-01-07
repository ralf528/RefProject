#include "stdafx.h"
#include "MY_FontMgr.h"


MY_FontMgr::MY_FontMgr(void)
{
	ZeroMemory( m_destString, _MAX_FNAME );
	ZeroMemory( m_fontName, _MAX_FNAME );
}


MY_FontMgr::~MY_FontMgr(void)
{
}

//< ��� �ؽ�Ʈ
void MY_FontMgr::OutputText( HDC hdc,
	const char *string, 
	const int x,
	const int y,
	const char *fontName,
	const int fontSize, 
	const int R_COLOR,
	const int G_COLOR,
	const int B_COLOR,
	const int width, 
	const int height,
	const int alignment
	)
{
	//< ���� ����( ���� )
	SetBkMode( hdc, TRANSPARENT );

	//< ��Ʈ �ҷ�����
	m_Font = CreateFont( fontSize,
		0,0,0,0,0,0,0,
		HANGEUL_CHARSET,
		0,0,0,
		VARIABLE_PITCH | FF_ROMAN,
		fontName );
	
	//< ����
	m_oldFont = (HFONT)SelectObject( hdc, m_Font );

	//< �� �ҷ�����
	SetTextColor( hdc, RGB( R_COLOR, G_COLOR, B_COLOR ) );

	//< ���
	if (width > 0 && height > 0)
	{
		RECT rt = {x, y, x + width, y + height};
		// ������ ���� ������
		//Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
		// ���� �߾� ������ �ʿ��� �� [ | DT_VCENTER | DT_SINGLELINE]
		DrawText(hdc, string, -1, &rt, alignment); 
	}
	else
	{
		TextOut( hdc, x, y, string, strlen( string ) );
	}

	//< ����
	SelectObject( hdc, m_oldFont );

	//< ��ȯ
	DeleteObject( m_Font );

	//< ���� 
	SetBkMode( hdc, OPAQUE );
}

//< ��Ʈ ���� ��Ʈ �ҷ�����
void MY_FontMgr::LoadText( const char *destString, 
						  const RECT ALIGN_RECT,
						  const char *fontName,
						  const int fontSize, 
						  const int ALIGN_TYPE,
						  const int R_COLOR,
						  const int G_COLOR,
						  const int B_COLOR )
{
	//< ��Ʈ�� ���� ����
	memmove_s( m_destString, _MAX_FNAME, destString, lstrlen( destString ) );
	memmove_s( m_fontName, _MAX_FNAME, fontName, lstrlen( fontName ) );

	m_fontSize = fontSize; 
	m_ALIGN_TYPE = ALIGN_TYPE;
	m_R_COLOR = R_COLOR;
	m_G_COLOR = G_COLOR;
	m_B_COLOR = B_COLOR;

	//< ���� ��Ʈ �ޱ�
	rect = ALIGN_RECT;
}

//< �ؽ�Ʈ�� �޾ƿ���
void MY_FontMgr::inChar( string inputChar )
{
	//< ��Ʈ�� ���� ����
	memmove_s( m_destString, _MAX_FNAME, inputChar.c_str(), inputChar.size()+1 );
}

//< �ҷ��� �ؽ�Ʈ�� ���
void MY_FontMgr::OutputText( HDC hdc )
{
	//< ���� ����( ���� )
	SetBkMode( hdc, TRANSPARENT );

	//< ��Ʈ �ҷ�����
	m_Font = CreateFont( m_fontSize,
		0,0,0,0,0,0,0,
		HANGEUL_CHARSET,
		0,0,0,
		VARIABLE_PITCH | FF_ROMAN,
		m_fontName );
	
	//< ����
	m_oldFont = (HFONT)SelectObject( hdc, m_Font );

	//< �� �ҷ�����
	SetTextColor( hdc, RGB( m_R_COLOR, m_G_COLOR, m_B_COLOR ) );

	//< �ؽ�Ʈ �׸���
	DrawText( hdc, m_destString, -1, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER ); 

	//< ����
	SelectObject( hdc, m_oldFont );

	//< ��ȯ
	DeleteObject( m_Font );

	//< ���� 
	SetBkMode( hdc, OPAQUE );
	SetTextColor( hdc, RGB( 0, 0, 0 ) );
}
