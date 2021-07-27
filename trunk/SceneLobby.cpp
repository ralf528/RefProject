#include "stdafx.h"

#include "ImageNode.h"
#include "MY_FontMgr.h"

#include "PopupMgr.h"

#include "SceneLobby.h"
//#include "SceneLogin.h"
#include "Scene/SceneChoiceChar.h"
//#include "SceneTitle.h"
//#include "ScenePlayGame.h"
//
#include "PopupBox.h"
#include "ButtonClass.h"
#include "RoomClass.h"
//#include "ChattingBox.h"

SceneLobby::SceneLobby(void)
{
	//< ��Ʈ �Ҵ�
	m_font = new MY_Font;

	//< ��� �̹���
	m_image = new PopupBox;

	//< ��ư �Ҵ�
	button_REFRESH = new ButtonClass;
	button_FRIEND_LIST = new ButtonClass;
	button_MAKE_ROOM = new ButtonClass;
	button_EXIT = new ButtonClass;

	//< �˾�â üũ

	//< ��
	room = new RoomClass;

	//< ä��â
	//chatting = new ChattingBox;

	//< ������
	roomCountInfo = 0;
	//���콺 üũ
	checkMosFRIENDLIST = true;
	checkMosMAKEROOM = true;
	checkMosEXIT = true;
}

SceneLobby::~SceneLobby(void)
{
	//< �����
	release();		
}


//< �ʱ�ȭ
bool SceneLobby::init( void ) 
{
	//< ����̹���
	//< ����̹���
	m_image->init(L"Data/Resource/Image/background_Login3.bmp",WINSIZE_X,WINSIZE_Y );
	m_image->setRectPos( 0,0, ALIGN_LEFT_TOP );
	//----------------------------------------------------------------------------
	//< ���ΰ�ħ button_REFRESH
	button_REFRESH->init(
		L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_REFRESH->loadFont( L"���ΰ�ħ", button_REFRESH->getRect(), 
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	//< ��ư �ʱ�ȭ
	button_FRIEND_LIST->init(
		L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_FRIEND_LIST->loadFont( L"ģ�����", button_FRIEND_LIST->getRect(), 
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	//< �游���
	button_MAKE_ROOM->init(
		L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_MAKE_ROOM->loadFont( L"�游���", button_MAKE_ROOM->getRect(), 
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	//< ������
	button_EXIT->init(
		L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",200, 50);
	button_EXIT->loadFont(L"������", button_EXIT->getRect(), 
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );

	//ALIGN_CENTER,				//< �߰�����
	button_REFRESH->setRectPos		( WINSIZE_X/20 *17, WINSIZE_Y/20 *14, ALIGN_CENTER );
	//button_FRIEND_LIST->setRectPos	( WINSIZE_X/20 *17, WINSIZE_Y/20 *14, ALIGN_CENTER );
	button_MAKE_ROOM->setRectPos	( WINSIZE_X/20 *17, WINSIZE_Y/20 *16, ALIGN_CENTER );
	button_EXIT->setRectPos			( WINSIZE_X/20 *17, WINSIZE_Y/20 *18, ALIGN_CENTER );
	//---------------------------------------------------------------------------------
	//< ��
	room->init();
	////< ä��â
	//chatting->init();
	////-------------------------------------------------------------------------------
	////�κ� ���� ���
	//SOUND_MGR->soundPlay(SOUND_LOBBY);

	return true;
}
//< ������Ʈ
void SceneLobby::update(float fDeltaTime)
{
    //if (true != TCPIP_CLIENT->emptyQueue())
    {
        //unsigned short type = TCPIP_CLIENT->getPacketType();
        //if (type == SC_ROOM_ALL_DATA)
        {
            /*PACKET packet;
            TCPIP_CLIENT->getPacket(packet);

            GAME_DATA->deleteAllRoomInfo();*/
            //for (int i = 0; i < packet.m_roomMenuUpdate.m_roomCnt; i++)
            if (false)
            {
                //GAME_DATA->addRoomInfo(packet.m_roomMenuUpdate.room[i]);
                room->makeRoom(1);
            }

           // TCPIP_CLIENT->popPacket();
        }
        /*else if (type == SC_LOBBY_ID_REQ)
        {
            PACKET packet;
            packet.m_loginReq.m_length = sizeof(LOGIN_REQ);
            packet.m_loginReq.m_type = CS_LOGIN_LOBBY;
            strcpy_s(packet.m_loginReq.m_id, GAME_DATA->getUserId());
            TCPIP_CLIENT->sendPacket(packet);
            TCPIP_CLIENT->popPacket();
        }*/
    }

	//< �˾��� ���� �ʾҴٸ� �������� �ʱ�
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< ��ư ��ġ �ޱ�
		button_REFRESH->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_REFRESH->getRect() ));
		button_REFRESH->update();
		button_FRIEND_LIST->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_FRIEND_LIST->getRect() ));
		button_FRIEND_LIST->update();
		button_MAKE_ROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_MAKE_ROOM->getRect() ));
		button_MAKE_ROOM->update();
		button_EXIT->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_EXIT->getRect() ));
		button_EXIT->update();

		//< ��
		room->update( mousePos );
		////< ä��â 
		//chatting->update( mousePos );
	}

	//< �˾�â�� �������� ������ ����
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< ���ΰ�ħ ��ư-------------------------------------------------
		if( button_REFRESH->getClickButton() == true  &&
			button_REFRESH->getPlayButtonAni() == true )
		{
			//< �ִϸ��̼� ������
			button_REFRESH->inPlayButtonAni( false );
			//< Ŭ�� ������
			button_REFRESH->inClickButton( false );
		}
		//< ģ����� ��ư-------------------------------------------------
		if( button_FRIEND_LIST->getClickButton() == true  &&
			button_FRIEND_LIST->getPlayButtonAni() == true )
		{
			//< �ִϸ��̼� ������
			button_FRIEND_LIST->inPlayButtonAni( false );
			//< Ŭ�� ������
			button_FRIEND_LIST->inClickButton( false );

			//< �游��� �˾�â
			//POPUP_MGR->changePopup( POPUP_LOBBY_FRIENDLIST );
			
			//< �ӽ� ������ �˾�
			POPUP_MGR->changePopup( POPUP_LOBBY_ENTER_ROOM_OPEN );
			//< �ӽ� ���ӿ��� �˾�
			//POPUP_MGR->changePopup( POPUP_GAME_OVER );

			//< �ʱ�ȭ
			POPUP_MGR->initPopup();

			//< �˾�â Ű��
		}

		//< �游��� ��ư-------------------------------------------------
		if( button_MAKE_ROOM->getClickButton() == true  &&
			button_MAKE_ROOM->getPlayButtonAni() == true )
		{
			//< �ִϸ��̼� ������
			button_MAKE_ROOM->inPlayButtonAni( false );
			//< Ŭ�� ������
			button_MAKE_ROOM->inClickButton( false );

			//< �游��� �˾�â
			//POPUP_MGR->changePopup( POPUP_LOBBY_MAKEROOM_OPEN );
            {
                room->makeRoom(1);
            }

			//< �ʱ�ȭ
			//POPUP_MGR->initPopup();

			//< �˾�â Ű��
		}

		//< ������ ��ư-------------------------------------------------
		//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
		if( button_EXIT->getClickButton() == true &&
			button_EXIT->getPlayButtonAni() == true )
		{
			//STATE_MGR->addState<SceneTitle>(SCENE_TITLE);
			//STATE_MGR->changeState( SCENE_TITLE );
			////< ����������
			//STATE_MGR->deleteState( SCENE_LOBBY );
			return;
		}
	}
	//< �˾�â�� ������ ����
	else
	{
		//< �˾� ����
		POPUP_MGR->updatePopup();

		//< 2�� �˾�( �˾����� ������ư �Ǻ� )
		int tempFlag = POPUP_MGR->buttonStatePopup();

		//< �Ҵ��� ���� �ʾҴٸ�
		if( tempFlag == false )
		{
			//< �˾�â ����
		}

		//< �游��� ��ư�� �����ٸ�
		if( tempFlag == POPUP_NO_POPUP_GET_MAKE_ROOM )
		{
			//< �˾�â ����
			STATE_MGR->addState<SceneChoiceChar>(SCENE_SELECT);
			STATE_MGR->changeState( SCENE_SELECT );
			//< ����������
			STATE_MGR->deleteState( SCENE_LOBBY );
		}
		//< ��ư������Ʈ ����
		POPUP_MGR->inButtonState();
	}
	/*if(SOUND_MGR->isPlaySound(SOUND_LOBBY)==false)
	{
	SOUND_MGR->soundPlay(SOUND_LOBBY);
	}*/
}

//< ����
void SceneLobby::render( HDC hdc ) 
{
	//< ����̹���
	m_image->renderNone( hdc );
	//�ӽ�---------------------------------------------------------
#ifdef _DEBUG
	if( NULL != hdc )
	{
		m_font->OutputText( hdc, 
			L"�κ� ��",
			0,0,
			L"HY��������M",
			65,
			0,0,0 );
	}
	//< ���콺�� �ö� �ִ� ���¸�
	if( button_FRIEND_LIST->getCheckMouseOn() == true ||
		button_MAKE_ROOM->getCheckMouseOn() == true ||
		button_EXIT->getCheckMouseOn() == true )
	{
		TextOut( hdc, 200,0, L"�浹",4);
	}
	else
	{
		TextOut( hdc, 200,0, L"���浹",6);
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
	//< ��
	room->render( hdc );
	////< ä��â
	//chatting->render( hdc );
	//-------------------------------------------------------------
	//< ��ư ����
	button_REFRESH->render( hdc );
	//button_FRIEND_LIST->render( hdc );
	button_MAKE_ROOM->render( hdc );
	button_EXIT->render( hdc );

	//< �˾�â�� ������ ����
	if( POPUP_MGR->getCheckPopup_ON() == true )
	{
		//< �˾�â ����
		POPUP_MGR->renderPopup( hdc );
	}
}
//< ����
void SceneLobby::release( void ) 
{
	//< ��Ʈ �����
	SAFE_DELETE( m_font );

	//< ��� �̹���
	if( m_image != NULL ){ m_image->release(); }
	SAFE_DELETE( m_image );

	//< ��ư �����
	if( button_REFRESH != NULL ){ button_REFRESH->release(); }
	SAFE_DELETE( button_REFRESH );
	if( button_FRIEND_LIST != NULL ){ button_FRIEND_LIST->release(); }
	SAFE_DELETE( button_FRIEND_LIST );
	if( button_MAKE_ROOM != NULL ){ button_MAKE_ROOM->release(); }
	SAFE_DELETE( button_MAKE_ROOM );
	if( button_EXIT != NULL ){ button_EXIT->release(); }
	SAFE_DELETE( button_EXIT );

	//< �� �����
	if( room != NULL ){ room->release(); }
	SAFE_DELETE( room );
	////< ä��â �����
	//if( chatting != NULL ) { chatting->release(); }
	//SAFE_DELETE( chatting );

	
}

//< �̺�Ʈó��
LRESULT	SceneLobby::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	//< �˾�â�� �������� ������ ����
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		switch( msg )
		{
		case WM_LBUTTONUP :
			{
				//< ���ΰ�ħ ��ư-------------------------------------------------
				if( button_REFRESH->getCheckMouseOn() == true )
				{
					button_REFRESH->inClickButton( true );
					
					break;
				}
				//< ģ����� ��ư-------------------------------------------------
				if( button_FRIEND_LIST->getCheckMouseOn() == true )
				{
					button_FRIEND_LIST->inClickButton( true );
					
					break;
				}
				//< �游��� ��ư-------------------------------------------------
				if( button_MAKE_ROOM->getCheckMouseOn() == true )
				{
					button_MAKE_ROOM->inClickButton( true );
					
					break;
				}
				//< ������ ��ư-------------------------------------------------
				if( button_EXIT->getCheckMouseOn() == true )
				{
					button_EXIT->inClickButton( true );
					
					break;
				}
			}
			break;
			//< ���콺 ��ġ �ޱ�
		case WM_MOUSEMOVE :
			{
				mousePos.x = LOWORD( lparam );
				mousePos.y = HIWORD( lparam );
			}
			break;
		}
		
	}
	//< �˾�â�� ���������� �˾� ���ν��� ����
	else
	{
		//< ���ν��� �ѱ��
		return POPUP_MGR->PopupProc( wnd ,msg,wparam,lparam );
	}

	if( wparam != NULL ||
		lparam != NULL )
	{
		//< �游��� ���ν���
		room->StateProc( wnd, msg, wparam, lparam );
		////< ä��â ���ν���
		//return chatting->StateProc( wnd, msg, wparam, lparam );
	}

    // �ӽ�
    return POPUP_MGR->PopupProc(wnd, msg, wparam, lparam);
 }