#pragma once

#include "MY_FontMgr.h"
class ButtonClass;

typedef struct tag_MadeRoomInfo
{
	//< ���ȣ
	MY_Font outputRoomNum;
	//< ����
	MY_Font outputTobUser;
	//< ����
	MY_Font outputRoomName;
	//< ����/�����
	MY_Font outputOpen;
}MADE_ROOM_INFO;

class RoomButton
{
public:
	RoomButton(void);
	~RoomButton(void);

	//<�ʱ�ȭ
	void init( ROOM_INFO& makeRoom, int posX, int posY );
	//< ������Ʈ
	void update( POINT mousePos );
	//< ����
	void render( HDC hdc );
	//< �����
	void release( void );
	//< �̺�Ʈó��
	LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

	//< �� ��ȣ ����
	inline void setRoomNum(unsigned int roomNum) { m_roomNum = roomNum; }

private :
	//< �� -- ����â
	ButtonClass *button_ROOM;
	//< �� ��ȣ
	unsigned int m_roomNum;

	//< ��� ����
	MADE_ROOM_INFO madeRoom;

	//< ���� ����� �̹���
	ImageNode imageOpen;
	ImageNode imageClose;
	bool checkOpen;
};

