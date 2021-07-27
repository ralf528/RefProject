#include "stdafx.h"
#include "Popup_Lobby_EnterRoom_open.h"

#include "../../ImageNode.h"
#include "../../PopupBox.h"
#include "../../CheckBox.h"
#include "../../MY_FontMgr.h"
#include "../SceneChoiceChar.h"

Popup_Lobby_EnterRoom_open::Popup_Lobby_EnterRoom_open(void)
{
	//< ����� �̹���
	alpaImage = new ImageNode(0);
	//< �˾�â �̹���
	popupImage = new PopupBox;

	//< �Է� ��Ʈ �̹���
	inputInfo_ID = new ButtonClass;
	inputInfo_PASS = new ButtonClass;
	//< �Է�ĭ
	m_inputID_Board = new ButtonClass;
	m_inputPass_Board = new ButtonClass;

	//< ��������
	playUser = new MY_Font; 

	//< ���콺 ������
	mousePos.x =0;
	mousePos.y =0;

	//< ��ư
	button_JOINROOM = new ButtonClass;
	button_CANCEL = new ButtonClass;

	//< ���Ի���
	breakInto = true;

	//< ��ư ���� �ʱ�ȭ
	button_STATE = POPUP_NONE;
}


Popup_Lobby_EnterRoom_open::~Popup_Lobby_EnterRoom_open(void)
{
	release();
}

//< �ʱ�ȭ
void Popup_Lobby_EnterRoom_open::init( void )
{
	//< ���� ������ �޾ƿ���
    int getChoiceNumber = 0;// GAME_DATA->getChoiceNumber();

	//< ������ 
	//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(getChoiceNumber);
    ROOM_INFO newRoom;
    memset(&newRoom, 0, sizeof(newRoom));

	//< ���� �̹��� �ε�
	loadImage();

	//< ����
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< �˾� �̹��� ���� �ޱ�
	POINT tempPoint = popupImage->getCenter();
	//---------------------------------------------------------------------------
	//< ���� ���� �ޱ�
	RECT tempRect = popupImage->getRect();
	tempRect.top -= 80;
	tempRect.bottom -= 80;
	TCHAR arr[256];

	//< �����̸�, ���� �÷������� ������

	if(newRoom.m_isCharSelect == true)
	{
		swprintf_s( arr, L"%s �� ��  %d/2�� (ĳ���� ������)", newRoom.m_userName[0],newRoom.m_userCount );
	}
	else
	{
		swprintf_s( arr, L"%s �� ��  %d/2���� (������)", newRoom.m_userName[0],newRoom.m_userCount );
	}

	//< ���� ���� �޾ƿ���
	playUser->LoadText( arr, tempRect, L"HY������M", 40, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< ����ǥ�� ���̸�
	inputInfo_ID->init(L"Data/Resource/Image/board_join.bmp",
		L"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_ID->setRectPos( tempPoint.x -150, tempPoint.y - 66 +70, ALIGN_CENTER );
	//< ����ǥ�� ��й�ȣ
	inputInfo_PASS->init(L"Data/Resource/Image/board_join.bmp",
		L"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_PASS->setRectPos( tempPoint.x -150, tempPoint.y - 2 +70, ALIGN_CENTER );

	//< ����ǥ�� ���̸�
	inputInfo_ID->loadFont(L"���̸�",
		inputInfo_ID->getRect(), 
		L"HY������M", 30, ALIGN_CENTER, 255,255,255 );
	//< ����ǥ�� ��й�ȣ
	inputInfo_PASS->loadFont(L"��й�ȣ",
		inputInfo_PASS->getRect(), 
		L"HY������M", 30, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< �Է��� ID
	m_inputID_Board->init(L"Data/Resource/Image/JoinRoom.bmp",
		L"Data/Resource/Image/JoinRoom.bmp",300, 60 );
	m_inputID_Board->setRectPos( tempPoint.x +110, tempPoint.y - 66 +70, ALIGN_CENTER );

	//< ���� ����
	memset( arr, 0, sizeof( char )*256 );
	memmove_s( arr, 256, newRoom.m_roomName , lstrlen( newRoom.m_roomName ) );

	//< ���� �ε�
	m_inputID_Board->loadFont( arr,
		m_inputID_Board->getRect(),
		L"HY������M", 30, ALIGN_CENTER, 255,255,255 );

	//< �Է��� PASS
	m_inputPass_Board->init(L"Data/Resource/Image/button_INPUT_ROCK.bmp",
		L"Data/Resource/Image/button_INPUT_ROCK.bmp",300, 60 );
	m_inputPass_Board->setRectPos( tempPoint.x+110, tempPoint.y - 2 +70, ALIGN_CENTER );

	//---------------------------------------------------------------------------
	//< ��ư �����ϱ�
	button_JOINROOM->init(L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_JOINROOM->loadFont(L"�����ϱ�", button_JOINROOM->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_JOINROOM->setRectPos( tempPoint.x+160, tempPoint.y+130 +20, ALIGN_CENTER );

	//< ��ư ���
	button_CANCEL->init(L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_CANCEL->loadFont(L"���", button_CANCEL->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CANCEL->setRectPos( tempPoint.x-150, tempPoint.y+130 +20, ALIGN_CENTER );
	//---------------------------------------------------------------------------
}

//< ������Ʈ
void Popup_Lobby_EnterRoom_open::update( POINT mousePos )
{
	//< ��ư 
	button_JOINROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_JOINROOM->getRect() ));
	button_JOINROOM->update();
	button_CANCEL->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CANCEL->getRect() ));
	button_CANCEL->update();

	//< �Է��� ��ġ �ޱ�
	m_inputPass_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_inputPass_Board->getRect() ));
	m_inputPass_Board->update();

	//< ��Ŷ�� ��� ���� �ʴٸ�
	//if(true != TCPIP_CLIENT->emptyQueue())
	//{
	//	unsigned short type = TCPIP_CLIENT->getPacketType();
	//	if(type == SC_GAME_JOIN_YES) //> �� ���� ����
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
	//		//< ���� ���� ����

	//		TCPIP_CLIENT->popPacket();
	//		POPUP_MGR->changePopup(POPUP_LOBBY_ENTER_ROOM_FAILL);
	//		return;
	//	}
	//}

	//< ��ư �����-------------------------------------------------
	if( button_JOINROOM->getPlayButtonAni() == true )
	{
		//< ���� ������
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
	//< ��ư cancel
	if( button_CANCEL->getPlayButtonAni() == true )
	{
		//< ���� ������
		button_CANCEL->inCheckMouseOn( false );
		button_CANCEL->inClickButton( false );
		button_CANCEL->inPlayButtonAni( false );
		//< Ŭ�� ����
		button_STATE = POPUP_NO_POPUP;
	}
}

//< ����
void Popup_Lobby_EnterRoom_open::render( HDC hdc )
{
	//< ���� �̹��� ����
	alpaImage->render( hdc, 0,0  );
	//< �˾�â ����
	popupImage->render( hdc );

	if( popupImage->getPlayPopupBoxAni() == true )
	{
		//--------------------------------------------------------
		//< �Է� ��Ʈ �̹���
		inputInfo_ID->render( hdc );
		inputInfo_PASS->render( hdc );
		//--------------------------------------------------------
		//< �Էº���
		m_inputID_Board->render( hdc );
		m_inputPass_Board->render( hdc );
		//--------------------------------------------------------
		//< ��ư
		button_JOINROOM->render( hdc );
		button_CANCEL->render( hdc );
		//--------------------------------------------------------
		//< ���� ���� ���
		playUser->OutputText( hdc );
	}
}

//< �����
void Popup_Lobby_EnterRoom_open::release( void )
{
	//< �ҷ��� �̹��� �����
	if( alpaImage != NULL ){ alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( popupImage != NULL ){ popupImage->release(); }
	SAFE_DELETE( popupImage );
	//< ��ư
	if( button_JOINROOM != NULL ){ button_JOINROOM->release(); }
	SAFE_DELETE( button_JOINROOM );
	if( button_CANCEL != NULL ){ button_CANCEL->release(); }
	SAFE_DELETE( button_CANCEL );
	//< �Է� ��Ʈ �̹���
	if( inputInfo_ID != NULL ){ inputInfo_ID->release(); }
	SAFE_DELETE( inputInfo_ID );
	if( inputInfo_PASS != NULL ){ inputInfo_PASS->release(); }
	SAFE_DELETE( inputInfo_PASS );
	//< �Է�ĭ
	if( m_inputID_Board != NULL ){ m_inputID_Board->release(); }
	SAFE_DELETE( m_inputID_Board );
	if( m_inputPass_Board != NULL ){ m_inputPass_Board->release(); }
	SAFE_DELETE( m_inputPass_Board );
	SAFE_DELETE( playUser );
}

//< �̹��� �ҷ�����
void Popup_Lobby_EnterRoom_open::loadImage( void )
{
	//< ���� �̹���
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load(L"Data/Resource/Image/Alpa_background.bmp",
		0, 0, RM_TRANS );
	//< �˾�â
	popupImage->init(L"Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< �̺�Ʈó��
LRESULT	Popup_Lobby_EnterRoom_open::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
		//< ���콺 ��ġ �ޱ�
	case WM_MOUSEMOVE :
		{
			mousePos.x = LOWORD( lparam );
			mousePos.y = HIWORD( lparam );
		}
		break;
	case WM_LBUTTONUP :
		{
			//< ��ư ����-------------------------------------------------
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_JOINROOM->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_JOINROOM->inClickButton( true );
			}
			//< ��ư cancel
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_CANCEL->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_CANCEL->inClickButton( true );
			}
		}
		break;
		//< ���� �Է�
	case WM_CHAR :
		{
		}
		break;
		//< Ű���� �Է¹ޱ�
	case WM_KEYDOWN :
		switch(wparam)
		{
			//< ����Ű �Է�
		case VK_RETURN:
			{		
				button_JOINROOM->inClickButton( true );
			}
			break;
			//< �齺���̽� �Է�
		case VK_BACK :
			{
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< ������ �ޱ�
int Popup_Lobby_EnterRoom_open::getNextScene( void )
{
    if (button_STATE == POPUP_NO_POPUP_GET_MAKE_ROOM)
    {
        return POPUP_NO_POPUP_GET_MAKE_ROOM;
    }

	//< ��ư�� ���������� ����
	if( button_STATE != POPUP_NONE )
	{
		if( button_STATE != POPUP_NO_POPUP &&
			button_STATE != POPUP_LOBBY_MAKEROOM_OPEN &&
			button_STATE != POPUP_LOBBY_MAKEROOM_CLOSE )
		{
			//< �ӽ� ����
            string tempID;// = inputRoomName->getString();
            string tempPA;// = inputPass->getString();

			//< �Է� ���� Ȯ��
			if( tempID.size() <= 0 ||
				tempPA.size() <= 0 )
			{
				//< �Է� ���� ����
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

				//	//< ������ ���� ���� ����
				//	GAME_DATA->setMyRoomName(tempID.c_str());
				//	GAME_DATA->setMyRoomOption(breakInto);
				//}

				//unsigned short type = TCPIP_CLIENT->getPacketType();
				//if(type == SC_GAME_CREATE_YES)
				{
					//< �游��� ���� POPUP_NO_POPUP_GET_MAKE_ROOM
					button_STATE = POPUP_LOBBY_MAKEROOM_SUCCESS;

					//TCPIP_CLIENT->init();
				}
				//else if(type == SC_GAME_CREATE_NO)
				{
					//< ����� ���� ���
					//button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;

					//TCPIP_CLIENT->init();
				}
			}
		}
	}

	return button_STATE; 
}
