#pragma once

//< 체크박스
enum
{
	CHECK_BOX_OFF,
	CHECK_BOX_ON,
};

class CheckBox
{
public:
	CheckBox(void);
	~CheckBox(void);

	//< 초기화
	void init( 
		TCHAR *checkOFF_FILE_NAME,
		TCHAR *overlapOff_FILE_NAME,
		TCHAR *checkON_FILE_NAME, 
		TCHAR *overlapON_FILE_NAME, 
		int sizeX, int sizeY );
	//< 업데이트
	void update( void );
	//< 랜더
	void render( HDC hdc );
	//< 지우기
	void release( void );

	//< 폰트 불러오기
	void loadFont( const TCHAR *destString,
		const RECT ALIGN_RECT,
		const TCHAR *fontName,
		const int fontSize, 
		const int ALIGN_TYPE,
		const int R_COLOR,
		const int G_COLOR,
		const int B_COLOR );

public :
	//< 기준 버튼 이미지 불러오기
	void loadImage(TCHAR *FILE_NAME, int sizeX, int sizeY );
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

	//< 체크버튼 상태 받기
	int getCheckBox( void )
	{
		return checkBoxState;
	}
	//< 체크버튼 상태 변경
	void inCheckBox( int CHECK_STATE )
	{
		checkBoxState = CHECK_STATE;
	}

private :
	//< 클릭 애니메이션
	void aniClickButton( HDC hdc );

private :
	//< 이미지 OFF
	ImageNode *checkOFF;
	//< 이미지 ON
	ImageNode *checkON;
	
	//< 마우스 오버 이미지
	ImageNode *overlapOFF;
	ImageNode *overlapON;

	//< 체크박스 상태
	int checkBoxState;

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

private :
	//< 렉트 중점
	POINT rectCenter;
};

