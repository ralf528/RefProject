#include "stdafx.h"
#include "ButtonClass.h"
#include "MY_FontMgr.h"

ButtonClass::ButtonClass(void)
{
	//< �Ҵ�
	buttonImage = new ImageNode(0);
	buttonImage2 = new ImageNode(0);
	buttonImage3 = new ImageNode(0);

	//< ��Ʈ �Ҵ�
	font = new MY_Font;

	//< ��ư �浹Ȯ��
	checkMouseOn = false;
	//< ��ư ���� Ȯ��
	checkClickButton = false;
	//< �ִϸ��̼� Ȯ��
	playButtonAni = false;

	//< ���� ��, ��
	checkTrueButton = true;

	//< ��ư �ִ� �ӵ� ����
	speed = 5;
	aniTime = GetTickCount();
}


ButtonClass::~ButtonClass(void)
{
	//< ��������
	release();
}


//< �ʱ�ȭ
void ButtonClass::init( char *dest_FILE_NAME, char *overlap_FILE_NAME, int sizeX, int sizeY )
{
	//< �̹��� �ε�
	loadImage( dest_FILE_NAME, sizeX, sizeY );
	//< ������ �̹��� �ε�
	loadImage2( overlap_FILE_NAME, sizeX, sizeY );
}
//< �ʱ�ȭ
void ButtonClass::init( char *dest_FILE_NAME, char *overlap_FILE_NAME, char *noChoice_FILE_NAME, int sizeX, int sizeY )
{
	//< �̹��� �ε�
	loadImage( dest_FILE_NAME, sizeX, sizeY );
	//< ������ �̹��� �ε�
	loadImage2( overlap_FILE_NAME, sizeX, sizeY );
	//< ���þȵ� �̹��� �ҷ�����
	buttonImage3->load( noChoice_FILE_NAME, sizeX, sizeY, RM_TRANS );
}

//< ��Ʈ �ҷ�����
void ButtonClass::loadFont( const char *destString, 
		const RECT ALIGN_RECT,
		const char *fontName = "����",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 )
{
	//< ��Ʈ �θ���
	font->LoadText( destString, 
		ALIGN_RECT,
		fontName,
		fontSize, ALIGN_TYPE,
		R_COLOR,G_COLOR,B_COLOR );
}

//< ������Ʈ
void ButtonClass::update( void )
{
	//< �ܺ� ��Ʈ �ޱ�
	font->inFontRect( buttonRect );
}

//< ����
void ButtonClass::render( HDC hdc )
{
	if( checkTrueButton == true )
	{
		//< ��ư�� �������� 
		if( checkClickButton == true )
		{
			//< �ִϸ��̼� ���
			aniClickButton(hdc);
		}
		//< ���콺 ������� �ٸ� �̹��� ����ϱ�
		else if( checkMouseOn == true )
		{
			buttonImage2->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}
		//< ����Ʈ �̹��� ���
		else
		{
			//< ��Ʈũ�� �̸�����
			//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
			//< ��Ʈ ��ġ��ŭ �̹��� �׸���
			buttonImage->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}
	}
	else
	{
		//< ���úҰ� �̹��� ���
		buttonImage3->render( hdc, buttonRect.left, buttonRect.top );
	}
}

//< Ŭ�� �ִϸ��̼�
void ButtonClass::aniClickButton( HDC hdc )
{
	//< ������ �ޱ�
	SIZE size = buttonImage2->getSize();
	//< �ӽ� ī��Ʈ
	static int count =0;
	static int minCount = 5;
	int sizeAni = 5;
	static int i = sizeAni;

	if( count <= 20 )
	{
		//< ������ ���� ����
		size.cx += count;
		size.cy += count;

		if( count < 10 )
		{
			size.cx -= minCount;
			size.cy -= minCount;
			//< �̹��� �ִϸ��̼�
			buttonImage2->renderSize( hdc, buttonRect.left-(count-minCount)/2, buttonRect.top-(count-minCount)/2, size.cx, size.cy );
			minCount++;
			//< ��Ʈ �ҷ�����
			if( i <= sizeAni )
			{
				font->inSize( font->getSize() -3 );
				i++;
			}
			font->OutputText( hdc );
		}
		else if(  count >= 10 && count <= 15 )
		{
			//< �̹��� �ִϸ��̼�
			buttonImage2->renderSize( hdc, buttonRect.left - count/2, buttonRect.top - count/2, size.cx, size.cy );
			//< ��Ʈ �ҷ�����
			if( i >= sizeAni )
			{
				font->inSize( font->getSize() + 3 );
				i--;
			}
			font->OutputText( hdc );
		}
		else
		{
			//< ��Ʈ ��ġ��ŭ �̹��� �׸���
			buttonImage2->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}

		//< ���� �ð� �ޱ�
		DWORD nowTime = GetTickCount();

		if( speed + aniTime <= nowTime )
		{
			aniTime = nowTime;

			count ++;
		}
	}

	//< �ִϸ��̼� ��� Ȯ��
	if( count >= 20 )
	{
		playButtonAni = true;
		checkClickButton = true;
		count = 0;
		minCount = 5;
	}
}
//< �����
void ButtonClass::release( void )
{
	//< ��ư �̹��� ����
	if( buttonImage != NULL ){ buttonImage->release(); }
	SAFE_DELETE( buttonImage );
	if( buttonImage2 != NULL ){ buttonImage2->release(); }
	SAFE_DELETE( buttonImage2 );
	if( buttonImage3 != NULL ){ buttonImage3->release(); }
	SAFE_DELETE( buttonImage3 );
	//< ��Ʈ �̹��� ����
	SAFE_DELETE( font );
}

//public :
//< ��ư �̹��� �ҷ�����
void ButtonClass::loadImage( char *FILE_NAME, int sizeX, int sizeY )
{
	//< ��ư �̹��� �ҷ�����
	buttonImage->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
	
	//< ��Ʈ �ʱ�ȭ
	SetRect( &buttonRect, 0,0, sizeX, sizeY );
	//< ���� ã��
	rectCenter.x = sizeX/2;
	rectCenter.y = sizeY/2;
}

//< ��ư ���콺���� �̹��� �ҷ�����
void ButtonClass::loadImage2( char *FILE_NAME, int sizeX, int sizeY )
{
	//< ��ư �̹��� �ҷ�����
	buttonImage2->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
}

//< �ܺ� ��ġ �ޱ�
void ButtonClass::setRectPos( int posX, int posY, int ALIGE_TYPE )
{
	//< �ӽ� ��ġ
	POINT tempPos;

	//< �ӽ� ��ġ�� ������ �ޱ�
	tempPos.x = posX - rectCenter.x;
	tempPos.y = posY + rectCenter.y;

	switch( ALIGE_TYPE )
	{
	//< �߰�����
	case ALIGN_CENTER :
		{
			//< ��Ʈ �̵�
			buttonRect.left = posX - rectCenter.x;
			buttonRect.top = posY - rectCenter.y;
			buttonRect.right = posX + rectCenter.x;
			buttonRect.bottom = posY + rectCenter.y;
		}
		break;
	//< ������ ����
	case ALIGN_LEFT_TOP :
		{
			//< ��Ʈ �̵�
			buttonRect.left = posX ;
			buttonRect.top = posY ;
			buttonRect.right = posX + rectCenter.x*2;
			buttonRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< ���� �Ʒ� ����
	case ALIGN_RIGHT_TOP :
		{
			//< ��Ʈ �̵�
			buttonRect.left = posX - rectCenter.x*2;
			buttonRect.top = posY ;
			buttonRect.right = posX  ;
			buttonRect.bottom = posY - rectCenter.y*2;
		}
		break;
	//< ������ �� ����
	case ALIGN_LEFT_BOTTOM : 
		{
			//< ��Ʈ �̵�
			buttonRect.left = posX ;
			buttonRect.top = posY - rectCenter.y*2;
			buttonRect.right = posX - rectCenter.x*2;
			buttonRect.bottom = posY ;
		}
		break;
	//< ������ �Ʒ� ����
	case ALIGN_RIGHT_BOTTOM :
		{
			//< ��Ʈ �̵�
			buttonRect.left = posX - rectCenter.x*2;
			buttonRect.top = posY - rectCenter.y*2;
			buttonRect.right = posX ;
			buttonRect.bottom = posY;
		}
		break;
	}
}
