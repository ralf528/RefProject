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

//< �� â
class RoomClass
{
public:
	RoomClass(void);
	~RoomClass(void);

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

	//< �游���
	void makeRoom( int roomNumber );

private :
	//< ��Ʈ
	MY_Font* m_font;

	//< ��� �̹���
	PopupBox *m_image;

	//< ������� ��
	RoomButton *room[4];
	//< �÷���
	bool roomFlag[4];

	//< ���ķ�Ʈ
	RECT algnRect;
	SIZE algnSize;
	//< ���� ����Ʈ
	POINT pos1;
	POINT pos2;
	POINT pos3;
	POINT pos4;

private :
	//< ������� ������ �ޱ�
	int makeRoomCount;
};

