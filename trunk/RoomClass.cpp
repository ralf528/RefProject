#include "stdafx.h"
#include "RoomClass.h"

#include "MY_FontMgr.h"
#include "PopupBox.h"
#include "RoomButton.h"

RoomClass::RoomClass(void)
{
	//< ��Ʈ
	m_font = new MY_Font;
	//< ��� �̹���
	m_image = new PopupBox;

	//< �÷��� �ʱ�ȭ
	for( int i=0; i<4; i++ )
	{
		roomFlag[i] = false;
		room[i] = NULL;
	}

	//< ������� ������
	makeRoomCount = 0;
}


RoomClass::~RoomClass(void)
{
	release();
}


//< �ʱ�ȭ
void RoomClass::init( void )
{
	//< ��� �̹��� �ε�
	m_image->loadImage( "Data/Resource/Image/Popup_Box3.bmp", 1170,350 );

	//< ���� ��ġ
	m_image->setRectPos( WINSIZE_X/2, WINSIZE_Y/2-150, ALIGN_CENTER );

	//< ���� �̹��� ���� ���
	algnRect = m_image->getRect();
	algnSize = m_image->getSize();

	//< 1�ڸ�
	pos1.x = algnRect.left +(algnSize.cx/4) +20;
	pos1.y = algnRect.top+(algnSize.cy/4) +15 ;
	//< 2�ڸ�
	pos2.x = algnRect.left +((algnSize.cx/4)*3) -20;
	pos2.y = algnRect.top+(algnSize.cy/4) +15 ;
	//< 3�ڸ�
	pos3.x = algnRect.left +(algnSize.cx/4) +20;
	pos3.y = algnRect.top+((algnSize.cy/4)*3) -15 ;
	//< 4�ڸ�
	pos4.x = algnRect.left +((algnSize.cx/4)*3) -20;
	pos4.y = algnRect.top+((algnSize.cy/4)*3) -15 ;

	//< ������� ������ �ޱ�
	//makeRoomCount = GAME_DATA->getRoomCount();
}


//< ������Ʈ
void RoomClass::update( POINT mousePos )
{
	for( int i=0; i<4; i++ )
	{
		//< ���ư �÷��װ� ������ ������Ʈ
		if( roomFlag[i] == true )
		{
			room[i]->update( mousePos );
		}
	}
}


//< ����
void RoomClass::render( HDC hdc )
{
	//< ��� ����
	m_image->renderNone( hdc );

	for( int i=0; i<4; i++ )
	{
		//< ���ư �÷��װ� ������ ����
		if( roomFlag[i] == true )
		{
			room[i]->render( hdc );
		}

	}
}


//< �����
void RoomClass::release( void )
{
	//< ��Ʈ
	SAFE_DELETE( m_font );

	//< ����̹���
	if( NULL != m_image ){ m_image->release(); }
	SAFE_DELETE( m_image );

	//< ���ư
	for( int i=0; i<4; i++ )
	{
		if( roomFlag[i] == true )
		{
			if( NULL != room[i] ){ room[i]->release(); }
			SAFE_DELETE( room[i] );
		}
	}
}

//< �游���
void RoomClass::makeRoom( int roomNumber )
{
	//< �游��� �����ߴٸ�
	switch( roomNumber )
	{
	case MAKE_ROOM_NONE :
		{

		}
		break;
	case MAKE_ROOM_01 :
		{
			if( room[0] == NULL )
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(0);
                ROOM_INFO newRoom;
                memset(&newRoom, 0, sizeof(ROOM_INFO));
                newRoom.m_roomNum = 1;
                newRoom.m_userCount = 1;

                strcpy_s(newRoom.m_roomName, sizeof(newRoom.m_roomName), "��");
                strcpy_s(newRoom.m_userName[0], sizeof(newRoom.m_userName[0]), "me");

				//< ���ư �Ҵ�
				room[0] = new RoomButton;

				//< ���ư �ʱ�ȭ
				room[0]->init( newRoom, pos1.x, pos1.y );

				//< �÷��� Ű��
				roomFlag[0] = true;

				room[0]->setRoomNum(newRoom.m_roomNum);
			}
			else if(room[0] != NULL)
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(0);
                ROOM_INFO newRoom;
				//< ���ư �ʱ�ȭ
				room[0]->init( newRoom, pos1.x, pos1.y );

				//< �÷��� Ű��
				roomFlag[0] = true;

				room[0]->setRoomNum(newRoom.m_roomNum);
			}
		}
		break;
	case MAKE_ROOM_02 :
		{
			if( room[1] == NULL )
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(1);
                ROOM_INFO newRoom;

				//< ���ư �Ҵ�
				room[1] = new RoomButton;

				//< ���ư �ʱ�ȭ
				room[1]->init( newRoom, pos2.x, pos2.y );

				//< �÷��� Ű��
				roomFlag[1] = true;

				room[1]->setRoomNum(newRoom.m_roomNum);
			}
			else if(room[1] != NULL)
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(1);
                ROOM_INFO newRoom;
				//< ���ư �ʱ�ȭ
				room[1]->init( newRoom, pos1.x, pos1.y );

				//< �÷��� Ű��
				roomFlag[1] = true;

				room[1]->setRoomNum(newRoom.m_roomNum);
			}
		}
		break;
	case MAKE_ROOM_03 :
		{
			if( room[2] != NULL )
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(2);
                ROOM_INFO newRoom;

				//< ���ư �Ҵ�
				room[2] = new RoomButton;

				//< ���ư �ʱ�ȭ
				room[2]->init( newRoom, pos3.x, pos3.y );

				//< �÷��� Ű��
				roomFlag[2] = true;

				room[2]->setRoomNum(newRoom.m_roomNum);

				//< ������ ���ȣ
				//GAME_DATA->inChoiceNumber( 1 );
			}
			else if(room[2] != NULL)
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(2);
                ROOM_INFO newRoom;
				//< ���ư �ʱ�ȭ
				room[2]->init( newRoom, pos1.x, pos1.y );

				//< �÷��� Ű��
				roomFlag[2] = true;

				room[2]->setRoomNum(newRoom.m_roomNum);

				//< ������ ���ȣ
				//GAME_DATA->inChoiceNumber( 1 );
			}
		}
		break;
	case MAKE_ROOM_04 :
		{
			SAFE_DELETE(room[3]);
			if( room[3] != NULL )
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(3);
                ROOM_INFO newRoom;

				//< ���ư �Ҵ�
				room[3] = new RoomButton;

				//< ���ư �ʱ�ȭ
				room[3]->init( newRoom, pos4.x, pos4.y );

				//< �÷��� Ű��
				roomFlag[3] = true;

				room[3]->setRoomNum(newRoom.m_roomNum);

				//< ������ ���ȣ
				//GAME_DATA->inChoiceNumber( 3 );
			}
			else if(room[3] != NULL)
			{
				//< ������ 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(3);
                ROOM_INFO newRoom;
				//< ���ư �ʱ�ȭ
				room[3]->init( newRoom, pos1.x, pos1.y );

				//< �÷��� Ű��
				roomFlag[3] = true;

				room[3]->setRoomNum(newRoom.m_roomNum);

				//< ������ ���ȣ
				//GAME_DATA->inChoiceNumber( 3 );
			}
		}
		break;
	default :
		break;
	}
}

//< �̺�Ʈó��
LRESULT	RoomClass::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	//< ���ư
	for( int i=0; i<4; i++ )
	{
		//< ���ν��� ����
		if( roomFlag[i] == true )
		{
			room[i]->StateProc( wnd, msg, wparam, lparam );
		}
	}
	return NULL;
}