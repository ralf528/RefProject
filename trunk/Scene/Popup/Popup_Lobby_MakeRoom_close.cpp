#include "stdafx.h"
#include "Popup_Lobby_MakeRoom_close.h"

#include "ImageNode.h"
#include "PopupBox.h"
#include "CheckBox.h"

Popup_Lobby_MakeRoom_close::Popup_Lobby_MakeRoom_close(void)
{
	//< ����� �̹���
	alpaImage = new ImageNode(0);
	//< �˾�â �̹���
	popupImage = new PopupBox;

	//< �Է� ��Ʈ �̹���
	inputInfo_ID = new ButtonClass;
	inputInfo_PASS = new ButtonClass;
	inputInfo_REPASS = new ButtonClass;
	//< �Է�ĭ
	m_inputID_Board = new ButtonClass;
	m_inputPass_Board = new ButtonClass;

	//< �游���
	inputRoomName = new InputString;
	inputPass = new InputString;

	//< ���콺 ������
	mousePos.x =0;
	mousePos.y =0;

	//< ��ư
	button_MAKEROOM = new ButtonClass;
	button_CANCEL = new ButtonClass;
	//< ��ư
	button_OPEN = new CheckBox;
	button_CLOSE = new CheckBox;
	//< üũ�ڽ�
	checkBox_OK = new CheckBox;
	checkBox_NO = new CheckBox;

	//< ���Ի���
	breakInto = true;

	//< ��ư ���� �ʱ�ȭ
	button_STATE = POPUP_NONE;
}

Popup_Lobby_MakeRoom_close::~Popup_Lobby_MakeRoom_close(void)
{
	release();
}

//< �ʱ�ȭ
void Popup_Lobby_MakeRoom_close::init( void )
{
	//< ���� �̹��� �ε�
	loadImage();

	//< ����
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< �˾� �̹��� ���� �ޱ�
	POINT tempPoint = popupImage->getCenter();
	//----------------------------------------------------------------------------
	//< ����ǥ�� ���̸�
	inputInfo_ID->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_ID->setRectPos( tempPoint.x -150, tempPoint.y - 66 +30, ALIGN_CENTER );
	//< ����ǥ�� ��й�ȣ
	inputInfo_PASS->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_PASS->setRectPos( tempPoint.x -150, tempPoint.y - 2 +30, ALIGN_CENTER );
	//< ����ǥ�� �������
	inputInfo_REPASS->init( "Data/Resource/Image/board_join.bmp",
		"Data/Resource/Image/board_join.bmp",200, 60 );
	inputInfo_REPASS->setRectPos( tempPoint.x -150, tempPoint.y + 62 +30, ALIGN_CENTER );

	//< ����ǥ�� ���̸�
	inputInfo_ID->loadFont( "���̸�",
		inputInfo_ID->getRect(), 
		"HY������M", 30, ALIGN_CENTER, 255,255,255 );
	//< ����ǥ�� ��й�ȣ
	inputInfo_PASS->loadFont( "��й�ȣ",
		inputInfo_PASS->getRect(), 
		"HY������M", 30, ALIGN_CENTER, 255,255,255 );
	//< ����ǥ�� �������
	inputInfo_REPASS->loadFont( "����",
		inputInfo_REPASS->getRect(), 
		"HY������M", 30, ALIGN_CENTER, 255,255,255 );
	//----------------------------------------------------------------------------
	//< �Է��� ID
	m_inputID_Board->init( "Data/Resource/Image/button_INPUT.bmp",
		"Data/Resource/Image/button_INPUT_02.bmp",300, 60 );
	m_inputID_Board->setRectPos( tempPoint.x +110, tempPoint.y - 66 +30, ALIGN_CENTER );
	//< �Է��� PASS
	m_inputPass_Board->init( "Data/Resource/Image/button_INPUT.bmp",
		"Data/Resource/Image/button_INPUT_02.bmp",300, 60 );
	m_inputPass_Board->setRectPos( tempPoint.x+110, tempPoint.y - 2 +30, ALIGN_CENTER );

	//< �Է� ���̸�
	inputRoomName->init( m_inputID_Board->getRect(), 
		"HY������M", 30, ALIGN_CENTER, 0,0,0 );
	//< �Է� Pass
	inputPass->init( m_inputPass_Board->getRect(), 
		"HY������M", 30, ALIGN_CENTER, 0,0,0 );
	//---------------------------------------------------------------------------
	//< ��ư MAKEROOM
	button_MAKEROOM->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_MAKEROOM->loadFont("�游���", button_MAKEROOM->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_MAKEROOM->setRectPos( tempPoint.x+160, tempPoint.y+130 +20, ALIGN_CENTER );

	//< ��ư ���
	button_CANCEL->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_CANCEL->loadFont("���", button_CANCEL->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CANCEL->setRectPos( tempPoint.x-150, tempPoint.y+130 +20, ALIGN_CENTER );
	//---------------------------------------------------------------------------
	//< ��ư ����
	button_OPEN->init("Data/Resource/Image/button_top.bmp",
		"Data/Resource/Image/button_top_02.bmp",
		"Data/Resource/Image/button_top2.bmp",
		"Data/Resource/Image/button_top2_02.bmp",
		200, 50 );
	button_OPEN->loadFont("������", button_OPEN->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OPEN->setRectPos( popupImage->getRect().left+100, popupImage->getRect().top-40 +160, ALIGN_LEFT_TOP );

	//< ��ư �����
	button_CLOSE->init("Data/Resource/Image/button_top.bmp",
		"Data/Resource/Image/button_top_02.bmp",
		"Data/Resource/Image/button_top2.bmp",
		"Data/Resource/Image/button_top2_02.bmp",
		200, 50  );
	button_CLOSE->loadFont("�������", button_CLOSE->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_CLOSE->setRectPos( popupImage->getRect().left+200+100, popupImage->getRect().top-40 +160, ALIGN_LEFT_TOP );

	//< ó���� ��� ���·� �����
	button_CLOSE->inCheckBox( CHECK_BOX_ON );
	//--------------------------------------------------------------
	//< ��ư üũ�ڽ� ��
	checkBox_OK->init("Data/Resource/Image/on_off.bmp",
		"Data/Resource/Image/on_off_02.bmp",
		"Data/Resource/Image/on_off2.bmp",
		"Data/Resource/Image/on_off2_02.bmp",
		145, 60 );
	checkBox_OK->loadFont("���", checkBox_OK->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_OK->setRectPos( tempPoint.x+35, tempPoint.y + 62 +30, ALIGN_CENTER );

	//< ��ư ü�׹ڽ� �ƴϿ�
	checkBox_NO->init("Data/Resource/Image/on_off.bmp",
		"Data/Resource/Image/on_off_02.bmp",
		"Data/Resource/Image/on_off2.bmp",
		"Data/Resource/Image/on_off2_02.bmp",
		145, 60  );
	checkBox_NO->loadFont("�����", checkBox_NO->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_NO->setRectPos( tempPoint.x+185, tempPoint.y + 62 +30, ALIGN_CENTER );

	//< ó���� ��� ���·� �����
	checkBox_OK->inCheckBox( CHECK_BOX_ON );
	//---------------------------------------------------------------------------
}

//< ������Ʈ
void Popup_Lobby_MakeRoom_close::update( POINT mousePos )
{
	//< ��ư 
	button_MAKEROOM->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_MAKEROOM->getRect() ));
	button_MAKEROOM->update();
	button_CANCEL->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CANCEL->getRect() ));
	button_CANCEL->update();
	//< ��ư ���� �����
	button_OPEN->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OPEN->getRect() ));
	button_OPEN->update();
	button_CLOSE->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_CLOSE->getRect() ));
	button_CLOSE->update();
	//< üũ�ڽ� 
	checkBox_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_OK->getRect() ));
	checkBox_OK->update(); 
	checkBox_NO->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_NO->getRect() ));
	checkBox_NO->update();

	//< �Է��� ��ġ �ޱ�
	m_inputID_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_inputID_Board->getRect() ));
	m_inputID_Board->update();
	m_inputPass_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_inputPass_Board->getRect() ));
	m_inputPass_Board->update();

	//< ��Ŷ�� ��� ���� �ʴٸ�
	if(true != TCPIP_CLIENT->emptyQueue())
	{
		unsigned short type = TCPIP_CLIENT->getPacketType();
		if(type == SC_ROOM_CREATE_YES)
		{
			//< �游��� ���� POPUP_NO_POPUP_GET_MAKE_ROOM
			button_STATE = POPUP_LOBBY_MAKEROOM_SUCCESS;

			PACKET packet;
			TCPIP_CLIENT->getPacket(packet);

			//> ���� ���� ����
			INITCONFIG initConfig;
			//> ���� ��Ʈ
			initConfig.serverPort = packet.m_roomCreateAck.m_port;
			//> ���� ���� ����
			initConfig.recvBufCnt = 10;
			//> ���� ���� ������
			initConfig.recvBufSize = 1024;
			//> �۽� ���� ����
			initConfig.sendBufCnt = 10;
			//> �۽� ���� ������
			initConfig.sendBufSize = 1024;
			//> �۾��� ������ ����
			initConfig.workerThreadCnt = 1;
			//> ���μ��� ó�� ������ ����
			initConfig.processThreadCnt = 1;
			//> ��Ŷ ���� ó�� ���� ����
			initConfig.processPacketCnt = 100;
			HOST_SERVER->setHostis(true);
			HOST_SERVER->setIsConnector(false);
			//> ���� ����
			HOST_SERVER->ServerStart(initConfig);
			//> Ŀ�ؼ� ����
			CONNECTION_MGR->CreateConnection(initConfig,4);

			TCPIP_CLIENT->popPacket();
		}
		else if(type == SC_ROOM_CREATE_NO)
		{
			//< ����� ���� ���
			button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;

			TCPIP_CLIENT->popPacket();
		}
	}
	//< ��ư �游���-------------------------------------------------
	if( button_MAKEROOM->getPlayButtonAni() == true )
	{
		//< ���� ������
		button_MAKEROOM->inCheckMouseOn( false );
		button_MAKEROOM->inClickButton( false );
		button_MAKEROOM->inPlayButtonAni( false );

		//< �ӽ� ����
		string tempID = inputRoomName->getString();
		string tempPA = inputPass->getString();

		//< �Է� ���� Ȯ��
		if( tempID.size() <= 0 ||
			tempPA.size() <= 0 )
		{
			//< �Է� ���� ����
			button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;
		}
		else
		{
			PACKET packet;
			packet.m_roomCreateReq.m_length = sizeof(CREATE_ROOM_REQ);
			packet.m_roomCreateReq.m_type = CS_ROOM_CREATE;
			packet.m_roomCreateReq.m_isSecret = true;
			if( checkBox_OK->getCheckBox() == CHECK_BOX_ON )
			{
				packet.m_roomCreateReq.m_isTrespass = true;
			}
			else
			{
				packet.m_roomCreateReq.m_isTrespass = false;
			}
			strcpy_s(packet.m_roomCreateReq.m_roomName, sizeof(packet.m_roomCreateReq.m_roomName), tempID.c_str());
			strcpy_s(packet.m_roomCreateReq.m_roomPW, sizeof(packet.m_roomCreateReq.m_roomPW), tempPA.c_str());
			TCPIP_CLIENT->sendPacket(packet);
		}
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
	//< ��ư ���� -------------------------------------------------
	//< ����
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( button_OPEN->getPlayButtonAni() == true )
	{
		//< ���� ������
		button_OPEN->inCheckMouseOn( false );
		button_OPEN->inClickButton( false );
		button_OPEN->inPlayButtonAni( false );
		//< Ŭ�� ����
		button_STATE = POPUP_LOBBY_MAKEROOM_OPEN;
	}
	//< �����
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( button_CLOSE->getPlayButtonAni() == true )
	{
		//< ���� ������
		button_CLOSE->inCheckMouseOn( false );
		button_CLOSE->inClickButton( false );
		button_CLOSE->inPlayButtonAni( false );
		//< Ŭ�� ����
		button_STATE = POPUP_LOBBY_MAKEROOM_CLOSE;

		//< ��� ��� ���·� �����
		button_CLOSE->inCheckBox( CHECK_BOX_ON );
	}

	//üũ�ڽ�--------------------------------------------------------
	//< ���
	if( checkBox_OK->getPlayButtonAni() == true )
	{
		//< ���� ������
		checkBox_OK->inCheckMouseOn( false );
		checkBox_OK->inClickButton( false );
		checkBox_OK->inPlayButtonAni( false );

		//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
		if( checkBox_NO->getCheckBox() == CHECK_BOX_ON )
		{
			checkBox_NO->inCheckBox( CHECK_BOX_OFF );
		}
		//< üũ���·� �����
		checkBox_OK->inCheckBox( CHECK_BOX_ON );

		//< Ŭ�� ����
		button_STATE = POPUP_NONE;
	}
	//< �����
	if( checkBox_NO->getPlayButtonAni() == true )
	{
		//< ���� ������
		checkBox_NO->inCheckMouseOn( false );
		checkBox_NO->inClickButton( false );
		checkBox_NO->inPlayButtonAni( false );

		//< ����� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
		if( checkBox_OK->getCheckBox() == CHECK_BOX_ON )
		{
			checkBox_OK->inCheckBox( CHECK_BOX_OFF );
		}
		//< üũ���·� �����
		checkBox_NO->inCheckBox( CHECK_BOX_ON );

		//< Ŭ�� ����
		button_STATE = POPUP_NONE;
	}

	//< �Է�â ���̵�-------------------------------------------------
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( m_inputID_Board->getPlayButtonAni() == true )
	{
		//< �ִϸ��̼� ������
		m_inputID_Board->inPlayButtonAni( false );
		//< Ŭ�� ������
		m_inputID_Board->inClickButton( false );

		//< ���̵� �Է� ����
		//inputRoomName->inInputCheck( true );
	}
	//< �н�����----------------------------------------------------------
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( m_inputPass_Board->getPlayButtonAni() == true )
	{
		//< �ִϸ��̼� ������
		m_inputPass_Board->inPlayButtonAni( false );
		//< Ŭ�� ������
		m_inputPass_Board->inClickButton( false );

		//< �н����� �Է� ����
		//inputPass->inInputCheck( true );
	}
	//------------------------------------------------------------

	//< ���̸� �н����� �Է�
	inputRoomName->update( );
	inputPass->update( );
}

//< ����
void Popup_Lobby_MakeRoom_close::render( HDC hdc )
{
	//< ���� �̹��� ����
	alpaImage->render( hdc, 0,0  );
	//< �˾�â ����
	popupImage->render( hdc );

	if( popupImage->getPlayPopupBoxAni() == true )
	{
		//-------------------------------------------------
		//< ��ư ���� �����
		button_OPEN->render( hdc );
		button_CLOSE->render( hdc );
		//-------------------------------------------
		//< üũ�ڽ�
		checkBox_OK->render( hdc );
		checkBox_NO->render( hdc );
		//--------------------------------------------------------
		//< �Է� ��Ʈ �̹���
		inputInfo_ID->render( hdc );
		inputInfo_PASS->render( hdc );
		inputInfo_REPASS->render( hdc );
		//--------------------------------------------------------
		//< �Էº���
		m_inputID_Board->render( hdc );
		m_inputPass_Board->render( hdc );
		//--------------------------------------------------------
		//< �Է� ���̸� �н�����
		inputRoomName->render( hdc );
		inputPass->renderStar( hdc );
		//--------------------------------------------------------
		//< ��ư
		button_MAKEROOM->render( hdc );
		button_CANCEL->render( hdc );
	}
}

//< �����
void Popup_Lobby_MakeRoom_close::release( void )
{
	//< �ҷ��� �̹��� �����
	if( alpaImage != NULL ){ alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( popupImage != NULL ){ popupImage->release(); }
	SAFE_DELETE( popupImage );
	//< ��ư
	if( button_MAKEROOM != NULL ){ button_MAKEROOM->release(); }
	SAFE_DELETE( button_MAKEROOM );
	if( button_CANCEL != NULL ){ button_CANCEL->release(); }
	SAFE_DELETE( button_CANCEL );
	//< ��ư ���� �����
	if( button_OPEN != NULL ){ button_OPEN->release(); }
	SAFE_DELETE( button_OPEN );
	if( button_CLOSE != NULL ){ button_CLOSE->release(); }
	SAFE_DELETE( button_CLOSE );
	//< üũ�ڽ�
	if( checkBox_OK != NULL ){ checkBox_OK->release(); }
	SAFE_DELETE( checkBox_OK );
	if( checkBox_NO != NULL ){ checkBox_NO->release(); }
	SAFE_DELETE( checkBox_NO );
	//< �Է� ��Ʈ �̹���
	if( inputInfo_ID != NULL ){ inputInfo_ID->release(); }
	SAFE_DELETE( inputInfo_ID );
	if( inputInfo_PASS != NULL ){ inputInfo_PASS->release(); }
	SAFE_DELETE( inputInfo_PASS );
	if( inputInfo_REPASS != NULL ){ inputInfo_REPASS->release(); }
	SAFE_DELETE( inputInfo_REPASS );
	//< �Է�ĭ
	if( m_inputID_Board != NULL ){ m_inputID_Board->release(); }
	SAFE_DELETE( m_inputID_Board );
	if( m_inputPass_Board != NULL ){ m_inputPass_Board->release(); }
	SAFE_DELETE( m_inputPass_Board );
	//< �Է� ��Ʈ �����
	if( inputRoomName != NULL ){ inputRoomName->release(); }
	SAFE_DELETE( inputRoomName );
	if( inputPass != NULL ){ inputPass->release(); }
	SAFE_DELETE( inputPass );
}

//< �̹��� �ҷ�����
void Popup_Lobby_MakeRoom_close::loadImage( void )
{
	//< ���� �̹���
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );
	//< �˾�â
	popupImage->init("Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< �̺�Ʈó��
LRESULT	Popup_Lobby_MakeRoom_close::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
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
			//< ��ư ȸ������-------------------------------------------------
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_MAKEROOM->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_MAKEROOM->inClickButton( true );
			}
			//< ��ư cancel
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_CANCEL->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_CANCEL->inClickButton( true );
			}

			//< ���� �����-------------------------------------------------
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_OPEN->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_OPEN->inClickButton( true );
			}
			//< �����
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_CLOSE->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_CLOSE->inClickButton( true );
			}

			//< ���� ���-------------------------------------------------
			//< ���콺 ������� �ٸ��̹��� ���
			if( checkBox_OK->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_OK->inClickButton( true );
			}
			//< �����
			//< ���콺 ������� �ٸ��̹��� ���
			if( checkBox_NO->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_NO->inClickButton( true );
			}

			//-----------------------------------------------------------
			//< ���̸�
			//< ���콺 ������ ���� ����
			if( m_inputID_Board->getCheckMouseOn() == true )
			{
				m_inputID_Board->inClickButton( true );
				//< �н����� �Է��� ����
				inputPass->inInputCheck( false );
				inputRoomName->inInputCheck( true );
			}
			//< �� �н�����
			//< ���콺 ������ ���� ����
			if( m_inputPass_Board->getCheckMouseOn() == true )
			{
				m_inputPass_Board->inClickButton( true );
				//< ���̵� �Է��� ����
				inputRoomName->inInputCheck( false );
				inputPass->inInputCheck( true );
			}
		}
		break;
		//< ���� �Է�
	case WM_CHAR :
		{
			//< ������ �Է¹ޱ�
			inputRoomName->getChar( wparam );
			inputPass->getChar( wparam );
		}
		break;
		//< Ű���� �Է¹ޱ�
	case WM_KEYDOWN :
		switch(wparam)
		{
		case VK_RETURN :
			{
				//< �н����� �Է����̶��
				if( inputPass->getInputCheck() == true )
				{
					//< �н����� �Է� ����
					inputPass->inInputCheck( false );
					//< ���̵� �Է� ����
					inputRoomName->inInputCheck( false );
					button_MAKEROOM->inClickButton( true );
					break;
				}
			}
			break;
			//< ����Ű �Է�
		case VK_TAB :
			{		
				//< ó�� �Է��̶��
				if( inputRoomName->getInputCheck() == false &&
					inputPass->getInputCheck() == false)
				{
					//< ���̵� �Է� ����
					m_inputID_Board->inClickButton( true );
					inputRoomName->inInputCheck( true );
					break;
				}

				//< ���̵� �Է����̶��
				if( inputRoomName->getInputCheck() == true )
				{
					//< ���̵� �Է� ����
					inputRoomName->inInputCheck( false );
					//< �н����� �Է� �ִϸ��̼� ����
					m_inputPass_Board->inClickButton( true );
					inputPass->inInputCheck( true );
					break;
				}

				//< ó�� �Է��̶��
				if( inputRoomName->getInputCheck() == false &&
					inputPass->getInputCheck() == true )
				{
					//< ���̵� �Է� ����
					m_inputID_Board->inClickButton( true );
					inputRoomName->inInputCheck( true );
					break;
				}
			}
			break;
			//< �齺���̽� �Է�
		case VK_BACK :
			{
				//< ���� �Է� �����
				inputRoomName->backSpace();
				inputPass->backSpace();
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< ������ �ޱ�
int Popup_Lobby_MakeRoom_close::getNextScene( void )
{
	//< ��ư�� ���������� ����
	//if( button_STATE != POPUP_NONE )
	//{
	//	if( button_STATE != POPUP_NO_POPUP &&
	//		button_STATE != POPUP_LOBBY_MAKEROOM_OPEN &&
	//		button_STATE != POPUP_LOBBY_MAKEROOM_CLOSE )
	//	{
	//		//< �ӽ� ����
	//		string tempID = inputRoomName->getString();
	//		string tempPA = inputPass->getString();

	//		//< �Է� ���� Ȯ��
	//		if( tempID.size() <= 0 ||
	//			tempPA.size() <= 0 )
	//		{
	//			//< �Է� ���� ����
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

	//				//< ������ ���� ���� ����
	//				GAME_DATA->setMyRoomName(tempID.c_str());
	//				GAME_DATA->setMyRoomOption(breakInto);
	//			}

	//			unsigned short type = TCPIP_CLIENT->getPacketType();
	//			if(type == SC_GAME_CREATE_YES)
	//			{
	//				//< �游��� ���� POPUP_NO_POPUP_GET_MAKE_ROOM
	//				button_STATE = POPUP_LOBBY_MAKEROOM_SUCCESS;

	//				TCPIP_CLIENT->init();
	//			}
	//			else if(type == SC_GAME_CREATE_NO)
	//			{
	//				//< ����� ���� ���
	//				button_STATE = POPUP_LOGIN_JOIN_FAIL_NONE;

	//				TCPIP_CLIENT->init();
	//			}
	//		}
	//	}
	//}
	return button_STATE; 
}
