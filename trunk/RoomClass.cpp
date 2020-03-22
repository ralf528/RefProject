#include "stdafx.h"
#include "RoomClass.h"

#include "MY_FontMgr.h"
#include "PopupBox.h"
#include "RoomButton.h"

RoomClass::RoomClass(void)
{
	//< 폰트
	m_font = new MY_Font;
	//< 배경 이미지
	m_image = new PopupBox;

	//< 플래그 초기화
	for( int i=0; i<4; i++ )
	{
		roomFlag[i] = false;
		room[i] = NULL;
	}

	//< 만들어진 방정보
	makeRoomCount = 0;
}


RoomClass::~RoomClass(void)
{
	release();
}


//< 초기화
void RoomClass::init( void )
{
	//< 배경 이미지 로드
	m_image->loadImage( "Data/Resource/Image/Popup_Box3.bmp", 1170,350 );

	//< 고정 위치
	m_image->setRectPos( WINSIZE_X/2, WINSIZE_Y/2-150, ALIGN_CENTER );

	//< 정렬 이미지 정보 얻기
	algnRect = m_image->getRect();
	algnSize = m_image->getSize();

	//< 1자리
	pos1.x = algnRect.left +(algnSize.cx/4) +20;
	pos1.y = algnRect.top+(algnSize.cy/4) +15 ;
	//< 2자리
	pos2.x = algnRect.left +((algnSize.cx/4)*3) -20;
	pos2.y = algnRect.top+(algnSize.cy/4) +15 ;
	//< 3자리
	pos3.x = algnRect.left +(algnSize.cx/4) +20;
	pos3.y = algnRect.top+((algnSize.cy/4)*3) -15 ;
	//< 4자리
	pos4.x = algnRect.left +((algnSize.cx/4)*3) -20;
	pos4.y = algnRect.top+((algnSize.cy/4)*3) -15 ;

	//< 만들어진 방정보 받기
	//makeRoomCount = GAME_DATA->getRoomCount();
}


//< 업데이트
void RoomClass::update( POINT mousePos )
{
	for( int i=0; i<4; i++ )
	{
		//< 방버튼 플래그가 켜지면 업데이트
		if( roomFlag[i] == true )
		{
			room[i]->update( mousePos );
		}
	}
}


//< 랜더
void RoomClass::render( HDC hdc )
{
	//< 배경 랜더
	m_image->renderNone( hdc );

	for( int i=0; i<4; i++ )
	{
		//< 방버튼 플래그가 켜지면 랜더
		if( roomFlag[i] == true )
		{
			room[i]->render( hdc );
		}

	}
}


//< 지우기
void RoomClass::release( void )
{
	//< 폰트
	SAFE_DELETE( m_font );

	//< 배경이미지
	if( NULL != m_image ){ m_image->release(); }
	SAFE_DELETE( m_image );

	//< 방버튼
	for( int i=0; i<4; i++ )
	{
		if( roomFlag[i] == true )
		{
			if( NULL != room[i] ){ room[i]->release(); }
			SAFE_DELETE( room[i] );
		}
	}
}

//< 방만들기
void RoomClass::makeRoom( int roomNumber )
{
	//< 방만들기 성공했다면
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
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(0);
                ROOM_INFO newRoom;
                memset(&newRoom, 0, sizeof(ROOM_INFO));
                newRoom.m_roomNum = 1;
                newRoom.m_userCount = 1;

                strcpy_s(newRoom.m_roomName, sizeof(newRoom.m_roomName), "방");
                strcpy_s(newRoom.m_userName[0], sizeof(newRoom.m_userName[0]), "me");

				//< 방버튼 할당
				room[0] = new RoomButton;

				//< 방버튼 초기화
				room[0]->init( newRoom, pos1.x, pos1.y );

				//< 플래그 키기
				roomFlag[0] = true;

				room[0]->setRoomNum(newRoom.m_roomNum);
			}
			else if(room[0] != NULL)
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(0);
                ROOM_INFO newRoom;
				//< 방버튼 초기화
				room[0]->init( newRoom, pos1.x, pos1.y );

				//< 플래그 키기
				roomFlag[0] = true;

				room[0]->setRoomNum(newRoom.m_roomNum);
			}
		}
		break;
	case MAKE_ROOM_02 :
		{
			if( room[1] == NULL )
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(1);
                ROOM_INFO newRoom;

				//< 방버튼 할당
				room[1] = new RoomButton;

				//< 방버튼 초기화
				room[1]->init( newRoom, pos2.x, pos2.y );

				//< 플래그 키기
				roomFlag[1] = true;

				room[1]->setRoomNum(newRoom.m_roomNum);
			}
			else if(room[1] != NULL)
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(1);
                ROOM_INFO newRoom;
				//< 방버튼 초기화
				room[1]->init( newRoom, pos1.x, pos1.y );

				//< 플래그 키기
				roomFlag[1] = true;

				room[1]->setRoomNum(newRoom.m_roomNum);
			}
		}
		break;
	case MAKE_ROOM_03 :
		{
			if( room[2] != NULL )
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(2);
                ROOM_INFO newRoom;

				//< 방버튼 할당
				room[2] = new RoomButton;

				//< 방버튼 초기화
				room[2]->init( newRoom, pos3.x, pos3.y );

				//< 플래그 키기
				roomFlag[2] = true;

				room[2]->setRoomNum(newRoom.m_roomNum);

				//< 선택한 방번호
				//GAME_DATA->inChoiceNumber( 1 );
			}
			else if(room[2] != NULL)
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(2);
                ROOM_INFO newRoom;
				//< 방버튼 초기화
				room[2]->init( newRoom, pos1.x, pos1.y );

				//< 플래그 키기
				roomFlag[2] = true;

				room[2]->setRoomNum(newRoom.m_roomNum);

				//< 선택한 방번호
				//GAME_DATA->inChoiceNumber( 1 );
			}
		}
		break;
	case MAKE_ROOM_04 :
		{
			SAFE_DELETE(room[3]);
			if( room[3] != NULL )
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(3);
                ROOM_INFO newRoom;

				//< 방버튼 할당
				room[3] = new RoomButton;

				//< 방버튼 초기화
				room[3]->init( newRoom, pos4.x, pos4.y );

				//< 플래그 키기
				roomFlag[3] = true;

				room[3]->setRoomNum(newRoom.m_roomNum);

				//< 선택한 방번호
				//GAME_DATA->inChoiceNumber( 3 );
			}
			else if(room[3] != NULL)
			{
				//< 방정보 
				//ROOM_INFO &newRoom = GAME_DATA->getRoomInfo(3);
                ROOM_INFO newRoom;
				//< 방버튼 초기화
				room[3]->init( newRoom, pos1.x, pos1.y );

				//< 플래그 키기
				roomFlag[3] = true;

				room[3]->setRoomNum(newRoom.m_roomNum);

				//< 선택한 방번호
				//GAME_DATA->inChoiceNumber( 3 );
			}
		}
		break;
	default :
		break;
	}
}

//< 이벤트처리
LRESULT	RoomClass::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	//< 방버튼
	for( int i=0; i<4; i++ )
	{
		//< 프로시저 전달
		if( roomFlag[i] == true )
		{
			room[i]->StateProc( wnd, msg, wparam, lparam );
		}
	}
	return NULL;
}