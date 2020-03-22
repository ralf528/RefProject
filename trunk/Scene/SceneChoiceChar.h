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

	//< 초기화
	virtual bool init( void ) ;
	//< 업데이트
	virtual void update(float fDeltaTime) ;
	//< 랜더
	virtual void render( HDC hdc ) ;
	//< 해제
	virtual void release( void ) ;
	//< 이벤트처리
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//< 폰트
	MY_Font* m_font;
	MY_Font* m_fontBox1;
	MY_Font* m_fontBox2;

	//< 배경 이미지
	PopupBox *m_image;

	//< 버튼 -- 게임시작
	ButtonClass *button_START_GAME;
	ButtonClass *button_BACK;
	int button_STATE;
	//---------------------------------------------
	//< 입력판
	PopupBox *m_StateBox1;
	PopupBox *m_StateBox2;

	//< 종족 선택
	CheckBox *checkBox_Box1_01;
	CheckBox *checkBox_Box1_02;
	CheckBox *checkBox_Box1_03;
	CheckBox *checkBox_Box1_04;
	//< 직업 선택
	CheckBox *checkBox_Box2_01;
	CheckBox *checkBox_Box2_02;
	CheckBox *checkBox_Box2_03;
	CheckBox *checkBox_Box2_04;
	//---------------------------------------------
	//< 팝업창 켜져있는지 체크
};

