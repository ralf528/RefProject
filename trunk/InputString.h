#pragma once

#include "MY_FontMgr.h"

//< 스트링 입력 클래스
class InputString
{
public:
	InputString(void);
	~InputString(void);

	//< 초기화
	void init( RECT ALIGN_RECT, TCHAR *FontName, int FontSize, int ALIGN_TYPE,
					   int Rcolor, int Gcolor, int Bcolor );
	//< 업데이트
	void update( void );
	//< 랜더
	void render( HDC hdc );
	//< 랜더 별그리기
	void renderStar( HDC hdc );
	//< 지우기
	void release( void );

public :
	//< 문자열 입력받기
	void getChar( WPARAM wparam );
	//< 백스페이스로 없애기
	void backSpace( void );
	//< 입력문자 삭제
	void clear(void)
	{
		inputString.clear();
		outputString->clear();
	}
	//< 입력 체크 받기
	bool getInputCheck( void )
	{
		return inputCheck;
	}
	//< 입력 체크 변경
	void inInputCheck( bool check )
	{
		inputCheck = check;
	}

	//< 현재까지 입력된 스트링 받기
	TCHAR* getString( void )
	{
		//return MY_Font::StringToTCHAR(inputString);
		return (TCHAR*)inputString.c_str();
	}
	//< 스트링 받기
	wstring getCharString( void )
	{
		return inputString;
	}

	void setString(const TCHAR* buf)
	{
		inputString = buf;
	}

private :
	//< 스트링 입력
	wstring inputString;
	//< 입력 스트링 표시 폰트
	MY_Font* outputString;
	//< 기준 렉트
	RECT rect;

	//< 입력 가능 체크
	bool inputCheck;
};

