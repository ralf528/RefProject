#pragma once

class InputString;

//< �˾�â �߻�Ŭ����
class Popup_Loot
{
public:
	Popup_Loot(void);
	virtual ~Popup_Loot(void);

	//< �ʱ�ȭ
	virtual void init( void ) = 0;
	//< ������Ʈ
	virtual void update( POINT mousePos ) = 0;
	//< ����
	virtual void render( HDC hdc ) = 0;
	//< �����
	virtual void release( void ) = 0;

	//< �̺�Ʈó��
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam ) = 0;

public :
	//< �̹��� �ҷ�����
	virtual void loadImage( void ) = 0;

	//< �ܺη�Ʈ �ޱ�
	virtual RECT getRect( void ) = 0;

	//< ������ �ޱ�
	virtual int getNextScene( void ) = 0;

	//< ������ 
	virtual void inNextScene( void ) = 0;
};

