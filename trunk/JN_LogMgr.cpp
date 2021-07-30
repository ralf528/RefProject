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

///< �α�â ����
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

///< �α����
int		 JN_LogMgr::addLog(char* strmsg, ... )
{
	char	szBuff[1024];
	char	szDate[128];
	char	szTime[128];

	_strdate_s( szDate );
	_strtime_s( szTime );
	vsprintf_s( szBuff, strmsg, (char *)(&strmsg+1) );

	// Console�� ����� ��� 
	if( m_target & JN_LOG_CONSOLE )
	{
		printf( "(date[%s] time[%s]) : %s\n", szDate, szTime, szBuff );
	}

	// Log File�� ����� ���
	if( m_target & JN_LOG_FILE )
	{
		errorFile("(date[%s] time[%s]) : %s\n",szDate, szTime, szBuff );
	}

#ifdef _DEBUG
	// Log Window�� ����� ��� 
	if( m_target & JN_LOG_WINDOW )
	{
		TCHAR MessageBuffer[1024] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szBuff, int(strlen(szBuff)), MessageBuffer, 1024);

		SendMessage( m_wndListBox, LB_ADDSTRING, 0, (LPARAM)MessageBuffer);
		LRESULT n = SendMessage( m_wndListBox, LB_GETCOUNT, 0, 0L ) - 1;
		SendMessage( m_wndListBox, LB_SETCURSEL, (WPARAM)n, 0L );

		//< �θ� Ȯ��
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

///< ���â�� ���� ��� 
 void  JN_LogMgr::errorOutput(char* strmsg, ...)
{
	char szBuf[256];
	va_list list;				///< ����Ʈ ������ �����Ѵ�.

	va_start(list,strmsg);			///< ���˿� ����
	vsprintf_s(szBuf,strmsg,list);	///< �°� �ڸ��� 
	va_end(list);				///< ����Ʈ �� 

	//::OutputDebugStr(szBuf);
	//::OutputDebugStr("\n");
}

///< �޼����ڽ��� ���� ��� 
 void  JN_LogMgr::errorMsgBox(char* strmsg, ...)
{
	char szBuf[256];
	va_list list;				///< ����Ʈ ������ �����Ѵ�.

	va_start(list,strmsg);			///< ���˿� ����
	vsprintf_s(szBuf,strmsg,list);	///< �°� �ڸ��� 
	va_end(list);				///< ����Ʈ �� 
	
    LPCWSTR buf[256];
    memcpy(buf, szBuf, 256);

#ifdef _DEBUG
    //::MessageBox(NULL, *buf, "Error", MB_ICONERROR | MB_OK);
#else
	///< Release����̸� ������ ���Ϸ� ����Ѵ�.
	errorFile(szBuf);
#endif
}

///< ���Ϸ� ���� �޼��� ���� 
 void  JN_LogMgr::errorFile(char* strmsg, ...)
{
	///< ������ ������ ������ 
	SYSTEMTIME		st;
	GetLocalTime(&st);
	char szBuf[256];

	///< �αװ� ���� Ÿ��
	if( m_target & JN_LOG_FILE )
	{
		//wsprintf(szBuf,"%s.txt",m_filename);
	}
	else
	{
		//wsprintf(szBuf,"ERROR_LOG_%d��%d��%d��.txt",st.wYear,st.wMonth,st.wDay);
	}
	
	string a;

	///< c�� ��Ÿ���� ��������� 
	///< ������ ���ó�¥�� ���� ������ �ִ��� Ȯ���Ѵ�.
	FILE*		fp = NULL;
	fopen_s(&fp,szBuf,"a");

	///< ���� ó�� 
	if( fp == NULL )
	{
		//errorMsgBox("���� ���Ϸ� ���� ����");
		return;	
	}
	///< ������ �̾� ���̱� �Ѵ�.
	else
	{
		///< ���� 
		char	buffer[256];
		va_list list;				///< ����Ʈ ������ �����Ѵ�.

		va_start(list,strmsg);			///< ���˿� ����
		vsprintf_s(buffer,strmsg,list);	///< �°� �ڸ��� 
		va_end(list);				///< ����Ʈ �� 
		fprintf(fp,"%s\n",buffer);
	}

	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}
}

//������������������������������������������������������������������������������������
// �٦���- , Janus. �α� ������ ���� ������
//������������������������������������������������������������������������������������
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

	///< ���� ������
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

//������������������������������������������������������������������������������������
// �٦���- , Janus. �α� ������ �޼��� ���ν��� ������
//������������������������������������������������������������������������������������
LRESULT CALLBACK JN_LogMgr::wndLogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}