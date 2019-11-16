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
	//< �˾� �ʱ�ȭ
	nowPopup = NULL;

	//< ���� �˾� �÷���
	nowPopupFlag = POPUP_NONE;
	//< ���� �˾� �÷���
	oldPopupFlag = POPUP_NONE;
	m_checkPopup_ON = false;
}


PopupMgr::~PopupMgr(void)
{
	//< ��� �˾� �����
	if( nowPopup != NULL )
	{
		deletePopup();
	}
}

//< �˾� �ʱ�ȭ
void PopupMgr::initPopup( void )
{
	//< �˾� �ʱ�ȭ
	if( nowPopup != NULL )
	{
		//nowPopup->init();
	}
}

//< �˾� ����
void PopupMgr::updatePopup( void )
{
	//< �˾� ������Ʈ
	if( nowPopup != NULL )
	{
		//nowPopup->update( m_mousePos );
	}
}

//< �˾� ����
void PopupMgr::renderPopup( HDC hdc )
{
	//< �˾� ����
	if( nowPopup != NULL )
	{
		//nowPopup->render( hdc );
	}
}

//< �˾� �ٲٱ�
bool PopupMgr::changePopup( unsigned int PopupID )
{
	//< �˾� ���� �ޱ�
	nowPopupFlag = PopupID;

	if( nowPopupFlag != oldPopupFlag )
	{
		//< �˾�â ����
		switch( PopupID )
		{
		case POPUP_NONE :
			{
				//< �˾� ������
				oldPopupFlag = POPUP_NONE;
				m_checkPopup_ON = false;
			}
			break;
		case POPUP_NO_POPUP :
			{
				//< �˾� �����
				deletePopup( );
				//< �˾� ���� ����
				oldPopupFlag = POPUP_NO_POPUP;
				m_checkPopup_ON = false;
				return false;
			}
			break;
		case POPUP_NO_POPUP_GET_MAKE_ROOM :
			{
				//< �˾� �����
				deletePopup( );
				//< �˾� ���� ����
				oldPopupFlag = POPUP_NO_POPUP_GET_MAKE_ROOM;
				m_checkPopup_ON = true;
				return false;
			}
			break;
		case POPUP_LOGIN_LOGIN_OVERLABID :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Login_OverlabFaill;
				//nowPopup->inGameInfo( STATE
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_LOGIN_OVERLABID;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_LOGIN_DISCORD_PASS :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Fail_Discord_Pass;
				//nowPopup->inGameInfo( STATE
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_LOGIN_DISCORD_PASS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_LOGIN_FAILL:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Login_Fail;
				//nowPopup->inGameInfo( STATE
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_LOGIN_FAILL;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_LOGIN_SUCCESS:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Login_Success;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_LOGIN_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_EXIT:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Exit;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_EXIT;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Join;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_JOIN;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_SUCCESS:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Join_Success;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_JOIN_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAILL:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Join_Faill;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_JOIN_FAILL;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAIL_NONE:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Fail_None;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_JOIN_FAIL_NONE;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Fail_Overlap_Id;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Login_Fail_Discord_Pass;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_TITLE_RANK :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Title_Rank;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_TITLE_RANK;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_TITLE_COLLECTION :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Title_Collection;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_TITLE_COLLECTION;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_TITLE_LOGOUT :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Back;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_TITLE_LOGOUT;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_FRIENDLIST:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_FriendList;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_FRIENDLIST;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_MAKEROOM_OPEN :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_MakeRoom_Open;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_MAKEROOM_OPEN;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_MAKEROOM_CLOSE :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_MakeRoom_close;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_MAKEROOM_CLOSE;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_MAKEROOM_SUCCESS :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_MakeRoom_Success;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_MAKEROOM_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_CLOSE:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_EnterRoom_close;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_CLOSE;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_OPEN :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_EnterRoom_open;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_OPEN;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_SUCCESS:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_EnterRoom_Success;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_SUCCESS;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_LOBBY_ENTER_ROOM_FAILL:
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Lobby_EnterRoom_Faill;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_LOBBY_ENTER_ROOM_FAILL;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_GAME_WAIT_USER :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Game_WaitUser;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_GAME_WAIT_USER;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_GAME_OVER :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Game_GameOver;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_GAME_OVER;
				m_checkPopup_ON = true;
			}
			break;
		case POPUP_GAME_RANK :
			{
				//< �˾� �����
				deletePopup( );
				//< �Ҵ�
				//nowPopup = new Popup_Game_Rank;
				//< �˾� ���� ����
				oldPopupFlag = POPUP_GAME_RANK;
				m_checkPopup_ON = true;
			}
			break;
		}
		//< �ʱ�ȭ
		//nowPopup->init();
	}
	return true;
}
//< �˾� �����
void PopupMgr::deletePopup( void )
{
	//< �˾� �����
	if( nowPopup != NULL )
	{
		//nowPopup->release();
	}
	//SAFE_DELETE( nowPopup );
}

//< �˾� �̺�Ʈ ó��
LRESULT PopupMgr::PopupProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch(msg)
	{
	//< ���콺 �ޱ�
	case WM_MOUSEMOVE:
		{
			m_mousePos.x = LOWORD(lparam);
			m_mousePos.y = HIWORD(lparam);
		}
		break;
	}

	//< �˾�â�� ���������� ����
	if( nowPopup != NULL )
	{
		//return nowPopup->StateProc( wnd, msg, wparam, lparam );
	}
	//< �ƴϸ� ����
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}


//< ���� ��ư���� �˾� �Ҵ�
int PopupMgr::buttonStatePopup( void )
{
	if( nowPopup != NULL )
	{
        int buttonState = 0;// = nowPopup->getNextScene();
		//< ������ �˾��� �游����� 2�� �ѱ��
		if( buttonState == POPUP_NO_POPUP_GET_MAKE_ROOM )
		{
			return POPUP_NO_POPUP_GET_MAKE_ROOM; //< 2�� �÷���
		}

		//< ������ �˾����� �Ҵ�
		if( buttonState != POPUP_NONE )
		{
			//< �˾� ���� �Ҵ�
			changePopup( buttonState );
		}
		//< �Ҵ�
		return true;
	}
	//< ����
	return false;
}