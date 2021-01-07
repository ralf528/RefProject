#pragma once

#include "Singleton.h"

//폰트 매니저
class MY_FontMgr;
//이미지 노드
class ImageNode;
//< 맵
class tileMap;

class GameMgr
{
private:
	GameMgr(void);
	~GameMgr(void);

	//< 싱글톤으로 만들자
	SINGLETON( GameMgr );

public:
	//////////////////////////////////////////////////////////////////////////
	//<외부 인터페이스
	//////////////////////////////////////////////////////////////////////////
	//< 초기화
	bool	init( void );
	//< 업데이트
	void	update( void );
	//< 렌더
	void	render( void );
	//< 해제
	void	release( void );

	//< 메시지루프
	WPARAM	msgLoop( void );
	//< 프로시져
	LRESULT WndProc(HWND wnd ,UINT msg ,WPARAM wparam, LPARAM lparam );

	//< 윈도우 핸들 얻기
	inline HWND			getHwnd(void)		{ return m_mainWnd; }
	//< 메인 윈도우 인스턴스 핸들얻기
	inline HINSTANCE	getInst( void )		{ return m_mainInstance; }

	//< 다이얼로그 프로시저
	friend BOOL CALLBACK newMapDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	//////////////////////////////////////////////////////////////////////////
	//< 내부 함수	
	//////////////////////////////////////////////////////////////////////////
	void	clearScreen( void );

private:
	//////////////////////////////////////////////////////////////////////////
	//< 멤버변수
	//////////////////////////////////////////////////////////////////////////
	//< 메인 윈도우 핸들
	HWND		m_mainWnd;
	HINSTANCE	m_mainInstance;	
	
	//< 실행경로
	char	m_path[ _MAX_FNAME ];

	//< 좌표
	POINT		m_mousePos;
};

//< 전역매니져
#define GAME_MGR	Singleton<GameMgr>::getInstance()
