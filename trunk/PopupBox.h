#pragma once

#include "ImageNode.h"
class ImageNode;

//< 팝업상자 클래스
class PopupBox
{
public:
	PopupBox(void);
	~PopupBox(void);

//< 초기화
	void init( char *dest_FILE_NAME, int sizeX, int sizeY );
	//< 업데이트
	void update( void );
	//< 랜더
	void render( HDC hdc );
	void renderNone( HDC hdc );
	//< 지우기
	void release( void );

public :
	//< 팝업 이미지 불러오기
	void loadImage( char *FILE_NAME, int sizeX, int sizeY );
	//< 외부 위치 받기
	void setRectPos( int posX, int posY, int ALIGE_TYPE );
	//< 외부 위치 받기
	void setRectPos( RECT rect );

public :
	//< 애니메이션 상태 
	void inPlayPopupBoxAni( bool checkAni ){ playPopupBoxAni = checkAni; }

	//< 애니메이션 재쟁 확인 넘기기
	bool getPlayPopupBoxAni( void ){ return playPopupBoxAni; }

	//< 중점 넘기기
	POINT getCenter( void ){ return posCenter; }

	//< 렉트 넘기기
	RECT getRect( void ){ return PopupBoxRect; }

	//< 사이즈 넘기기
	SIZE getSize( void ){ return PopupBoxImage->getSize(); }

private :
	//< 애니메이션
	void aniPopupBox( HDC hdc );

private :
	//< 이미지
	ImageNode *PopupBoxImage;

	//< 팝업 이미지 렉트
	RECT PopupBoxRect;

	//< 버튼 애니메이션 재생 확인
	bool playPopupBoxAni;

private :
	//< 렉트 중점
	POINT rectCenter;
	//< 위치 중점
	POINT posCenter;
};


