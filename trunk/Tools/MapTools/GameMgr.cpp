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

//< 초기화
bool GameMgr::init( void )
{
	//< 핸들체크
	if( NULL == g_hWnd || NULL == g_hInst )
	{
		return false;
	}
	//< 보관
	m_mainWnd = g_hWnd;
	m_mainInstance = g_hInst;

	//맵초기화
	MAP_EDITER->init();

	//< 카메라 초기화
	CAMERA->init();

	//< 난수 발생기 초기화
	srand(GetTickCount());

	//////////////////////////////////////////////////////////////////////////
	//< 로그윈도우 
#ifdef _DEBUG
	LOG_MGR->logInit( JN_LOG_ALL );
#endif
	//< 경로얻기
	GetCurrentDirectory( _MAX_FNAME, m_path );

	keyInput::initKey();

	//랜더 매니저 초기화 & 백 버퍼 이미지 생성
	RENDER_MGR->init();

	//< 타이머 생성
	SetTimer( m_mainWnd, 1 , 10 , NULL );
	
	//< 메세지보내기 : 이걸보내면업데이트가 강제로 수행된다.(초기화다음에호출해라)
	SendMessage( m_mainWnd, WM_TIMER , 1, 0 );

#ifdef _DEBUG
	LOG_MGR->addLog("윈도우 시작");
#endif
	return true;
}

//< 해제
void GameMgr::release( void )
{	
	KillTimer( m_mainWnd, 1 );
}

//< 업데이트
void GameMgr::update( void )
{
	//< 카메라 업데이트
	CAMERA->update();

	//브러쉬 변환
	if( keyInput::onceKeyDown( 'W' ) )
	{
		MAP_EDITER->nextBrush();
	}
	if( keyInput::onceKeyDown( 'Q' ) )
	{
		MAP_EDITER->prevBrush();
	}
	//< 맵 갱신
	MAP_EDITER->update();

	//< 화면갱신
	InvalidateRect( m_mainWnd, NULL, FALSE );
}
//< 렌더
void GameMgr::render( void )
{
	//< 화면 클리어
	RENDER_MGR->clearBack();

	HDC backDC = RENDER_MGR->getBackDC();

	//< 타일맵 출력
	MAP_EDITER->render( backDC );

	//< 실행경로
	//TextOut( backDC, 0,0, m_path, strlen(m_path));

	//< 조합
	//char buf[ _MAX_FNAME ];
	//sprintf_s( buf, _MAX_FNAME,"x :%d , y : %d",m_mousePos.x, m_mousePos.y );
	//TextOut( backDC,0,13,buf,strlen(buf));

	//< 마우스 위치 출력
	char buff[50];
	sprintf_s( buff,50, "X = %d", m_mousePos.x/TILE_SIZE_X );
	TextOut( backDC, 700,0, buff, lstrlen(buff) ); 
	sprintf_s( buff,50, "Y = %d", m_mousePos.y/TILE_SIZE_Y );
	TextOut( backDC, 780,0, buff, lstrlen(buff) ); 

	//< 프레임이 그려진 백버퍼를 출력
	RENDER_MGR->renderFrame();
}

//< 메시지루프
WPARAM GameMgr::msgLoop( void )
{
	//< 엑셀레이터
	HACCEL hAccel;
	hAccel = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	MSG			Message;		//메세지 구조체 선언	
	//<GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterCrazy, UINT wMsgFilterMAx)메시지큐에서 읽어들인  메세지가 WM_QUIT면 false 리턴 나머지는 true 리턴
	//<lpMsg : 메시지의 주소
	//<hWnd : 윈도우의 핸들 0이면 모든 윈도우의 메시지를 가져오고, 핸들 값을 지정하면 그핸들값에 포함된 메시지만 가져온다.
	//<wMsgFilterCrazy, wMsgFilterMAx : 메시지를 읽어들일 범위 최소값 최대값(사용할경우 시스템이 무한루프에 빠질수 있다.)
	//< 4 메세지 루프(사용자로부터의 메시지를 처리한다 !메시지 구동시스템)
	while(GetMessage(&Message,0,0,0))
	{
		if(!TranslateAccelerator(g_hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);// 키보드 입력 메시지를 관리한다(a라는  키가 눌렸을때 a라는 키가 눌렸다는 메세지를 만들어낸다.)
			DispatchMessage(&Message); // 메시지를 가지고 프로시져함수를 호출하는 역활 
		}
	}

	return Message.wParam;
}

//< 프로시져
LRESULT GameMgr::WndProc(HWND wnd ,UINT msg ,WPARAM wparam, LPARAM lparam )
{
	PAINTSTRUCT	ps;

	switch(msg)
	{
	//< 포커스처리
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
				//< 맵 세이브
				MAP_EDITER->saveMap("testMap.txt");
				MessageBox( wnd, "저장되었습니다.", "Success Save", MB_OK );
				break;

			case ID_FILE_ASSAVE:
				break;

			case ID_FILE_LOADMAP:
				//< 맵 로드
				MAP_EDITER->loadMap( "testMap.txt" );
				MessageBox( wnd, "불러왔습니다.", "Success Load", MB_OK );
				break;

			case ID_FILE_EXIT:
				if( IDOK == MessageBox( wnd, "종료하시겠습니까?", "Exit", MB_OKCANCEL ) )
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

	//< wndProc에서 처리 되지 않은 나머지 메시지들을 처리해준다.
	//< 윈도우크기 변경이나, 이동 등를 처리해준다.
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}

//< 다이얼로그 프로시저
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
				//< 에디트 컨트롤의 값을 받아옴
				int width = GetDlgItemInt( hDlg, IDC_EDIT_WIDTH, NULL, FALSE );
				int height= GetDlgItemInt( hDlg, IDC_EDIT_HEIGHT, NULL, FALSE );
				
				//< 새로운 맵 생성
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