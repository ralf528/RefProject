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
	//< �ʱ�ȭ
	virtual bool init( void ) ;
	//< ������Ʈ
	virtual void update( void ) ;
	//< ����
	virtual void render( HDC hdc ) ;
	//< ����
	virtual void release( void ) ;
	//< �̺�Ʈó��
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//< ��Ʈ
	MY_Font *m_font;
	
	//< ��� �̹���
	PopupBox *m_image;

	//< ��ư -- ���ΰ�ħ
	ButtonClass *button_REFRESH;
	//< ��ư -- ģ�����
	ButtonClass *button_FRIEND_LIST;
	//< �游���
	ButtonClass *button_MAKE_ROOM;
	//< ������
	ButtonClass *button_EXIT;

	//<-------------------------------
	//< ��
	RoomClass *room;
	//< ������� �� üũ
	int roomCountInfo;
	
    //< ä��â 
	ChattingBox *chatting;

	//���콺 üũ
	bool checkMosFRIENDLIST;
	bool checkMosMAKEROOM;
	bool checkMosEXIT;
};

