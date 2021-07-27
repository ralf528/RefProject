#include "stdafx.h"
#include "RoomButton.h"

//#include "SceneChoiceChar.h"
#include "ButtonClass.h"

RoomButton::RoomButton(void)
{
	//< 할당
	button_ROOM = new ButtonClass;
}


RoomButton::~RoomButton(void)
{
	release();
}


//<초기화
void RoomButton::init( ROOM_INFO& makeRoom, int posX, int posY )
{
	//< 방 이미지
	button_ROOM->init(
		L"Data/Resource/Image/room_none.bmp",
		L"Data/Resource/Image/room_none_02.bmp",540, 140);

	//< 방 위치 
	button_ROOM->setRectPos( posX , posY, ALIGN_CENTER );

	//< 공개 비공개 이미지
	imageOpen.load( L"Data/Resource/Image/roomInfo_open.bmp", 64, 24 );
	imageClose.load( L"Data/Resource/Image/roomInfo_close.bmp", 64, 24 );

	//< 임시 렉트 받기
	RECT tempRect = button_ROOM->getRect();
	TCHAR arr[256] = L"";

	//< 방제
	madeRoom.outputRoomName.LoadText(
		makeRoom.m_roomName, 
		tempRect, 
		L"HY헤드라인M",
		40, ALIGN_CENTER, 255,255,255 );
	madeRoom.outputRoomName.inSetRect(
		tempRect.left	+100,
		tempRect.top	+60,
		tempRect.right	-90,
		tempRect.bottom	-20 );

	swprintf_s( arr, 256, L"%d", makeRoom.m_roomNum );
	//< 방번호
	madeRoom.outputRoomNum.LoadText(
		arr, 
		tempRect, 
		L"HY헤드라인M",
		50, ALIGN_CENTER, 255,255,255 );
	madeRoom.outputRoomNum.inSetRect(
		tempRect.left	+60,
		tempRect.top	+40,
		tempRect.left	+100,
		tempRect.top	+100 );

	swprintf_s( arr, 256, L"%s의방 %d/2명 게임중", makeRoom.m_userName[0],makeRoom.m_userCount );
	//< 방장
	madeRoom.outputTobUser.LoadText(
		arr, 
		tempRect, 
		L"HY헤드라인M",
		20, ALIGN_CENTER, 200,200,200 );
	madeRoom.outputTobUser.inSetRect(
		tempRect.left	+100,
		tempRect.top	+20,
		tempRect.right	-90,
		tempRect.bottom	-80 );

	checkOpen = makeRoom.m_isSecret;
}

//< 업데이트
void RoomButton::update( POINT mousePos )
{
	//< 방 위치
	button_ROOM->update();

	//< 방위치
	button_ROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_ROOM->getRect() ));

	//< 방 버튼-------------------------------------------------
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

		//< 팝업 바꾸기-----------------------------------------------
		//< 공개 방이라면 
		POPUP_MGR->changePopup( POPUP_LOBBY_ENTER_ROOM_OPEN );
		//< 비공개 방이라면
		//POPUP_MGR->changePopup( POPUP_LOBBY_ENTER_ROOM_CLOSE );

		button_ROOM->inPlayButtonAni(false);
		button_ROOM->inCheckMouseOn(false);
		button_ROOM->inClickButton( false );
		return;
	}
}

//< 랜더
void RoomButton::render( HDC hdc )
{
	//< 방버튼 랜더
	button_ROOM->render( hdc );
	madeRoom.outputRoomName.OutputText( hdc );
	madeRoom.outputRoomNum.OutputText( hdc );
	madeRoom.outputTobUser.OutputText( hdc );

	//< 임시 렉트 받기
	RECT tempRect = button_ROOM->getRect();
	if( checkOpen == false )
	{
		//< 공개, 비공개 이미지
		imageOpen.render( hdc, tempRect.left +20, tempRect.top +10 );
	}
	else
	{
		//< 공개, 비공개 이미지
		imageClose.render( hdc, tempRect.left +20, tempRect.top +10 );
	}
	//< 미리보기 렉트////////////////////////////////////////////////////////////////////////////////
	////< 방제목
	//Rectangle( hdc, madeRoom.outputRoomName.getRect().left,
	//	madeRoom.outputRoomName.getRect().top,
	//	madeRoom.outputRoomName.getRect().right,
	//	madeRoom.outputRoomName.getRect().bottom );
	////< 방 넘버
	//Rectangle( hdc, madeRoom.outputRoomNum.getRect().left,
	//	madeRoom.outputRoomNum.getRect().top,
	//	madeRoom.outputRoomNum.getRect().right,
	//	madeRoom.outputRoomNum.getRect().bottom );
	////< 방장 
	//Rectangle( hdc, madeRoom.outputTobUser.getRect().left,
	//	madeRoom.outputTobUser.getRect().top,
	//	madeRoom.outputTobUser.getRect().right,
	//	madeRoom.outputTobUser.getRect().bottom );
	//< 미리보기
	//Rectangle( hdc, algnRect.left, algnRect.top, algnRect.right, algnRect.bottom );
	//////////////////////////////////////////////////////////////////////////////////////////////////
}

//< 지우기
void RoomButton::release( void )
{
	//< 버튼 지우기
	if( button_ROOM != NULL ){ button_ROOM->release(); }
	SAFE_DELETE( button_ROOM );
}

//< 이벤트처리
LRESULT	RoomButton::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP : //< 마우스를 땔때 한번 실행
		{
			//< 만들어진 방 버튼-------------------------------------------------
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

