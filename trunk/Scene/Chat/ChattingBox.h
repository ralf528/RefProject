#pragma once

#define MAX_CHAR_LINE 4

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

class ChattingBox
{
public:
	ChattingBox(void);
	~ChattingBox(void);

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
	wstring userName;
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
	CHAR_LINE inputData[4];
	//< 저장 데이터
	CHAR_LINE inputDataSave[8];
};

