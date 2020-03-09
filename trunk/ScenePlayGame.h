#pragma once

#include "Scene.h"
#include "MY_FontMgr.h"

//< 맵
class tileMap;
//< 캐릭터
class character;
//< 채팅창
class ChattingGame;

class ScenePlayGame : public Scene
{
public:
	ScenePlayGame(void);
	virtual ~ScenePlayGame(void);

public :
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

	//< 포탈 후 초기화
	void initByPortal(POINT &destPos);

private:
	//< UI 로딩
	void initUI( void );
	//< UI 그리기
	void renderUI(HDC hdc);


private :
	//< 게임 화면 DC
	HDC screenDC;
	//< 게임중인지 여부
	bool m_playingGame;

	//< 캐릭터 정보
	character *m_player;

	//타일맵 정보
	tileMap *m_map;

private : //< UI관련-------------------------------------------
	//< 스킬버튼
	ButtonClass m_button_Skill[4];

	//< 아이템 버튼
	ButtonClass m_m_button_Item[4];

	//< 체력
	ImageNode m_bar_live;
	ImageNode m_bar_live_back;
	//< 체력 표시
	MY_Font m_bar_live_string;

	//< 마나
	ImageNode m_bar_mana;
	ImageNode m_bar_mana_back;
	//< 마나 표시
	MY_Font m_bar_mana_string;

	//< 경험치
	ImageNode m_bar_experience;
	ImageNode m_bar_experience_back;
	//< 경험치 표시
	MY_Font m_bar_experience_string;

	//< 캐릭터 이름
	MY_Font m_charName;

	//< 스텟
	ButtonClass m_stat[3];
	MY_Font m_stat_S;
	MY_Font m_stat_Q;
	MY_Font m_stat_M;

	//< 레벨 표시
	ButtonClass m_lv_bar;
	MY_Font m_lv_bar_string;

	//< 도달 층 표시
	MY_Font m_stage;

	//< 상태이상
	MY_Font m_charState;

    //< 채팅창
	ChattingGame *chatting;
	//< 앤터키 판단
	int checkEnter;
};