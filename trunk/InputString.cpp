#include "stdafx.h"
#include "InputString.h"
#include "MY_FontMgr.h"

InputString::InputString(void)
{
	//< �Է� ��Ʈ�� ǥ�� ��Ʈ �Ҵ�
	outputString = new MY_Font;
	//< ��ǲüũ ����
	inputCheck = false;
}


InputString::~InputString(void)
{
	//< �����
	release();
}


//< �ʱ�ȭ
void InputString::init( RECT ALIGN_RECT, TCHAR *FontName, int FontSize, int ALIGN_TYPE,
					   int Rcolor, int Gcolor, int Bcolor )
{
	//< ��Ʈ �ޱ�
	rect = ALIGN_RECT;

	//< �ؽ�Ʈ �ε�
	outputString->LoadText(getString(),
		rect,
		L"HY������M",
		FontSize, ALIGN_TYPE, Rcolor,Gcolor,Bcolor );
}

//< ������Ʈ
void InputString::update( void )
{
	//outputString->inChar( inputString );
}

//< ����
void InputString::render( HDC hdc )
{
	//< �ؽ�Ʈ ���
	outputString->OutputText( hdc ); 
}
//< ���� ���׸���
void InputString::renderStar( HDC hdc )
{
	//< �ؽ�Ʈ ���
	outputString->OutputStar( hdc );
}

//< �����
void InputString::release( void )
{
	//< ��Ʈ �����
	inputString.clear();
	SAFE_DELETE( outputString );
}


//public :
//< ���ڿ� �Է¹ޱ�
void InputString::getChar( WPARAM wparam )
{
	//< ��ǲ üũ�� ������������ �Է¹ޱ�
	if( inputCheck == true )
	{
		//< ����Ű �Է¹ޱ�
		if( VK_TAB != wparam && VK_RETURN != wparam && VK_BACK != wparam && VK_ESCAPE != wparam )
		{
			//< ��Ʈ���� ����   
			char ch = (char)wparam;

			inputString.push_back( ch );
			outputString->inChar( inputString );
		}
	}
}

//< �齺���̽��� ���ֱ�
void InputString::backSpace( void )
{
	//< ��ǲ üũ�� ������������ �Է¹ޱ�
	if( inputCheck == true )
	{
		//< ���� ����
		size_t len = inputString.size();

		//< ���ڿ� ���̰� 0�̸� �������� ����
		if( 0 < len )
		{
			//< 1����Ʈ ���ڸ�
			if( 0 < inputString[ len - 1 ] )
			{
				inputString.pop_back();
			}
			//< 2����Ʈ ���ڸ�
			else
			{
				inputString.pop_back();
				inputString.pop_back();
			}
			outputString->inChar( inputString );
		}
	}
}
