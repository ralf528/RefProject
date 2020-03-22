#pragma once

#include "popup.h"

class PopupBox;
class ButtonClass;
class InputString;
class CheckBox;

class Popup_Lobby_MakeRoom_Open : public Popup
{
public:
	Popup_Lobby_MakeRoom_Open(void);
	virtual ~Popup_Lobby_MakeRoom_Open(void);

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
	ButtonClass *inputInfo_REPASS;
	//< �Է�ĭ
	ButtonClass *m_inputID_Board;
	ButtonClass *m_inputPass_Board;

	//< ��ư
	ButtonClass *button_MAKEROOM;
	ButtonClass *button_CANCEL;
	//< ��ư ���� �����
	CheckBox *button_OPEN;
	CheckBox *button_CLOSE;
	//< üũ�ڽ�(����)
	CheckBox *checkBox_OK;
	CheckBox *checkBox_NO;
	int button_STATE;

	//< ���콺 ����Ʈ
	POINT mousePos;
	
	//< ���� ����
private :
	//< ���̸�
	InputString *inputRoomName;
	//< ���� ��� �����
	bool breakInto;
};

