#pragma once

//#include "MCI.h"
#include "Scene.h"

class SceneIntro : public Scene
{
public:
	SceneIntro(void);
	virtual ~SceneIntro(void);

public :
	//< �ʱ�ȭ
	virtual bool init( void ) ;
	//< ������Ʈ
	virtual void update( void ) ;
	//< ����
	virtual void render( HDC hdc ) ;
	//< ����
	virtual void release( void ) ;
	
	//< �̺�Ʈó��
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//MCI m_mci;
};

