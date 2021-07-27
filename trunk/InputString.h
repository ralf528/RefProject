#pragma once

#include "MY_FontMgr.h"

//< ��Ʈ�� �Է� Ŭ����
class InputString
{
public:
	InputString(void);
	~InputString(void);

	//< �ʱ�ȭ
	void init( RECT ALIGN_RECT, TCHAR *FontName, int FontSize, int ALIGN_TYPE,
					   int Rcolor, int Gcolor, int Bcolor );
	//< ������Ʈ
	void update( void );
	//< ����
	void render( HDC hdc );
	//< ���� ���׸���
	void renderStar( HDC hdc );
	//< �����
	void release( void );

public :
	//< ���ڿ� �Է¹ޱ�
	void getChar( WPARAM wparam );
	//< �齺���̽��� ���ֱ�
	void backSpace( void );
	//< �Է¹��� ����
	void clear(void)
	{
		inputString.clear();
		outputString->clear();
	}
	//< �Է� üũ �ޱ�
	bool getInputCheck( void )
	{
		return inputCheck;
	}
	//< �Է� üũ ����
	void inInputCheck( bool check )
	{
		inputCheck = check;
	}

	//< ������� �Էµ� ��Ʈ�� �ޱ�
	TCHAR* getString( void )
	{
		return MY_Font::StringToTCHAR(inputString);
	}
	//< ��Ʈ�� �ޱ�
	string getCharString( void )
	{
		return inputString;
	}

	void setString(const char* buf)
	{
		inputString = buf;
	}

private :
	//< ��Ʈ�� �Է�
	string inputString;
	//< �Է� ��Ʈ�� ǥ�� ��Ʈ
	MY_Font* outputString;
	//< ���� ��Ʈ
	RECT rect;

	//< �Է� ���� üũ
	bool inputCheck;
};

