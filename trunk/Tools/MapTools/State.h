#pragma once

//< �߻� �� Ŭ����
class State
{
public:
	State(void){}
	virtual ~State(void){}

public :
	//< �ʱ�ȭ
	virtual bool init( void ) = 0;
	//< ������Ʈ
	virtual void update( void ) = 0;
	//< ����
	virtual void render( HDC hdc ) = 0;
	//< ����
	virtual void release( void ) = 0;
	//< �̺�Ʈ ó��
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )= 0;
};