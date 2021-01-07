#pragma once
/*
	프로젝트에 공용으로 사용되는 함수
*/

enum MOUSE_STATE
{
	MOUSE_BTN_NONE,
	MOUSE_BTN_DOWN,
	MOUSE_BTN_UP,
	MOUSE_BTN_PRESS,
	MOUSE_END,
};

enum MOUSE_BUTTON
{
	MOUSE_LBUTTON,
	MOUSE_RBUTTON,
	MOUSE_MBUTTON,
	MOUSE_BUTTON_END,
};

namespace myUTIL
{
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	// ☆━─ 2015.04, 수학관련, Ackashic. ─━☆
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	namespace math
	{		
		//< 두점사이의 거리
		float	distancePtToPt( const POINT &pt1, const POINT &pt2 );
		//< 점 이동
		void	moveToPt(POINT *originPos, POINT *destPos,float speed = 3.f);
		//< 각도 계산
		float	calcAnglePtToPt(POINT *destPos, POINT *srcPos);
	}//math
	    
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	// ☆━─ 2015.04, 충돌관련, Ackashic. ─━☆
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	namespace collision
	{
		//< 점 사각
		bool	 isColPtInRect( const POINT &pt , const RECT &rc );
		//< 사각 사각
		bool	 isColRectAndRect( const RECT &rc1, const RECT &rc2 );
		//< 원 점
		bool	 isColPtInCircle( const POINT &pt, const RECT &circle );
		//< 원 원
		bool	 isColCirAndCir( const RECT &cir1, const RECT &cir2 );
		//< 원 사각
		bool	 isColCirAndRect( const RECT &cir, const RECT &rc );
		//선과 원의 충돌 체크
		bool	isColLineAndCir( POINT &pos1, POINT &pos2, POINT &center , float r );
	}//collision

	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	// ☆━─ 2015.04, 윈도우 관련, Ackashic. ─━☆
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	namespace window
	{
		//< 포커스처리
		void			setFocusMainWindow( bool focus );
		//< 메인 윈도우포커스확인
		bool			isFocusWindow( void );
	}//window
	
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	// ☆━─ 2015.04, 키입력 관련, Ackashic. ─━☆
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	namespace keyInput
	{
		//< 키모든 플래그 초기화
		void		initKey( void );
		//< 키눌림처리
		bool		isKeyDown( int keyValue );
		//< 플래그확인
		bool		isToggle( int keyValue );
		//< 키 한번 누름처리
		bool		onceKeyDown( int keyValue );
		//< 키 한번 땜처리
		bool		onceKeyUp( int keyValue );

		//////////////////////////////////////////////////////////////////////
		// 마우스
		//////////////////////////////////////////////////////////////////////
		//> 마우스 업데이트
		void mouseUpdate();

		//> 마우스 상태 얻기
		bool getMouseState(const int mouseState);

		//> 마우스 위치 세팅
		void setMousePos(POINT* mousePos);
		//> 마우스 위치 얻기
		POINT getMousePos();

		//> 해당 마우스 버튼 다운 확인
		bool isMouseDown(MOUSE_BUTTON mouseBtn);
		//> 해당 마우스 버튼 업 확인
		bool isMouseUp(MOUSE_BUTTON mouseBtn);
		//> 해당 마우스 버튼 눌림 확인
		bool isMousePress(MOUSE_BUTTON mouseBtn);
	}//keyInput
	
}//< namespace end