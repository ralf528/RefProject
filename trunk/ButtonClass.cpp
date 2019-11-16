#include "stdafx.h"
#include "ButtonClass.h"
#include "MY_FontMgr.h"

ButtonClass::ButtonClass(void)
{
	//< 할당
	buttonImage = new ImageNode(0);
	buttonImage2 = new ImageNode(0);
	buttonImage3 = new ImageNode(0);

	//< 폰트 할당
	font = new MY_Font;

	//< 버튼 충돌확인
	checkMouseOn = false;
	//< 버튼 눌림 확인
	checkClickButton = false;
	//< 애니메이션 확인
	playButtonAni = false;

	//< 선택 불, 가
	checkTrueButton = true;

	//< 버튼 애니 속도 설정
	speed = 5;
	aniTime = GetTickCount();
}


ButtonClass::~ButtonClass(void)
{
	//< 모두지우기
	release();
}


//< 초기화
void ButtonClass::init( char *dest_FILE_NAME, char *overlap_FILE_NAME, int sizeX, int sizeY )
{
	//< 이미지 로드
	loadImage( dest_FILE_NAME, sizeX, sizeY );
	//< 오버렙 이미지 로드
	loadImage2( overlap_FILE_NAME, sizeX, sizeY );
}
//< 초기화
void ButtonClass::init( char *dest_FILE_NAME, char *overlap_FILE_NAME, char *noChoice_FILE_NAME, int sizeX, int sizeY )
{
	//< 이미지 로드
	loadImage( dest_FILE_NAME, sizeX, sizeY );
	//< 오버렙 이미지 로드
	loadImage2( overlap_FILE_NAME, sizeX, sizeY );
	//< 선택안됨 이미지 불러오기
	buttonImage3->load( noChoice_FILE_NAME, sizeX, sizeY, RM_TRANS );
}

//< 폰트 불러오기
void ButtonClass::loadFont( const char *destString, 
		const RECT ALIGN_RECT,
		const char *fontName = "굴림",
		const int fontSize = 10, 
		const int ALIGN_TYPE = ALIGN_CENTER,
		const int R_COLOR = 255,
		const int G_COLOR = 255,
		const int B_COLOR = 255 )
{
	//< 폰트 부르기
	font->LoadText( destString, 
		ALIGN_RECT,
		fontName,
		fontSize, ALIGN_TYPE,
		R_COLOR,G_COLOR,B_COLOR );
}

//< 업데이트
void ButtonClass::update( void )
{
	//< 외부 렉트 받기
	font->inFontRect( buttonRect );
}

//< 랜더
void ButtonClass::render( HDC hdc )
{
	if( checkTrueButton == true )
	{
		//< 버튼이 눌렸으면 
		if( checkClickButton == true )
		{
			//< 애니메이션 출력
			aniClickButton(hdc);
		}
		//< 마우스 오버라면 다른 이미지 출력하기
		else if( checkMouseOn == true )
		{
			buttonImage2->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}
		//< 디폴트 이미지 출력
		else
		{
			//< 렉트크기 미리보기
			//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
			//< 렉트 위치만큼 이미지 그리기
			buttonImage->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}
	}
	else
	{
		//< 선택불가 이미지 출력
		buttonImage3->render( hdc, buttonRect.left, buttonRect.top );
	}
}

//< 클릭 애니메이션
void ButtonClass::aniClickButton( HDC hdc )
{
	//< 사이즈 받기
	SIZE size = buttonImage2->getSize();
	//< 임시 카운트
	static int count =0;
	static int minCount = 5;
	int sizeAni = 5;
	static int i = sizeAni;

	if( count <= 20 )
	{
		//< 사이즈 새로 갱신
		size.cx += count;
		size.cy += count;

		if( count < 10 )
		{
			size.cx -= minCount;
			size.cy -= minCount;
			//< 이미지 애니메이션
			buttonImage2->renderSize( hdc, buttonRect.left-(count-minCount)/2, buttonRect.top-(count-minCount)/2, size.cx, size.cy );
			minCount++;
			//< 폰트 불러오기
			if( i <= sizeAni )
			{
				font->inSize( font->getSize() -3 );
				i++;
			}
			font->OutputText( hdc );
		}
		else if(  count >= 10 && count <= 15 )
		{
			//< 이미지 애니메이션
			buttonImage2->renderSize( hdc, buttonRect.left - count/2, buttonRect.top - count/2, size.cx, size.cy );
			//< 폰트 불러오기
			if( i >= sizeAni )
			{
				font->inSize( font->getSize() + 3 );
				i--;
			}
			font->OutputText( hdc );
		}
		else
		{
			//< 렉트 위치만큼 이미지 그리기
			buttonImage2->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}

		//< 현재 시간 받기
		DWORD nowTime = GetTickCount();

		if( speed + aniTime <= nowTime )
		{
			aniTime = nowTime;

			count ++;
		}
	}

	//< 애니메이션 재생 확인
	if( count >= 20 )
	{
		playButtonAni = true;
		checkClickButton = true;
		count = 0;
		minCount = 5;
	}
}
//< 지우기
void ButtonClass::release( void )
{
	//< 버튼 이미지 삭제
	if( buttonImage != NULL ){ buttonImage->release(); }
	SAFE_DELETE( buttonImage );
	if( buttonImage2 != NULL ){ buttonImage2->release(); }
	SAFE_DELETE( buttonImage2 );
	if( buttonImage3 != NULL ){ buttonImage3->release(); }
	SAFE_DELETE( buttonImage3 );
	//< 폰트 이미지 삭제
	SAFE_DELETE( font );
}

//public :
//< 버튼 이미지 불러오기
void ButtonClass::loadImage( char *FILE_NAME, int sizeX, int sizeY )
{
	//< 버튼 이미지 불러오기
	buttonImage->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
	
	//< 렉트 초기화
	SetRect( &buttonRect, 0,0, sizeX, sizeY );
	//< 중점 찾기
	rectCenter.x = sizeX/2;
	rectCenter.y = sizeY/2;
}

//< 버튼 마우스오버 이미지 불러오기
void ButtonClass::loadImage2( char *FILE_NAME, int sizeX, int sizeY )
{
	//< 버튼 이미지 불러오기
	buttonImage2->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
}

//< 외부 위치 받기
void ButtonClass::setRectPos( int posX, int posY, int ALIGE_TYPE )
{
	//< 임시 위치
	POINT tempPos;

	//< 임시 위치에 포지션 받기
	tempPos.x = posX - rectCenter.x;
	tempPos.y = posY + rectCenter.y;

	switch( ALIGE_TYPE )
	{
	//< 중간정렬
	case ALIGN_CENTER :
		{
			//< 렉트 이동
			buttonRect.left = posX - rectCenter.x;
			buttonRect.top = posY - rectCenter.y;
			buttonRect.right = posX + rectCenter.x;
			buttonRect.bottom = posY + rectCenter.y;
		}
		break;
	//< 왼쪽위 정렬
	case ALIGN_LEFT_TOP :
		{
			//< 렉트 이동
			buttonRect.left = posX ;
			buttonRect.top = posY ;
			buttonRect.right = posX + rectCenter.x*2;
			buttonRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< 왼쪽 아래 정렬
	case ALIGN_RIGHT_TOP :
		{
			//< 렉트 이동
			buttonRect.left = posX - rectCenter.x*2;
			buttonRect.top = posY ;
			buttonRect.right = posX  ;
			buttonRect.bottom = posY - rectCenter.y*2;
		}
		break;
	//< 오른쪽 위 정렬
	case ALIGN_LEFT_BOTTOM : 
		{
			//< 렉트 이동
			buttonRect.left = posX ;
			buttonRect.top = posY - rectCenter.y*2;
			buttonRect.right = posX - rectCenter.x*2;
			buttonRect.bottom = posY ;
		}
		break;
	//< 오른쪽 아래 정렬
	case ALIGN_RIGHT_BOTTOM :
		{
			//< 렉트 이동
			buttonRect.left = posX - rectCenter.x*2;
			buttonRect.top = posY - rectCenter.y*2;
			buttonRect.right = posX ;
			buttonRect.bottom = posY;
		}
		break;
	}
}
