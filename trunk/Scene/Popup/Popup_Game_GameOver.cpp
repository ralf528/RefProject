#include "stdafx.h"
#include "Popup_Game_GameOver.h"

#include "../../ImageNode.h"
#include "../../PopupBox.h"
#include "../../MY_FontMgr.h"
//#include "../../FriendListClass.h"
//#include "../../SceneTitle.h"

Popup_Game_GameOver::Popup_Game_GameOver(void)
{
	//< ����� �̹���
	alpaImage = new ImageNode(0);

	//< �� �ִϸ��̼�
	bloodAni = new ImageNode(0);
	bloodAniInfo = new ANI_INFO;
	//< ���ӿ���
	gameOverAni = new ImageNode(0);
	gameOverAniInfo = new ANI_INFO;

	//< ��ư
	button_OK = new ButtonClass;
	button_STATE = POPUP_NONE;

	//< ��Ʈ
	font = new MY_Font;

	startAniCount = GetTickCount();
	aniCountCheck = true;
}


Popup_Game_GameOver::~Popup_Game_GameOver(void)
{
	release();
}


//< �ʱ�ȭ
void Popup_Game_GameOver::init( void )
{
	//< ���� �̹��� �ε�
	loadImage();

	//< �� �׸� �ҷ�����
	bloodAni->load("Data/Resource/Image/gameOver/blood.bmp",
		11520,720,RM_TRANS );
	
	//< �Ǿִ� �ִϸ��̼� ����
	bloodAniInfo->aniSize.cx = 1280;
	bloodAniInfo->aniSize.cy = 720;
	bloodAniInfo->frameCntX = 9;
	bloodAniInfo->frameCntY = 1;
	bloodAniInfo->frameSpeed = 100;
	bloodAniInfo->nowFrame = 0;
	bloodAniInfo->playAni = false;
	bloodAniInfo->loop = false;
	bloodAniInfo->lastTime = GetTickCount();

	//< ���ӿ��� �׸� �ҷ�����
	gameOverAni->load("Data/Resource/Image/gameOver/gameover.bmp",
		19200,720,RM_TRANS );
	
	//< ���ӿ��� �ִϸ��̼� ����
	gameOverAniInfo->aniSize.cx = 1280;
	gameOverAniInfo->aniSize.cy = 720;
	gameOverAniInfo->frameCntX = 15;
	gameOverAniInfo->frameCntY = 1;
	gameOverAniInfo->frameSpeed = 250;
	gameOverAniInfo->nowFrame = 0;
	gameOverAniInfo->playAni = false;
	gameOverAniInfo->loop = false;
	gameOverAniInfo->lastTime = GetTickCount();

	//< ��ư Ȯ��
	button_OK->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		 200, 50 );
	button_OK->loadFont("Ȯ��", button_OK->getRect(), 
		"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OK->setRectPos( WINSIZE_X/2, WINSIZE_Y/2+100, ALIGN_CENTER );

}

//< ������Ʈ
void Popup_Game_GameOver::update( POINT mousePos )
{
	//< ��ư Ȯ��
	button_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OK->getRect() ));
	button_OK->update();

	//if(true != TCPIP_CLIENT->emptyQueue())
	//{
	//	unsigned short type = TCPIP_CLIENT->getPacketType();
	//	if(type == SC_RANKING)
	//	{
	//		PACKET packet;
	//		TCPIP_CLIENT->getPacket(packet);
	//		GAME_DATA->clearRank();
	//		for(unsigned short i = 0; i < packet.m_rankInfoAck.m_rankCnt; i++)
	//		{
	//			GAME_DATA->inRank(packet.m_rankInfoAck.m_rankInfo[i]);
	//		}
	//		//< �˾� ���� ����
	//		POPUP_MGR->changePopup( POPUP_GAME_RANK );

	//		//< �ʱ�ȭ
	//		POPUP_MGR->initPopup();

	//		TCPIP_CLIENT->popPacket();
	//		return;
	//	}
	//}

	//< ��ư Ȯ��-------------------------------------------------
	if( button_OK->getPlayButtonAni() == true )
	{
		button_OK->inClickButton( false );
		button_OK->inPlayButtonAni( false );

		//< ��ŷ�˾� ����
		//button_STATE = POPUP_GAME_RANK;

		//button_STATE = POPUP_TITLE_RANK;
		return;
	}

	if( aniCountCheck == true )
	{
		int count = 4000;
		DWORD nowCount = GetTickCount();

		if( startAniCount + count < nowCount )
		{
			bloodAniInfo->playAni = true;
			aniCountCheck = false;
		}
	}

	//< �Ǿִ� 
	if( bloodAniInfo->playAni == true )
	{
		DWORD nTime = GetTickCount();

		if( bloodAniInfo->lastTime + bloodAniInfo->frameSpeed <= nTime )
		{
			//< �ð� ����
			bloodAniInfo->lastTime = nTime;
			//< �ִ� ������ ����
			bloodAniInfo->nowFrame++;

			//< �ִϸ��̼� ��� �Ϸ�
			if( bloodAniInfo->frameCntX == bloodAniInfo->nowFrame )
			{
				//< �ִ� ������ ������
				bloodAniInfo->nowFrame = 0;
				//< ��� �Ϸ�
				bloodAniInfo->playAni = false;

				//< ���ӿ��� ��� ����
				gameOverAniInfo->playAni = true;
			}
		}
	}

	//< ���ӿ��� �ִ� 
	if( gameOverAniInfo->playAni == true )
	{
		DWORD nTime = GetTickCount();

		if( gameOverAniInfo->lastTime + gameOverAniInfo->frameSpeed <= nTime )
		{
			//< �ð� ����
			gameOverAniInfo->lastTime = nTime;
			//< �ִ� ������ ����
			gameOverAniInfo->nowFrame++;

			//< �ִϸ��̼� ��� �Ϸ�
			if( gameOverAniInfo->frameCntX == gameOverAniInfo->nowFrame )
			{
				//< �ִ� ������ ������
				gameOverAniInfo->nowFrame = 0;
				//< ��� �Ϸ�
				gameOverAniInfo->playAni = false;
			}
		}
	}
}

//< ����
void Popup_Game_GameOver::render( HDC hdc )
{
	//< ���� �̹��� ����
	alpaImage->render( hdc, 0,0  );

	if( aniCountCheck == false )
	{
	//< �� �ִϸ��̼�
	if( bloodAniInfo->playAni == true )
	{
		//< ���̹��� ����
		bloodAni->render( hdc, 
			0,0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy,
			bloodAniInfo->nowFrame * bloodAniInfo->aniSize.cx, 0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy );
	}
	else
	{
		//< �׳� ���̹��� ����
		bloodAni->render( hdc, 
			0,0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy,
			8 * bloodAniInfo->aniSize.cx, 0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy );


		//< ���ӿ��� �ִϸ��̼�
		if( gameOverAniInfo->playAni == true )
		{
			//< ���̹��� ����
			gameOverAni->render( hdc, 
				0,0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy,
				gameOverAniInfo->nowFrame * gameOverAniInfo->aniSize.cx, 0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy );
		}
		else
		{
			//< �׳� ���̹��� ����
			gameOverAni->render( hdc, 
				0,0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy,
				14 * gameOverAniInfo->aniSize.cx, 0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy );

			//< ��ư
			button_OK->render( hdc );
		}
	}
	}
}

//< �����
void Popup_Game_GameOver::release( void )
{
	//< �ҷ��� �̹��� �����
	if( alpaImage != NULL ) { alpaImage->release(); }
	SAFE_DELETE( alpaImage );

	//< ���̹��� �����
	if( bloodAni != NULL ) { bloodAni->release();}
	SAFE_DELETE( bloodAni );
	SAFE_DELETE( bloodAniInfo );
	//< ���̹��� �����
	if( gameOverAni != NULL ) { gameOverAni->release();}
	SAFE_DELETE( gameOverAni );
	SAFE_DELETE( gameOverAniInfo );

	//< ��ư �����
	if( button_OK != NULL ) { button_OK->release();}
	SAFE_DELETE( button_OK );

	//< ��Ʈ �����
	SAFE_DELETE( font );
}

//< �̹��� �ҷ�����
void Popup_Game_GameOver::loadImage( void )
{
	//< ���� �̹���
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );
}

//< �̺�Ʈó��
LRESULT	Popup_Game_GameOver::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP :
		{
			//< ���콺 ������� �ٸ��̹��� ���
			if( button_OK->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_OK->inClickButton( true );
			}
		}
		break;
	case WM_KEYDOWN :
		{
			switch( wparam )
			{
			case VK_RETURN :
				{
					button_OK->inClickButton( true );
				}
				break;
			}
		}
		break;
	}
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}