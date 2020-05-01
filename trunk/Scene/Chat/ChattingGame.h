#pragma once

#define MAX_CHAR_LINE 5

#include "../../MY_FontMgr.h"
#include "../../PopupBox.h"
class PopupBox;

typedef struct tag_charLine
{
	//< ���� ��Ʈ
	RECT rect[2];
	//< ���� �̸� ���
	MY_Font name;
	//< �Է� ��Ʈ��
	MY_Font text;
}CHAR_LINE;


class ChattingGame
{
public:
	ChattingGame(void);
	~ChattingGame(void);

	//< �ʱ�ȭ
	void init( void );
	//< ������Ʈ
	void update( POINT mousePos );
	//< ����
	void render( HDC hdc );
	//< �����
	void release( void );
	//< �̺�Ʈó��
	LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

	//< ��Ʈ�� ���� ���
	void StringUpdate( void );
	//< ��Ʈ�� �ֱ�
	void StringPush( void );

	//void packetProcess(const PACKET* packet);

	//< ä�� ���̱� ���� �ޱ�
	bool getChatingView( void )
	{
		return m_OnBackground;
	}
	//< ä�ú��̱� ���� ����
	void inChatingView( void )
	{
		//< �ð�����
		checkTime = GetTickCount();
		m_OnBackground = true;
	}

	//< ä�� ���� �ޱ�
	bool getChatingOn( void )
	{
		return m_onChat;
	}


    void changeChattingOn(void)
    {
        m_onChat = !m_onChat;
    }

private :
	//< ��Ʈ
	MY_Font* m_font;

	//< ��ư
	ButtonClass *button_UP;
	ButtonClass *button_DOWN;
	//< ��ũ�ѹ�
	ButtonClass *button_SCROLL;
	ButtonClass *button_SCROLL_NODE;
	//< ��ũ�ѹ� ��ǥ
	int nodePosition;

	//< ���� ����
	string userName;
	RECT userNameRect;

	//< ä���Է� ����
	ButtonClass *m_input_Board;

	//< ä�� �Է�â
	InputString *inputChar;
	//< ä��â ������
	int stringPage;
	int oldStringPage;

	//< ��� �̹���
	PopupBox *m_image;

	//< ��� ������
	CHAR_LINE inputData[5];
	//< ���� ������
	CHAR_LINE inputDataSave[9];

	//< ä�� �÷���
	bool m_OnBackground;
	bool m_onChat;
	//< ���� �ð�
	DWORD nowTime;
	//< �ִ� �ð�
	DWORD checkTime;
	//< �ð�üũ
	int count;
};

