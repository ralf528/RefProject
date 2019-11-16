#pragma once

class ImageNode;
class MY_Font;

//< 버튼 이미지 클래스
class ButtonClass
{
public :
	ButtonClass(void);
	~ButtonClass(void);

	//< 초기화
	void init( char *dest_FILE_NAME, char *overlap_FILE_NAME, int sizeX, int sizeY );
	//< 추가버튼 초기화 
	void init( 
		char *dest_FILE_NAME, 
		char *overlap_FILE_NAME,
		char *noChoice_FILE_NAME,
		int sizeX, int sizeY );
	//< 업데이트
	void update( void );
	//< 랜더
	void render( HDC hdc );
	//< 지우기
	void release( void );

	//< 폰트 불러오기
	void loadFont( const char *destString, 
		const RECT ALIGN_RECT,
		const char *fontName,
		const int fontSize, 
		const int ALIGN_TYPE,
		const int R_COLOR,
		const int G_COLOR,
		const int B_COLOR );

public :
	//< 버튼 이미지 불러오기
	void loadImage( char *FILE_NAME, int sizeX, int sizeY );
	//< 버튼 마우스오버 이미지 불러오기
	void loadImage2( char *FILE_NAME, int sizeX, int sizeY );
	//< 외부 위치 받기
	void setRectPos( int posX, int posY, int ALIGE_TYPE );

	//< 버튼 이미지 렉트 넘기기
	RECT getRect( void ){ return buttonRect; }

public :
	//< 충돌 확인
	void inCheckMouseOn( bool buttonState ){ checkMouseOn = buttonState; }
	//< 눌림 확인
	void inClickButton( bool buttonState )
	{ 
		checkClickButton = buttonState;	
	}
	//< 애니메이션 상태 
	void inPlayButtonAni( bool checkAni )
	{
		playButtonAni = checkAni; 
	}

	//< 충돌 상태 넘기기
	bool getCheckMouseOn( void )
	{ 
		return checkMouseOn; 
	}
	//< 눌림 확인 넘기기
	bool getClickButton( void )
	{ 
		return checkClickButton; 
	}
	//< 애니메이션 재쟁 확인 넘기기
	bool getPlayButtonAni( void )
	{ 
		return playButtonAni;
	}

	//< 버튼 잠금 해제
	void checkButtonTrue( void ){ checkTrueButton = true; }
	//< 버튼 잠금
	void checkButtonFalse( void ){ checkTrueButton = false; }

private :
	//< 클릭 애니메이션
	void aniClickButton( HDC hdc );

private :
	//< 이미지
	ImageNode *buttonImage;
	//< 마우스 오버 이미지
	ImageNode *buttonImage2;
	//< 선택안됨 이미지 
	ImageNode *buttonImage3;
	//< 선택 가능, 불가
	bool checkTrueButton;

	//< 폰트 받기
	MY_Font *font;

	//< 버튼 이미지 렉트
	RECT buttonRect;

	//< 버튼 충돌확인
	bool checkMouseOn;
	//< 버튼 눌림 확인
	bool checkClickButton;
	//< 버튼 애니메이션 재생 확인
	bool playButtonAni;

	//< 버튼 애니 속도
	int speed ;
	//< 버튼 애니 시간
	DWORD aniTime;

private :
	//< 렉트 중점
	POINT rectCenter;
};

