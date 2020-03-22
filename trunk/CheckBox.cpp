#include "stdafx.h"
#include "CheckBox.h"

#include "MY_FontMgr.h"

CheckBox::CheckBox(void)
{
	//< 할당
	checkOFF = new ImageNode(0);
	checkON = new ImageNode(0);
	overlapOFF = new ImageNode(0);
	overlapON = new ImageNode(0);

	//< 폰트 할당
	font = new MY_Font;

	//< 버튼 충돌확인
	checkMouseOn = false;
	//< 버튼 눌림 확인
	checkClickButton = false;
	//< 애니메이션 확인
	playButtonAni = false;

	//< 체크박스 상태
	checkBoxState = CHECK_BOX_OFF;
}

CheckBox::~CheckBox(void)
{
	//< 모두지우기
	release();
}

//< 초기화
void CheckBox::init( char *checkOFF_FILE_NAME, char *overlapOFF_FILE_NAME,
					char *checkON_FILE_NAME, char *overlapON_FILE_NAME,
					int sizeX, int sizeY )
{
	//< 체크오프 이미지 로드
	loadImage( checkOFF_FILE_NAME, sizeX, sizeY );
	//< 체크온 이미지 로드
	checkON->load( checkON_FILE_NAME, sizeX, sizeY, RM_TRANS );
	//< 오버랩 이미지
	overlapOFF->load( overlapOFF_FILE_NAME, sizeX, sizeY, RM_TRANS );
	overlapON->load( overlapON_FILE_NAME, sizeX, sizeY, RM_TRANS );
}

//< 폰트 불러오기
void CheckBox::loadFont( const char *destString, 
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
void CheckBox::update( void )
{
	//< 외부 렉트 받기
	font->inFontRect( buttonRect );
}

//< 랜더
void CheckBox::render( HDC hdc )
{
	//< 오프 상태라면 
	if( checkBoxState == CHECK_BOX_OFF )
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
			overlapOFF->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}
		//< 디폴트 이미지 출력
		else
		{
			//< 렉트크기 미리보기
			//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
			//< 렉트 위치만큼 이미지 그리기
			checkOFF->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}
	}
	//< 온 상태라면
	else
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
			overlapON->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}
		//< 디폴트 이미지 출력
		else
		{
			//< 렉트크기 미리보기
			//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
			//< 렉트 위치만큼 이미지 그리기
			checkON->render( hdc, buttonRect.left, buttonRect.top );
			//< 폰트 불러오기
			font->OutputText( hdc );
		}
	}
}

//< 클릭 애니메이션
void CheckBox::aniClickButton( HDC hdc )
{
	//< 사이즈 받기
	SIZE size = overlapOFF->getSize();
	//< 임시 카운트
	static int count =0;
	static int minCount = 5;
	int sizeAni = 5;
	static int i = sizeAni;

	//< 체크가 OFF 상태라면 
	if( checkBoxState == CHECK_BOX_OFF )
	{
		if( count <= 30 )
		{
			//< 사이즈 새로 갱신
			size.cx += count;
			size.cy += count;

			if( count < 15 )
			{
				size.cx -= minCount;
				size.cy -= minCount;
				//< 이미지 애니메이션
				overlapOFF->renderSize( hdc, buttonRect.left-(count-minCount)/2, buttonRect.top-(count-minCount)/2, size.cx, size.cy );
				minCount++;
				//< 폰트 불러오기
				if( i <= sizeAni )
				{
					font->inSize( font->getSize() -3 );
					i++;
				}
				font->OutputText( hdc );
			}
			else if(  count >= 15 && count <= 25 )
			{
				//< 이미지 애니메이션
				overlapOFF->renderSize( hdc, buttonRect.left - count/2, buttonRect.top - count/2, size.cx, size.cy );
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
				overlapOFF->render( hdc, buttonRect.left, buttonRect.top );
				//< 폰트 불러오기
				font->OutputText( hdc );
			}
			count ++;
		}

		//< 애니메이션 재생 확인
		if( count >= 30 )
		{
			playButtonAni = true;
			checkClickButton = true;
			count = 0;
			minCount = 5;
			//< 체크박스 상태
			checkBoxState = CHECK_BOX_ON;
		}
	}
	//< 체크가 ON 상태라면
	else
	{
		if( count <= 30 )
		{
			//< 사이즈 새로 갱신
			size.cx += count;
			size.cy += count;

			if( count < 15 )
			{
				size.cx -= minCount;
				size.cy -= minCount;
				//< 이미지 애니메이션
				overlapON->renderSize( hdc, buttonRect.left-(count-minCount)/2, buttonRect.top-(count-minCount)/2, size.cx, size.cy );
				minCount++;
				//< 폰트 불러오기
				if( i <= sizeAni )
				{
					font->inSize( font->getSize() -3 );
					i++;
				}
				font->OutputText( hdc );
			}
			else if(  count >= 15 && count <= 25 )
			{
				//< 이미지 애니메이션
				overlapON->renderSize( hdc, buttonRect.left - count/2, buttonRect.top - count/2, size.cx, size.cy );
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
				overlapON->render( hdc, buttonRect.left, buttonRect.top );
				//< 폰트 불러오기
				font->OutputText( hdc );
			}
			count ++;
		}

		//< 애니메이션 재생 확인
		if( count >= 30 )
		{
			playButtonAni = true;
			checkClickButton = true;
			count = 0;
			minCount = 5;
			//< 체크박스 상태
			checkBoxState = CHECK_BOX_OFF;
		}
	}
}
//< 지우기
void CheckBox::release( void )
{
	//< 버튼 이미지 삭제
	if( checkOFF != NULL ){ checkOFF->release(); }
	SAFE_DELETE( checkOFF );
	if( checkON != NULL ){ checkON->release(); }
	SAFE_DELETE( checkON );
	if( overlapOFF != NULL ){ overlapOFF->release(); }
	SAFE_DELETE( overlapOFF );
	if( overlapON != NULL ){ overlapON->release(); }
	SAFE_DELETE( overlapON );
	//< 폰트 이미지 삭제
	SAFE_DELETE( font );
}

//public :
//< 버튼 이미지 불러오기
void CheckBox::loadImage( char *FILE_NAME, int sizeX, int sizeY )
{
	//< 버튼 이미지 불러오기
	checkOFF->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
	
	//< 렉트 초기화
	SetRect( &buttonRect, 0,0, sizeX, sizeY );
	//< 중점 찾기
	rectCenter.x = sizeX/2;
	rectCenter.y = sizeY/2;
}

//< 외부 위치 받기
void CheckBox::setRectPos( int posX, int posY, int ALIGE_TYPE )
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
