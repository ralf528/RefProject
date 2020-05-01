#pragma once

#define MAX_CHAR_LINE 5

#include "../../MY_FontMgr.h"
#include "../../PopupBox.h"
class PopupBox;

typedef struct tag_charLine
{
	//< 고정 랙트
	RECT rect[2];
	//< 유저 이름 출력
	MY_Font name;
	//< 입력 스트링
	MY_Font text;
}CHAR_LINE;


class ChattingGame
{
public:
	ChattingGame(void);
	~ChattingGame(void);

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

	//< 스트링 갱신 출력
	void StringUpdate( void );
	//< 스트링 넣기
	void StringPush( void );

	//void packetProcess(const PACKET* packet);

	//< 채팅 보이기 상태 받기
	bool getChatingView( void )
	{
		return m_OnBackground;
	}
	//< 채팅보이기 상태 변경
	void inChatingView( void )
	{
		//< 시간갱신
		checkTime = GetTickCount();
		m_OnBackground = true;
	}

	//< 채팅 상태 받기
	bool getChatingOn( void )
	{
		return m_onChat;
	}


    void changeChattingOn(void)
    {
        m_onChat = !m_onChat;
    }

private :
	//< 폰트
	MY_Font* m_font;

	//< 버튼
	ButtonClass *button_UP;
	ButtonClass *button_DOWN;
	//< 스크롤바
	ButtonClass *button_SCROLL;
	ButtonClass *button_SCROLL_NODE;
	//< 스크롤바 좌표
	int nodePosition;

	//< 유저 네임
	string userName;
	RECT userNameRect;

	//< 채팅입력 보드
	ButtonClass *m_input_Board;

	//< 채팅 입력창
	InputString *inputChar;
	//< 채팅창 페이지
	int stringPage;
	int oldStringPage;

	//< 배경 이미지
	PopupBox *m_image;

	//< 출력 데이터
	CHAR_LINE inputData[5];
	//< 저장 데이터
	CHAR_LINE inputDataSave[9];

	//< 채팅 플래그
	bool m_OnBackground;
	bool m_onChat;
	//< 현재 시간
	DWORD nowTime;
	//< 애니 시간
	DWORD checkTime;
	//< 시간체크
	int count;
};

