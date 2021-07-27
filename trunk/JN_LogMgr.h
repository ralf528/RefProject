#pragma once

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// File		: JN_LogMgr
// Desc		: 싱글톤으로 구현된 로그 클래스 - 에러 및 로그관련 출력을 담당
//				MessageBox,File,Console,Window등으로 출력이 가능
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <windows.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace std;

///< 로그 출력 타입 
#define JN_LOG_NONE				0x00000000
#define JN_LOG_CONSOLE			0x00000001
#define JN_LOG_FILE				0x00000002
#define JN_LOG_WINDOW			0x00000004
#define JN_LOG_ALL				( JN_LOG_CONSOLE | JN_LOG_FILE | JN_LOG_WINDOW)
#define JN_LOG_WINDOW_TITLE		L"Log..."
#define JN_LOG_WINDOW_CX		250
#define JN_LOG_WINDOW_CY		768

///< 로그윈도우 타입
enum HWND_TYPE
{
	LOG_TYPE_WIN = 0,
	LOG_TYPE_LIST_BOX,
	LOG_TYPE_END
};

#include "Singleton.h"

class JN_LogMgr 
{
private:
	JN_LogMgr( void );
	~JN_LogMgr( void );
	//< 싱글톤으로
	SINGLETON(JN_LogMgr);

public:
	//< 로그창 설정
	void 					logInit(unsigned int target, HWND parentWnd = NULL, const char* fileName = NULL);
	//< 로그찍기
	int						addLog(char* strmsg, ... );
	//< 출력창에 에러 출력 
	void 					errorOutput(char* strmsg, ...);
	//< 메세지박스로 에러 출력 
	void 					errorMsgBox(char* strmsg, ...);
	//< 파일로 에러 메세지 저장 
	void 					errorFile(char* strmsg, ...);
	//< 정리
	void 					Release(  void  );

private:
	//< 로그 윈도우 생성
	 void 					createLogWindow(HWND hWnd = NULL);
	//< 로그 윈도우 메세지 프로시져
	static	LRESULT CALLBACK	 wndLogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
	unsigned int				m_target;
	char						m_filename[MAX_PATH];
	HWND						m_wndLog;
	HWND						m_wndListBox;
	HWND						m_parent;
};

/*
	사용방법 : logInit을 호출하고 인자로 사용할 타겟을 지정하면 로그를 사용할수있다.
	추가로 로그를 넣고 싶을때는 addLog함수를 호출하면된다.
*/

//< 로그매니져
#define		LOG_MGR		Singleton<JN_LogMgr>::GetInstance()