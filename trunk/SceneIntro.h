#pragma once

//#include "MCI.h"
#include "Scene.h"

class SceneIntro : public Scene
{
public:
	SceneIntro(void);
	virtual ~SceneIntro(void);

public :
	//< 초기화
	virtual bool init( void ) ;
	//< 업데이트
	virtual void update( void ) ;
	//< 랜더
	virtual void render( HDC hdc ) ;
	//< 해제
	virtual void release( void ) ;
	
	//< 이벤트처리
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//MCI m_mci;
};

