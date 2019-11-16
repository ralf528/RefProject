#include "stdafx.h"
#include <Vfw.h>
#include "SceneIntro.h"

SceneIntro::SceneIntro(void)
{

}
SceneIntro::~SceneIntro(void)
{
	//< 지우기
	release();
}

//< 초기화
bool SceneIntro::init( void ) 
{
	/*m_mci.LoadMovie("Data/movie/intro.wmv");
	m_mci.PlayMovie();*/

	return true;
}
//< 업데이트
void SceneIntro::update( void ) 
{
}
//< 랜더
void SceneIntro::render( HDC hdc ) 
{

}
//< 해제
void SceneIntro::release( void ) 
{

}

//< 이벤트처리
LRESULT	SceneIntro::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
		//< 키보드 입력받기
	case WM_KEYDOWN:
		switch(wparam)
		{
			//< 엔터키 입력
		case VK_ESCAPE:
			//m_mci.ReleaseMovie();
			//씬 추가
			//STATE_MGR->addState<SceneLogin>(SCENE_LOGIN);
			//씬 선택
			STATE_MGR->changeState( SCENE_LOGIN );
			//< 현재 씬 삭제
			STATE_MGR->deleteState( SCENE_INTRO );
			break;
		}
	case MCIWNDM_NOTIFYMODE:
		{
			switch( lparam )
			{
			case MCI_MODE_STOP:
				{
					//< 동영상 다 보면 로그인 씬으로
					//m_mci.ReleaseMovie();
					//씬 추가
					//STATE_MGR->addState<SceneLogin>(SCENE_LOGIN);
					////씬 선택
					//STATE_MGR->changeState( SCENE_LOGIN );
					////< 현재 씬 삭제
					//STATE_MGR->deleteState( SCENE_INTRO );
				}
				break;
			}
		}
	}
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}