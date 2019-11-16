#pragma once

#include "Scene.h"

class MY_Font;
class InputString;
class PopupBox;
class ButtonClass;
class RoomClass;
class ChattingBox;

enum
{
	ST_PLAYGAME =1,
	ST_CHAR,
	ST_ITEM,
	ST_RANK,
	ST_ENDGAME
};

class SceneLobby : public Scene
{
public:
	SceneLobby(void);
	virtual ~SceneLobby(void);

public :
	//< 초기화
	virtual bool init( void ) ;
	//< 업데이트
	virtual void update( void ) ;
	//< 랜더
	virtual void render( HDC hdc ) ;
	//< 해제
	virtual void release( void ) ;
	//< 이벤트처리
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//< 폰트
	MY_Font *m_font;
	
	//< 배경 이미지
	PopupBox *m_image;

	//< 버튼 -- 새로고침
	ButtonClass *button_REFRESH;
	//< 버튼 -- 친구목록
	ButtonClass *button_FRIEND_LIST;
	//< 방만들기
	ButtonClass *button_MAKE_ROOM;
	//< 나가기
	ButtonClass *button_EXIT;

	//<-------------------------------
	//< 방
	RoomClass *room;
	//< 만들어진 방 체크
	int roomCountInfo;
	
    //< 채팅창 
	ChattingBox *chatting;

	//마우스 체크
	bool checkMosFRIENDLIST;
	bool checkMosMAKEROOM;
	bool checkMosEXIT;
};

