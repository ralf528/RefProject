#include "stdafx.h"

#include "../../MY_FontMgr.h"
#include "../../PopupBox.h"
#include "../../InputString.h"
#include "../../ButtonClass.h"
#include "ChattingGame.h"


ChattingGame::ChattingGame(void)
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

	//< ä�ÿ�
	m_OnBackground = false;
	m_onChat = false;
	count = 8000;
}

ChattingGame::~ChattingGame(void)
{
	release();
}



//< �ʱ�ȭ
void ChattingGame::init( void )
{
	//< ��� �̹��� �ε�
	m_image->loadImage( "Data/Resource/Image/Alpa_background_CHAR.bmp", 440,196 );

	//< ���� ��ġ
	m_image->setRectPos( WINSIZE_X/2+410, WINSIZE_Y/2+160, ALIGN_CENTER );

	//< �˾� �̹��� ���� �ޱ�
	POINT tempPoint = m_image->getCenter();

	//< �Է��� 
	m_input_Board->init( "Data/Resource/Image/button_CHAR_GAME.bmp",
		"Data/Resource/Image/button_CHAR_GAME.bmp",440, 31 );
	m_input_Board->setRectPos( tempPoint.x, tempPoint.y+90, ALIGN_CENTER ); 
	//< �ӽ� ��Ʈ
	RECT tempRect = m_input_Board->getRect();
	tempRect.left += 60;

	//< �Է� 
	inputChar->init( tempRect, "HY������M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	//< �Է� ����
	inputChar->inInputCheck( true );

	//< ���� ������
	int posX = 835;
	int posY = 430;

	//< ��Ʈ ũ��
	int rectsizeX = 50;
	int rectsizeY = 30;

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
		inputData[j].name.LoadText( inputData[j].rect[0], "HY������M", 18, ALIGN_CENTER, 255,255,255 );
		inputData[j].text.LoadText( inputData[j].rect[1], "HY������M", 18, ALIGN_LEFT_TOP, 255,255,255 );
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
		inputDataSave[j].name.LoadText( inputDataSave[j].rect[0], "HY������M", 20, ALIGN_CENTER, 255,255,255 );
		inputDataSave[j].text.LoadText( inputDataSave[j].rect[1], "HY������M", 20, ALIGN_LEFT_TOP, 255,255,255 );
	}

	//< ���� �̸� ��Ʈ
	userNameRect.left = posX ;
	userNameRect.top = posY +165 ;
	userNameRect.right = rectsizeX +posX;
	userNameRect.bottom = rectsizeY +posY +165;

	//< ��ư ��,�Ʒ�
	button_UP->init("Data/Resource/Image/button_UP.bmp",
		"Data/Resource/Image/button_UP_02.bmp",
		"Data/Resource/Image/button_UP_DIS.bmp",
		45, 46 );
	button_DOWN->init("Data/Resource/Image/button_DOWN.bmp",
		"Data/Resource/Image/button_DOWN_02.bmp",
		"Data/Resource/Image/button_DOWN_DIS.bmp",
		45, 46 );
	button_UP->setRectPos( 942, 441, ALIGN_CENTER );
	button_DOWN->setRectPos( 942, 580, ALIGN_CENTER );

	//< ��ũ�ѹ�
	button_SCROLL->init("Data/Resource/Image/scroll_board.bmp",
		"Data/Resource/Image/scroll_board.bmp",
		32, 94 );
	button_SCROLL_NODE->init("Data/Resource/Image/scroll_board_loot.bmp",
		"Data/Resource/Image/scroll_board_loot.bmp",
		26, 12 );
	button_SCROLL->setRectPos( 942, 510, ALIGN_CENTER );
	button_SCROLL_NODE->setRectPos( 942, nodePosition, ALIGN_CENTER );

	//---------------------------------------------------------------------------------------------
	//< ���� �̸� �ޱ�
	//userName = GAME_DATA->getUserId();
	m_font->LoadText( userName.c_str(), userNameRect, "HY������M", 20, ALIGN_CENTER, 255,255,255 );
	//---------------------------------------------------------------------------------------------

	//< ������ �ð� �ޱ�
	checkTime = GetTickCount();
}

//< ������Ʈ
void ChattingGame::update( POINT mousePos )
{
	if( m_OnBackground == true )
	{
		//< ���� �ð� �ޱ�
		nowTime = GetTickCount();

		//< üũ ����
		if( checkTime+count <= nowTime )
		{
			checkTime = nowTime;
			m_OnBackground = false;
			m_onChat = false;
		}
	}

	//< �Է�
	inputChar->update( );
	//< ��Ʈ�� ǥ�� ����
	StringUpdate();
}

//< ����
void ChattingGame::render( HDC hdc )
{
	//< ä��â�� ������ ����
	if( m_OnBackground == true )
	{
		//< ��� ����
		m_image->renderNone( hdc );

		//< �Էº���
		if(m_onChat == true)
		{
			m_input_Board->render( hdc );
			m_font->OutputText( hdc );
		}
		//-------------------------------------------------------
		//< ���� �̸�
		//Rectangle( hdc, userNameRect.left, userNameRect.top, userNameRect.right, userNameRect.bottom );
		
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
	}
	//< ��ũ�ѹ�
	//button_SCROLL->render( hdc );
	//button_SCROLL_NODE->render( hdc );
	//< ��ư
	//button_UP->render( hdc );
	//button_DOWN->render( hdc );
}

//< �����
void ChattingGame::release( void )
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
LRESULT	ChattingGame::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP :
		{
			////< �Է�â
			//if( m_input_Board->getCheckMouseOn() == true )
			//{
			//		m_input_Board->inClickButton( true );
			//}
			////< ��ư ��
			//if( button_UP->getCheckMouseOn() == true &&
			//	button_UP->getPlayButtonAni() == false )
			//{
			//	//< Ŭ������ ���� ����
			//	button_UP->inClickButton( true );
			//}
			////< ��ư �ٿ�
			//if( button_DOWN->getCheckMouseOn() == true &&
			//	button_DOWN->getPlayButtonAni() == false )
			//{
			//	//< Ŭ������ ���� ����
			//	button_DOWN->inClickButton( true );
			//}
		}
		break;
		//< ���� �Է�
	case WM_CHAR :
		{
			//< ä���� ������ �Է¹ޱ�
			if( m_onChat == true )
			{
				//< �Է¹ޱ�
				inputChar->getChar( wparam );
			}
		}
		break;
		//< Ű���� �Է¹ޱ�
	case WM_KEYDOWN :
		switch(wparam)
        {
            //< ����Ű �Է�
            case VK_RETURN:
            {
                //< ä��â�� ������ �Է¹ޱ�
                if (m_onChat == false)
                {
                    inChatingView();
                }
                else
                {
                    //< �Էµ� ��Ʈ���� �ִٸ� ����
                    if (inputChar->getCharString().size() != 0)
                    {
                        //< 5������
                        nodePosition = 548;

                        //< ����
                        StringPush();

                        ////< 5�������� ������
                        stringPage = 5;
                        oldStringPage = 0;

                        //< �Է� �����
                        inputChar->clear();
                    }
                }
                changeChattingOn();

            }
            break;
        
            //< �齺���̽� �Է�
            case VK_BACK:
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
void ChattingGame::StringUpdate( void )
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
			inputData[4].name.clear();
			inputData[4].text.clear();
			inputData[4].name.inCharChar( inputDataSave[4].name.getChar() );
			inputData[4].text.inCharChar( inputDataSave[4].text.getChar() );
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
			inputData[4].name.clear();
			inputData[4].text.clear();
			inputData[4].name.inCharChar( inputDataSave[5].name.getChar() );
			inputData[4].text.inCharChar( inputDataSave[5].text.getChar() );
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
			inputData[4].name.clear();
			inputData[4].text.clear();
			inputData[4].name.inCharChar( inputDataSave[6].name.getChar() );
			inputData[4].text.inCharChar( inputDataSave[6].text.getChar() );
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
			inputData[4].name.clear();
			inputData[4].text.clear();
			inputData[4].name.inCharChar( inputDataSave[7].name.getChar() );
			inputData[4].text.inCharChar( inputDataSave[7].text.getChar() );
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
			inputData[4].name.clear();
			inputData[4].text.clear();
			inputData[4].name.inCharChar( inputDataSave[8].name.getChar() );
			inputData[4].text.inCharChar( inputDataSave[8].text.getChar() );
			//< ��Ʈ�� ������ ����
			oldStringPage = 5;
		}
		break;
	}
	}
}
//< ��Ʈ�� ����
void ChattingGame::StringPush( void )
{
	//< ��Ʈ�� �б�
	for( int i=0; i<8; i++ )
	{
		inputDataSave[i].name.clear();
		inputDataSave[i].text.clear();
		inputDataSave[i].name.inCharChar( inputDataSave[i+1].name.getChar() );
		inputDataSave[i].text.inCharChar( inputDataSave[i+1].text.getChar() );
	}
	//< ��Ʈ���� ����
	inputDataSave[8].name.clear();
	inputDataSave[8].text.clear();
	inputDataSave[8].name.inChar( userName );
	inputDataSave[8].text.inCharChar( inputChar->getString() );
}

//void ChattingGame::packetProcess(const PACKET* packet)
//{
//	if(true == HOST_SERVER->getHostis())
//	{
//		HOST_SERVER->sendOtherPlayer((char*)&packet, packet->m_chatMsg.m_length);
//	}
//	inChatingView();
//	inputChar->setString(packet->m_chatMsg.m_chatMsg);
//	userName = packet->m_chatMsg.m_id;
//
//	//< ����
//	StringPush();
//	//< 5�������� ������
//	stringPage = 5;
//	oldStringPage = 0;
//	//< �Է� �����
//	inputChar->clear();
//
//	userName = GAME_DATA->getUserId();
//	
//}