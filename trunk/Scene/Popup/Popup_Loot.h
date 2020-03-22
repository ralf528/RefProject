#pragma once

class InputString;

//< 팝업창 추상클래스
class Popup_Loot
{
public:
	Popup_Loot(void);
	virtual ~Popup_Loot(void);

	//< 초기화
	virtual void init( void ) = 0;
	//< 업데이트
	virtual void update( POINT mousePos ) = 0;
	//< 랜더
	virtual void render( HDC hdc ) = 0;
	//< 지우기
	virtual void release( void ) = 0;

	//< 이벤트처리
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam ) = 0;

public :
	//< 이미지 불러오기
	virtual void loadImage( void ) = 0;

	//< 외부렉트 받기
	virtual RECT getRect( void ) = 0;

	//< 씬정보 받기
	virtual int getNextScene( void ) = 0;

	//< 씬정보 
	virtual void inNextScene( void ) = 0;
};

