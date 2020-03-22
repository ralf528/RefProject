#pragma once

#include "MY_FontMgr.h"
class ButtonClass;

typedef struct tag_MadeRoomInfo
{
	//< 방번호
	MY_Font outputRoomNum;
	//< 방장
	MY_Font outputTobUser;
	//< 방제
	MY_Font outputRoomName;
	//< 공개/비공개
	MY_Font outputOpen;
}MADE_ROOM_INFO;

class RoomButton
{
public:
	RoomButton(void);
	~RoomButton(void);

	//<초기화
	void init( ROOM_INFO& makeRoom, int posX, int posY );
	//< 업데이트
	void update( POINT mousePos );
	//< 랜더
	void render( HDC hdc );
	//< 지우기
	void release( void );
	//< 이벤트처리
	LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

	//< 방 번호 설정
	inline void setRoomNum(unsigned int roomNum) { m_roomNum = roomNum; }

private :
	//< 방 -- 선택창
	ButtonClass *button_ROOM;
	//< 방 번호
	unsigned int m_roomNum;

	//< 방번 정보
	MADE_ROOM_INFO madeRoom;

	//< 공개 비공개 이미지
	ImageNode imageOpen;
	ImageNode imageClose;
	bool checkOpen;
};

