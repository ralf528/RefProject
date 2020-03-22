#pragma once

#include "popup.h"

class PopupBox;

class Popup_Lobby_EnterRoom_Success :public Popup
{
public:
	Popup_Lobby_EnterRoom_Success(void);
	virtual ~Popup_Lobby_EnterRoom_Success(void);

	//< �ʱ�ȭ
	virtual void init( void );
	//< ������Ʈ
	virtual void update( POINT mousePos );
	//< ����
	virtual void render( HDC hdc );
	//< �����
	virtual void release( void );

	//< �̺�Ʈó��
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

public :
	//< �̹��� �ҷ�����
	virtual void loadImage( void );

	//< �ܺη�Ʈ �ޱ�
	virtual RECT getRect( void )
	{
		return rect;
	}

	//< ������ �ޱ�
	virtual int getNextScene( void )
	{
		return button_STATE;
	}

	//< ������ 
	virtual void inNextScene( void )
	{
		button_STATE = POPUP_NONE;
	}

private :

	//< ��� �̹���( ��Ӱ� )
	ImageNode *alpaImage;

	//< �˾�â �̹���
	PopupBox *popupImage;
	//< ��Ʈ
	RECT rect;

	//< ��ư
	ButtonClass *button_OK;
	int button_STATE;

	//< �� �Ҵ� ���
	bool makeRoom;

	//< ��Ʈ
	MY_Font* font;
};

