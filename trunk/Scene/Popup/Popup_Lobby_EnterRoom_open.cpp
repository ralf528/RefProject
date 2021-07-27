#include "stdafx.h"
#include "Popup_Lobby_EnterRoom_open.h"

#include "../../ImageNode.h"
#include "../../PopupBox.h"
#include "../../CheckBox.h"
#include "../../MY_FontMgr.h"
#include "../SceneChoiceChar.h"

Popup_Lobby_EnterRoom_open::Popup_Lobby_EnterRoom_open(void)
{
	//< 배경판 이미지
	alpaImage = new ImageNode(0);
	//< 팝업창 이미지
	popupImage = new PopupBox;

	//< 입력 맨트 이미지
	inputInfo_ID = new ButtonClass;
	inputInfo_PASS = new ButtonClass;
	//< 입력칸
	m_inputID_Board = new ButtonClass;
	m_inputPass_Board = new ButtonClass;

	//< 유저정보
	playUser = new MY_Font; 

	//< 마우스 포인터
	mousePos.x =0;
	mousePos.y =0;

	//< 버튼
	button_JOINROOM = new ButtonClass;
	button_CANCEL = new ButtonClass;

	//< 난입상태
	breakInto = true;

	//< 버튼 상태 초기화
	button_STATE = POPUP_NONE;
}


Popup_Lobby_EnterRoom_open::~Popup_Lobby_EnterRoom_open(void)
{
	release();
}

//< 초기화
void Popup_Lobby_EnterRoom_open::init( void )
{
	//< 선택 방정보 받아오기
    int getChoiceNumber = 0;// GAME_DATA->getChoiceNumber();

	//< 방정보 
	//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(getChoiceNumber);
    ROOM_INFO newRoom;
    memset(&newRoom, 0, sizeof(newRoom));

	//< 지정 이미지 로드
	loadImage();

	//< 정렬
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< 팝업 이미지 중점 받기
	POINT tempPoint = popupImage->getCenter();
	//---------------------------------------------------------------------------
	//< 유저 정보 받기
	RECT tempRect = popupImage->getRect();
	tempRect.top -= 80;
	tempRect.bottom -= 80;
	TCHAR arr[256];

	//< 유저이름, 현재 플레이중인 유저수

	if(newRoom.m_isCharSelect == true)
	{
		swprintf_s( arr, L"%s 의 방  %d/2명 (캐릭터 선택중)", newRoom.m_userName[0],newRoom.m_userCount );
	}
	else
	{
		swprintf_s( arr, L"%s 의 방  %d/2명이 (게임중)", newRoom.m_userName[0],newRoom.m_userCount );
	}

	//< 유저 정보 받아오기
	playUser->LoadText( arr, tempRect, L"HY헤드라인M", 40, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< 정보표시 방이름
	inputInfo_ID->init(L"Data/Resource/Image/board_join.bmp",
		L"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_ID->setRectPos( tempPoint.x -150, tempPoint.y - 66 +70, ALIGN_CENTER );
	//< 정보표시 비밀번호
	inputInfo_PASS->init(L"Data/Resource/Image/board_join.bmp",
		L"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_PASS->setRectPos( tempPoint.x -150, tempPoint.y - 2 +70, ALIGN_CENTER );

	//< 정보표시 방이름
	inputInfo_ID->loadFont(L"방이름",
		inputInfo_ID->getRect(), 
		L"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//< 정보표시 비밀번호
	inputInfo_PASS->loadFont(L"비밀번호",
		inputInfo_PASS->getRect(), 
		L"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< 입력판 ID
	m_inputID_Board->init(L"Data/Resource/Image/JoinRoom.bmp",
		L"Data/Resource/Image/JoinRoom.bmp",300, 60 );
	m_inputID_Board->setRectPos( tempPoint.x +110, tempPoint.y - 66 +70, ALIGN_CENTER );

	//< 유저 방제
	memset( arr, 0, sizeof( char )*256 );
	memmove_s( arr, 256, newRoom.m_roomName , lstrlen( newRoom.m_roomName ) );

	//< 방제 로드
	m_inputID_Board->loadFont( arr,
		m_inputID_Board->getRect(),
		L"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );

	//< 입력판 PASS
	m_inputPass_Board->init(L"Data/Resource/Image/button_INPUT_ROCK.bmp",
		L"Data/Resource/Image/button_INPUT_ROCK.bmp",300, 60 );
	m_inputPass_Board->setRectPos( tempPoint.x+110, tempPoint.y - 2 +70, ALIGN_CENTER );

	//---------------------------------------------------------------------------
	//< 버튼 같이하기
	button_JOINROOM->init(L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_JOINROOM->loadFont(L"같이하기", button_JOINROOM->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_JOINROOM->setRectPos( tempPoint.x+160, tempPoint.y+130 +20, ALIGN_CENTER );

	//< 버튼 취소
	button_CANCEL->init(L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_CANCEL->loadFont(L"취소", button_CANCEL->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CANCEL->setRectPos( tempPoint.x-150, tempPoint.y+130 +20, ALIGN_CENTER );
	//---------------------------------------------------------------------------
}

//< 업데이트
void Popup_Lobby_EnterRoom_open::update( POINT mousePos )
{
	//< 버튼 
	button_JOINROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_JOINROOM->getRect() ));
	button_JOINROOM->update();
	button_CANCEL->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CANCEL->getRect() ));
	button_CANCEL->update();

	//< 입력판 위치 받기
	m_inputPass_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_inputPass_Board->getRect() ));
	m_inputPass_Board->update();

	//< 패킷이 비어 있지 않다면
	//if(true != TCPIP_CLIENT->emptyQueue())
	//{
	//	unsigned short type = TCPIP_CLIENT->getPacketType();
	//	if(type == SC_GAME_JOIN_YES) //> 방 접속 성공
	//	{
	//		PACKET packet;
	//		TCPIP_CLIENT->getPacket(packet);
	//		ROOM_INFO& roomInfo = GAME_DATA->getRoomInfoFromNum(packet.m_roomJoinReq.m_roomNum);
	//		GAME_DATA->setHostAddr(roomInfo.m_hostIP);
	//		GAME_DATA->setHostPort(roomInfo.m_hostPort);
	//		//TCPIP_CLIENT->serverConnect(roomInfo.m_hostIP, roomInfo.m_hostPort);
	//		HOST_SERVER->setHostis(false);
	//		POPUP_MGR->changePopup(POPUP_LOBBY_ENTER_ROOM_SUCCESS);
	//		TCPIP_CLIENT->popPacket();
	//		
	//		return;
	//	}
	//	if(type == SC_GAME_JOIN_NO)
	//	{
	//		//< 게임 접속 거절

	//		TCPIP_CLIENT->popPacket();
	//		POPUP_MGR->changePopup(POPUP_LOBBY_ENTER_ROOM_FAILL);
	//		return;
	//	}
	//}

	//< 버튼 방들어가기-------------------------------------------------
	if( button_JOINROOM->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		button_JOINROOM->inCheckMouseOn( false );
		button_JOINROOM->inClickButton( false );
		button_JOINROOM->inPlayButtonAni( false );

		//PACKET packet;
		/*packet.m_roomJoinReq.m_length = sizeof(ROOMJOIN_REQ);
		packet.m_roomJoinReq.m_type = CS_GAME_JOIN;
		ROOM_INFO roomInfo = GAME_DATA->getRoomInfo(GAME_DATA->getChoiceNumber());
		packet.m_roomJoinReq.m_roomNum = roomInfo.m_roomNum;
		TCPIP_CLIENT->sendPacket(packet);*/

        POPUP_MGR->changePopup(POPUP_LOBBY_ENTER_ROOM_SUCCESS);
        return;
	}
	//< 버튼 cancel
	if( button_CANCEL->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		button_CANCEL->inCheckMouseOn( false );
		button_CANCEL->inClickButton( false );
		button_CANCEL->inPlayButtonAni( false );
		//< 클릭 리턴
		button_STATE = POPUP_NO_POPUP;
	}
}

//< 랜더
void Popup_Lobby_EnterRoom_open::render( HDC hdc )
{
	//< 투명 이미지 랜더
	alpaImage->render( hdc, 0,0  );
	//< 팝업창 랜더
	popupImage->render( hdc );

	if( popupImage->getPlayPopupBoxAni() == true )
	{
		//--------------------------------------------------------
		//< 입력 맨트 이미지
		inputInfo_ID->render( hdc );
		inputInfo_PASS->render( hdc );
		//--------------------------------------------------------
		//< 입력보드
		m_inputID_Board->render( hdc );
		m_inputPass_Board->render( hdc );
		//--------------------------------------------------------
		//< 버튼
		button_JOINROOM->render( hdc );
		button_CANCEL->render( hdc );
		//--------------------------------------------------------
		//< 유저 정보 출력
		playUser->OutputText( hdc );
	}
}

//< 지우기
void Popup_Lobby_EnterRoom_open::release( void )
{
	//< 불러온 이미지 지우기
	if( alpaImage != NULL ){ alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( popupImage != NULL ){ popupImage->release(); }
	SAFE_DELETE( popupImage );
	//< 버튼
	if( button_JOINROOM != NULL ){ button_JOINROOM->release(); }
	SAFE_DELETE( button_JOINROOM );
	if( button_CANCEL != NULL ){ button_CANCEL->release(); }
	SAFE_DELETE( button_CANCEL );
	//< 입력 맨트 이미지
	if( inputInfo_ID != NULL ){ inputInfo_ID->release(); }
	SAFE_DELETE( inputInfo_ID );
	if( inputInfo_PASS != NULL ){ inputInfo_PASS->release(); }
	SAFE_DELETE( inputInfo_PASS );
	//< 입력칸
	if( m_inputID_Board != NULL ){ m_inputID_Board->release(); }
	SAFE_DELETE( m_inputID_Board );
	if( m_inputPass_Board != NULL ){ m_inputPass_Board->release(); }
	SAFE_DELETE( m_inputPass_Board );
	SAFE_DELETE( playUser );
}

//< 이미지 불러오기
void Popup_Lobby_EnterRoom_open::loadImage( void )
{
	//< 알파 이미지
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load(L"Data/Resource/Image/Alpa_background.bmp",
		0, 0, RM_TRANS );
	//< 팝업창
	popupImage->init(L"Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< 이벤트처리
LRESULT	Popup_Lobby_EnterRoom_open::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
		//< 마우스 위치 받기
	case WM_MOUSEMOVE :
		{
			mousePos.x = LOWORD( lparam );
			mousePos.y = HIWORD( lparam );
		}
		break;
	case WM_LBUTTONUP :
		{
			//< 버튼 입장-------------------------------------------------
			//< 마우스 오버라면 다른이미지 출력
			if( button_JOINROOM->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_JOINROOM->inClickButton( true );
			}
			//< 버튼 cancel
			//< 마우스 오버라면 다른이미지 출력
			if( button_CANCEL->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_CANCEL->inClickButton( true );
			}
		}
		break;
		//< 문자 입력
	case WM_CHAR :
		{
		}
		break;
		//< 키보드 입력받기
	case WM_KEYDOWN :
		switch(wparam)
		{
			//< 엔터키 입력
		case VK_RETURN:
			{		
				button_JOINROOM->inClickButton( true );
			}
			break;
			//< 백스페이스 입력
		case VK_BACK :
			{
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< 씬정보 받기
int Popup_Lobby_EnterRoom_open::getNextScene( void )
{
    if (button_STATE == POPUP_NO_POPUP_GET_MAKE_ROOM)
    {
        return POPUP_NO_POPUP_GET_MAKE_ROOM;
    }

	//< 버튼이 눌렸을때만 실행
	if( button_STATE != POPUP_NONE )
	{
		if( button_STATE != POPUP_NO_POPUP &&
			button_STATE != POPUP_LOBBY_MAKEROOM_OPEN &&
			button_STATE != POPUP_LOBBY_MAKEROOM_CLOSE )
		{
			//< 임시 복사
            string tempID;// = inputRoomName->getString();
            string tempPA;// = inputPass->getString();

			//< 입력 부족 확인
			if( tempID.size() <= 0 ||
				tempPA.size() <= 0 )
			{
				//< 입력 정보 부족
				button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
				return button_STATE;
			}
			else
			{
				//if(0 == TCPIP_CLIENT->getPacketType())
				//{
				//	PACKET packet;
				//	packet.m_basicMsg.m_length = sizeof(BASIC_MSG);
				//	packet.m_basicMsg.m_type = CS_GAME_CREATE;

				//	TCPIP_CLIENT->sendPacket((char*)&packet);

				//	//< 접속할 방의 정보 저장
				//	GAME_DATA->setMyRoomName(tempID.c_str());
				//	GAME_DATA->setMyRoomOption(breakInto);
				//}

				//unsigned short type = TCPIP_CLIENT->getPacketType();
				//if(type == SC_GAME_CREATE_YES)
				{
					//< 방만들기 성공 POPUP_NO_POPUP_GET_MAKE_ROOM
					button_STATE = POPUP_LOBBY_MAKEROOM_SUCCESS;

					//TCPIP_CLIENT->init();
				}
				//else if(type == SC_GAME_CREATE_NO)
				{
					//< 만들기 실패 출력
					//button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;

					//TCPIP_CLIENT->init();
				}
			}
		}
	}

	return button_STATE; 
}
