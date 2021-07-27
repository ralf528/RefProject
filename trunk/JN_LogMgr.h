#pragma once

//������������������������������������������������������������������������������������
// File		: JN_LogMgr
// Desc		: �̱������� ������ �α� Ŭ���� - ���� �� �αװ��� ����� ���
//				MessageBox,File,Console,Window������ ����� ����
//������������������������������������������������������������������������������������
#include <windows.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace std;

///< �α� ��� Ÿ�� 
#define JN_LOG_NONE				0x00000000
#define JN_LOG_CONSOLE			0x00000001
#define JN_LOG_FILE				0x00000002
#define JN_LOG_WINDOW			0x00000004
#define JN_LOG_ALL				( JN_LOG_CONSOLE | JN_LOG_FILE | JN_LOG_WINDOW)
#define JN_LOG_WINDOW_TITLE		L"Log..."
#define JN_LOG_WINDOW_CX		250
#define JN_LOG_WINDOW_CY		768

///< �α������� Ÿ��
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
	//< �̱�������
	SINGLETON(JN_LogMgr);

public:
	//< �α�â ����
	void 					logInit(unsigned int target, HWND parentWnd = NULL, const char* fileName = NULL);
	//< �α����
	int						addLog(char* strmsg, ... );
	//< ���â�� ���� ��� 
	void 					errorOutput(char* strmsg, ...);
	//< �޼����ڽ��� ���� ��� 
	void 					errorMsgBox(char* strmsg, ...);
	//< ���Ϸ� ���� �޼��� ���� 
	void 					errorFile(char* strmsg, ...);
	//< ����
	void 					Release(  void  );

private:
	//< �α� ������ ����
	 void 					createLogWindow(HWND hWnd = NULL);
	//< �α� ������ �޼��� ���ν���
	static	LRESULT CALLBACK	 wndLogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
	unsigned int				m_target;
	char						m_filename[MAX_PATH];
	HWND						m_wndLog;
	HWND						m_wndListBox;
	HWND						m_parent;
};

/*
	����� : logInit�� ȣ���ϰ� ���ڷ� ����� Ÿ���� �����ϸ� �α׸� ����Ҽ��ִ�.
	�߰��� �α׸� �ְ� �������� addLog�Լ��� ȣ���ϸ�ȴ�.
*/

//< �α׸Ŵ���
#define		LOG_MGR		Singleton<JN_LogMgr>::GetInstance()