#pragma once

#include "windows.h"

//< �߻� �� Ŭ����
class State
{
public:
	State(){}
	virtual ~State(){}

public :
	//< �ʱ�ȭ
	virtual bool init() = 0;
	//< ������Ʈ
	virtual void update(float fDeltaTime) = 0;
	//< ����
	virtual void render( HDC hdc ) = 0;
	//< ����
	virtual void release( void ) = 0;
	//< �̺�Ʈ ó��
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )= 0;
};