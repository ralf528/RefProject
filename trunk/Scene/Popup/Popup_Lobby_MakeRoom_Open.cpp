#include "stdafx.h"
#include "Popup_Lobby_MakeRoom_Open.h"

#include "../../ImageNode.h"
#include "../../PopupBox.h"
#include "../../CheckBox.h"

Popup_Lobby_MakeRoom_Open::Popup_Lobby_MakeRoom_Open(void)
{
	//< 배경판 이미지
	alpaImage = new ImageNode(0);
	//< 팝업창 이미지
	popupImage = new PopupBox;

	//< 입력 맨트 이미지
	inputInfo_ID = new ButtonClass;
	inputInfo_PASS = new ButtonClass;
	inputInfo_REPASS = new ButtonClass;
	//< 입력칸
	m_inputID_Board = new ButtonClass;
	m_inputPass_Board = new ButtonClass;

	//< 방만들기
	inputRoomName = new InputString;

	//< 마우스 포인터
	mousePos.x =0;
	mousePos.y =0;

	//< 버튼
	button_MAKEROOM = new ButtonClass;
	button_CANCEL = new ButtonClass;
	//< 버튼
	button_OPEN = new CheckBox;
	button_CLOSE = new CheckBox;
	//< 체크박스
	checkBox_OK = new CheckBox;
	checkBox_NO = new CheckBox;

	//< 난입상태
	breakInto = true;

	//< 버튼 상태 초기화
	button_STATE = POPUP_NONE;
}

Popup_Lobby_MakeRoom_Open::~Popup_Lobby_MakeRoom_Open(void)
{
	release();
}


//< 초기화
void Popup_Lobby_MakeRoom_Open::init( void )
{
	//< 지정 이미지 로드
	loadImage();

	//< 정렬
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< 팝업 이미지 중점 받기
	POINT tempPoint = popupImage->getCenter();
	//----------------------------------------------------------------------------
	//< 정보표시 방이름
	inputInfo_ID->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_ID->setRectPos( tempPoint.x -150, tempPoint.y - 66 +30, ALIGN_CENTER );
	//< 정보표시 비밀번호
	inputInfo_PASS->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_PASS->setRectPos( tempPoint.x -150, tempPoint.y - 2 +30, ALIGN_CENTER );
	//< 정보표시 난입허용
	inputInfo_REPASS->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_REPASS->setRectPos( tempPoint.x -150, tempPoint.y + 62 +30, ALIGN_CENTER );

	//< 정보표시 방이름
	inputInfo_ID->loadFont( "방이름",
		inputInfo_ID->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//< 정보표시 비밀번호
	inputInfo_PASS->loadFont( "비밀번호",
		inputInfo_PASS->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//< 정보표시 난입허용
	inputInfo_REPASS->loadFont( "난입",
		inputInfo_REPASS->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< 입력판 ID
	m_inputID_Board->init( "Data/Resource/Image/button_INPUT.bmp",
		"Data/Resource/Image/button_INPUT_02.bmp",300, 60 );
	m_inputID_Board->setRectPos( tempPoint.x +110, tempPoint.y - 66 +30, ALIGN_CENTER );
	//< 입력판 PASS
	m_inputPass_Board->init( "Data/Resource/Image/button_INPUT_ROCK.bmp",
		"Data/Resource/Image/button_INPUT_ROCK.bmp",300, 60 );
	m_inputPass_Board->setRectPos( tempPoint.x+110, tempPoint.y - 2 +30, ALIGN_CENTER );

	//< 입력 방이름
	inputRoomName->init( m_inputID_Board->getRect(), 
		"HY헤드라인M", 30, ALIGN_CENTER, 0,0,0 );
	//---------------------------------------------------------------------------
	//< 버튼 MAKEROOM
	button_MAKEROOM->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_MAKEROOM->loadFont("방만들기", button_MAKEROOM->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_MAKEROOM->setRectPos( tempPoint.x+160, tempPoint.y+130 +20, ALIGN_CENTER );

	//< 버튼 취소
	button_CANCEL->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_CANCEL->loadFont("취소", button_CANCEL->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CANCEL->setRectPos( tempPoint.x-150, tempPoint.y+130 +20, ALIGN_CENTER );
	//---------------------------------------------------------------------------
	
	//< 버튼 공개
	button_OPEN->init("Data/Resource/Image/button_top.bmp",
		"Data/Resource/Image/button_top_02.bmp",
		"Data/Resource/Image/button_top2.bmp",
		"Data/Resource/Image/button_top2_02.bmp",
		200, 50 );
	button_OPEN->loadFont("공개방", button_OPEN->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OPEN->setRectPos( popupImage->getRect().left +100, popupImage->getRect().top-40 +160, ALIGN_LEFT_TOP );

	//< 버튼 비공개
	button_CLOSE->init("Data/Resource/Image/button_top.bmp",
		"Data/Resource/Image/button_top_02.bmp",
		"Data/Resource/Image/button_top2.bmp",
		"Data/Resource/Image/button_top2_02.bmp",
		200, 50  );
	button_CLOSE->loadFont("비공개방", button_CLOSE->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CLOSE->setRectPos( popupImage->getRect().left+200 +100, popupImage->getRect().top-40 +160, ALIGN_LEFT_TOP );

	//< 처음은 허용 상태로 만들기
	button_OPEN->inCheckBox( CHECK_BOX_ON );
	//--------------------------------------------------------------
	//< 버튼 체크박스 허용
	checkBox_OK->init("Data/Resource/Image/on_off.bmp",
		"Data/Resource/Image/on_off_02.bmp",
		"Data/Resource/Image/on_off2.bmp",
		"Data/Resource/Image/on_off2_02.bmp",
		145, 60 );
	checkBox_OK->loadFont("허용", checkBox_OK->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_OK->setRectPos( tempPoint.x+35, tempPoint.y + 62 +30, ALIGN_CENTER );

	//< 버튼 체그박스 비허용
	checkBox_NO->init("Data/Resource/Image/on_off.bmp",
		"Data/Resource/Image/on_off_02.bmp",
		"Data/Resource/Image/on_off2.bmp",
		"Data/Resource/Image/on_off2_02.bmp",
		145, 60  );
	checkBox_NO->loadFont("비허용", checkBox_NO->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_NO->setRectPos( tempPoint.x+185, tempPoint.y + 62 +30, ALIGN_CENTER );

	//< 처음은 허용 상태로 만들기
	checkBox_OK->inCheckBox( CHECK_BOX_ON );
	//---------------------------------------------------------------------------
}

//< 업데이트
void Popup_Lobby_MakeRoom_Open::update( POINT mousePos )
{
	//< 버튼 
	button_MAKEROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_MAKEROOM->getRect() ));
	button_MAKEROOM->update();
	button_CANCEL->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CANCEL->getRect() ));
	button_CANCEL->update();
	//< 버튼 공개 비공개
	button_OPEN->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OPEN->getRect() ));
	button_OPEN->update();
	button_CLOSE->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CLOSE->getRect() ));
	button_CLOSE->update();
	//< 체크박스 
	checkBox_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_OK->getRect() ));
	checkBox_OK->update(); 
	checkBox_NO->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_NO->getRect() ));
	checkBox_NO->update();

	//< 입력판 위치 받기
	m_inputID_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_inputID_Board->getRect() ));
	m_inputID_Board->update();

	//< 패킷이 비어 있지 않다면
	//if(true != TCPIP_CLIENT->emptyQueue())
	//{
	//	//< 데이터 받았을 때
	//	unsigned short type = TCPIP_CLIENT->getPacketType();
	//	if(type == SC_ROOM_CREATE_YES)
	//	{
	//		//< 방만들기 성공 POPUP_NO_POPUP_GET_MAKE_ROOM
	//		button_STATE = POPUP_LOBBY_MAKEROOM_SUCCESS;

	//		/*PACKET sendPacket;
	//		sendPacket.m_logout.m_length = sizeof(LOGOUT);
	//		sendPacket.m_logout.m_type = CS_LOGOUT_LOBBY;
	//		strcpy_s(sendPacket.m_logout.m_id, GAME_DATA->getUserId());*/

	//		PACKET packet;
	//		TCPIP_CLIENT->getPacket(packet);

	//		//> 서버 정보 설정
	//		INITCONFIG initConfig;
	//		//> 서버 포트
	//		initConfig.serverPort = packet.m_roomCreateAck.m_port;
	//		//> 수신 버퍼 개수
	//		initConfig.recvBufCnt = 20;
	//		//> 수신 버퍼 사이즈
	//		initConfig.recvBufSize = 1024;
	//		//> 송신 버퍼 개수
	//		initConfig.sendBufCnt = 20;
	//		//> 송신 버퍼 사이즈
	//		initConfig.sendBufSize = 1024;
	//		//> 작업자 스레드 개수
	//		initConfig.workerThreadCnt = 1;
	//		//> 프로세스 처리 스레드 개수
	//		initConfig.processThreadCnt = 1;
	//		//> 패킷 동시 처리 가능 개수
	//		initConfig.processPacketCnt = 50;
	//		HOST_SERVER->setHostis(true);
	//		HOST_SERVER->setIsConnector(false);
	//		//> 서버 시작
	//		HOST_SERVER->ServerStart(initConfig);
	//		//> 커넥션 생성
	//		CONNECTION_MGR->CreateConnection(initConfig,4);

	//		TCPIP_CLIENT->popPacket();
	//	}
	//	else if(type == SC_ROOM_CREATE_NO)
	//	{
	//		//< 만들기 실패 출력
	//		button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
	//		TCPIP_CLIENT->popPacket();
	//	}
	//}

	//< 버튼 방만들기-------------------------------------------------
	if( button_MAKEROOM->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		button_MAKEROOM->inCheckMouseOn( false );
		button_MAKEROOM->inClickButton( false );
		button_MAKEROOM->inPlayButtonAni( false );

		//< 임시 복사
		string tempID = inputRoomName->getString();
		
		//< 입력 부족 확인
		if( tempID.size() <= 0 )
		{
			//< 입력 정보 부족
			button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
		}
		else
		{
			/*PACKET packet;
			packet.m_roomCreateReq.m_length = sizeof(CREATE_ROOM_REQ);
			packet.m_roomCreateReq.m_type = CS_ROOM_CREATE;
			packet.m_roomCreateReq.m_isSecret = false;*/
			if( checkBox_OK->getCheckBox() == CHECK_BOX_ON )
			{
				//packet.m_roomCreateReq.m_isTrespass = true;
			}
			else
			{
				//packet.m_roomCreateReq.m_isTrespass = false;
			}

			//strcpy_s(packet.m_roomCreateReq.m_roomName, sizeof(packet.m_roomCreateReq.m_roomName), tempID.c_str());
			//strcpy_s(packet.m_roomCreateReq.m_roomPW, sizeof(packet.m_roomCreateReq.m_roomPW), " ");
			//TCPIP_CLIENT->sendPacket(packet);
		}
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
	//< 버튼 공개 -------------------------------------------------
	//< 공개
	//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
	if( button_OPEN->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		button_OPEN->inCheckMouseOn( false );
		button_OPEN->inClickButton( false );
		button_OPEN->inPlayButtonAni( false );
		//< 클릭 리턴
		button_STATE = POPUP_LOBBY_MAKEROOM_OPEN;

		//< 계속 허용 상태로 만들기
		button_OPEN->inCheckBox( CHECK_BOX_ON );
	}
	//< 비공개
	//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
	if( button_CLOSE->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		button_CLOSE->inCheckMouseOn( false );
		button_CLOSE->inClickButton( false );
		button_CLOSE->inPlayButtonAni( false );
		//< 클릭 리턴
		button_STATE = POPUP_LOBBY_MAKEROOM_CLOSE;
	}

	//체크박스--------------------------------------------------------
	//< 허용
	if( checkBox_OK->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		checkBox_OK->inCheckMouseOn( false );
		checkBox_OK->inClickButton( false );
		checkBox_OK->inPlayButtonAni( false );

		//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
		if( checkBox_NO->getCheckBox() == CHECK_BOX_ON )
		{
			checkBox_NO->inCheckBox( CHECK_BOX_OFF );
		}
		//< 체크상태로 만들기
		checkBox_OK->inCheckBox( CHECK_BOX_ON );

		//< 클릭 리턴
		button_STATE = POPUP_NONE;

		//< 플래그
		breakInto = true;
	}
	//< 비허용
	if( checkBox_NO->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		checkBox_NO->inCheckMouseOn( false );
		checkBox_NO->inClickButton( false );
		checkBox_NO->inPlayButtonAni( false );

		//< 허용의 체크박스가 ON이라면 OFF로 바꾸기
		if( checkBox_OK->getCheckBox() == CHECK_BOX_ON )
		{
			checkBox_OK->inCheckBox( CHECK_BOX_OFF );
		}
		//< 체크상태로 만들기
		checkBox_NO->inCheckBox( CHECK_BOX_ON );

		//< 클릭 리턴
		button_STATE = POPUP_NONE;

		//< 플래그
		breakInto = false;
	}

	//< 입력창 아이디-------------------------------------------------
	//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
	if( m_inputID_Board->getPlayButtonAni() == true )
	{
		//< 애니메이션 돌리기
		m_inputID_Board->inPlayButtonAni( false );
		//< 클릭 돌리기
		m_inputID_Board->inClickButton( false );

		//< 아이디 입력 실행
		//inputRoomName->inInputCheck( true );
	}

	//< 방이름 입력
	inputRoomName->update( );
}

//< 랜더
void Popup_Lobby_MakeRoom_Open::render( HDC hdc )
{
	//< 투명 이미지 랜더
	alpaImage->render( hdc, 0,0  );
	//< 팝업창 랜더
	popupImage->render( hdc );

	if( popupImage->getPlayPopupBoxAni() == true )
	{
		//-------------------------------------------------
		//< 버튼 공개 비공개
		button_OPEN->render( hdc );
		button_CLOSE->render( hdc );
		//-------------------------------------------
		//< 체크박스
		checkBox_OK->render( hdc );
		checkBox_NO->render( hdc );
		//--------------------------------------------------------
		//< 입력 맨트 이미지
		inputInfo_ID->render( hdc );
		inputInfo_PASS->render( hdc );
		inputInfo_REPASS->render( hdc );
		//--------------------------------------------------------
		//< 입력보드
		m_inputID_Board->render( hdc );
		m_inputPass_Board->render( hdc );
		//--------------------------------------------------------
		//< 입력 방이름 
		inputRoomName->render( hdc );
		//-------------------------------------------------------
		//< 버튼
		button_MAKEROOM->render( hdc );
		button_CANCEL->render( hdc );
	}
}

//< 지우기
void Popup_Lobby_MakeRoom_Open::release( void )
{
	//< 불러온 이미지 지우기
	if( alpaImage != NULL ){ alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( popupImage != NULL ){ popupImage->release(); }
	SAFE_DELETE( popupImage );
	//< 버튼
	if( button_MAKEROOM != NULL ){ button_MAKEROOM->release(); }
	SAFE_DELETE( button_MAKEROOM );
	if( button_CANCEL != NULL ){ button_CANCEL->release(); }
	SAFE_DELETE( button_CANCEL );
	//< 버튼 공개 비공개
	if( button_OPEN != NULL ){ button_OPEN->release(); }
	SAFE_DELETE( button_OPEN );
	if( button_CLOSE != NULL ){ button_CLOSE->release(); }
	SAFE_DELETE( button_CLOSE );
	//< 체크박스
	if( checkBox_OK != NULL ){ checkBox_OK->release(); }
	SAFE_DELETE( checkBox_OK );
	if( checkBox_NO != NULL ){ checkBox_NO->release(); }
	SAFE_DELETE( checkBox_NO );
	//< 입력 맨트 이미지
	if( inputInfo_ID != NULL ){ inputInfo_ID->release(); }
	SAFE_DELETE( inputInfo_ID );
	if( inputInfo_PASS != NULL ){ inputInfo_PASS->release(); }
	SAFE_DELETE( inputInfo_PASS );
	if( inputInfo_REPASS != NULL ){ inputInfo_REPASS->release(); }
	SAFE_DELETE( inputInfo_REPASS );
	//< 입력칸
	if( m_inputID_Board != NULL ){ m_inputID_Board->release(); }
	SAFE_DELETE( m_inputID_Board );
	if( m_inputPass_Board != NULL ){ m_inputPass_Board->release(); }
	SAFE_DELETE( m_inputPass_Board );
	//< 입력 폰트 지우기
	if( inputRoomName != NULL ){ inputRoomName->release(); }
	SAFE_DELETE( inputRoomName );
}

//< 이미지 불러오기
void Popup_Lobby_MakeRoom_Open::loadImage( void )
{
	//< 알파 이미지
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );
	//< 팝업창
	popupImage->init("Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< 이벤트처리
LRESULT	Popup_Lobby_MakeRoom_Open::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
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
			//< 버튼 회원가입-------------------------------------------------
			//< 마우스 오버라면 다른이미지 출력
			if( button_MAKEROOM->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_MAKEROOM->inClickButton( true );
			}
			//< 버튼 cancel
			//< 마우스 오버라면 다른이미지 출력
			if( button_CANCEL->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_CANCEL->inClickButton( true );
			}

			//< 공개 비공개-------------------------------------------------
			//< 마우스 오버라면 다른이미지 출력
			if( button_OPEN->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_OPEN->inClickButton( true );
			}
			//< 비공개
			//< 마우스 오버라면 다른이미지 출력
			if( button_CLOSE->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_CLOSE->inClickButton( true );
			}

			//< 난입 허용-------------------------------------------------
			//< 마우스 오버라면 다른이미지 출력
			if( checkBox_OK->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_OK->inClickButton( true );
			}
			//< 비허용
			//< 마우스 오버라면 다른이미지 출력
			if( checkBox_NO->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_NO->inClickButton( true );
			}

			//-----------------------------------------------------------
			//< 방이름
			//< 마우스 눌리면 상태 변경
			if( m_inputID_Board->getCheckMouseOn() == true )
			{
				m_inputID_Board->inClickButton( true );
				inputRoomName->inInputCheck( true );
			}
		}
		break;
		//< 문자 입력
	case WM_CHAR :
		{
			inputRoomName->getChar( wparam );
		}
		break;
		//< 키보드 입력받기
	case WM_KEYDOWN :
		switch(wparam)
		{
		case VK_RETURN :
			{
				//< 아이디 입력중이라면
				if( inputRoomName->getInputCheck() == true )
				{
					//< 아이디 입력 종료
					inputRoomName->inInputCheck( false );
					button_MAKEROOM->inClickButton( true );
					break;
				}
			}
			break;
			//< 엔터키 입력
		case VK_TAB:
			{		
				//< 처음 입력이라면
				if( inputRoomName->getInputCheck() == false )
				{
					//< 아이디 입력 실행
					m_inputID_Board->inClickButton( true );
					inputRoomName->inInputCheck( true );
					break;
				}
			}
			break;
			//< 백스페이스 입력
		case VK_BACK :
			{
				inputRoomName->backSpace();
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< 씬정보 받기
int Popup_Lobby_MakeRoom_Open::getNextScene( void )
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

	//		//< 입력 부족 확인
	//		if( tempID.size() <= 0 )
	//		{
	//			//< 입력 정보 부족
	//			button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
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
	//			
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
