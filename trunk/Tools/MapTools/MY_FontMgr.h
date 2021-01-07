#pragma once

class MY_FontMgr
{
public:
	MY_FontMgr(void);
	~MY_FontMgr(void);

	//< �ٷ� ��� �ؽ�Ʈ
	void OutputText( HDC hdc,
		const char *string, 
		const int x,
		const int y,
		const char *fontName = "����",
		const int fontSize = 10, 
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255,
		const int width = 0, 
		const int height = 0,
		const int alignment = DT_CENTER
		);

	//< ��Ʈ ���� ��Ʈ �ҷ�����
	void LoadText( const char *destString, 
		const RECT ALIGN_RECT,
		const char *fontName = "����",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 
		);

	//< �ҷ��� �ؽ�Ʈ�� ���
	void OutputText( HDC hdc );

	//< �ؽ�Ʈ�� �޾ƿ���
	void inChar( string inputChar );

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
	int getSize( void )
	{
		return m_fontSize;
	}
private :
	char m_destString[_MAX_FNAME];
	char m_fontName[_MAX_FNAME];
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

