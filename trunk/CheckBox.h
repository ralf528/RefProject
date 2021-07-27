#pragma once

//< üũ�ڽ�
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

	//< �ʱ�ȭ
	void init( 
		TCHAR *checkOFF_FILE_NAME,
		TCHAR *overlapOff_FILE_NAME,
		TCHAR *checkON_FILE_NAME, 
		TCHAR *overlapON_FILE_NAME, 
		int sizeX, int sizeY );
	//< ������Ʈ
	void update( void );
	//< ����
	void render( HDC hdc );
	//< �����
	void release( void );

	//< ��Ʈ �ҷ�����
	void loadFont( const TCHAR *destString,
		const RECT ALIGN_RECT,
		const TCHAR *fontName,
		const int fontSize, 
		const int ALIGN_TYPE,
		const int R_COLOR,
		const int G_COLOR,
		const int B_COLOR );

public :
	//< ���� ��ư �̹��� �ҷ�����
	void loadImage(TCHAR *FILE_NAME, int sizeX, int sizeY );
	//< �ܺ� ��ġ �ޱ�
	void setRectPos( int posX, int posY, int ALIGE_TYPE );

	//< ��ư �̹��� ��Ʈ �ѱ��
	RECT getRect( void ){ return buttonRect; }

public :
	//< �浹 Ȯ��
	void inCheckMouseOn( bool buttonState ){ checkMouseOn = buttonState; }
	//< ���� Ȯ��
	void inClickButton( bool buttonState )
	{ 
		checkClickButton = buttonState;	
	}
	//< �ִϸ��̼� ���� 
	void inPlayButtonAni( bool checkAni )
	{
		playButtonAni = checkAni; 
	}

	//< �浹 ���� �ѱ��
	bool getCheckMouseOn( void )
	{ 
		return checkMouseOn; 
	}
	//< ���� Ȯ�� �ѱ��
	bool getClickButton( void )
	{ 
		return checkClickButton; 
	}
	//< �ִϸ��̼� ���� Ȯ�� �ѱ��
	bool getPlayButtonAni( void )
	{ 
		return playButtonAni;
	}

	//< üũ��ư ���� �ޱ�
	int getCheckBox( void )
	{
		return checkBoxState;
	}
	//< üũ��ư ���� ����
	void inCheckBox( int CHECK_STATE )
	{
		checkBoxState = CHECK_STATE;
	}

private :
	//< Ŭ�� �ִϸ��̼�
	void aniClickButton( HDC hdc );

private :
	//< �̹��� OFF
	ImageNode *checkOFF;
	//< �̹��� ON
	ImageNode *checkON;
	
	//< ���콺 ���� �̹���
	ImageNode *overlapOFF;
	ImageNode *overlapON;

	//< üũ�ڽ� ����
	int checkBoxState;

	//< ��Ʈ �ޱ�
	MY_Font *font;

	//< ��ư �̹��� ��Ʈ
	RECT buttonRect;

	//< ��ư �浹Ȯ��
	bool checkMouseOn;
	//< ��ư ���� Ȯ��
	bool checkClickButton;
	//< ��ư �ִϸ��̼� ��� Ȯ��
	bool playButtonAni;

private :
	//< ��Ʈ ����
	POINT rectCenter;
};

