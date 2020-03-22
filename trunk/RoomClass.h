#pragma once

class PopupBox;
class RoomButton;

enum tag_makeroom
{
	MAKE_ROOM_NONE,
	MAKE_ROOM_01,
	MAKE_ROOM_02,
	MAKE_ROOM_03,
	MAKE_ROOM_04
};

//< 방 창
class RoomClass
{
public:
	RoomClass(void);
	~RoomClass(void);

	//< 초기화
	void init( void );
	//< 업데이트
	void update( POINT mousePos );
	//< 랜더
	void render( HDC hdc );
	//< 지우기
	void release( void );
	//< 이벤트처리
	LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

	//< 방만들기
	void makeRoom( int roomNumber );

private :
	//< 폰트
	MY_Font* m_font;

	//< 배경 이미지
	PopupBox *m_image;

	//< 만들어진 방
	RoomButton *room[4];
	//< 플래그
	bool roomFlag[4];

	//< 정렬렉트
	RECT algnRect;
	SIZE algnSize;
	//< 정렬 포인트
	POINT pos1;
	POINT pos2;
	POINT pos3;
	POINT pos4;

private :
	//< 만들어진 방정보 받기
	int makeRoomCount;
};

