#include "stdafx.h"
#include <Vfw.h>
#include "SceneIntro.h"

SceneIntro::SceneIntro(void)
{

}
SceneIntro::~SceneIntro(void)
{
	//< �����
	release();
}

//< �ʱ�ȭ
bool SceneIntro::init( void ) 
{
	/*m_mci.LoadMovie("Data/movie/intro.wmv");
	m_mci.PlayMovie();*/

	return true;
}
//< ������Ʈ
void SceneIntro::update( void ) 
{
}
//< ����
void SceneIntro::render( HDC hdc ) 
{

}
//< ����
void SceneIntro::release( void ) 
{

}

//< �̺�Ʈó��
LRESULT	SceneIntro::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
		//< Ű���� �Է¹ޱ�
	case WM_KEYDOWN:
		switch(wparam)
		{
			//< ����Ű �Է�
		case VK_ESCAPE:
			//m_mci.ReleaseMovie();
			//�� �߰�
			//STATE_MGR->addState<SceneLogin>(SCENE_LOGIN);
			//�� ����
			STATE_MGR->changeState( SCENE_LOGIN );
			//< ���� �� ����
			STATE_MGR->deleteState( SCENE_INTRO );
			break;
		}
	case MCIWNDM_NOTIFYMODE:
		{
			switch( lparam )
			{
			case MCI_MODE_STOP:
				{
					//< ������ �� ���� �α��� ������
					//m_mci.ReleaseMovie();
					//�� �߰�
					//STATE_MGR->addState<SceneLogin>(SCENE_LOGIN);
					////�� ����
					//STATE_MGR->changeState( SCENE_LOGIN );
					////< ���� �� ����
					//STATE_MGR->deleteState( SCENE_INTRO );
				}
				break;
			}
		}
	}
	return (DefWindowProc( wnd ,msg,wparam,lparam));
}