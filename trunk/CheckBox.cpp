#include "stdafx.h"
#include "CheckBox.h"

#include "MY_FontMgr.h"

CheckBox::CheckBox(void)
{
	//< �Ҵ�
	checkOFF = new ImageNode(0);
	checkON = new ImageNode(0);
	overlapOFF = new ImageNode(0);
	overlapON = new ImageNode(0);

	//< ��Ʈ �Ҵ�
	font = new MY_Font;

	//< ��ư �浹Ȯ��
	checkMouseOn = false;
	//< ��ư ���� Ȯ��
	checkClickButton = false;
	//< �ִϸ��̼� Ȯ��
	playButtonAni = false;

	//< üũ�ڽ� ����
	checkBoxState = CHECK_BOX_OFF;
}

CheckBox::~CheckBox(void)
{
	//< ��������
	release();
}

//< �ʱ�ȭ
void CheckBox::init( char *checkOFF_FILE_NAME, char *overlapOFF_FILE_NAME,
					char *checkON_FILE_NAME, char *overlapON_FILE_NAME,
					int sizeX, int sizeY )
{
	//< üũ���� �̹��� �ε�
	loadImage( checkOFF_FILE_NAME, sizeX, sizeY );
	//< üũ�� �̹��� �ε�
	checkON->load( checkON_FILE_NAME, sizeX, sizeY, RM_TRANS );
	//< ������ �̹���
	overlapOFF->load( overlapOFF_FILE_NAME, sizeX, sizeY, RM_TRANS );
	overlapON->load( overlapON_FILE_NAME, sizeX, sizeY, RM_TRANS );
}

//< ��Ʈ �ҷ�����
void CheckBox::loadFont( const char *destString, 
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
void CheckBox::update( void )
{
	//< �ܺ� ��Ʈ �ޱ�
	font->inFontRect( buttonRect );
}

//< ����
void CheckBox::render( HDC hdc )
{
	//< ���� ���¶�� 
	if( checkBoxState == CHECK_BOX_OFF )
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
			overlapOFF->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}
		//< ����Ʈ �̹��� ���
		else
		{
			//< ��Ʈũ�� �̸�����
			//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
			//< ��Ʈ ��ġ��ŭ �̹��� �׸���
			checkOFF->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}
	}
	//< �� ���¶��
	else
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
			overlapON->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}
		//< ����Ʈ �̹��� ���
		else
		{
			//< ��Ʈũ�� �̸�����
			//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
			//< ��Ʈ ��ġ��ŭ �̹��� �׸���
			checkON->render( hdc, buttonRect.left, buttonRect.top );
			//< ��Ʈ �ҷ�����
			font->OutputText( hdc );
		}
	}
}

//< Ŭ�� �ִϸ��̼�
void CheckBox::aniClickButton( HDC hdc )
{
	//< ������ �ޱ�
	SIZE size = overlapOFF->getSize();
	//< �ӽ� ī��Ʈ
	static int count =0;
	static int minCount = 5;
	int sizeAni = 5;
	static int i = sizeAni;

	//< üũ�� OFF ���¶�� 
	if( checkBoxState == CHECK_BOX_OFF )
	{
		if( count <= 30 )
		{
			//< ������ ���� ����
			size.cx += count;
			size.cy += count;

			if( count < 15 )
			{
				size.cx -= minCount;
				size.cy -= minCount;
				//< �̹��� �ִϸ��̼�
				overlapOFF->renderSize( hdc, buttonRect.left-(count-minCount)/2, buttonRect.top-(count-minCount)/2, size.cx, size.cy );
				minCount++;
				//< ��Ʈ �ҷ�����
				if( i <= sizeAni )
				{
					font->inSize( font->getSize() -3 );
					i++;
				}
				font->OutputText( hdc );
			}
			else if(  count >= 15 && count <= 25 )
			{
				//< �̹��� �ִϸ��̼�
				overlapOFF->renderSize( hdc, buttonRect.left - count/2, buttonRect.top - count/2, size.cx, size.cy );
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
				overlapOFF->render( hdc, buttonRect.left, buttonRect.top );
				//< ��Ʈ �ҷ�����
				font->OutputText( hdc );
			}
			count ++;
		}

		//< �ִϸ��̼� ��� Ȯ��
		if( count >= 30 )
		{
			playButtonAni = true;
			checkClickButton = true;
			count = 0;
			minCount = 5;
			//< üũ�ڽ� ����
			checkBoxState = CHECK_BOX_ON;
		}
	}
	//< üũ�� ON ���¶��
	else
	{
		if( count <= 30 )
		{
			//< ������ ���� ����
			size.cx += count;
			size.cy += count;

			if( count < 15 )
			{
				size.cx -= minCount;
				size.cy -= minCount;
				//< �̹��� �ִϸ��̼�
				overlapON->renderSize( hdc, buttonRect.left-(count-minCount)/2, buttonRect.top-(count-minCount)/2, size.cx, size.cy );
				minCount++;
				//< ��Ʈ �ҷ�����
				if( i <= sizeAni )
				{
					font->inSize( font->getSize() -3 );
					i++;
				}
				font->OutputText( hdc );
			}
			else if(  count >= 15 && count <= 25 )
			{
				//< �̹��� �ִϸ��̼�
				overlapON->renderSize( hdc, buttonRect.left - count/2, buttonRect.top - count/2, size.cx, size.cy );
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
				overlapON->render( hdc, buttonRect.left, buttonRect.top );
				//< ��Ʈ �ҷ�����
				font->OutputText( hdc );
			}
			count ++;
		}

		//< �ִϸ��̼� ��� Ȯ��
		if( count >= 30 )
		{
			playButtonAni = true;
			checkClickButton = true;
			count = 0;
			minCount = 5;
			//< üũ�ڽ� ����
			checkBoxState = CHECK_BOX_OFF;
		}
	}
}
//< �����
void CheckBox::release( void )
{
	//< ��ư �̹��� ����
	if( checkOFF != NULL ){ checkOFF->release(); }
	SAFE_DELETE( checkOFF );
	if( checkON != NULL ){ checkON->release(); }
	SAFE_DELETE( checkON );
	if( overlapOFF != NULL ){ overlapOFF->release(); }
	SAFE_DELETE( overlapOFF );
	if( overlapON != NULL ){ overlapON->release(); }
	SAFE_DELETE( overlapON );
	//< ��Ʈ �̹��� ����
	SAFE_DELETE( font );
}

//public :
//< ��ư �̹��� �ҷ�����
void CheckBox::loadImage( char *FILE_NAME, int sizeX, int sizeY )
{
	//< ��ư �̹��� �ҷ�����
	checkOFF->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
	
	//< ��Ʈ �ʱ�ȭ
	SetRect( &buttonRect, 0,0, sizeX, sizeY );
	//< ���� ã��
	rectCenter.x = sizeX/2;
	rectCenter.y = sizeY/2;
}

//< �ܺ� ��ġ �ޱ�
void CheckBox::setRectPos( int posX, int posY, int ALIGE_TYPE )
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
