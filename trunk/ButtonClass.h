#pragma once

class ImageNode;
class MY_Font;

//< ��ư �̹��� Ŭ����
class ButtonClass
{
public :
	ButtonClass(void);
	~ButtonClass(void);

	//< �ʱ�ȭ
	void init( char *dest_FILE_NAME, char *overlap_FILE_NAME, int sizeX, int sizeY );
	//< �߰���ư �ʱ�ȭ 
	void init( 
		char *dest_FILE_NAME, 
		char *overlap_FILE_NAME,
		char *noChoice_FILE_NAME,
		int sizeX, int sizeY );
	//< ������Ʈ
	void update( void );
	//< ����
	void render( HDC hdc );
	//< �����
	void release( void );

	//< ��Ʈ �ҷ�����
	void loadFont( const char *destString, 
		const RECT ALIGN_RECT,
		const char *fontName,
		const int fontSize, 
		const int ALIGN_TYPE,
		const int R_COLOR,
		const int G_COLOR,
		const int B_COLOR );

public :
	//< ��ư �̹��� �ҷ�����
	void loadImage( char *FILE_NAME, int sizeX, int sizeY );
	//< ��ư ���콺���� �̹��� �ҷ�����
	void loadImage2( char *FILE_NAME, int sizeX, int sizeY );
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

	//< ��ư ��� ����
	void checkButtonTrue( void ){ checkTrueButton = true; }
	//< ��ư ���
	void checkButtonFalse( void ){ checkTrueButton = false; }

private :
	//< Ŭ�� �ִϸ��̼�
	void aniClickButton( HDC hdc );

private :
	//< �̹���
	ImageNode *buttonImage;
	//< ���콺 ���� �̹���
	ImageNode *buttonImage2;
	//< ���þȵ� �̹��� 
	ImageNode *buttonImage3;
	//< ���� ����, �Ұ�
	bool checkTrueButton;

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

	//< ��ư �ִ� �ӵ�
	int speed ;
	//< ��ư �ִ� �ð�
	DWORD aniTime;

private :
	//< ��Ʈ ����
	POINT rectCenter;
};

