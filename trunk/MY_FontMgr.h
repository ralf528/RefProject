#pragma once

class MY_Font
{
public:
	MY_Font(void);
	~MY_Font(void);

	//< 바로 출력 텍스트
	void OutputText( HDC hdc,
		const char *string, 
		const int x,
		const int y,
		const char *fontName = "굴림",
		const int fontSize = 10, 
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255,
		const int width = 0, 
		const int height = 0,
		const int alignment = DT_CENTER
		);

	//< 렉트 정렬 폰트 불러오기
	void LoadText( const char *destString, 
		const RECT ALIGN_RECT,
		const char *fontName = "굴림",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 
		);

	//< 스트링 빼고 정보 불러오기
	void LoadText( 
		const RECT ALIGN_RECT,
		const char *fontName = "굴림",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 
		);

	//< 불러온 텍스트로 출력
	void OutputText( HDC hdc );
	//< 불러온 텍스트로 출력
	void OutputText( HDC hdc, int left, int top, int right, int bottom );
	//< 텍스트 수만큼 별 출력
	void OutputStar( HDC hdc );
	//< 텍스트 받아서 출력
	void OutputText( HDC hdc, char *outputText );

	//< 텍스트만 받아오기
	void inChar( string& inputChar );

	//< 렉트받아오기
	void inFontRect( RECT ButtonRect )
	{
		rect = ButtonRect;
	}
	//< 크기 받아오기
	void inSize( int FontSize )
	{
		m_fontSize = FontSize;
	}
	RECT getRect( void )
	{
		return rect;
	}
	int getSize( void )
	{
		return m_fontSize;
	}
	//< 폰트 렉트 깔기
	void inSetRect( int left, int top, int right, int bottom )
	{
		SetRect( &rect, left, top, right, bottom );
	}

	//< 지우기
	void clear( void )
	{
		memset( m_destString, 0, sizeof(char) * _MAX_FNAME );
	}
	//< 문자열 받기
	char* getChar( void )
	{
		return m_destString;
	}
	//< 문자열 주기
	void inCharChar( char *dest )
	{
		memmove_s( m_destString, _MAX_FNAME, dest, lstrlen( dest ) );
	}

private :
	char m_destString[_MAX_FNAME];
	char m_fontName[_MAX_FNAME];
	int m_fontSize; 
	int m_ALIGN_TYPE;
	int m_R_COLOR;
	int m_G_COLOR;
	int m_B_COLOR;

	//< 기준 렉트
	RECT rect;

private :
	//< 멤버 폰트
	HFONT m_Font;
	//< 올드 폰트
	HFONT m_oldFont;
};

