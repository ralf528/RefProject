#pragma once
/*
	프로젝트에 공용으로 사용되는 함수
*/
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
		bool	moveToPt(POINT *originPos, POINT *destPos,float speed = 3.f);
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
	}//keyInput
	
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	// ☆━─ 2015.04, FPS 타이머, Ackashic. ─━☆
	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	namespace FpsTime
	{
		//< 초기화
		void initFpsTime(void);
		//< 해제
		void releaseFpsTime(void);
		//< 프로그램 시작 후 흘러간 전체 시간 얻기
		float getWorldTime(void);
		//< 프레임당 경과시간( 한 프레임 )
		float getElapsedTime(void);
		//< 프레임 타임 업데이트( 기본 FPS 60 )
		void fpsTimeUpdate( float fLock = 60.0f );
		//< 프레임 렌더링 하기
		void renderFps( HDC hdc, unsigned long textColor = RGB(0,0,0) );
		//< 시간 동기화 변수
		float getTimeRate( void );
	};

	namespace animation
	{
		//애니메이션 설정
		void setAniInfo( unsigned int imgID, LPANI_INFO aniInfo, bool startFlag, bool loop, bool playContinue, int cx, int cy = 1, int aniSpeed = 50);
		//갱신
		void updateAni( LPANI_INFO aniInfo );
	}

}//< namespace end