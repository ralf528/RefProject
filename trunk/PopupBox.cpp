#include "stdafx.h"
#include "PopupBox.h"
#include "ImageNode.h"

PopupBox::PopupBox( void )
{
	//< �Ҵ�
	PopupBoxImage = new ImageNode(0);


	//< �ִϸ��̼� Ȯ��
	playPopupBoxAni = false;
}

PopupBox::~PopupBox(void)
{
	//< ��������
	release();
}

//< �ʱ�ȭ
void PopupBox::init(TCHAR *dest_FILE_NAME, int sizeX, int sizeY )
{
	//< �̹��� �ε�
	loadImage( dest_FILE_NAME, sizeX, sizeY );
}

//< ������Ʈ
void PopupBox::update( void )
{
	
}

//< ����
void PopupBox::render( HDC hdc )
{
	//< �ִϸ��̼� ����� �ȉ�ٸ� 
	if( playPopupBoxAni == false )
	{
		//< �ִϸ��̼� ���
		aniPopupBox(hdc);
	}
	//< ����Ʈ �̹��� ���
	else
	{
		//< ��Ʈũ�� �̸�����
		//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
		//< ��Ʈ ��ġ��ŭ �̹��� �׸���
		PopupBoxImage->render( hdc, PopupBoxRect.left, PopupBoxRect.top );
	}
}
//< �ִϸ��̼� ���� ���
void PopupBox::renderNone( HDC hdc )
{
	//< ��Ʈũ�� �̸�����
	//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
	//< ��Ʈ ��ġ��ŭ �̹��� �׸���
	PopupBoxImage->render( hdc, PopupBoxRect.left, PopupBoxRect.top );
}
//< �ִϸ��̼�
void PopupBox::aniPopupBox( HDC hdc )
{
	//< ������ �ޱ�
	SIZE size = PopupBoxImage->getSize();
	//< �ӽ� ī��Ʈ
	static int count =0;
	static int minCount = 5;

	if( count <= 60 )
	{
		//< ������ ���� ����
		size.cx += count;
		size.cy += count;

		if( count < 10 )
		{
			size.cx -= minCount;
			size.cy -= minCount;
			//< �̹��� �ִϸ��̼�
			PopupBoxImage->renderSize( hdc, PopupBoxRect.left-(count-minCount)/2, PopupBoxRect.top-(count-minCount)/2, size.cx, size.cy );
			minCount++;
		}
		else if(  count >= 10 && count <= 30 )
		{
			//< �̹��� �ִϸ��̼�
			PopupBoxImage->renderSize( hdc, PopupBoxRect.left - count/2, PopupBoxRect.top - count/2, size.cx, size.cy );
		}
		else
		{
			//< ��Ʈ ��ġ��ŭ �̹��� �׸���
			PopupBoxImage->render( hdc, PopupBoxRect.left, PopupBoxRect.top );
		}
		count ++;
	}

	//< �ִϸ��̼� ��� Ȯ��
	if( count >= 60 )
	{
		playPopupBoxAni = true;
		count = 0;
		minCount = 5;
	}
}
//< �����
void PopupBox::release( void )
{
	//< �˾� �̹��� ����
	if( PopupBoxImage != NULL ){ PopupBoxImage->release(); }
	SAFE_DELETE( PopupBoxImage );
}

//public :
//< �˾� �̹��� �ҷ�����
void PopupBox::loadImage(TCHAR *FILE_NAME, int sizeX, int sizeY )
{
	//< ��ư �̹��� �ҷ�����
	PopupBoxImage->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
	
	//< ��Ʈ �ʱ�ȭ
	SetRect( &PopupBoxRect, 0,0, sizeX, sizeY );
	//< ���� ã��
	rectCenter.x = sizeX/2;
	rectCenter.y = sizeY/2;
}

//< �ܺ� ��ġ �ޱ�
void PopupBox::setRectPos( int posX, int posY, int ALIGE_TYPE )
{
	//< ��ġ ���� ��ġ�� ������ �ޱ�
	posCenter.x = posX;
	posCenter.y = posY;

	switch( ALIGE_TYPE )
	{
	//< �߰�����
	case ALIGN_CENTER :
		{
			//< ��Ʈ �̵�
			PopupBoxRect.left = posX - rectCenter.x;
			PopupBoxRect.top = posY - rectCenter.y;
			PopupBoxRect.right = posX + rectCenter.x;
			PopupBoxRect.bottom = posY + rectCenter.y;
		}
		break;
	//< ������ ����
	case ALIGN_LEFT_TOP :
		{
			//< ��Ʈ �̵�
			PopupBoxRect.left = posX ;
			PopupBoxRect.top = posY ;
			PopupBoxRect.right = posX + rectCenter.x*2;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< ���� �Ʒ� ����
	case ALIGN_LEFT_BOTTOM :
		{
			//< ��Ʈ �̵�
			PopupBoxRect.left = posX ;
			PopupBoxRect.top = posY - rectCenter.y*2;;
			PopupBoxRect.right = posX  ;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< ������ �� ����
	case ALIGN_RIGHT_TOP : 
		{
			//< ��Ʈ �̵�
			PopupBoxRect.left = posX - rectCenter.x*2;
			PopupBoxRect.top = posY ;
			PopupBoxRect.right = posX - rectCenter.x*2;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< ������ �Ʒ� ����
	case ALIGN_RIGHT_BOTTOM :
		{
			//< ��Ʈ �̵�
			PopupBoxRect.left = posX - rectCenter.x*2;
			PopupBoxRect.top = posY - rectCenter.y*2;
			PopupBoxRect.right = posX + rectCenter.x*2;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	}
}


//< �ܺ� ��ġ �ޱ�
void PopupBox::setRectPos( RECT rect )
{
	//< ��Ʈ �̵�
	PopupBoxRect = rect;
}
