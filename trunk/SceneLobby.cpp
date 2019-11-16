#include "stdafx.h"

#include "ImageNode.h"
#include "MY_FontMgr.h"

#include "PopupMgr.h"

#include "SceneLobby.h"
//#include "SceneLogin.h"
//#include "SceneChoiceChar.h"
//#include "SceneTitle.h"
//#include "ScenePlayGame.h"
//
#include "PopupBox.h"
#include "ButtonClass.h"
//#include "RoomClass.h"
//#include "ChattingBox.h"

SceneLobby::SceneLobby(void)
{
	//< 폰트 할당
	m_font = new MY_Font;

	//< 배경 이미지
	m_image = new PopupBox;

	//< 버튼 할당
	button_REFRESH = new ButtonClass;
	button_FRIEND_LIST = new ButtonClass;
	button_MAKE_ROOM = new ButtonClass;
	button_EXIT = new ButtonClass;

	//< 팝업창 체크

	//< 방
	//room = new RoomClass;

	//< 채팅창
	//chatting = new ChattingBox;

	//< 방정보
	roomCountInfo = 0;
	//마우스 체크
	checkMosFRIENDLIST = true;
	checkMosMAKEROOM = true;
	checkMosEXIT = true;
}

SceneLobby::~SceneLobby(void)
{
	//< 지우기
	release();		
}


//< 초기화
bool SceneLobby::init( void ) 
{
	//< 배경이미지
	//< 배경이미지
	m_image->init("Data/Resource/Image/background_Login3.bmp",WINSIZE_X,WINSIZE_Y );
	m_image->setRectPos( 0,0, ALIGN_LEFT_TOP );
	//----------------------------------------------------------------------------
	//< 새로고침 button_REFRESH
	button_REFRESH->init(
		"Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_REFRESH->loadFont( "새로고침", button_REFRESH->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	//< 버튼 초기화
	button_FRIEND_LIST->init(
		"Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_FRIEND_LIST->loadFont( "친구목록", button_FRIEND_LIST->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	//< 방만들기
	button_MAKE_ROOM->init(
		"Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_MAKE_ROOM->loadFont( "방만들기", button_MAKE_ROOM->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	//< 나가기
	button_EXIT->init(
		"Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_EXIT->loadFont( "나가기", button_EXIT->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );

	//ALIGN_CENTER,				//< 중간정렬
	button_REFRESH->setRectPos		( WINSIZE_X/20 *17, WINSIZE_Y/20 *14, ALIGN_CENTER );
	//button_FRIEND_LIST->setRectPos	( WINSIZE_X/20 *17, WINSIZE_Y/20 *14, ALIGN_CENTER );
	button_MAKE_ROOM->setRectPos	( WINSIZE_X/20 *17, WINSIZE_Y/20 *16, ALIGN_CENTER );
	button_EXIT->setRectPos			( WINSIZE_X/20 *17, WINSIZE_Y/20 *18, ALIGN_CENTER );
	//---------------------------------------------------------------------------------
	////< 방
	//room->init();
	////< 채팅창
	//chatting->init();
	////-------------------------------------------------------------------------------
	////로비 사운드 재생
	//SOUND_MGR->soundPlay(SOUND_LOBBY);

	return true;
}
//< 업데이트
void SceneLobby::update( void ) 
{
	//< 팝업이 켜지 않았다면 갱신하지 않기
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< 버튼 위치 받기
		button_REFRESH->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_REFRESH->getRect() ));
		button_REFRESH->update();
		button_FRIEND_LIST->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_FRIEND_LIST->getRect() ));
		button_FRIEND_LIST->update();
		button_MAKE_ROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_MAKE_ROOM->getRect() ));
		button_MAKE_ROOM->update();
		button_EXIT->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_EXIT->getRect() ));
		button_EXIT->update();

		////< 방
		//room->update( mousePos );
		////< 채팅창 
		//chatting->update( mousePos );
	}

	//< 팝업창이 열려있지 않으면 실행
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< 새로고침 버튼-------------------------------------------------
		if( button_REFRESH->getClickButton() == true  &&
			button_REFRESH->getPlayButtonAni() == true )
		{
			//< 애니메이션 돌리기
			button_REFRESH->inPlayButtonAni( false );
			//< 클릭 돌리기
			button_REFRESH->inClickButton( false );
		}
		//< 친구목록 버튼-------------------------------------------------
		if( button_FRIEND_LIST->getClickButton() == true  &&
			button_FRIEND_LIST->getPlayButtonAni() == true )
		{
			//< 애니메이션 돌리기
			button_FRIEND_LIST->inPlayButtonAni( false );
			//< 클릭 돌리기
			button_FRIEND_LIST->inClickButton( false );

			//< 방만들기 팝업창
			//POPUP_MGR->changePopup( POPUP_LOBBY_FRIENDLIST );
			
			//< 임시 방정보 팝업
			POPUP_MGR->changePopup( POPUP_LOBBY_ENTER_ROOM_OPEN );
			//< 임시 게임오버 팝업
			//POPUP_MGR->changePopup( POPUP_GAME_OVER );

			//< 초기화
			POPUP_MGR->initPopup();

			//< 팝업창 키기
		}

		//< 방만들기 버튼-------------------------------------------------
		if( button_MAKE_ROOM->getClickButton() == true  &&
			button_MAKE_ROOM->getPlayButtonAni() == true )
		{
			//< 애니메이션 돌리기
			button_MAKE_ROOM->inPlayButtonAni( false );
			//< 클릭 돌리기
			button_MAKE_ROOM->inClickButton( false );

			//< 방만들기 팝업창
			POPUP_MGR->changePopup( POPUP_LOBBY_MAKEROOM_OPEN );

			//< 초기화
			POPUP_MGR->initPopup();

			//< 팝업창 키기
		}

		//< 나가기 버튼-------------------------------------------------
		//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
		if( button_EXIT->getClickButton() == true &&
			button_EXIT->getPlayButtonAni() == true )
		{
			//STATE_MGR->addState<SceneTitle>(SCENE_TITLE);
			//STATE_MGR->changeState( SCENE_TITLE );
			////< 기존씬삭제
			//STATE_MGR->deleteState( SCENE_LOBBY );
			return;
		}
	}
	//< 팝업창이 켜지면 갱신
	else
	{
		//< 팝업 갱신
		POPUP_MGR->updatePopup();

		//< 2차 팝업( 팝업에서 눌린버튼 판별 )
		int tempFlag = POPUP_MGR->buttonStatePopup();

		//< 할당이 되지 않았다면
		if( tempFlag == false )
		{
			//< 팝업창 끄기
		}

		//< 방만들기 버튼을 눌렀다면
		if( tempFlag == POPUP_NO_POPUP_GET_MAKE_ROOM )
		{
			//< 팝업창 끄기
			//STATE_MGR->addState<SceneChoiceChar>(SCENE_SELECT);
			//STATE_MGR->changeState( SCENE_SELECT );
			////< 기존씬삭제
			//STATE_MGR->deleteState( SCENE_LOBBY );
		}
		//< 버튼스테이트 끄기
		POPUP_MGR->inButtonState();
	}
	/*if(SOUND_MGR->isPlaySound(SOUND_LOBBY)==false)
	{
	SOUND_MGR->soundPlay(SOUND_LOBBY);
	}*/
}

//< 랜더
void SceneLobby::render( HDC hdc ) 
{
	//< 배경이미지
	m_image->renderNone( hdc );
	//임시---------------------------------------------------------
#ifdef _DEBUG
	if( NULL != hdc )
	{
		m_font->OutputText( hdc, 
			"로비 씬",
			0,0,
			"HY얕은샘물M",
			65,
			0,0,0 );
	}
	//< 마우스가 올라가 있는 상태면
	if( button_FRIEND_LIST->getCheckMouseOn() == true ||
		button_MAKE_ROOM->getCheckMouseOn() == true ||
		button_EXIT->getCheckMouseOn() == true )
	{
		TextOut( hdc, 200,0, "충돌",4);
	}
	else
	{
		TextOut( hdc, 200,0, "비충돌",6);
	}
	/*if(button_FRIEND_LIST->getCheckMouseOn() == true && checkMosFRIENDLIST == true)
	{
		SOUND_MGR->soundPlay(SOUND_BGM5);
		checkMosFRIENDLIST = false;
	}
	else if(button_FRIEND_LIST->getCheckMouseOn() == false && checkMosFRIENDLIST == false)
	{
		checkMosFRIENDLIST = true;
	}
	if(button_MAKE_ROOM->getCheckMouseOn() == true && checkMosMAKEROOM == true)
	{
		SOUND_MGR->soundPlay(SOUND_BGM5);
		checkMosMAKEROOM = false;
	}
	else if(button_MAKE_ROOM->getCheckMouseOn() == false && checkMosMAKEROOM == false)
	{
		checkMosMAKEROOM = true;
	}
	if(button_EXIT->getCheckMouseOn() == true && checkMosEXIT == true)
	{
		SOUND_MGR->soundPlay(SOUND_BGM5);
		checkMosEXIT = false;
	}
	else if(button_EXIT->getCheckMouseOn() == false && checkMosEXIT == false)
	{
		checkMosEXIT = true;
	}*/
#endif
	//-------------------------------------------------------------
	//< 방
	//room->render( hdc );
	////< 채팅창
	//chatting->render( hdc );
	//-------------------------------------------------------------
	//< 버튼 랜더
	button_REFRESH->render( hdc );
	//button_FRIEND_LIST->render( hdc );
	button_MAKE_ROOM->render( hdc );
	button_EXIT->render( hdc );

	//< 팝업창이 켜지면 랜더
	if( POPUP_MGR->getCheckPopup_ON() == true )
	{
		//< 팝업창 랜더
		POPUP_MGR->renderPopup( hdc );
	}
}
//< 해제
void SceneLobby::release( void ) 
{
	//< 폰트 지우기
	SAFE_DELETE( m_font );

	//< 배경 이미지
	if( m_image != NULL ){ m_image->release(); }
	SAFE_DELETE( m_image );

	//< 버튼 지우기
	if( button_REFRESH != NULL ){ button_REFRESH->release(); }
	SAFE_DELETE( button_REFRESH );
	if( button_FRIEND_LIST != NULL ){ button_FRIEND_LIST->release(); }
	SAFE_DELETE( button_FRIEND_LIST );
	if( button_MAKE_ROOM != NULL ){ button_MAKE_ROOM->release(); }
	SAFE_DELETE( button_MAKE_ROOM );
	if( button_EXIT != NULL ){ button_EXIT->release(); }
	SAFE_DELETE( button_EXIT );

	////< 방 지우기
	//if( room != NULL ){ room->release(); }
	//SAFE_DELETE( room );
	////< 채팅창 지우기
	//if( chatting != NULL ) { chatting->release(); }
	//SAFE_DELETE( chatting );

	
}

//< 이벤트처리
LRESULT	SceneLobby::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	//< 팝업창이 열려있지 않으면 실행
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		switch( msg )
		{
		case WM_LBUTTONUP :
			{
				//< 새로고침 버튼-------------------------------------------------
				if( button_REFRESH->getCheckMouseOn() == true )
				{
					button_REFRESH->inClickButton( true );
					
					break;
				}
				//< 친구목록 버튼-------------------------------------------------
				if( button_FRIEND_LIST->getCheckMouseOn() == true )
				{
					button_FRIEND_LIST->inClickButton( true );
					
					break;
				}
				//< 방만들기 버튼-------------------------------------------------
				if( button_MAKE_ROOM->getCheckMouseOn() == true )
				{
					button_MAKE_ROOM->inClickButton( true );
					
					break;
				}
				//< 나가기 버튼-------------------------------------------------
				if( button_EXIT->getCheckMouseOn() == true )
				{
					button_EXIT->inClickButton( true );
					
					break;
				}
			}
			break;
			//< 마우스 위치 받기
		case WM_MOUSEMOVE :
			{
				mousePos.x = LOWORD( lparam );
				mousePos.y = HIWORD( lparam );
			}
			break;
		}
		
	}
	//< 팝업창이 켜져있으면 팝업 프로시저 실행
	else
	{
		//< 프로시저 넘기기
		return POPUP_MGR->PopupProc( wnd ,msg,wparam,lparam );
	}

	if( wparam != NULL ||
		lparam != NULL )
	{
		//< 방만들기 프로시저
		//room->StateProc( wnd, msg, wparam, lparam );
		////< 채팅창 프로시저
		//return chatting->StateProc( wnd, msg, wparam, lparam );
	}

    // 임시
    return POPUP_MGR->PopupProc(wnd, msg, wparam, lparam);
 }