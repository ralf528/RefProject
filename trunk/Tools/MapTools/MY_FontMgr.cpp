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

//< 출력 텍스트
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
	//< 배경색 없음( 투명 )
	SetBkMode( hdc, TRANSPARENT );

	//< 폰트 불러오기
	m_Font = CreateFont( fontSize,
		0,0,0,0,0,0,0,
		HANGEUL_CHARSET,
		0,0,0,
		VARIABLE_PITCH | FF_ROMAN,
		fontName );
	
	//< 선택
	m_oldFont = (HFONT)SelectObject( hdc, m_Font );

	//< 색 불러오기
	SetTextColor( hdc, RGB( R_COLOR, G_COLOR, B_COLOR ) );

	//< 사용
	if (width > 0 && height > 0)
	{
		RECT rt = {x, y, x + width, y + height};
		// 테투리 범위 디버깅용
		//Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
		// 세로 중앙 정렬이 필요할 때 [ | DT_VCENTER | DT_SINGLELINE]
		DrawText(hdc, string, -1, &rt, alignment); 
	}
	else
	{
		TextOut( hdc, x, y, string, strlen( string ) );
	}

	//< 복구
	SelectObject( hdc, m_oldFont );

	//< 반환
	DeleteObject( m_Font );

	//< 배경색 
	SetBkMode( hdc, OPAQUE );
}

//< 렉트 정렬 폰트 불러오기
void MY_FontMgr::LoadText( const char *destString, 
						  const RECT ALIGN_RECT,
						  const char *fontName,
						  const int fontSize, 
						  const int ALIGN_TYPE,
						  const int R_COLOR,
						  const int G_COLOR,
						  const int B_COLOR )
{
	//< 스트링 정보 저장
	memmove_s( m_destString, _MAX_FNAME, destString, lstrlen( destString ) );
	memmove_s( m_fontName, _MAX_FNAME, fontName, lstrlen( fontName ) );

	m_fontSize = fontSize; 
	m_ALIGN_TYPE = ALIGN_TYPE;
	m_R_COLOR = R_COLOR;
	m_G_COLOR = G_COLOR;
	m_B_COLOR = B_COLOR;

	//< 정렬 랙트 받기
	rect = ALIGN_RECT;
}

//< 텍스트만 받아오기
void MY_FontMgr::inChar( string inputChar )
{
	//< 스트링 정보 저장
	memmove_s( m_destString, _MAX_FNAME, inputChar.c_str(), inputChar.size()+1 );
}

//< 불러온 텍스트로 출력
void MY_FontMgr::OutputText( HDC hdc )
{
	//< 배경색 없음( 투명 )
	SetBkMode( hdc, TRANSPARENT );

	//< 폰트 불러오기
	m_Font = CreateFont( m_fontSize,
		0,0,0,0,0,0,0,
		HANGEUL_CHARSET,
		0,0,0,
		VARIABLE_PITCH | FF_ROMAN,
		m_fontName );
	
	//< 선택
	m_oldFont = (HFONT)SelectObject( hdc, m_Font );

	//< 색 불러오기
	SetTextColor( hdc, RGB( m_R_COLOR, m_G_COLOR, m_B_COLOR ) );

	//< 텍스트 그리기
	DrawText( hdc, m_destString, -1, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER ); 

	//< 복구
	SelectObject( hdc, m_oldFont );

	//< 반환
	DeleteObject( m_Font );

	//< 배경색 
	SetBkMode( hdc, OPAQUE );
	SetTextColor( hdc, RGB( 0, 0, 0 ) );
}
