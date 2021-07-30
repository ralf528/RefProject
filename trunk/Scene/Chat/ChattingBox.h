#pragma once

#define MAX_CHAR_LINE 4

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

class ChattingBox
{
public:
	ChattingBox(void);
	~ChattingBox(void);

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
	wstring userName;
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
	CHAR_LINE inputData[4];
	//< ���� ������
	CHAR_LINE inputDataSave[8];
};

