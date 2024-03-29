#pragma once

#include "windows.h"

//< 추상 씬 클래스
class State
{
public:
	State(){}
	virtual ~State(){}

public :
	//< 초기화
	virtual bool init() = 0;
	//< 업데이트
	virtual void update(float fDeltaTime) = 0;
	//< 랜더
	virtual void render( HDC hdc ) = 0;
	//< 해제
	virtual void release( void ) = 0;
	//< 이벤트 처리
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )= 0;
};