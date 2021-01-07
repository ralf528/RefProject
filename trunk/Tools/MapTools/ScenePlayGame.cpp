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

//< �ʱ�ȭ
bool ScenePlayGame::init( void ) 
{	
	//���ʱ�ȭ
	m_map = new tileMap;
	m_map->init();

	//< ī�޶� �ʱ�ȭ
	CAMERA->init();

#ifdef _DEBUG
		LOG_MGR->addLog("%s", "�÷��̾� �ʱ�ȭ" );
#endif
	return true;
}
//< ������Ʈ
void ScenePlayGame::update( void ) 
{
}

//< ����
void ScenePlayGame::render( HDC hdc )
{
	if( NULL != hdc )
	{
		//< Ÿ�ϸ� ���
		m_map->render( hdc );
	}
}
//< ����
void ScenePlayGame::release( void ) 
{
	SAFE_DELETE( m_map );
}

//< �̺�Ʈó��
LRESULT ScenePlayGame::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	case WM_COMMAND:
		{
			switch( LOWORD( wparam ) )
			{
			case ID_FILE_NEWMAP:
				//< ���ο� �� ����
				m_map->newMap( 10, 10 );
				break;
				
			case ID_FILE_SAVEMAP:
				//< �� ���̺�
				m_map->saveMap("textMap.txt");
				break;

			case ID_FILE_ASSAVE:
				break;

			case ID_FILE_LOADMAP:
				//< �� �ε�
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