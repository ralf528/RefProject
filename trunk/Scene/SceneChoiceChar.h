#pragma once

#include "../scene.h"
#include "../MY_FontMgr.h"

class PopupBox;
class ButtonClass;
class CheckBox;

class SceneChoiceChar :public Scene
{
public:
	SceneChoiceChar(void);
	virtual ~SceneChoiceChar(void);

	//< �ʱ�ȭ
	virtual bool init( void ) ;
	//< ������Ʈ
	virtual void update(float fDeltaTime) ;
	//< ����
	virtual void render( HDC hdc ) ;
	//< ����
	virtual void release( void ) ;
	//< �̺�Ʈó��
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//< ��Ʈ
	MY_Font* m_font;
	MY_Font* m_fontBox1;
	MY_Font* m_fontBox2;

	//< ��� �̹���
	PopupBox *m_image;

	//< ��ư -- ���ӽ���
	ButtonClass *button_START_GAME;
	ButtonClass *button_BACK;
	int button_STATE;
	//---------------------------------------------
	//< �Է���
	PopupBox *m_StateBox1;
	PopupBox *m_StateBox2;

	//< ���� ����
	CheckBox *checkBox_Box1_01;
	CheckBox *checkBox_Box1_02;
	CheckBox *checkBox_Box1_03;
	CheckBox *checkBox_Box1_04;
	//< ���� ����
	CheckBox *checkBox_Box2_01;
	CheckBox *checkBox_Box2_02;
	CheckBox *checkBox_Box2_03;
	CheckBox *checkBox_Box2_04;
	//---------------------------------------------
	//< �˾�â �����ִ��� üũ
};

