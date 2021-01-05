#include "stdafx.h"
#include "Popup_Game_GameOver.h"

#include "../../ImageNode.h"
#include "../../PopupBox.h"
#include "../../MY_FontMgr.h"
//#include "../../FriendListClass.h"
//#include "../../SceneTitle.h"

Popup_Game_GameOver::Popup_Game_GameOver(void)
{
	//< 배경판 이미지
	alpaImage = new ImageNode(0);

	//< 피 애니메이션
	bloodAni = new ImageNode(0);
	bloodAniInfo = new ANI_INFO;
	//< 게임오버
	gameOverAni = new ImageNode(0);
	gameOverAniInfo = new ANI_INFO;

	//< 버튼
	button_OK = new ButtonClass;
	button_STATE = POPUP_NONE;

	//< 폰트
	font = new MY_Font;

	startAniCount = GetTickCount();
	aniCountCheck = true;
}


Popup_Game_GameOver::~Popup_Game_GameOver(void)
{
	release();
}


//< 초기화
void Popup_Game_GameOver::init( void )
{
	//< 지정 이미지 로드
	loadImage();

	//< 피 그림 불러오기
	bloodAni->load("Data/Resource/Image/gameOver/blood.bmp",
		11520,720,RM_TRANS );
	
	//< 피애니 애니메이션 정보
	bloodAniInfo->aniSize.cx = 1280;
	bloodAniInfo->aniSize.cy = 720;
	bloodAniInfo->frameCntX = 9;
	bloodAniInfo->frameCntY = 1;
	bloodAniInfo->frameSpeed = 100;
	bloodAniInfo->nowFrame = 0;
	bloodAniInfo->playAni = false;
	bloodAniInfo->loop = false;
	bloodAniInfo->lastTime = GetTickCount();

	//< 게임오버 그림 불러오기
	gameOverAni->load("Data/Resource/Image/gameOver/gameover.bmp",
		19200,720,RM_TRANS );
	
	//< 게임오버 애니메이션 정보
	gameOverAniInfo->aniSize.cx = 1280;
	gameOverAniInfo->aniSize.cy = 720;
	gameOverAniInfo->frameCntX = 15;
	gameOverAniInfo->frameCntY = 1;
	gameOverAniInfo->frameSpeed = 250;
	gameOverAniInfo->nowFrame = 0;
	gameOverAniInfo->playAni = false;
	gameOverAniInfo->loop = false;
	gameOverAniInfo->lastTime = GetTickCount();

	//< 버튼 확인
	button_OK->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		 200, 50 );
	button_OK->loadFont("확인", button_OK->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OK->setRectPos( WINSIZE_X/2, WINSIZE_Y/2+100, ALIGN_CENTER );

}

//< 업데이트
void Popup_Game_GameOver::update( POINT mousePos )
{
	//< 버튼 확인
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
	//		//< 팝업 상태 변경
	//		POPUP_MGR->changePopup( POPUP_GAME_RANK );

	//		//< 초기화
	//		POPUP_MGR->initPopup();

	//		TCPIP_CLIENT->popPacket();
	//		return;
	//	}
	//}

	//< 버튼 확인-------------------------------------------------
	if( button_OK->getPlayButtonAni() == true )
	{
		button_OK->inClickButton( false );
		button_OK->inPlayButtonAni( false );

		//< 랭킹팝업 리턴
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

	//< 피애니 
	if( bloodAniInfo->playAni == true )
	{
		DWORD nTime = GetTickCount();

		if( bloodAniInfo->lastTime + bloodAniInfo->frameSpeed <= nTime )
		{
			//< 시간 갱신
			bloodAniInfo->lastTime = nTime;
			//< 애니 프레임 증가
			bloodAniInfo->nowFrame++;

			//< 애니메이션 재생 완료
			if( bloodAniInfo->frameCntX == bloodAniInfo->nowFrame )
			{
				//< 애니 프레임 돌리기
				bloodAniInfo->nowFrame = 0;
				//< 재생 완료
				bloodAniInfo->playAni = false;

				//< 게임오버 재생 시작
				gameOverAniInfo->playAni = true;
			}
		}
	}

	//< 게임오버 애니 
	if( gameOverAniInfo->playAni == true )
	{
		DWORD nTime = GetTickCount();

		if( gameOverAniInfo->lastTime + gameOverAniInfo->frameSpeed <= nTime )
		{
			//< 시간 갱신
			gameOverAniInfo->lastTime = nTime;
			//< 애니 프레임 증가
			gameOverAniInfo->nowFrame++;

			//< 애니메이션 재생 완료
			if( gameOverAniInfo->frameCntX == gameOverAniInfo->nowFrame )
			{
				//< 애니 프레임 돌리기
				gameOverAniInfo->nowFrame = 0;
				//< 재생 완료
				gameOverAniInfo->playAni = false;
			}
		}
	}
}

//< 랜더
void Popup_Game_GameOver::render( HDC hdc )
{
	//< 투명 이미지 랜더
	alpaImage->render( hdc, 0,0  );

	if( aniCountCheck == false )
	{
	//< 피 애니메이션
	if( bloodAniInfo->playAni == true )
	{
		//< 피이미지 렌더
		bloodAni->render( hdc, 
			0,0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy,
			bloodAniInfo->nowFrame * bloodAniInfo->aniSize.cx, 0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy );
	}
	else
	{
		//< 그냥 피이미지 렌더
		bloodAni->render( hdc, 
			0,0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy,
			8 * bloodAniInfo->aniSize.cx, 0,
			bloodAniInfo->aniSize.cx, bloodAniInfo->aniSize.cy );


		//< 게임오버 애니메이션
		if( gameOverAniInfo->playAni == true )
		{
			//< 피이미지 렌더
			gameOverAni->render( hdc, 
				0,0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy,
				gameOverAniInfo->nowFrame * gameOverAniInfo->aniSize.cx, 0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy );
		}
		else
		{
			//< 그냥 피이미지 렌더
			gameOverAni->render( hdc, 
				0,0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy,
				14 * gameOverAniInfo->aniSize.cx, 0,
				gameOverAniInfo->aniSize.cx, gameOverAniInfo->aniSize.cy );

			//< 버튼
			button_OK->render( hdc );
		}
	}
	}
}

//< 지우기
void Popup_Game_GameOver::release( void )
{
	//< 불러온 이미지 지우기
	if( alpaImage != NULL ) { alpaImage->release(); }
	SAFE_DELETE( alpaImage );

	//< 피이미지 지우기
	if( bloodAni != NULL ) { bloodAni->release();}
	SAFE_DELETE( bloodAni );
	SAFE_DELETE( bloodAniInfo );
	//< 피이미지 지우기
	if( gameOverAni != NULL ) { gameOverAni->release();}
	SAFE_DELETE( gameOverAni );
	SAFE_DELETE( gameOverAniInfo );

	//< 버튼 지우기
	if( button_OK != NULL ) { button_OK->release();}
	SAFE_DELETE( button_OK );

	//< 폰트 지우기
	SAFE_DELETE( font );
}

//< 이미지 불러오기
void Popup_Game_GameOver::loadImage( void )
{
	//< 알파 이미지
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );
}

//< 이벤트처리
LRESULT	Popup_Game_GameOver::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_LBUTTONUP :
		{
			//< 마우스 오버라면 다른이미지 출력
			if( button_OK->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
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