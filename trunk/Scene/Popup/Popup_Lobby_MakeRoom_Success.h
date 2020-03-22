#pragma once
#include "popup.h"

class PopupBox;
class ButtonClass;

class Popup_Lobby_MakeRoom_Success :public Popup
{
public:
	Popup_Lobby_MakeRoom_Success(void);
	virtual ~Popup_Lobby_MakeRoom_Success(void);

	//< 초기화
	virtual void init( void );
	//< 업데이트
	virtual void update( POINT mousePos );
	//< 랜더
	virtual void render( HDC hdc );
	//< 지우기
	virtual void release( void );

	//< 이벤트처리
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

public :
	//< 이미지 불러오기
	virtual void loadImage( void );

	//< 외부렉트 받기
	virtual RECT getRect( void )
	{
		return rect;
	}

	//< 씬정보 받기
	virtual int getNextScene( void )
	{
		return button_STATE;
	}

	//< 씬정보 
	virtual void inNextScene( void )
	{
		button_STATE = POPUP_NONE;
	}

private :

	//< 배경 이미지( 어둡게 )
	ImageNode *alpaImage;

	//< 팝업창 이미지
	PopupBox *popupImage;
	//< 렉트
	RECT rect;

	//< 버튼
	ButtonClass *button_OK;
	int button_STATE;

	//< 방 할당 명령
	bool makeRoom;

	//< 폰트
	MY_FontMgr *font;
};

