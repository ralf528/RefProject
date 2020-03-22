#include "stdafx.h"
#include "Popup_Lobby_EnterRoom_Faill.h"

#include "ImageNode.h"
#include "PopupBox.h"
#include "MY_FontMgr.h"
#include "SceneTitle.h"
#include "SceneChoiceChar.h"

Popup_Lobby_EnterRoom_Faill::Popup_Lobby_EnterRoom_Faill(void)
{
	//< 배경판 이미지
	alpaImage = new ImageNode(0);
	//< 팝업창 이미지
	popupImage = new PopupBox;
	//< 버튼
	button_OK = new ButtonClass;
	button_STATE = POPUP_NONE;

	//< 폰트
	font = new MY_FontMgr;

	//< 방 할당 명령
	makeRoom = false;
}

Popup_Lobby_EnterRoom_Faill::~Popup_Lobby_EnterRoom_Faill(void)
{
	release();
}


//< 초기화
void Popup_Lobby_EnterRoom_Faill::init( void )
{
	//< 지정 이미지 로드
	loadImage();

	//< 정렬
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< 팝업 이미지 중점 받기
	POINT tempPoint = popupImage->getCenter();

	//< 버튼
	button_OK->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		 200, 50 );
	button_OK->loadFont("확인", button_OK->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OK->setRectPos( tempPoint.x, tempPoint.y+130 +20, ALIGN_CENTER );
}

//< 업데이트
void Popup_Lobby_EnterRoom_Faill::update( POINT mousePos )
{
	//< 버튼 
	button_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OK->getRect() ));
	button_OK->update();
	//< 버튼-------------------------------------------------
	//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
	if( button_OK->getPlayButtonAni() == true )
	{
		//< 상태 돌리기
		button_OK->inClickButton( false );
		button_OK->inPlayButtonAni( false );
		//< 팝업 끄기
		button_STATE = POPUP_NO_POPUP;
		return;
	}

	//< 팝업 멘트
	font->LoadText( "입장 불가! 조건을 확인하세요!", popupImage->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
}

//< 랜더
void Popup_Lobby_EnterRoom_Faill::render( HDC hdc )
{
	//< 투명 이미지 랜더
	alpaImage->render( hdc, 0,0  );
	//< 팝업창 랜더
	popupImage->render( hdc );

	if( popupImage->getPlayPopupBoxAni() == true )
	{
		//< 버튼
		button_OK->render( hdc );

		//< 폰트
		font->OutputText( hdc );
	}
}

//< 지우기
void Popup_Lobby_EnterRoom_Faill::release( void )
{
	//< 불러온 이미지 지우기
	if( alpaImage != NULL ){ alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( alpaImage != NULL ){ popupImage->release(); }
	SAFE_DELETE( popupImage );
	if( alpaImage != NULL ){ button_OK->release(); }
	SAFE_DELETE( button_OK );
	//< 폰트 지우기
	SAFE_DELETE( font );
}

//< 이미지 불러오기
void Popup_Lobby_EnterRoom_Faill::loadImage( void )
{
	//< 알파 이미지
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );

	popupImage->init("Data/Resource/Image/Popup_Box.bmp", 700, 500 );
}

//< 이벤트처리
LRESULT	Popup_Lobby_EnterRoom_Faill::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	//< 마우스를 땔때 
	case WM_LBUTTONUP :
		{
			//< 버튼-------------------------------------------------
			//< 마우스 오버라면 다른이미지 출력
			if( button_OK->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_OK->inClickButton( true );
			}
		}
		break;
	//< 키보드 입력받기
	case WM_KEYDOWN :
		switch(wparam)
		{
		//< 엔터키 입력
		case VK_RETURN:
			{
				button_OK->inClickButton( true );
			}
			break;
		}
		break;
	}
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}