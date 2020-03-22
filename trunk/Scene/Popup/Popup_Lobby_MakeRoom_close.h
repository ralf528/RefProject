#pragma once

#include "popup.h"

class ImageNode;
class PopupBox;
class ButtonClass;
class CheckBox;

class Popup_Lobby_MakeRoom_close : public Popup
{
public:
	Popup_Lobby_MakeRoom_close(void);
	virtual ~Popup_Lobby_MakeRoom_close(void);

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
	virtual int getNextScene( void );

	//< 씬정보 
	virtual void inNextScene( void )
	{
		button_STATE = POPUP_NONE;
	}

private :
	//< 버튼상태 판별
	void joinState( void );

private :
	//< 배경 이미지( 어둡게 )
	ImageNode *alpaImage;

	//< 팝업창 이미지
	PopupBox *popupImage;
	//< 렉트
	RECT rect;

	//< 입력 맨트 이미지
	ButtonClass *inputInfo_ID;
	ButtonClass *inputInfo_PASS;
	ButtonClass *inputInfo_REPASS;
	//< 입력칸
	ButtonClass *m_inputID_Board;
	ButtonClass *m_inputPass_Board;

	//< 버튼
	ButtonClass *button_MAKEROOM;
	ButtonClass *button_CANCEL;
	//< 버튼 공개 비공개
	CheckBox *button_OPEN;
	CheckBox *button_CLOSE;
	//< 체크박스(난입)
	CheckBox *checkBox_OK;
	CheckBox *checkBox_NO;
	int button_STATE;

	//< 마우스 포인트
	POINT mousePos;
	
	//< 유저 정보
private :
	//< 방이름
	InputString *inputRoomName;
	//< 방비번
	InputString *inputPass;
	//< 난입 허용 비허용
	bool breakInto;
};

