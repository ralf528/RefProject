#include "stdafx.h"
#include "Popup_Lobby_FriendList.h"

#include "ImageNode.h"
#include "PopupBox.h"
#include "MY_FontMgr.h"
#include "FriendListClass.h"

Popup_Lobby_FriendList::Popup_Lobby_FriendList(void)
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

	//< 친구 리스트
	friendListPage = new FriendListClass;
}

Popup_Lobby_FriendList::~Popup_Lobby_FriendList(void)
{
	release();
}


//< 초기화
void Popup_Lobby_FriendList::init( void )
{
	//< 지정 이미지 로드
	loadImage();

	//< 정렬
	popupImage->setRectPos( WINSIZE_X/2, WINSIZE_Y/2, ALIGN_CENTER );

	//< 팝업 이미지 중점 받기
	POINT tempPoint = popupImage->getCenter();
	RECT tempRect = popupImage->getRect();
	
	//< 버튼 확인
	button_OK->init("Data/Resource/Image/button_OK.bmp",
		"Data/Resource/Image/button_OK_02.bmp",
		 200, 50 );
	button_OK->loadFont("확인", button_OK->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_OK->setRectPos( tempRect.right-40, tempRect.bottom-50, ALIGN_RIGHT_BOTTOM );

	//< 친구 리스트
	friendListPage->init();
}

//< 업데이트
void Popup_Lobby_FriendList::update( POINT mousePos )
{
	//< 버튼 확인
	button_OK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_OK->getRect() ));
	button_OK->update();

	//< 버튼 확인-------------------------------------------------
	//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
	if( button_OK->getPlayButtonAni() == true )
	{
		button_OK->inClickButton( false );
		button_OK->inPlayButtonAni( false );
		//< 클릭 리턴
		button_STATE = POPUP_NO_POPUP ;
		return;
	}

	font->LoadText( "친구 목록", popupImage->getRect(), 
		"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );

	//< 친구 리스트
	friendListPage->update( mousePos );
}

//< 랜더
void Popup_Lobby_FriendList::render( HDC hdc )
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
		font->OutputText( hdc, 0, 0, 0, -540 );
	}

	//< 친구 리스트
	friendListPage->render( hdc );
}

//< 지우기
void Popup_Lobby_FriendList::release( void )
{
	//< 불러온 이미지 지우기
	if( alpaImage != NULL ) { alpaImage->release(); }
	SAFE_DELETE( alpaImage );
	if( popupImage != NULL ) { popupImage->release();}
	SAFE_DELETE( popupImage );
	//< 버튼 지우기
	if( button_OK != NULL ) { button_OK->release();}
	SAFE_DELETE( button_OK );
	//< 폰트 지우기
	SAFE_DELETE( font );
	//< 친구 지우기
	if( friendListPage != NULL ) { friendListPage->release();}
	SAFE_DELETE( friendListPage );
}

//< 이미지 불러오기
void Popup_Lobby_FriendList::loadImage( void )
{
	//< 알파 이미지
	//alpaImage->loadImage("Data/Resource/Image/Alpa_background.bmp", 1024, 768 );
	alpaImage->load( "Data/Resource/Image/Alpa_background.bmp", 
		0, 0, RM_TRANS );

	//< 배경판 이미지
	popupImage->init("Data/Resource/Image/Popup_Box2.bmp", 850, 640 );
}

//< 이벤트처리
LRESULT	Popup_Lobby_FriendList::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
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
	}
	return friendListPage->StateProc( wnd ,msg,wparam,lparam);
}