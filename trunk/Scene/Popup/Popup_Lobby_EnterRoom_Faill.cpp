#include "stdafx.h"
#include "Popup_Lobby_EnterRoom_Faill.h"

#include "ImageNode.h"
#include "PopupBox.h"
#include "MY_FontMgr.h"
#include "SceneTitle.h"
#include "SceneChoiceChar.h"

Popup_Lobby_EnterRoom_Faill::Popup_Lobby_EnterRoom_Faill(void)
{
	//< ����� �̹���
	alpaImage = new ImageNode(0);
	//< �˾�â �̹���
	popupImage = new PopupBox;
	//< ��ư
	button_OK = new ButtonClass;
	button_STATE = POPUP_NONE;

	//< ��Ʈ
	font = new MY_FontMgr;

	//< �� �Ҵ� ���
	makeRoom = false;
}

Popup_Lobby_EnterRoom_Faill::~Popup_Lobby_EnterRoom_Faill(void)
{
	release();
}


//< �ʱ�ȭ
void Popup_Lobby_EnterRoom_Faill::init( void )
{
	//< ���� �̹��� �ε�
	loadImage();

	//< ����
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< �˾� �̹��� ���� �ޱ�
	POINT tempPoint = popupImage->getCenter();

	//< ��ư
	button_OK->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		 200, 50 );
	button_OK->loadFont("Ȯ��", button_OK->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OK->setRectPos( tempPoint.x, tempPoint.y+130 +20, ALIGN_CENTER );
}

//< ������Ʈ
void Popup_Lobby_EnterRoom_Faill::update( POINT mousePos )
{
	//< ��ư 
	button_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OK->getRect() ));
	button_OK->update();
	//< ��ư-------------------------------------------------
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( button_OK->getPlayButtonAni() == true )
	{
		//< ���� ������
		button_OK->inClickButton( false );
		button_OK->inPlayButtonAni( false );
		//< �˾� ����
		button_STATE = POPUP_NO_POPUP;
		return;
	}

	//< �˾� ��Ʈ
	font->LoadText( "���� �Ұ�! ������ Ȯ���ϼ���!", popupImage->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
}

//< ����
void Popup_Lobby_EnterRoom_Faill::render( HDC hdc )
{
	//< ���� �̹��� ����
	alpaImage->render( hdc, 0,0  );
	//< �˾�â ����
	popupImage->render( hdc );

	if( popupImage->getPlayPopupBoxAni() == true )
	{
		//< ��ư
		button_OK->render( hdc );

		//< ��Ʈ
		font->OutputText( hdc );
	}
}

//< �����
void Popup_Lobby_EnterRoom_Faill::release( void )
{
	//< �ҷ��� �̹��� �����
	if( alpaImage != NULL ){ alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( alpaImage != NULL ){ popupImage->release(); }
	SAFE_DELETE( popupImage );
	if( alpaImage != NULL ){ button_OK->release(); }
	SAFE_DELETE( button_OK );
	//< ��Ʈ �����
	SAFE_DELETE( font );
}

//< �̹��� �ҷ�����
void Popup_Lobby_EnterRoom_Faill::loadImage( void )
{
	//< ���� �̹���
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );

	popupImage->init("Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< �̺�Ʈó��
LRESULT	Popup_Lobby_EnterRoom_Faill::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	//< ���콺�� ���� 
	case WM_LBUTTONUP :
		{
			//< ��ư-------------------------------------------------
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_OK->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_OK->inClickButton( true );
			}
		}
		break;
	//< Ű���� �Է¹ޱ�
	case WM_KEYDOWN :
		switch(wparam)
		{
		//< ����Ű �Է�
		case VK_RETURN:
			{
				button_OK->inClickButton( true );
			}
			break;
		}
		break;
	}
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}