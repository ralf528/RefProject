#include "stdafx.h"

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ��������, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������
HINSTANCE	g_hInst;								//�ν��Ͻ� �ڵ� ���� (�ü������ ������ ��ȣ)
HWND		g_hWnd;									//������ �ڵ� ���� (�����츦 ��ǥ�ϴ� ��ȣ)
//< �������ڿ�
TCHAR  		g_ClassName[128] = _T("Ackashic");		//Ŭ���� �̸�
TCHAR  		g_WinName[128] = _T("Ackashic");		//������ �̸�
//< �޴�
LPCTSTR		lpszClass=TEXT("Menu");

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, �Լ� ������ Ÿ��, Ackashic. ������(�Լ��� ���� ����)
//��������������������������������������������������������������������������������������������������������������
//< ������ ���� �� ���
void	registWnd( void );
//< ������ ���� �� �����ֱ�
bool	createWnd( void );
//< ������ ���ν���
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ������ ���� �Լ�, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������
// apientry			==  winmain�Լ��� ȣ�� ���
// hInstance		==	���α׷��� �ν��Ͻ� �ڵ�(�������� �ü������ ������ �������� �ڵ��ȣ(�������))
// hPrevInstance	==	�ٷ� �տ� ����� ���α׷��� �ν��Ͻ� �ڵ�
// lpszCmdParam		==	���� ���Ŀ� �� ������ ��ΰ� ���޵ȴ�.
// nCmdShow			==  �����츦 ȭ�鿡 ����� ���('�����츦 Ȱ��ȭ �Ͽ� �����ش�'��� �ǹ�, �Ǵ� �����.)
//��������������������������������������������������������������������������������������������������������������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	//< �����ν��Ͻ�
	g_hInst = hInstance;
	
	//< 1. ���� / 2. ��� 
	registWnd();

	//< 3. ���� 
	if( false == createWnd() )
	{
		//< ������ ��������
		return 0;
	}

	//< �ʱ�ȭ
	if( GAME_MGR->init() == false )
	{
		return 0;
	}
	
	//< 4. �����츦 ȭ�鿡 �����ش�
	ShowWindow(g_hWnd, nCmdShow);

	//< 5. �޼��� ����
	WPARAM wparam = GAME_MGR->msgLoop();

	//< ����
	GAME_MGR->release();
		
	return wparam;
}

//< 1. ������ ����, 2. ���
void	registWnd( void )
{
	WNDCLASS	WndClass;		//������ Ŭ���� ����

	//< 1 ������ Ŭ���� �ۼ� (�������� �Ӽ��� ���� �Ѵ�)
	WndClass.cbClsExtra		= 0;									//������� ���������� ����� ���и޸�	
	WndClass.cbWndExtra		= 0;									//������� ���������� ����� ���и޸�
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ����
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//Ŀ���� �����Ѵ�(���ҽ��� ���ؼ� ���ϴ� �׷��ȸ� ��� �Ҽ��� �ִ�)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//�������� �д´�(���ҽ��� ���ؼ� ���ϴ� �׷��ȸ� ��� �Ҽ��� �ִ�)
	WndClass.hInstance		= g_hInst;								//������ Ŭ������ �ν��Ͻ�(�������� �ü������ ������ �������� �ڵ��ȣ(�������))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//������ ���ν����� �̸�(�������� �޽��� ó�� �Լ��� ����)
	WndClass.lpszClassName	= g_ClassName;							//������ Ŭ������ �̸�(�������� Ŭ���� �̸��� ���̴�)
	WndClass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);			//�޴��� �̸�(���ҽ� ������ ���� ������ �������, ����� ���ϸ� NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//�������� ��Ÿ��(�������� ũ�Ⱑ ���Ҷ� �ٽ� �׸���.)

	//< 2 Ŭ������ ����Ѵ� (������ ������ Ŭ������ ����Ѵ�)
	RegisterClass(&WndClass);								
}

//< 3. ������ ����
bool	createWnd( void )
{
	//< ������â ũ�� �����.
	int width = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 4;
	int hegith = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 4 +
		GetSystemMetrics(SM_CYCAPTION);
	
	//< ������â �߾����� ���� �����
	int screenX = GetSystemMetrics( SM_CXSCREEN );
	int screenY = GetSystemMetrics( SM_CYSCREEN );
	int startX = screenX / 2 - WINSIZE_X/2;
	int startY = screenY / 2 - WINSIZE_Y/2;
	
	//< 3 �����츦 ����� (�޸� �� �����츦 �����Ѵ�)
	g_hWnd = CreateWindow(g_ClassName,				// ������Ŭ���� ���ڿ� 
		g_WinName,									// Ÿ��Ʋ�ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,						// �������� ���� �ɼ�(OR ������ ���)Ÿ��Ʋ��, ��ũ�ѹ�, ũ���������� ���
		startX, startY,								// ������ ������ġ
		width, hegith,								// ������ ũ��
		NULL,										// �θ��������� �ڵ� (�θ� �����찡 ���� �ڽ��� �ֻ��� ������ �϶� NULL)
		(HMENU)NULL,								// �޴��� �ڵ� (�޴��� ��� ���ϹǷ� NULL)			
		g_hInst,									// �ν��Ͻ�
		NULL);										// createStruct��� ����ü�� �ּ� (�������� �����츦 ���鶧 ��� �ǳ� ���� ������� �ʴ´�.)

	if( NULL == g_hWnd )
	{
		//< ������ ���� ���� �޼��� ó��
		return false;
	}	

	return true;
}

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ������ ���ν���, Crazy.(�޼��� ó�� �Լ�) ������
//��������������������������������������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam, LPARAM lParam)
{
	return GAME_MGR->WndProc( hWnd, iMessage, wParam,lParam );
}
