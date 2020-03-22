#pragma once
#include "popup.h"

class ImageNode;
class PopupBox;
class ButtonClass;
class CheckBox;

class Popup_Lobby_EnterRoom_open :public Popup
{
public:
	Popup_Lobby_EnterRoom_open(void);
	virtual ~Popup_Lobby_EnterRoom_open(void);

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
	virtual int getNextScene( void );

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

	//< �Է� ��Ʈ �̹���
	ButtonClass *inputInfo_ID;
	ButtonClass *inputInfo_PASS;
	//< �Է�ĭ
	ButtonClass *m_inputID_Board;
	ButtonClass *m_inputPass_Board;

	//< ��ư
	ButtonClass *button_JOINROOM;
	ButtonClass *button_CANCEL;
	int button_STATE;

	//< ���콺 ����Ʈ
	POINT mousePos;
	
	//< ���� ����
private :
	//< ���̸�
	MY_Font* playUser;
	//< ���� ��� �����
	bool breakInto;
};

