#include "stdafx.h"
#include "ChattingBox.h"

#include "../../MY_FontMgr.h"
#include "../../PopupBox.h"
#include "../../InputString.h"
#include "../../ButtonClass.h"

ChattingBox::ChattingBox(void)
{
	//< 폰트
	m_font = new MY_Font;
	//< 배경 이미지
	m_image = new PopupBox;

	//< 채팅 입력 판
	m_input_Board = new ButtonClass;
	//< 입력 스트링
	inputChar = new InputString;

	//< 버튼 위,아래
	button_UP = new ButtonClass;
	button_DOWN = new ButtonClass;
	//< 스크롤바
	button_SCROLL = new ButtonClass;
	button_SCROLL_NODE = new ButtonClass;

	//< 처음은 5페이지에서 시작
	stringPage = 5;
	oldStringPage = 0;
	//< 5페이지
	nodePosition = 548;
}


ChattingBox::~ChattingBox(void)
{
	release();
}


//< 초기화
void ChattingBox::init( void )
{
	//< 배경 이미지 로드
	m_image->loadImage( L"Data/Resource/Image/Popup_Box4.bmp", 921,270 );

	//< 고정 위치
	m_image->setRectPos( WINSIZE_X/2-120, WINSIZE_Y/2+180, ALIGN_CENTER );

	//< 팝업 이미지 중점 받기
	POINT tempPoint = m_image->getCenter();

	//< 입력판 
	m_input_Board->init( L"Data/Resource/Image/button_CHAR_02.bmp",
		L"Data/Resource/Image/button_CHAR_02.bmp",888, 44 );
	m_input_Board->setRectPos( tempPoint.x, tempPoint.y+90, ALIGN_CENTER ); 
	//< 임시 렉트
	RECT tempRect = m_input_Board->getRect();
	tempRect.left += 120;

	//< 입력 
	inputChar->init( tempRect, L"HY헤드라인M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	//< 입력 실행
	inputChar->inInputCheck( true );

	//< 고정 포지션
	int posX = 84;
	int posY = 437;

	//< 렉트 크가
	int rectsizeX = 100;
	int rectsizeY = 40;

	//< 간격
	int cell = 5;
	int cell2 = 50;

	//< 랭킹정보 랙트 깔기
	for( int j=0; j<MAX_CHAR_LINE; j++ )
	{
		SetRect( &inputData[j].rect[0], 
			0			+posX, 
			0			+posY +(rectsizeY*j), 
			rectsizeX	+posX, 
			rectsizeY	+posY +(rectsizeY*j) );

		SetRect( &inputData[j].rect[1], 
			0			+posX	+ rectsizeX + cell, 
			0			+posY +(rectsizeY*j), 
			(rectsizeX	+posX   + rectsizeX*8)-20, 
			rectsizeY	+posY +(rectsizeY*j) );

		inputData[j].name.clear();
		inputData[j].text.clear();
		inputData[j].name.LoadText( inputData[j].rect[0], L"HY헤드라인M", 20, ALIGN_CENTER, 255,255,255 );
		inputData[j].text.LoadText( inputData[j].rect[1], L"HY헤드라인M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	}
	//< 랭킹정보 저장 랙트 깔기
	for( int j=0; j<8; j++ )
	{
		SetRect( &inputDataSave[j].rect[0], 
			0			+posX, 
			0			+posY +(rectsizeY*j), 
			rectsizeX	+posX, 
			rectsizeY	+posY +(rectsizeY*j) );

		SetRect( &inputDataSave[j].rect[1], 
			0			+posX	+ rectsizeX + cell, 
			0			+posY +(rectsizeY*j), 
			(rectsizeX	+posX   + rectsizeX*8)-20, 
			rectsizeY	+posY +(rectsizeY*j) );

		inputDataSave[j].name.clear();
		inputDataSave[j].text.clear();
		inputDataSave[j].name.LoadText( inputDataSave[j].rect[0], L"HY헤드라인M", 20, ALIGN_CENTER, 255,255,255 );
		inputDataSave[j].text.LoadText( inputDataSave[j].rect[1], L"HY헤드라인M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	}

	//< 유저 이름 렉트
	userNameRect.left = 84;
	userNameRect.top = 614;
	userNameRect.right = 183;
	userNameRect.bottom = 647;

	//< 버튼 위,아래
	button_UP->init(L"Data/Resource/Image/button_UP.bmp",
		L"Data/Resource/Image/button_UP_02.bmp",
		L"Data/Resource/Image/button_UP_DIS.bmp",
		45, 46 );
	button_DOWN->init(L"Data/Resource/Image/button_DOWN.bmp",
		L"Data/Resource/Image/button_DOWN_02.bmp",
		L"Data/Resource/Image/button_DOWN_DIS.bmp",
		45, 46 );
	button_UP->setRectPos( 942, 441, ALIGN_CENTER );
	button_DOWN->setRectPos( 942, 580, ALIGN_CENTER );

	//< 스크롤바
	button_SCROLL->init(L"Data/Resource/Image/scroll_board.bmp",
		L"Data/Resource/Image/scroll_board.bmp",
		32, 94 );
	button_SCROLL_NODE->init(L"Data/Resource/Image/scroll_board_loot.bmp",
		L"Data/Resource/Image/scroll_board_loot.bmp",
		26, 12 );
	button_SCROLL->setRectPos( 942, 510, ALIGN_CENTER );
	button_SCROLL_NODE->setRectPos( 942, nodePosition, ALIGN_CENTER );

	//---------------------------------------------------------------------------------------------
	//< 유저 이름 받기
	//userName = GAME_DATA->getUserId();
	m_font->LoadText(MY_Font::StringToTCHAR(userName), userNameRect, L"HY헤드라인M", 20, ALIGN_CENTER, 255,255,255 );
	//---------------------------------------------------------------------------------------------
}

//< 업데이트
void ChattingBox::update( POINT mousePos )
{

	//< 패킷이 비어 있지 않다면
	//if(true != TCPIP_CLIENT->emptyQueue())
	//{
	//	unsigned short type = TCPIP_CLIENT->getPacketType();
	//	if(type == SC_CHATTING)
	//	{
	//		PACKET packet;
	//		TCPIP_CLIENT->getPacket(packet);
	//		inputChar->setString(packet.m_chatMsg.m_chatMsg);
	//		userName = packet.m_chatMsg.m_id;

	//		//< 저장
	//		StringPush();
	//		//< 5페이지로 돌리기
	//		stringPage = 5;
	//		oldStringPage = 0;
	//		//< 입력 지우기
	//		inputChar->clear();

	//		userName = GAME_DATA->getUserId();

	//		TCPIP_CLIENT->popPacket();
	//	}
	//}

	//< 입력판 위치 받기
	m_input_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_input_Board->getRect() ));
	m_input_Board->update();

	//< 버튼 위,아래
	button_UP->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_UP->getRect() ));
	button_UP->update();
	button_DOWN->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_DOWN->getRect() ));
	button_DOWN->update();

	//< 스크롤바 체크
	button_SCROLL_NODE->setRectPos( 942, nodePosition, ALIGN_CENTER );

	//< 패스워드----------------------------------------------------------
	//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
	if( m_input_Board->getPlayButtonAni() == true )
	{
		//< 애니메이션 돌리기
		m_input_Board->inPlayButtonAni( false );
		//< 클릭 돌리기
		m_input_Board->inClickButton( false );
	}

	//< 버튼 위-------------------------------------------------
	if( button_UP->getPlayButtonAni() == true )
	{
		if( stringPage > 1 )
		{
			//< 페이지 감소
			stringPage --;
			//< 좌표이동
			nodePosition = nodePosition - 19;
		}
		button_UP->inClickButton( false );
		button_UP->inPlayButtonAni( false );
	}
	//< 버튼 아래-------------------------------------------------
	if( button_DOWN->getPlayButtonAni() == true )
	{	
		if( stringPage < 5 )
		{
			//< 페이지 증가
			stringPage ++;
			//< 좌표이동
			nodePosition = nodePosition + 19;
		}
		button_DOWN->inClickButton( false );
		button_DOWN->inPlayButtonAni( false );
	}
	//< 버튼 잠그기------------------------------------------------
	if( stringPage == 1 )
	{
		button_DOWN->checkButtonTrue();
		button_UP->checkButtonFalse();
	}
	else if( stringPage == 5 )
	{
		button_DOWN->checkButtonFalse();
		button_UP->checkButtonTrue();
	}
	else
	{
		button_DOWN->checkButtonTrue();
		button_UP->checkButtonTrue();
	}

	//< 입력
	inputChar->update( );
	//< 스트링 표시 갱신
	StringUpdate();
}

//< 랜더
void ChattingBox::render( HDC hdc )
{
	//< 배경 랜더
	m_image->renderNone( hdc );

	//< 입력보드
	m_input_Board->render( hdc );
	//-------------------------------------------------------
	//< 유저 이름
	//Rectangle( hdc, userNameRect.left, userNameRect.top, userNameRect.right, userNameRect.bottom );
	m_font->OutputText( hdc );
	//< 입력
	inputChar->render( hdc );

	//< 그리기
	for( int j=0; j<MAX_CHAR_LINE; j++ )
	{
		//Rectangle( hdc, inputData[j].rect[0].left, inputData[j].rect[0].top, inputData[j].rect[0].right, inputData[j].rect[0].bottom );
		//Rectangle( hdc, inputData[j].rect[1].left, inputData[j].rect[1].top, inputData[j].rect[1].right, inputData[j].rect[1].bottom );
		inputData[j].text.OutputText( hdc );
		inputData[j].name.OutputText( hdc );
	}

	//< 스크롤바
	button_SCROLL->render( hdc );
	button_SCROLL_NODE->render( hdc );
	//< 버튼
	button_UP->render( hdc );
	button_DOWN->render( hdc );
}

//< 지우기
void ChattingBox::release( void )
{
	//< 폰트
	SAFE_DELETE( m_font );
	//< 배경이미지
	if( NULL != m_image ){ m_image->release(); }
	SAFE_DELETE( m_image );

	if( m_input_Board != NULL ){ m_input_Board->release(); }
	SAFE_DELETE( m_input_Board );

	if( inputChar != NULL ){ inputChar->release(); }
	SAFE_DELETE( inputChar );

	//< 버튼 지우기
	if( button_UP != NULL ) { button_UP->release();}
	SAFE_DELETE( button_UP );
	if( button_DOWN != NULL ) { button_DOWN->release();}
	SAFE_DELETE( button_DOWN );
	//< 스크롤바
	if( button_SCROLL != NULL ) { button_SCROLL->release();}
	SAFE_DELETE( button_SCROLL );
	if( button_SCROLL_NODE != NULL ) { button_SCROLL_NODE->release();}
	SAFE_DELETE( button_SCROLL_NODE );
}

//< 이벤트처리
LRESULT	ChattingBox::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP :
		{
			//< 입력창
			if( m_input_Board->getCheckMouseOn() == true )
			{
					m_input_Board->inClickButton( true );
			}
			//< 버튼 업
			if( button_UP->getCheckMouseOn() == true &&
				button_UP->getPlayButtonAni() == false )
			{
				//< 클릭으로 상태 변경
				button_UP->inClickButton( true );
			}
			//< 버튼 다운
			if( button_DOWN->getCheckMouseOn() == true &&
				button_DOWN->getPlayButtonAni() == false )
			{
				//< 클릭으로 상태 변경
				button_DOWN->inClickButton( true );
			}
		}
		break;
		//< 문자 입력
	case WM_CHAR :
		{
			//< 입력받기
			inputChar->getChar( wparam );
		}
		break;
		//< 키보드 입력받기
	case WM_KEYDOWN :
		switch(wparam)
		{
			//< 엔터키 입력
		case VK_RETURN:
			{	
				//< 입력된 스트링이 있다면 갱신
				if( inputChar->getCharString().size() != 0 )
				{
					//< 5페이지
					nodePosition = 548;

					//< 저장
					StringPush();

					//< 5페이지로 돌리기
					stringPage = 5;
					oldStringPage = 0;

					/*PACKET sendPacket;
					sendPacket.m_chatMsg.m_type = CS_CHATTING;
					sendPacket.m_chatMsg.m_length = sizeof(CHAT_MSG);
					strcpy_s(sendPacket.m_chatMsg.m_chatMsg, inputChar->getString());
					strcpy_s(sendPacket.m_chatMsg.m_id, userName.c_str());
					TCPIP_CLIENT->sendPacket(sendPacket);*/

					//< 입력 지우기
					inputChar->clear();

					
				}
			}
			break;
			//< 백스페이스 입력
		case VK_BACK :
			{
				//< 정보 입력 지우기
				inputChar->backSpace();
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}
//< 스트링 갱신 출력
void ChattingBox::StringUpdate( void )
{
	if( oldStringPage != stringPage )
	{
	switch( stringPage )
	{
	case 1 :
		{
			//< 스트링 밀기
			inputData[0].name.clear();
			inputData[0].text.clear();
			inputData[0].name.inCharChar( inputDataSave[0].name.getChar() );
			inputData[0].text.inCharChar( inputDataSave[0].text.getChar() );
			inputData[1].name.clear();
			inputData[1].text.clear();
			inputData[1].name.inCharChar( inputDataSave[1].name.getChar() );
			inputData[1].text.inCharChar( inputDataSave[1].text.getChar() );
			inputData[2].name.clear();
			inputData[2].text.clear();
			inputData[2].name.inCharChar( inputDataSave[2].name.getChar() );
			inputData[2].text.inCharChar( inputDataSave[2].text.getChar() );
			inputData[3].name.clear();
			inputData[3].text.clear();
			inputData[3].name.inCharChar( inputDataSave[3].name.getChar() );
			inputData[3].text.inCharChar( inputDataSave[3].text.getChar() );
			//< 스트링 페이지 갱신
			oldStringPage = 1;
		}
		break;
	case 2 :
		{
			//< 스트링 밀기
			inputData[0].name.clear();
			inputData[0].text.clear();
			inputData[0].name.inCharChar( inputDataSave[1].name.getChar() );
			inputData[0].text.inCharChar( inputDataSave[1].text.getChar() );
			inputData[1].name.clear();
			inputData[1].text.clear();
			inputData[1].name.inCharChar( inputDataSave[2].name.getChar() );
			inputData[1].text.inCharChar( inputDataSave[2].text.getChar() );
			inputData[2].name.clear();
			inputData[2].text.clear();
			inputData[2].name.inCharChar( inputDataSave[3].name.getChar() );
			inputData[2].text.inCharChar( inputDataSave[3].text.getChar() );
			inputData[3].name.clear();
			inputData[3].text.clear();
			inputData[3].name.inCharChar( inputDataSave[4].name.getChar() );
			inputData[3].text.inCharChar( inputDataSave[4].text.getChar() );
			//< 스트링 페이지 갱신
			oldStringPage = 2;
		}
		break;
	case 3 :
		{
			//< 스트링 밀기
			inputData[0].name.clear();
			inputData[0].text.clear();
			inputData[0].name.inCharChar( inputDataSave[2].name.getChar() );
			inputData[0].text.inCharChar( inputDataSave[2].text.getChar() );
			inputData[1].name.clear();
			inputData[1].text.clear();
			inputData[1].name.inCharChar( inputDataSave[3].name.getChar() );
			inputData[1].text.inCharChar( inputDataSave[3].text.getChar() );
			inputData[2].name.clear();
			inputData[2].text.clear();
			inputData[2].name.inCharChar( inputDataSave[4].name.getChar() );
			inputData[2].text.inCharChar( inputDataSave[4].text.getChar() );
			inputData[3].name.clear();
			inputData[3].text.clear();
			inputData[3].name.inCharChar( inputDataSave[5].name.getChar() );
			inputData[3].text.inCharChar( inputDataSave[5].text.getChar() );
			//< 스트링 페이지 갱신
			oldStringPage = 3;
		}
		break;
	case 4 :
		{
			//< 스트링 밀기
			inputData[0].name.clear();
			inputData[0].text.clear();
			inputData[0].name.inCharChar( inputDataSave[3].name.getChar() );
			inputData[0].text.inCharChar( inputDataSave[3].text.getChar() );
			inputData[1].name.clear();
			inputData[1].text.clear();
			inputData[1].name.inCharChar( inputDataSave[4].name.getChar() );
			inputData[1].text.inCharChar( inputDataSave[4].text.getChar() );
			inputData[2].name.clear();
			inputData[2].text.clear();
			inputData[2].name.inCharChar( inputDataSave[5].name.getChar() );
			inputData[2].text.inCharChar( inputDataSave[5].text.getChar() );
			inputData[3].name.clear();
			inputData[3].text.clear();
			inputData[3].name.inCharChar( inputDataSave[6].name.getChar() );
			inputData[3].text.inCharChar( inputDataSave[6].text.getChar() );
			//< 스트링 페이지 갱신
			oldStringPage = 4;
		}
		break;
	case 5 :
		{
			//< 스트링 밀기
			inputData[0].name.clear();
			inputData[0].text.clear();
			inputData[0].name.inCharChar( inputDataSave[4].name.getChar() );
			inputData[0].text.inCharChar( inputDataSave[4].text.getChar() );
			inputData[1].name.clear();
			inputData[1].text.clear();
			inputData[1].name.inCharChar( inputDataSave[5].name.getChar() );
			inputData[1].text.inCharChar( inputDataSave[5].text.getChar() );
			inputData[2].name.clear();
			inputData[2].text.clear();
			inputData[2].name.inCharChar( inputDataSave[6].name.getChar() );
			inputData[2].text.inCharChar( inputDataSave[6].text.getChar() );
			inputData[3].name.clear();
			inputData[3].text.clear();
			inputData[3].name.inCharChar( inputDataSave[7].name.getChar() );
			inputData[3].text.inCharChar( inputDataSave[7].text.getChar() );
			//< 스트링 페이지 갱신
			oldStringPage = 5;
		}
		break;
	}
	}
}
//< 스트링 저장
void ChattingBox::StringPush( void )
{
	//< 스트링 밀기
	for( int i=0; i<7; i++ )
	{
		inputDataSave[i].name.clear();
		inputDataSave[i].text.clear();
		inputDataSave[i].name.inCharChar( inputDataSave[i+1].name.getChar() );
		inputDataSave[i].text.inCharChar( inputDataSave[i+1].text.getChar() );
	}
	//< 스트링에 저장
	/*inputData[6].name.clear();
	inputData[6].text.clear();
	inputData[6].name.inCharChar( inputData[7].name.getChar() );
	inputData[6].text.inCharChar( inputData[7].text.getChar() );*/
	//< 스트링에 저장
	inputDataSave[7].name.clear();
	inputDataSave[7].text.clear();
	inputDataSave[7].name.inChar( userName );
	inputDataSave[7].text.inCharChar( inputChar->getString() );
}