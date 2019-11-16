#include "stdafx.h"
#include "PopupMgr.h"

//#include "Popup_Login_Login_Fail.h"
//#include "Popup_Login_Login_Success.h"
//#include "Popup_Login_Exit.h"
//#include "Popup_Login_Join.h"
//#include "Popup_Login_Login_OverlabFaill.h"
//#include "Popup_Login_Join_Success.h"
//#include "Popup_Login_Join_Faill.h"
//#include "Popup_Login_Fail_None.h"
//#include "Popup_Login_Fail_Overlap_Id.h"
//#include "Popup_Login_Fail_Discord_Pass.h"
//#include "Popup_Back.h"
//#include "Popup_Title_Collection.h"
//#include "Popup_Title_Rank.h"
//#include "Popup_Lobby_MakeRoom_close.h"
//#include "Popup_Lobby_MakeRoom_Success.h"
//#include "Popup_Lobby_MakeRoom_Open.h"
//#include "Popup_Lobby_FriendList.h"
//#include "Popup_Lobby_EnterRoom_close.h"
//#include "Popup_Lobby_EnterRoom_open.h"
//#include "Popup_Lobby_EnterRoom_Success.h"
//#include "Popup_Lobby_EnterRoom_Faill.h"
//#include "Popup_Game_GameOver.h"
//#include "Popup_Game_Rank.h"
//#include "Popup_Game_WaitUser.h"

PopupMgr::PopupMgr(void)
{
	//< 팝업 초기화
	nowPopup = NULL;

	//< 현재 팝업 플래그
	nowPopupFlag = POPUP_NONE;
	//< 선택 팝업 플래그
	oldPopupFlag = POPUP_NONE;
	m_checkPopup_ON = false;
}


PopupMgr::~PopupMgr(void)
{
	//< 모든 팝업 지우기
	if( nowPopup != NULL )
	{
		deletePopup();
	}
}

//< 팝업 초기화
void PopupMgr::initPopup( void )
{
	//< 팝업 초기화
	if( nowPopup != NULL )
	{
		//nowPopup->init();
	}
}

//< 팝업 업뎃
void PopupMgr::updatePopup( void )
{
	//< 팝업 업데이트
	if( nowPopup != NULL )
	{
		//nowPopup->update( m_mousePos );
	}
}

//< 팝업 랜더
void PopupMgr::renderPopup( HDC hdc )
{
	//< 팝업 랜더
	if( nowPopup != NULL )
	{
		//nowPopup->render( hdc );
	}
}

//< 팝업 바꾸기
bool PopupMgr::changePopup( unsigned int PopupID )
{
	//< 팝업 상태 받기
	nowPopupFlag = PopupID;

	if( nowPopupFlag != oldPopupFlag )
	{
		//< 팝업창 상태
		switch( PopupID )
		{
		case POPUP_NONE :
			{
				//< 팝업 선택전
				oldPopupFlag = POPUP_NONE;
				m_checkPopup_ON = false;
			}
			break;
		case POPUP_NO_POPUP :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_NO_POPUP;
				m_checkPopup_ON = false;
				return false;
			}
			break;
		case POPUP_NO_POPUP_GET_MAKE_ROOM :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_NO_POPUP_GET_MAKE_ROOM;
				m_checkPopup_ON = true;
				return false;
			}
			break;
		case POPUP_LOGIN_LOGIN_OVERLABID :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Login_OverlabFaill;
				//nowPopup->inGameInfo( STATE
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_LOGIN_OVERLABID;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_LOGIN_DISCORD_PASS :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Fail_Discord_Pass;
				//nowPopup->inGameInfo( STATE
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_LOGIN_DISCORD_PASS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_LOGIN_FAILL:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Login_Fail;
				//nowPopup->inGameInfo( STATE
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_LOGIN_FAILL;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_LOGIN_SUCCESS:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Login_Success;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_LOGIN_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_EXIT:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Exit;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_EXIT;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Join;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_JOIN;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_SUCCESS:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Join_Success;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_JOIN_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAILL:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Join_Faill;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_JOIN_FAILL;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAIL_NONE:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Fail_None;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_JOIN_FAIL_NONE;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Fail_Overlap_Id;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Login_Fail_Discord_Pass;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_TITLE_RANK :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Title_Rank;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_TITLE_RANK;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_TITLE_COLLECTION :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Title_Collection;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_TITLE_COLLECTION;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_TITLE_LOGOUT :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Back;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_TITLE_LOGOUT;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_FRIENDLIST:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_FriendList;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_FRIENDLIST;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_MAKEROOM_OPEN :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_MakeRoom_Open;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_MAKEROOM_OPEN;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_MAKEROOM_CLOSE :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_MakeRoom_close;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_MAKEROOM_CLOSE;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_MAKEROOM_SUCCESS :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_MakeRoom_Success;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_MAKEROOM_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_CLOSE:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_EnterRoom_close;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_CLOSE;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_OPEN :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_EnterRoom_open;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_OPEN;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_SUCCESS:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_EnterRoom_Success;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_FAILL:
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Lobby_EnterRoom_Faill;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_FAILL;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_GAME_WAIT_USER :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Game_WaitUser;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_GAME_WAIT_USER;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_GAME_OVER :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Game_GameOver;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_GAME_OVER;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_GAME_RANK :
			{
				//< 팝업 지우기
				deletePopup( );
				//< 할당
				//nowPopup = new Popup_Game_Rank;
				//< 팝업 상태 갱신
				oldPopupFlag = POPUP_GAME_RANK;
				m_checkPopup_ON = true;
			}
			break;
		}
		//< 초기화
		//nowPopup->init();
	}
	return true;
}
//< 팝업 지우기
void PopupMgr::deletePopup( void )
{
	//< 팝업 지우기
	if( nowPopup != NULL )
	{
		//nowPopup->release();
	}
	//SAFE_DELETE( nowPopup );
}

//< 팝업 이벤트 처리
LRESULT PopupMgr::PopupProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch(msg)
	{
	//< 마우스 받기
	case WM_MOUSEMOVE:
		{
			m_mousePos.x = LOWORD(lparam);
			m_mousePos.y = HIWORD(lparam);
		}
		break;
	}

	//< 팝업창이 켜져있으면 실행
	if( nowPopup != NULL )
	{
		//return nowPopup->StateProc( wnd, msg, wparam, lparam );
	}
	//< 아니면 리턴
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}


//< 눌린 버튼으로 팝업 할당
int PopupMgr::buttonStatePopup( void )
{
	if( nowPopup != NULL )
	{
        int buttonState = 0;// = nowPopup->getNextScene();
		//< 선택한 팝업이 방만들기라면 2번 넘기기
		if( buttonState == POPUP_NO_POPUP_GET_MAKE_ROOM )
		{
			return POPUP_NO_POPUP_GET_MAKE_ROOM; //< 2번 플래그
		}

		//< 선택한 팝업으로 할당
		if( buttonState != POPUP_NONE )
		{
			//< 팝업 새로 할당
			changePopup( buttonState );
		}
		//< 할당
		return true;
	}
	//< 없음
	return false;
}