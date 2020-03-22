#include "stdafx.h"
#include "Popup_Lobby_EnterRoom_close.h"

#include "ImageNode.h"
#include "PopupBox.h"
#include "CheckBox.h"
#include "MY_FontMgr.h"

Popup_Lobby_EnterRoom_close::Popup_Lobby_EnterRoom_close(void)
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
	playUser = new MY_FontMgr; 
	//< 방 비번
	inputPass = new InputString;

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

Popup_Lobby_EnterRoom_close::~Popup_Lobby_EnterRoom_close(void)
{
	release();
}

//< 초기화
void Popup_Lobby_EnterRoom_close::init( void )
{
	//< 선택 방정보 받아오기
	int getChoiceNumber = GAME_DATA->getChoiceNumber();

	//< 방정보 
	ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(getChoiceNumber);

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
	char arr[256];

	//< 유저이름, 현재 플레이중인 유저수
	sprintf_s( arr,"%s 의 방  %d/2명이 게임중", newRoom.m_userName[0],newRoom.m_roomNum );

	//< 유저 정보 받아오기
	playUser->LoadText( arr, tempRect, "HY헤드라인M", 40, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< 정보표시 방이름
	inputInfo_ID->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_ID->setRectPos( tempPoint.x -150, tempPoint.y - 66 +70, ALIGN_CENTER );
	//< 정보표시 비밀번호
	inputInfo_PASS->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_PASS->setRectPos( tempPoint.x -150, tempPoint.y - 2 +70, ALIGN_CENTER );

	//< 정보표시 방이름
	inputInfo_ID->loadFont( "방이름",
		inputInfo_ID->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//< 정보표시 비밀번호
	inputInfo_PASS->loadFont( "비밀번호",
		inputInfo_PASS->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< 입력판 ID
	m_inputID_Board->init( "Data/Resource/Image/JoinRoom.bmp",
		"Data/Resource/Image/JoinRoom.bmp",300, 60 );
	m_inputID_Board->setRectPos( tempPoint.x +110, tempPoint.y - 66 +70, ALIGN_CENTER );

	//< 유저 방제
	memset( arr, 0, sizeof( char )*256 );
	memmove_s( arr, 256, newRoom.m_roomName , lstrlen( newRoom.m_roomName ) );

	//< 방제 로드
	m_inputID_Board->loadFont( arr,
		m_inputID_Board->getRect(),
		"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );

	//< 입력판 PASS
	m_inputPass_Board->init( "Data/Resource/Image/button_INPUT.bmp",
		"Data/Resource/Image/button_INPUT_02.bmp",300, 60 );
	m_inputPass_Board->setRectPos( tempPoint.x+110, tempPoint.y - 2 +70, ALIGN_CENTER );

	//< 입력 Pass
	inputPass->init( m_inputPass_Board->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 0,0,0 );
	//---------------------------------------------------------------------------
	//< 버튼 같이하기
	button_JOINROOM->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_JOINROOM->loadFont("같이하기", button_JOINROOM->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_JOINROOM->setRectPos( tempPoint.x+160, tempPoint.y+130 +20, ALIGN_CENTER );

	//< 버튼 취소
	button_CANCEL->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_CANCEL->loadFont("취소", button_CANCEL->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CANCEL->setRectPos( tempPoint.x-150, tempPoint.y+130 +20, ALIGN_CENTER );
	//---------------------------------------------------------------------------
}

//< 업데이트
void Popup_Lobby_EnterRoom_close::update( POINT mousePos )
{
	//< 버튼 
	button_JOINROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_JOINROOM->getRect() ));
	button_JOINROOM->update();
	button_CANCEL->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CANCEL->getRect() ));
	button_CANCEL->update();

	//< 입력판 위치 받기
	m_inputPass_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_inputPass_Board->getRect() ));
	m_inputPass_Board->update();

	//< 버튼 방들어가기-------------------------------------------------
	if( button_JOINROOM->getPlayButtonAni() == true )
	{
		//< 선택 방정보 받아오기
		int getChoiceNumber = GAME_DATA->getChoiceNumber();
		//< 방정보 
		ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(getChoiceNumber);

		//< 임시 복사
		string tempPA = inputPass->getString();

		//< 입력 부족 확인
		if( tempPA.size() <= 0 )
		{
			//< 입력 정보 부족
			button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
		}
		else
		{
			//< 비번 비교 비번이 일치하면
			if( 0 == lstrcmp( tempPA.c_str(), newRoom.m_roomPW ) )
			{
				//< 접속 성공
				PACKET packet;
				packet.m_roomJoinReq.m_length = sizeof(ROOMJOIN_REQ);
				packet.m_roomJoinReq.m_type = CS_GAME_JOIN;
				packet.m_roomJoinReq.m_roomNum = 1;
				TCPIP_CLIENT->sendPacket(packet);
			}
			//< 틀렸다면
			else
			{
				//< 실패 
				button_STATE = POPUP_LOBBY_ENTER_ROOM_FAILL;
			}
		}

		//< 상태 돌리기
		button_JOINROOM->inCheckMouseOn( false );
		button_JOINROOM->inClickButton( false );
		button_JOINROOM->inPlayButtonAni( false );
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

	//< 패스워드----------------------------------------------------------
	if( m_inputPass_Board->getPlayButtonAni() == true )
	{
		//< 애니메이션 돌리기
		m_inputPass_Board->inPlayButtonAni( false );
		//< 클릭 돌리기
		m_inputPass_Board->inClickButton( false );

		//< 패스워드 입력 실행
		//inputPass->inInputCheck( true );
	}
	//------------------------------------------------------------

	//< 방 패스워드 입력
	inputPass->update( );
}

//< 랜더
void Popup_Lobby_EnterRoom_close::render( HDC hdc )
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
		//< 입력 방이름 패스워드
		inputPass->renderStar( hdc );
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
void Popup_Lobby_EnterRoom_close::release( void )
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
	//< 입력 폰트 지우기
	if( inputPass != NULL ){ inputPass->release(); }
	SAFE_DELETE( inputPass );
	SAFE_DELETE( playUser );
}

//< 이미지 불러오기
void Popup_Lobby_EnterRoom_close::loadImage( void )
{
	//< 알파 이미지
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );
	//< 팝업창
	popupImage->init("Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< 이벤트처리
LRESULT	Popup_Lobby_EnterRoom_close::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
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
			//-----------------------------------------------------------
			//< 방 패스워드
			if( m_inputPass_Board->getCheckMouseOn() == true )
			{
				m_inputPass_Board->inClickButton( true );
				inputPass->inInputCheck( true );
			}
		}
		break;
		//< 문자 입력
	case WM_CHAR :
		{
			//< 방정보 입력받기
			inputPass->getChar( wparam );
		}
		break;
		//< 키보드 입력받기
	case WM_KEYDOWN :
		switch(wparam)
		{
		case VK_RETURN :
			{
				//< 패스워드 입력중이라면
				if( inputPass->getInputCheck() == true )
				{
					//< 패스워드 입력 종료
					inputPass->inInputCheck( false );
					button_JOINROOM->inClickButton( true );
					break;
				}
			}
			break;
			//< 엔터키 입력
		case VK_TAB :
			{		
				//< 처음 입력이라면
				if( inputPass->getInputCheck() == false)
				{
					//< 패스워드 입력 애니메이션 실행
					m_inputPass_Board->inClickButton( true );
					inputPass->inInputCheck( true );
					break;
				}
			}
			break;
			//< 백스페이스 입력
		case VK_BACK :
			{
				//< 정보 입력 지우기
				inputPass->backSpace();
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< 씬정보 받기
int Popup_Lobby_EnterRoom_close::getNextScene( void )
{
	//< 버튼이 눌렸을때만 실행
	//if( button_STATE != POPUP_NONE )
	//{
	//	if( button_STATE != POPUP_NO_POPUP &&
	//		button_STATE != POPUP_LOBBY_MAKEROOM_OPEN &&
	//		button_STATE != POPUP_LOBBY_MAKEROOM_CLOSE )
	//	{
	//		//< 임시 복사
	//		string tempID = inputRoomName->getString();
	//		string tempPA = inputPass->getString();

	//		//< 입력 부족 확인
	//		if( tempID.size() <= 0 ||
	//			tempPA.size() <= 0 )
	//		{
	//			//< 입력 정보 부족
	//			button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
	//			return button_STATE;
	//		}
	//		else
	//		{
	//			if(0 == TCPIP_CLIENT->getPacketType())
	//			{
	//				PACKET packet;
	//				packet.m_basicMsg.m_length = sizeof(BASIC_MSG);
	//				packet.m_basicMsg.m_type = CS_GAME_CREATE;

	//				TCPIP_CLIENT->sendPacket((char*)&packet);

	//				//< 접속할 방의 정보 저장
	//				GAME_DATA->setMyRoomName(tempID.c_str());
	//				GAME_DATA->setMyRoomOption(breakInto);
	//			}

	//			unsigned short type = TCPIP_CLIENT->getPacketType();
	//			if(type == SC_GAME_CREATE_YES)
	//			{
	//				//< 방만들기 성공 POPUP_NO_POPUP_GET_MAKE_ROOM
	//				button_STATE = POPUP_LOBBY_MAKEROOM_SUCCESS;

	//				TCPIP_CLIENT->init();
	//			}
	//			else if(type == SC_GAME_CREATE_NO)
	//			{
	//				//< 만들기 실패 출력
	//				button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;

	//				TCPIP_CLIENT->init();
	//			}
	//		}
	//	}
	//}
	return button_STATE; 
}
