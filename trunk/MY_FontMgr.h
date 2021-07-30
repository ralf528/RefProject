#pragma once

class MY_Font
{
public:
	MY_Font(void);
	~MY_Font(void);

	//< �ٷ� ��� �ؽ�Ʈ
	void OutputText( HDC hdc,
		const TCHAR *string,
		const int x,
		const int y,
		const TCHAR *fontName = L"����",
		const int fontSize = 10, 
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255,
		const int width = 0, 
		const int height = 0,
		const int alignment = DT_CENTER
		);

	//< ��Ʈ ���� ��Ʈ �ҷ�����
	void LoadText( const TCHAR *destString,
		const RECT ALIGN_RECT,
		const TCHAR *fontName = L"����",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 
		);

	//< ��Ʈ�� ���� ���� �ҷ�����
	void LoadText( 
		const RECT ALIGN_RECT,
		const TCHAR *fontName = L"����",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 
		);

	//< �ҷ��� �ؽ�Ʈ�� ���
	void OutputText( HDC hdc );
	//< �ҷ��� �ؽ�Ʈ�� ���
	void OutputText( HDC hdc, int left, int top, int right, int bottom );
	//< �ؽ�Ʈ ����ŭ �� ���
	void OutputStar( HDC hdc );
	//< �ؽ�Ʈ �޾Ƽ� ���
	void OutputText( HDC hdc, TCHAR *outputText );

	//< �ؽ�Ʈ�� �޾ƿ���
	void inChar( wstring& inputChar );

	//< ��Ʈ�޾ƿ���
	void inFontRect( RECT ButtonRect )
	{
		rect = ButtonRect;
	}
	//< ũ�� �޾ƿ���
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
	//< ��Ʈ ��Ʈ ���
	void inSetRect( int left, int top, int right, int bottom )
	{
		SetRect( &rect, left, top, right, bottom );
	}

	//< �����
	void clear( void )
	{
		memset( m_destString, 0, sizeof(char) * _MAX_FNAME );
	}
	//< ���ڿ� �ޱ�
	TCHAR* getChar( void )
	{
		return m_destString;
	}
	//< ���ڿ� �ֱ�
	void inCharChar(TCHAR* dest )
	{
		memmove_s( m_destString, _MAX_FNAME, dest, lstrlen( dest ) );
	}

public:
	static TCHAR* StringToTCHAR(string& s)
	{
		const char* all = s.c_str();
		size_t len = strlen(all) + 1;
		size_t cn;

		WCHAR* t = new WCHAR[len];
		mbstowcs_s(&cn, t, len, all, len);

		return (TCHAR*)t;
	}

	/*static char* TCharToChar(TCHAR* str)
	{
		char cTemp[_MAX_FNAME];
		WideCharToMultiByte(CP_ACP, 0, str, _MAX_FNAME, cTemp, _MAX_FNAME, NULL, NULL);
		return cTemp;
	}*/

private :
	TCHAR m_destString[_MAX_FNAME];
	TCHAR m_fontName[_MAX_FNAME];
	int m_fontSize; 
	int m_ALIGN_TYPE;
	int m_R_COLOR;
	int m_G_COLOR;
	int m_B_COLOR;

	//< ���� ��Ʈ
	RECT rect;

private :
	//< ��� ��Ʈ
	HFONT m_Font;
	//< �õ� ��Ʈ
	HFONT m_oldFont;
};

