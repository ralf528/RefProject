#pragma once

#include "popup.h"

//< ���ӿ��� �˾�â
class Popup_Game_GameOver :public Popup
{
public:
	Popup_Game_GameOver(void);
	virtual ~Popup_Game_GameOver(void);

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

	//< �� �ִϸ��̼� �̹���
	ImageNode *bloodAni;
	ANI_INFO *bloodAniInfo;
	//< �� �ִϸ��̼� �̹���
	ImageNode *gameOverAni;
	ANI_INFO *gameOverAniInfo;

	//< ��Ʈ
	RECT rect;

	//< ��ư
	ButtonClass *button_OK;
	int button_STATE;

	//< ��Ʈ
	MY_Font* font;

	//< ��ŸƮ ������
	DWORD startAniCount;
	//< ������ Ȯ��
	bool aniCountCheck;
};

