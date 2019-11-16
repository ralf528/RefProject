#pragma once

#include "ImageNode.h"
class ImageNode;

//< �˾����� Ŭ����
class PopupBox
{
public:
	PopupBox(void);
	~PopupBox(void);

//< �ʱ�ȭ
	void init( char *dest_FILE_NAME, int sizeX, int sizeY );
	//< ������Ʈ
	void update( void );
	//< ����
	void render( HDC hdc );
	void renderNone( HDC hdc );
	//< �����
	void release( void );

public :
	//< �˾� �̹��� �ҷ�����
	void loadImage( char *FILE_NAME, int sizeX, int sizeY );
	//< �ܺ� ��ġ �ޱ�
	void setRectPos( int posX, int posY, int ALIGE_TYPE );
	//< �ܺ� ��ġ �ޱ�
	void setRectPos( RECT rect );

public :
	//< �ִϸ��̼� ���� 
	void inPlayPopupBoxAni( bool checkAni ){ playPopupBoxAni = checkAni; }

	//< �ִϸ��̼� ���� Ȯ�� �ѱ��
	bool getPlayPopupBoxAni( void ){ return playPopupBoxAni; }

	//< ���� �ѱ��
	POINT getCenter( void ){ return posCenter; }

	//< ��Ʈ �ѱ��
	RECT getRect( void ){ return PopupBoxRect; }

	//< ������ �ѱ��
	SIZE getSize( void ){ return PopupBoxImage->getSize(); }

private :
	//< �ִϸ��̼�
	void aniPopupBox( HDC hdc );

private :
	//< �̹���
	ImageNode *PopupBoxImage;

	//< �˾� �̹��� ��Ʈ
	RECT PopupBoxRect;

	//< ��ư �ִϸ��̼� ��� Ȯ��
	bool playPopupBoxAni;

private :
	//< ��Ʈ ����
	POINT rectCenter;
	//< ��ġ ����
	POINT posCenter;
};


