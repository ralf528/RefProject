#include "stdafx.h"
#include "ImageNode.h"
#include "MY_FontMgr.h"
#include "tileMap.h"
#include "myUTIL.h"
#include "GameMgr.h"

using namespace myUTIL;



GameMgr::GameMgr(void)
{
}

GameMgr::~GameMgr(void)
{
	release();
}

//< �ʱ�ȭ
bool GameMgr::init( void )
{
	//< �ڵ�üũ
	if( NULL == g_hWnd || NULL == g_hInst )
	{
		return false;
	}
	//< ����
	m_mainWnd = g_hWnd;
	m_mainInstance = g_hInst;

	//���ʱ�ȭ
	MAP_EDITER->init();

	//< ī�޶� �ʱ�ȭ
	CAMERA->init();

	//< ���� �߻��� �ʱ�ȭ
	srand(GetTickCount());

	//////////////////////////////////////////////////////////////////////////
	//< �α������� 
#ifdef _DEBUG
	LOG_MGR->logInit( JN_LOG_ALL );
#endif
	//< ��ξ��
	GetCurrentDirectory( _MAX_FNAME, m_path );

	keyInput::initKey();

	//���� �Ŵ��� �ʱ�ȭ & �� ���� �̹��� ����
	RENDER_MGR->init();

	//< Ÿ�̸� ����
	SetTimer( m_mainWnd, 1 , 10 , NULL );
	
	//< �޼��������� : �̰ɺ����������Ʈ�� ������ ����ȴ�.(�ʱ�ȭ������ȣ���ض�)
	SendMessage( m_mainWnd, WM_TIMER , 1, 0 );

#ifdef _DEBUG
	LOG_MGR->addLog("������ ����");
#endif
	return true;
}

//< ����
void GameMgr::release( void )
{	
	KillTimer( m_mainWnd, 1 );
}

//< ������Ʈ
void GameMgr::update( void )
{
	//< ī�޶� ������Ʈ
	CAMERA->update();

	//�귯�� ��ȯ
	if( keyInput::onceKeyDown( 'W' ) )
	{
		MAP_EDITER->nextBrush();
	}
	if( keyInput::onceKeyDown( 'Q' ) )
	{
		MAP_EDITER->prevBrush();
	}
	//< �� ����
	MAP_EDITER->update();

	//< ȭ�鰻��
	InvalidateRect( m_mainWnd, NULL, FALSE );
}
//< ����
void GameMgr::render( void )
{
	//< ȭ�� Ŭ����
	RENDER_MGR->clearBack();

	HDC backDC = RENDER_MGR->getBackDC();

	//< Ÿ�ϸ� ���
	MAP_EDITER->render( backDC );

	//< ������
	//TextOut( backDC, 0,0, m_path, strlen(m_path));

	//< ����
	//char buf[ _MAX_FNAME ];
	//sprintf_s( buf, _MAX_FNAME,"x :%d , y : %d",m_mousePos.x, m_mousePos.y );
	//TextOut( backDC,0,13,buf,strlen(buf));

	//< ���콺 ��ġ ���
	char buff[50];
	sprintf_s( buff,50, "X = %d", m_mousePos.x/TILE_SIZE_X );
	TextOut( backDC, 700,0, buff, lstrlen(buff) ); 
	sprintf_s( buff,50, "Y = %d", m_mousePos.y/TILE_SIZE_Y );
	TextOut( backDC, 780,0, buff, lstrlen(buff) ); 

	//< �������� �׷��� ����۸� ���
	RENDER_MGR->renderFrame();
}

//< �޽�������
WPARAM GameMgr::msgLoop( void )
{
	//< ����������
	HACCEL hAccel;
	hAccel = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	MSG			Message;		//�޼��� ����ü ����	
	//<GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterCrazy, UINT wMsgFilterMAx)�޽���ť���� �о����  �޼����� WM_QUIT�� false ���� �������� true ����
	//<lpMsg : �޽����� �ּ�
	//<hWnd : �������� �ڵ� 0�̸� ��� �������� �޽����� ��������, �ڵ� ���� �����ϸ� ���ڵ鰪�� ���Ե� �޽����� �����´�.
	//<wMsgFilterCrazy, wMsgFilterMAx : �޽����� �о���� ���� �ּҰ� �ִ밪(����Ұ�� �ý����� ���ѷ����� ������ �ִ�.)
	//< 4 �޼��� ����(����ڷκ����� �޽����� ó���Ѵ� !�޽��� �����ý���)
	while(GetMessage(&Message,0,0,0))
	{
		if(!TranslateAccelerator(g_hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);// Ű���� �Է� �޽����� �����Ѵ�(a���  Ű�� �������� a��� Ű�� ���ȴٴ� �޼����� ������.)
			DispatchMessage(&Message); // �޽����� ������ ���ν����Լ��� ȣ���ϴ� ��Ȱ 
		}
	}

	return Message.wParam;
}

//< ���ν���
LRESULT GameMgr::WndProc(HWND wnd ,UINT msg ,WPARAM wparam, LPARAM lparam )
{
	PAINTSTRUCT	ps;

	switch(msg)
	{
	//< ��Ŀ��ó��
	case WM_SETFOCUS:
		{
			window::setFocusMainWindow( true );
		}
		break;
	case WM_KILLFOCUS:
		{
			window::setFocusMainWindow( false );
		}
		break;
	case WM_TIMER:
		update();
		break;

	case WM_PAINT:
		BeginPaint(wnd, &ps);
		render();
		EndPaint(wnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		{
			m_mousePos.x = LOWORD(lparam);
			m_mousePos.y = HIWORD(lparam);
			myUTIL::keyInput::setMousePos(&m_mousePos);
		}
		break;

	case WM_COMMAND:
		{
			switch( LOWORD( wparam ) )
			{
			case ID_FILE_NEWMAP:
				DialogBox( g_hInst, MAKEINTRESOURCE(IDD_DIALOG_NewMap), wnd, newMapDlgProc );
				break;

			case ID_FILE_SAVEMAP:
				//< �� ���̺�
				MAP_EDITER->saveMap("testMap.txt");
				MessageBox( wnd, "����Ǿ����ϴ�.", "Success Save", MB_OK );
				break;

			case ID_FILE_ASSAVE:
				break;

			case ID_FILE_LOADMAP:
				//< �� �ε�
				MAP_EDITER->loadMap( "testMap.txt" );
				MessageBox( wnd, "�ҷ��Խ��ϴ�.", "Success Load", MB_OK );
				break;

			case ID_FILE_EXIT:
				if( IDOK == MessageBox( wnd, "�����Ͻðڽ��ϱ�?", "Exit", MB_OKCANCEL ) )
				{
					SendMessage( wnd, WM_DESTROY, NULL, NULL );
					break;
				}
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	//< wndProc���� ó�� ���� ���� ������ �޽������� ó�����ش�.
	//< ������ũ�� �����̳�, �̵� � ó�����ش�.
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< ���̾�α� ���ν���
BOOL CALLBACK newMapDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch( msg )
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDOK:
			{
				//< ����Ʈ ��Ʈ���� ���� �޾ƿ�
				int width = GetDlgItemInt( hDlg, IDC_EDIT_WIDTH, NULL, FALSE );
				int height= GetDlgItemInt( hDlg, IDC_EDIT_HEIGHT, NULL, FALSE );
				
				//< ���ο� �� ����
				MAP_EDITER->newMap( width, height );

				EndDialog(hDlg, IDOK);
				return TRUE;
			}
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}