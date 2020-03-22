#include "stdafx.h"
#include "Popup_Lobby_FriendList.h"

#include "ImageNode.h"
#include "PopupBox.h"
#include "MY_FontMgr.h"
#include "FriendListClass.h"

Popup_Lobby_FriendList::Popup_Lobby_FriendList(void)
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

	//< ģ�� ����Ʈ
	friendListPage = new FriendListClass;
}

Popup_Lobby_FriendList::~Popup_Lobby_FriendList(void)
{
	release();
}


//< �ʱ�ȭ
void Popup_Lobby_FriendList::init( void )
{
	//< ���� �̹��� �ε�
	loadImage();

	//< ����
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< �˾� �̹��� ���� �ޱ�
	POINT tempPoint = popupImage->getCenter();
	RECT tempRect = popupImage->getRect();
	
	//< ��ư Ȯ��
	button_OK->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		 200, 50 );
	button_OK->loadFont("Ȯ��", button_OK->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OK->setRectPos( tempRect.right-40, tempRect.bottom-50, ALIGN_RIGHT_BOTTOM );

	//< ģ�� ����Ʈ
	friendListPage->init();
}

//< ������Ʈ
void Popup_Lobby_FriendList::update( POINT mousePos )
{
	//< ��ư Ȯ��
	button_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OK->getRect() ));
	button_OK->update();

	//< ��ư Ȯ��-------------------------------------------------
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( button_OK->getPlayButtonAni() == true )
	{
		button_OK->inClickButton( false );
		button_OK->inPlayButtonAni( false );
		//< Ŭ�� ����
		button_STATE = POPUP_NO_POPUP ;
		return;
	}

	font->LoadText( "ģ�� ���", popupImage->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );

	//< ģ�� ����Ʈ
	friendListPage->update( mousePos );
}

//< ����
void Popup_Lobby_FriendList::render( HDC hdc )
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
		font->OutputText( hdc, 0, 0, 0, -540 );
	}

	//< ģ�� ����Ʈ
	friendListPage->render( hdc );
}

//< �����
void Popup_Lobby_FriendList::release( void )
{
	//< �ҷ��� �̹��� �����
	if( alpaImage != NULL ) { alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( popupImage != NULL ) { popupImage->release();}
	SAFE_DELETE( popupImage );
	//< ��ư �����
	if( button_OK != NULL ) { button_OK->release();}
	SAFE_DELETE( button_OK );
	//< ��Ʈ �����
	SAFE_DELETE( font );
	//< ģ�� �����
	if( friendListPage != NULL ) { friendListPage->release();}
	SAFE_DELETE( friendListPage );
}

//< �̹��� �ҷ�����
void Popup_Lobby_FriendList::loadImage( void )
{
	//< ���� �̹���
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );

	//< ����� �̹���
	popupImage->init("Data/Resource/Image/Popup_Box2.bmp", 850, 640 );
}

//< �̺�Ʈó��
LRESULT	Popup_Lobby_FriendList::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP :
		{
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_OK->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_OK->inClickButton( true );
			}
		}
		break;
	}
	return friendListPage->StateProc( wnd ,msg,wparam,lparam);
}