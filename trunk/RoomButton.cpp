#include "stdafx.h"
#include "RoomButton.h"

//#include "SceneChoiceChar.h"
#include "ButtonClass.h"

RoomButton::RoomButton(void)
{
	//< �Ҵ�
	button_ROOM = new ButtonClass;
}


RoomButton::~RoomButton(void)
{
	release();
}


//<�ʱ�ȭ
void RoomButton::init( ROOM_INFO& makeRoom, int posX, int posY )
{
	//< �� �̹���
	button_ROOM->init(
		L"Data/Resource/Image/room_none.bmp",
		L"Data/Resource/Image/room_none_02.bmp",540, 140);

	//< �� ��ġ 
	button_ROOM->setRectPos( posX , posY, ALIGN_CENTER );

	//< ���� ����� �̹���
	imageOpen.load( L"Data/Resource/Image/roomInfo_open.bmp", 64, 24 );
	imageClose.load( L"Data/Resource/Image/roomInfo_close.bmp", 64, 24 );

	//< �ӽ� ��Ʈ �ޱ�
	RECT tempRect = button_ROOM->getRect();
	TCHAR arr[256] = L"";

	//< ����
	madeRoom.outputRoomName.LoadText(
		makeRoom.m_roomName, 
		tempRect, 
		L"HY������M",
		40, ALIGN_CENTER, 255,255,255 );
	madeRoom.outputRoomName.inSetRect(
		tempRect.left	+100,
		tempRect.top	+60,
		tempRect.right	-90,
		tempRect.bottom	-20 );

	swprintf_s( arr, 256, L"%d", makeRoom.m_roomNum );
	//< ���ȣ
	madeRoom.outputRoomNum.LoadText(
		arr, 
		tempRect, 
		L"HY������M",
		50, ALIGN_CENTER, 255,255,255 );
	madeRoom.outputRoomNum.inSetRect(
		tempRect.left	+60,
		tempRect.top	+40,
		tempRect.left	+100,
		tempRect.top	+100 );

	swprintf_s( arr, 256, L"%s�ǹ� %d/2�� ������", makeRoom.m_userName[0],makeRoom.m_userCount );
	//< ����
	madeRoom.outputTobUser.LoadText(
		arr, 
		tempRect, 
		L"HY������M",
		20, ALIGN_CENTER, 200,200,200 );
	madeRoom.outputTobUser.inSetRect(
		tempRect.left	+100,
		tempRect.top	+20,
		tempRect.right	-90,
		tempRect.bottom	-80 );

	checkOpen = makeRoom.m_isSecret;
}

//< ������Ʈ
void RoomButton::update( POINT mousePos )
{
	//< �� ��ġ
	button_ROOM->update();

	//< ����ġ
	button_ROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_ROOM->getRect() ));

	//< �� ��ư-------------------------------------------------
	if( button_ROOM->getClickButton() == true &&
		button_ROOM->getPlayButtonAni() == true )
	{

		/*PACKET packet;
		packet.m_roomJoinReq.m_length = sizeof(ROOMJOIN_REQ);
		packet.m_roomJoinReq.m_type = CS_GAME_JOIN;
		packet.m_roomJoinReq.m_roomNum = m_roomNum;
		TCPIP_CLIENT->sendPacket(packet);

		button_ROOM->inPlayButtonAni(false);
		button_ROOM->inCheckMouseOn(false);
		button_ROOM->inClickButton( false );*/

		//< �˾� �ٲٱ�-----------------------------------------------
		//< ���� ���̶�� 
		POPUP_MGR->changePopup( POPUP_LOBBY_ENTER_ROOM_OPEN );
		//< ����� ���̶��
		//POPUP_MGR->changePopup( POPUP_LOBBY_ENTER_ROOM_CLOSE );

		button_ROOM->inPlayButtonAni(false);
		button_ROOM->inCheckMouseOn(false);
		button_ROOM->inClickButton( false );
		return;
	}
}

//< ����
void RoomButton::render( HDC hdc )
{
	//< ���ư ����
	button_ROOM->render( hdc );
	madeRoom.outputRoomName.OutputText( hdc );
	madeRoom.outputRoomNum.OutputText( hdc );
	madeRoom.outputTobUser.OutputText( hdc );

	//< �ӽ� ��Ʈ �ޱ�
	RECT tempRect = button_ROOM->getRect();
	if( checkOpen == false )
	{
		//< ����, ����� �̹���
		imageOpen.render( hdc, tempRect.left +20, tempRect.top +10 );
	}
	else
	{
		//< ����, ����� �̹���
		imageClose.render( hdc, tempRect.left +20, tempRect.top +10 );
	}
	//< �̸����� ��Ʈ////////////////////////////////////////////////////////////////////////////////
	////< ������
	//Rectangle( hdc, madeRoom.outputRoomName.getRect().left,
	//	madeRoom.outputRoomName.getRect().top,
	//	madeRoom.outputRoomName.getRect().right,
	//	madeRoom.outputRoomName.getRect().bottom );
	////< �� �ѹ�
	//Rectangle( hdc, madeRoom.outputRoomNum.getRect().left,
	//	madeRoom.outputRoomNum.getRect().top,
	//	madeRoom.outputRoomNum.getRect().right,
	//	madeRoom.outputRoomNum.getRect().bottom );
	////< ���� 
	//Rectangle( hdc, madeRoom.outputTobUser.getRect().left,
	//	madeRoom.outputTobUser.getRect().top,
	//	madeRoom.outputTobUser.getRect().right,
	//	madeRoom.outputTobUser.getRect().bottom );
	//< �̸�����
	//Rectangle( hdc, algnRect.left, algnRect.top, algnRect.right, algnRect.bottom );
	//////////////////////////////////////////////////////////////////////////////////////////////////
}

//< �����
void RoomButton::release( void )
{
	//< ��ư �����
	if( button_ROOM != NULL ){ button_ROOM->release(); }
	SAFE_DELETE( button_ROOM );
}

//< �̺�Ʈó��
LRESULT	RoomButton::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP : //< ���콺�� ���� �ѹ� ����
		{
			//< ������� �� ��ư-------------------------------------------------
			if( button_ROOM->getCheckMouseOn() == true )
			{
				button_ROOM->inClickButton( true );
				break;
			}
		}
		break;
	}
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

