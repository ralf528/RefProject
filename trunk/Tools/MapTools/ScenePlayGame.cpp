#include "stdafx.h"
#include "ImageNode.h"
#include "MY_FontMgr.h"
#include "tileMap.h"
#include "ScenePlayGame.h"

using namespace myUTIL;
using namespace keyInput;
using namespace collision;

ScenePlayGame::ScenePlayGame(void)
	:m_playingGame(true)
{
}

ScenePlayGame::~ScenePlayGame(void)
{
	release();
}

//< 초기화
bool ScenePlayGame::init( void ) 
{	
	//맵초기화
	m_map = new tileMap;
	m_map->init();

	//< 카메라 초기화
	CAMERA->init();

#ifdef _DEBUG
		LOG_MGR->addLog("%s", "플레이씬 초기화" );
#endif
	return true;
}
//< 업데이트
void ScenePlayGame::update( void ) 
{
}

//< 랜더
void ScenePlayGame::render( HDC hdc )
{
	if( NULL != hdc )
	{
		//< 타일맵 출력
		m_map->render( hdc );
	}
}
//< 해제
void ScenePlayGame::release( void ) 
{
	SAFE_DELETE( m_map );
}

//< 이벤트처리
LRESULT ScenePlayGame::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_COMMAND:
		{
			switch( LOWORD( wparam ) )
			{
			case ID_FILE_NEWMAP:
				//< 새로운 맵 생성
				m_map->newMap( 10, 10 );
				break;
				
			case ID_FILE_SAVEMAP:
				//< 맵 세이브
				m_map->saveMap("textMap.txt");
				break;

			case ID_FILE_ASSAVE:
				break;

			case ID_FILE_LOADMAP:
				//< 맵 로드
				m_map->loadMap( START_LOAD_MAP_PATH );
				break;

			case ID_FILE_EXIT:
				SendMessage( wnd, WM_DESTROY, NULL, NULL );
				break;
			}
		}
		break;

	case WM_KEYDOWN:
		{
			switch( wparam )
			{
			case VK_ESCAPE:
				//pause
				m_playingGame=false;
				break;

			}
			break;
		}
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}