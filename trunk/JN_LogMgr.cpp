#include "stdafx.h"
#include <MMSystem.h>
#include "JN_LogMgr.h"

JN_LogMgr::JN_LogMgr( void )
{
	m_wndLog		= NULL;
	m_wndListBox	= NULL;
	m_filename[0]	= NULL;
	m_parent		= NULL;
	m_target		= JN_LOG_NONE;		
}

JN_LogMgr::~JN_LogMgr( void )
{
	Release();
}

///< 로그창 설정
 void 	JN_LogMgr::logInit(unsigned int target, HWND parentWnd, const char* fileName)
{
	m_target = target;

	if( target & JN_LOG_FILE && NULL != fileName  )
	{
		strcpy_s( m_filename, MAX_PATH, fileName );
	}
	else
	{
		m_filename[0] = NULL;
	}
#ifdef _DEBUG
	if( target & JN_LOG_WINDOW )
	{
		createLogWindow(parentWnd);
	}
#endif
	if( parentWnd != NULL )
	{
		m_parent = parentWnd;
	}

	addLog( "=== Begin Log === " );
}

///< 로그찍기
int		 JN_LogMgr::addLog(char* strmsg, ... )
{
	char	szBuff[1024];
	char	szDate[128];
	char	szTime[128];

	_strdate_s( szDate );
	_strtime_s( szTime );
	vsprintf_s( szBuff, strmsg, (char *)(&strmsg+1) );

	// Console에 출력할 경우 
	if( m_target & JN_LOG_CONSOLE )
	{
		printf( "(date[%s] time[%s]) : %s\n", szDate, szTime, szBuff );
	}

	// Log File에 출력할 경우
	if( m_target & JN_LOG_FILE )
	{
		errorFile("(date[%s] time[%s]) : %s\n",szDate, szTime, szBuff );
	}

#ifdef _DEBUG
	// Log Window에 출력할 경우 
	if( m_target & JN_LOG_WINDOW )
	{
		TCHAR MessageBuffer[1024] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szBuff, int(strlen(szBuff)), MessageBuffer, 1024);

		SendMessage( m_wndListBox, LB_ADDSTRING, 0, (LPARAM)MessageBuffer);
		LRESULT n = SendMessage( m_wndListBox, LB_GETCOUNT, 0, 0L ) - 1;
		SendMessage( m_wndListBox, LB_SETCURSEL, (WPARAM)n, 0L );

		//< 부모 확인
		if( m_parent != NULL )
		{
			SetFocus( m_parent );
			//SendMessage( m_parent, WM_SETFOCUS, TRUE , 0 );
		}
	}
#endif

	return 1;
}

 void  JN_LogMgr::Release( void )
{
	if( m_wndLog != NULL )
	{
		DestroyWindow( m_wndLog );
	}
}

///< 출력창에 에러 출력 
 void  JN_LogMgr::errorOutput(char* strmsg, ...)
{
	char szBuf[256];
	va_list list;				///< 리스트 변수를 선언한다.

	va_start(list,strmsg);			///< 포맷에 시작
	vsprintf_s(szBuf,strmsg,list);	///< 맞게 자르기 
	va_end(list);				///< 리스트 끝 

	//::OutputDebugStr(szBuf);
	//::OutputDebugStr("\n");
}

///< 메세지박스로 에러 출력 
 void  JN_LogMgr::errorMsgBox(char* strmsg, ...)
{
	char szBuf[256];
	va_list list;				///< 리스트 변수를 선언한다.

	va_start(list,strmsg);			///< 포맷에 시작
	vsprintf_s(szBuf,strmsg,list);	///< 맞게 자르기 
	va_end(list);				///< 리스트 끝 
	
    LPCWSTR buf[256];
    memcpy(buf, szBuf, 256);

#ifdef _DEBUG
    //::MessageBox(NULL, *buf, "Error", MB_ICONERROR | MB_OK);
#else
	///< Release모드이면 에러를 파일로 출력한다.
	errorFile(szBuf);
#endif
}

///< 파일로 에러 메세지 저장 
 void  JN_LogMgr::errorFile(char* strmsg, ...)
{
	///< 기존에 파일이 있으면 
	SYSTEMTIME		st;
	GetLocalTime(&st);
	char szBuf[256];

	///< 로그가 파일 타입
	if( m_target & JN_LOG_FILE )
	{
		//wsprintf(szBuf,"%s.txt",m_filename);
	}
	else
	{
		//wsprintf(szBuf,"ERROR_LOG_%d년%d월%d일.txt",st.wYear,st.wMonth,st.wDay);
	}
	
	string a;

	///< c형 스타일의 파일입출력 
	///< 기존에 오늘날짜에 대한 파일이 있는지 확인한다.
	FILE*		fp = NULL;
	fopen_s(&fp,szBuf,"a");

	///< 에러 처리 
	if( fp == NULL )
	{
		//errorMsgBox("에러 파일로 저장 실패");
		return;	
	}
	///< 있으면 이어 붙이기 한다.
	else
	{
		///< 저장 
		char	buffer[256];
		va_list list;				///< 리스트 변수를 선언한다.

		va_start(list,strmsg);			///< 포맷에 시작
		vsprintf_s(buffer,strmsg,list);	///< 맞게 자르기 
		va_end(list);				///< 리스트 끝 
		fprintf(fp,"%s\n",buffer);
	}

	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─- , Janus. 로그 윈도우 생성 ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 void 	 JN_LogMgr::createLogWindow(HWND hWnd)
{
	int			x, y, cx, cy;
	WNDCLASS	wc;
	RECT		rc;

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC)JN_LogMgr::wndLogProc;
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= GetModuleHandle( NULL );
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH) ;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= L"LogWin";

	RegisterClass(&wc);

	///< 메인 윈도우
	RECT	rcWin;

	GetWindowRect( GAME_MGR->GetHwnd() ,&rcWin);

	cx = JN_LOG_WINDOW_CX;
	cy = JN_LOG_WINDOW_CY;
	x = rcWin.right + 8;
	y = rcWin.top + 5;

	/// GetModuleHandle( NULL )
	HWND		hParenthWnd = NULL;
	HINSTANCE	hInst  = NULL;
	if( hWnd == NULL )
	{
		hParenthWnd = NULL;
		hInst		= GetModuleHandle( NULL );
	}
	else 
	{
		hParenthWnd = hWnd;
		hInst		= GetModuleHandle( L"Janus" );
	}

	m_wndLog = CreateWindow( 
		L"LogWin", 
		JN_LOG_WINDOW_TITLE,
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL,
		hInst, NULL );

	GetClientRect( m_wndLog, &rc );
	m_wndListBox = CreateWindow( L"listbox", L"", WS_CHILD | WS_VSCROLL , 0, 0, rc.right, rc.bottom, m_wndLog, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( m_wndLog, SW_SHOW );
	ShowWindow( m_wndListBox, SW_SHOW );
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─- , Janus. 로그 윈도우 메세지 프로시져 ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK JN_LogMgr::wndLogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}