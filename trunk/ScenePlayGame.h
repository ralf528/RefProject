#pragma once

#include "Scene.h"
#include "MY_FontMgr.h"

//< ��
class tileMap;
//< ĳ����
class character;
//< ä��â
class ChattingGame;

class ScenePlayGame : public Scene
{
public:
	ScenePlayGame(void);
	virtual ~ScenePlayGame(void);

public :
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

	//< ��Ż �� �ʱ�ȭ
	void initByPortal(POINT &destPos);

private:
	//< UI �ε�
	void initUI( void );
	//< UI �׸���
	void renderUI(HDC hdc);


private :
	//< ���� ȭ�� DC
	HDC screenDC;
	//< ���������� ����
	bool m_playingGame;

	//< ĳ���� ����
	character *m_player;

	//Ÿ�ϸ� ����
	tileMap *m_map;

private : //< UI����-------------------------------------------
	//< ��ų��ư
	ButtonClass m_button_Skill[4];

	//< ������ ��ư
	ButtonClass m_m_button_Item[4];

	//< ü��
	ImageNode m_bar_live;
	ImageNode m_bar_live_back;
	//< ü�� ǥ��
	MY_Font m_bar_live_string;

	//< ����
	ImageNode m_bar_mana;
	ImageNode m_bar_mana_back;
	//< ���� ǥ��
	MY_Font m_bar_mana_string;

	//< ����ġ
	ImageNode m_bar_experience;
	ImageNode m_bar_experience_back;
	//< ����ġ ǥ��
	MY_Font m_bar_experience_string;

	//< ĳ���� �̸�
	MY_Font m_charName;

	//< ����
	ButtonClass m_stat[3];
	MY_Font m_stat_S;
	MY_Font m_stat_Q;
	MY_Font m_stat_M;

	//< ���� ǥ��
	ButtonClass m_lv_bar;
	MY_Font m_lv_bar_string;

	//< ���� �� ǥ��
	MY_Font m_stage;

	//< �����̻�
	MY_Font m_charState;

    //< ä��â
	ChattingGame *chatting;
	//< ����Ű �Ǵ�
	int checkEnter;
};