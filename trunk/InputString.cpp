#include "stdafx.h"
#include "InputString.h"
#include "MY_FontMgr.h"

InputString::InputString(void)
{
	//< 입력 스트링 표시 폰트 할당
	outputString = new MY_Font;
	//< 인풋체크 변경
	inputCheck = false;
}


InputString::~InputString(void)
{
	//< 지우기
	release();
}


//< 초기화
void InputString::init( RECT ALIGN_RECT, TCHAR *FontName, int FontSize, int ALIGN_TYPE,
					   int Rcolor, int Gcolor, int Bcolor )
{
	//< 렉트 받기
	rect = ALIGN_RECT;

	//< 텍스트 로드
	outputString->LoadText(getString(),
		rect,
		L"HY헤드라인M",
		FontSize, ALIGN_TYPE, Rcolor,Gcolor,Bcolor );
}

//< 업데이트
void InputString::update( void )
{
	//outputString->inChar( inputString );
}

//< 랜더
void InputString::render( HDC hdc )
{
	//< 텍스트 출력
	outputString->OutputText( hdc ); 
}
//< 랜더 별그리기
void InputString::renderStar( HDC hdc )
{
	//< 텍스트 출력
	outputString->OutputStar( hdc );
}

//< 지우기
void InputString::release( void )
{
	//< 폰트 지우기
	inputString.clear();
	SAFE_DELETE( outputString );
}


//public :
//< 문자열 입력받기
void InputString::getChar( WPARAM wparam )
{
	//< 인풋 체크가 켜져있을때만 입력받기
	if( inputCheck == true )
	{
		//< 문자키 입력받기
		if( VK_TAB != wparam && VK_RETURN != wparam && VK_BACK != wparam && VK_ESCAPE != wparam )
		{
			//< 스트링에 저장   
			char ch = (char)wparam;

			inputString.push_back( ch );
			outputString->inChar( inputString );
		}
	}
}

//< 백스페이스로 없애기
void InputString::backSpace( void )
{
	//< 인풋 체크가 켜져있을때만 입력받기
	if( inputCheck == true )
	{
		//< 길이 측정
		size_t len = inputString.size();

		//< 문자열 길이가 0이면 실행하지 않음
		if( 0 < len )
		{
			//< 1바이트 문자면
			if( 0 < inputString[ len - 1 ] )
			{
				inputString.pop_back();
			}
			//< 2바이트 문자면
			else
			{
				inputString.pop_back();
				inputString.pop_back();
			}
			outputString->inChar( inputString );
		}
	}
}
