#include "stdafx.h"
#include "ChattingBox.h"

#include "../../MY_FontMgr.h"
#include "../../PopupBox.h"
#include "../../InputString.h"
#include "../../ButtonClass.h"

ChattingBox::ChattingBox(void)
{
	//< ��Ʈ
	m_font = new MY_Font;
	//< ��� �̹���
	m_image = new PopupBox;

	//< ä�� �Է� ��
	m_input_Board = new ButtonClass;
	//< �Է� ��Ʈ��
	inputChar = new InputString;

	//< ��ư ��,�Ʒ�
	button_UP = new ButtonClass;
	button_DOWN = new ButtonClass;
	//< ��ũ�ѹ�
	button_SCROLL = new ButtonClass;
	button_SCROLL_NODE = new ButtonClass;

	//< ó���� 5���������� ����
	stringPage = 5;
	oldStringPage = 0;
	//< 5������
	nodePosition = 548;
}


ChattingBox::~ChattingBox(void)
{
	release();
}


//< �ʱ�ȭ
void ChattingBox::init( void )
{
	//< ��� �̹��� �ε�
	m_image->loadImage( L"Data/Resource/Image/Popup_Box4.bmp", 921,270 );

	//< ���� ��ġ
	m_image->setRectPos( WINSIZE_X/2-120, WINSIZE_Y/2+180, ALIGN_CENTER );

	//< �˾� �̹��� ���� �ޱ�
	POINT tempPoint = m_image->getCenter();

	//< �Է��� 
	m_input_Board->init( L"Data/Resource/Image/button_CHAR_02.bmp",
		L"Data/Resource/Image/button_CHAR_02.bmp",888, 44 );
	m_input_Board->setRectPos( tempPoint.x, tempPoint.y+90, ALIGN_CENTER ); 
	//< �ӽ� ��Ʈ
	RECT tempRect = m_input_Board->getRect();
	tempRect.left += 120;

	//< �Է� 
	inputChar->init( tempRect, L"HY������M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	//< �Է� ����
	inputChar->inInputCheck( true );

	//< ���� ������
	int posX = 84;
	int posY = 437;

	//< ��Ʈ ũ��
	int rectsizeX = 100;
	int rectsizeY = 40;

	//< ����
	int cell = 5;
	int cell2 = 50;

	//< ��ŷ���� ��Ʈ ���
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
		inputData[j].name.LoadText( inputData[j].rect[0], L"HY������M", 20, ALIGN_CENTER, 255,255,255 );
		inputData[j].text.LoadText( inputData[j].rect[1], L"HY������M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	}
	//< ��ŷ���� ���� ��Ʈ ���
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
		inputDataSave[j].name.LoadText( inputDataSave[j].rect[0], L"HY������M", 20, ALIGN_CENTER, 255,255,255 );
		inputDataSave[j].text.LoadText( inputDataSave[j].rect[1], L"HY������M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	}

	//< ���� �̸� ��Ʈ
	userNameRect.left = 84;
	userNameRect.top = 614;
	userNameRect.right = 183;
	userNameRect.bottom = 647;

	//< ��ư ��,�Ʒ�
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

	//< ��ũ�ѹ�
	button_SCROLL->init(L"Data/Resource/Image/scroll_board.bmp",
		L"Data/Resource/Image/scroll_board.bmp",
		32, 94 );
	button_SCROLL_NODE->init(L"Data/Resource/Image/scroll_board_loot.bmp",
		L"Data/Resource/Image/scroll_board_loot.bmp",
		26, 12 );
	button_SCROLL->setRectPos( 942, 510, ALIGN_CENTER );
	button_SCROLL_NODE->setRectPos( 942, nodePosition, ALIGN_CENTER );

	//---------------------------------------------------------------------------------------------
	//< ���� �̸� �ޱ�
	//userName = GAME_DATA->getUserId();
	m_font->LoadText(MY_Font::StringToTCHAR(userName), userNameRect, L"HY������M", 20, ALIGN_CENTER, 255,255,255 );
	//---------------------------------------------------------------------------------------------
}

//< ������Ʈ
void ChattingBox::update( POINT mousePos )
{

	//< ��Ŷ�� ��� ���� �ʴٸ�
	//if(true != TCPIP_CLIENT->emptyQueue())
	//{
	//	unsigned short type = TCPIP_CLIENT->getPacketType();
	//	if(type == SC_CHATTING)
	//	{
	//		PACKET packet;
	//		TCPIP_CLIENT->getPacket(packet);
	//		inputChar->setString(packet.m_chatMsg.m_chatMsg);
	//		userName = packet.m_chatMsg.m_id;

	//		//< ����
	//		StringPush();
	//		//< 5�������� ������
	//		stringPage = 5;
	//		oldStringPage = 0;
	//		//< �Է� �����
	//		inputChar->clear();

	//		userName = GAME_DATA->getUserId();

	//		TCPIP_CLIENT->popPacket();
	//	}
	//}

	//< �Է��� ��ġ �ޱ�
	m_input_Board->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, m_input_Board->getRect() ));
	m_input_Board->update();

	//< ��ư ��,�Ʒ�
	button_UP->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_UP->getRect() ));
	button_UP->update();
	button_DOWN->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_DOWN->getRect() ));
	button_DOWN->update();

	//< ��ũ�ѹ� üũ
	button_SCROLL_NODE->setRectPos( 942, nodePosition, ALIGN_CENTER );

	//< �н�����----------------------------------------------------------
	//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
	if( m_input_Board->getPlayButtonAni() == true )
	{
		//< �ִϸ��̼� ������
		m_input_Board->inPlayButtonAni( false );
		//< Ŭ�� ������
		m_input_Board->inClickButton( false );
	}

	//< ��ư ��-------------------------------------------------
	if( button_UP->getPlayButtonAni() == true )
	{
		if( stringPage > 1 )
		{
			//< ������ ����
			stringPage --;
			//< ��ǥ�̵�
			nodePosition = nodePosition - 19;
		}
		button_UP->inClickButton( false );
		button_UP->inPlayButtonAni( false );
	}
	//< ��ư �Ʒ�-------------------------------------------------
	if( button_DOWN->getPlayButtonAni() == true )
	{	
		if( stringPage < 5 )
		{
			//< ������ ����
			stringPage ++;
			//< ��ǥ�̵�
			nodePosition = nodePosition + 19;
		}
		button_DOWN->inClickButton( false );
		button_DOWN->inPlayButtonAni( false );
	}
	//< ��ư ��ױ�------------------------------------------------
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

	//< �Է�
	inputChar->update( );
	//< ��Ʈ�� ǥ�� ����
	StringUpdate();
}

//< ����
void ChattingBox::render( HDC hdc )
{
	//< ��� ����
	m_image->renderNone( hdc );

	//< �Էº���
	m_input_Board->render( hdc );
	//-------------------------------------------------------
	//< ���� �̸�
	//Rectangle( hdc, userNameRect.left, userNameRect.top, userNameRect.right, userNameRect.bottom );
	m_font->OutputText( hdc );
	//< �Է�
	inputChar->render( hdc );

	//< �׸���
	for( int j=0; j<MAX_CHAR_LINE; j++ )
	{
		//Rectangle( hdc, inputData[j].rect[0].left, inputData[j].rect[0].top, inputData[j].rect[0].right, inputData[j].rect[0].bottom );
		//Rectangle( hdc, inputData[j].rect[1].left, inputData[j].rect[1].top, inputData[j].rect[1].right, inputData[j].rect[1].bottom );
		inputData[j].text.OutputText( hdc );
		inputData[j].name.OutputText( hdc );
	}

	//< ��ũ�ѹ�
	button_SCROLL->render( hdc );
	button_SCROLL_NODE->render( hdc );
	//< ��ư
	button_UP->render( hdc );
	button_DOWN->render( hdc );
}

//< �����
void ChattingBox::release( void )
{
	//< ��Ʈ
	SAFE_DELETE( m_font );
	//< ����̹���
	if( NULL != m_image ){ m_image->release(); }
	SAFE_DELETE( m_image );

	if( m_input_Board != NULL ){ m_input_Board->release(); }
	SAFE_DELETE( m_input_Board );

	if( inputChar != NULL ){ inputChar->release(); }
	SAFE_DELETE( inputChar );

	//< ��ư �����
	if( button_UP != NULL ) { button_UP->release();}
	SAFE_DELETE( button_UP );
	if( button_DOWN != NULL ) { button_DOWN->release();}
	SAFE_DELETE( button_DOWN );
	//< ��ũ�ѹ�
	if( button_SCROLL != NULL ) { button_SCROLL->release();}
	SAFE_DELETE( button_SCROLL );
	if( button_SCROLL_NODE != NULL ) { button_SCROLL_NODE->release();}
	SAFE_DELETE( button_SCROLL_NODE );
}

//< �̺�Ʈó��
LRESULT	ChattingBox::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP :
		{
			//< �Է�â
			if( m_input_Board->getCheckMouseOn() == true )
			{
					m_input_Board->inClickButton( true );
			}
			//< ��ư ��
			if( button_UP->getCheckMouseOn() == true &&
				button_UP->getPlayButtonAni() == false )
			{
				//< Ŭ������ ���� ����
				button_UP->inClickButton( true );
			}
			//< ��ư �ٿ�
			if( button_DOWN->getCheckMouseOn() == true &&
				button_DOWN->getPlayButtonAni() == false )
			{
				//< Ŭ������ ���� ����
				button_DOWN->inClickButton( true );
			}
		}
		break;
		//< ���� �Է�
	case WM_CHAR :
		{
			//< �Է¹ޱ�
			inputChar->getChar( wparam );
		}
		break;
		//< Ű���� �Է¹ޱ�
	case WM_KEYDOWN :
		switch(wparam)
		{
			//< ����Ű �Է�
		case VK_RETURN:
			{	
				//< �Էµ� ��Ʈ���� �ִٸ� ����
				if( inputChar->getCharString().size() != 0 )
				{
					//< 5������
					nodePosition = 548;

					//< ����
					StringPush();

					//< 5�������� ������
					stringPage = 5;
					oldStringPage = 0;

					/*PACKET sendPacket;
					sendPacket.m_chatMsg.m_type = CS_CHATTING;
					sendPacket.m_chatMsg.m_length = sizeof(CHAT_MSG);
					strcpy_s(sendPacket.m_chatMsg.m_chatMsg, inputChar->getString());
					strcpy_s(sendPacket.m_chatMsg.m_id, userName.c_str());
					TCPIP_CLIENT->sendPacket(sendPacket);*/

					//< �Է� �����
					inputChar->clear();

					
				}
			}
			break;
			//< �齺���̽� �Է�
		case VK_BACK :
			{
				//< ���� �Է� �����
				inputChar->backSpace();
			}
			break;
		}
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}
//< ��Ʈ�� ���� ���
void ChattingBox::StringUpdate( void )
{
	if( oldStringPage != stringPage )
	{
	switch( stringPage )
	{
	case 1 :
		{
			//< ��Ʈ�� �б�
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
			//< ��Ʈ�� ������ ����
			oldStringPage = 1;
		}
		break;
	case 2 :
		{
			//< ��Ʈ�� �б�
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
			//< ��Ʈ�� ������ ����
			oldStringPage = 2;
		}
		break;
	case 3 :
		{
			//< ��Ʈ�� �б�
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
			//< ��Ʈ�� ������ ����
			oldStringPage = 3;
		}
		break;
	case 4 :
		{
			//< ��Ʈ�� �б�
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
			//< ��Ʈ�� ������ ����
			oldStringPage = 4;
		}
		break;
	case 5 :
		{
			//< ��Ʈ�� �б�
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
			//< ��Ʈ�� ������ ����
			oldStringPage = 5;
		}
		break;
	}
	}
}
//< ��Ʈ�� ����
void ChattingBox::StringPush( void )
{
	//< ��Ʈ�� �б�
	for( int i=0; i<7; i++ )
	{
		inputDataSave[i].name.clear();
		inputDataSave[i].text.clear();
		inputDataSave[i].name.inCharChar( inputDataSave[i+1].name.getChar() );
		inputDataSave[i].text.inCharChar( inputDataSave[i+1].text.getChar() );
	}
	//< ��Ʈ���� ����
	/*inputData[6].name.clear();
	inputData[6].text.clear();
	inputData[6].name.inCharChar( inputData[7].name.getChar() );
	inputData[6].text.inCharChar( inputData[7].text.getChar() );*/
	//< ��Ʈ���� ����
	inputDataSave[7].name.clear();
	inputDataSave[7].text.clear();
	inputDataSave[7].name.inChar( userName );
	inputDataSave[7].text.inCharChar( inputChar->getString() );
}