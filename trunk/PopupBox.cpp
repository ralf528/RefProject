#include "stdafx.h"
#include "PopupBox.h"
#include "ImageNode.h"

PopupBox::PopupBox( void )
{
	//< 할당
	PopupBoxImage = new ImageNode(0);


	//< 애니메이션 확인
	playPopupBoxAni = false;
}

PopupBox::~PopupBox(void)
{
	//< 모두지우기
	release();
}

//< 초기화
void PopupBox::init(TCHAR *dest_FILE_NAME, int sizeX, int sizeY )
{
	//< 이미지 로드
	loadImage( dest_FILE_NAME, sizeX, sizeY );
}

//< 업데이트
void PopupBox::update( void )
{
	
}

//< 랜더
void PopupBox::render( HDC hdc )
{
	//< 애니메이션 재생이 안됬다면 
	if( playPopupBoxAni == false )
	{
		//< 애니메이션 출력
		aniPopupBox(hdc);
	}
	//< 디폴트 이미지 출력
	else
	{
		//< 렉트크기 미리보기
		//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
		//< 렉트 위치만큼 이미지 그리기
		PopupBoxImage->render( hdc, PopupBoxRect.left, PopupBoxRect.top );
	}
}
//< 애니메이션 없이 출력
void PopupBox::renderNone( HDC hdc )
{
	//< 렉트크기 미리보기
	//Rectangle( hdc, buttonRect.left, buttonRect.top, buttonRect.right, buttonRect.bottom );
	//< 렉트 위치만큼 이미지 그리기
	PopupBoxImage->render( hdc, PopupBoxRect.left, PopupBoxRect.top );
}
//< 애니메이션
void PopupBox::aniPopupBox( HDC hdc )
{
	//< 사이즈 받기
	SIZE size = PopupBoxImage->getSize();
	//< 임시 카운트
	static int count =0;
	static int minCount = 5;

	if( count <= 60 )
	{
		//< 사이즈 새로 갱신
		size.cx += count;
		size.cy += count;

		if( count < 10 )
		{
			size.cx -= minCount;
			size.cy -= minCount;
			//< 이미지 애니메이션
			PopupBoxImage->renderSize( hdc, PopupBoxRect.left-(count-minCount)/2, PopupBoxRect.top-(count-minCount)/2, size.cx, size.cy );
			minCount++;
		}
		else if(  count >= 10 && count <= 30 )
		{
			//< 이미지 애니메이션
			PopupBoxImage->renderSize( hdc, PopupBoxRect.left - count/2, PopupBoxRect.top - count/2, size.cx, size.cy );
		}
		else
		{
			//< 렉트 위치만큼 이미지 그리기
			PopupBoxImage->render( hdc, PopupBoxRect.left, PopupBoxRect.top );
		}
		count ++;
	}

	//< 애니메이션 재생 확인
	if( count >= 60 )
	{
		playPopupBoxAni = true;
		count = 0;
		minCount = 5;
	}
}
//< 지우기
void PopupBox::release( void )
{
	//< 팝업 이미지 삭제
	if( PopupBoxImage != NULL ){ PopupBoxImage->release(); }
	SAFE_DELETE( PopupBoxImage );
}

//public :
//< 팝업 이미지 불러오기
void PopupBox::loadImage(TCHAR *FILE_NAME, int sizeX, int sizeY )
{
	//< 버튼 이미지 불러오기
	PopupBoxImage->load( FILE_NAME, sizeX, sizeY, RM_TRANS );
	
	//< 렉트 초기화
	SetRect( &PopupBoxRect, 0,0, sizeX, sizeY );
	//< 중점 찾기
	rectCenter.x = sizeX/2;
	rectCenter.y = sizeY/2;
}

//< 외부 위치 받기
void PopupBox::setRectPos( int posX, int posY, int ALIGE_TYPE )
{
	//< 위치 중점 위치에 포지션 받기
	posCenter.x = posX;
	posCenter.y = posY;

	switch( ALIGE_TYPE )
	{
	//< 중간정렬
	case ALIGN_CENTER :
		{
			//< 렉트 이동
			PopupBoxRect.left = posX - rectCenter.x;
			PopupBoxRect.top = posY - rectCenter.y;
			PopupBoxRect.right = posX + rectCenter.x;
			PopupBoxRect.bottom = posY + rectCenter.y;
		}
		break;
	//< 왼쪽위 정렬
	case ALIGN_LEFT_TOP :
		{
			//< 렉트 이동
			PopupBoxRect.left = posX ;
			PopupBoxRect.top = posY ;
			PopupBoxRect.right = posX + rectCenter.x*2;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< 왼쪽 아래 정렬
	case ALIGN_LEFT_BOTTOM :
		{
			//< 렉트 이동
			PopupBoxRect.left = posX ;
			PopupBoxRect.top = posY - rectCenter.y*2;;
			PopupBoxRect.right = posX  ;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< 오른쪽 위 정렬
	case ALIGN_RIGHT_TOP : 
		{
			//< 렉트 이동
			PopupBoxRect.left = posX - rectCenter.x*2;
			PopupBoxRect.top = posY ;
			PopupBoxRect.right = posX - rectCenter.x*2;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	//< 오른쪽 아래 정렬
	case ALIGN_RIGHT_BOTTOM :
		{
			//< 렉트 이동
			PopupBoxRect.left = posX - rectCenter.x*2;
			PopupBoxRect.top = posY - rectCenter.y*2;
			PopupBoxRect.right = posX + rectCenter.x*2;
			PopupBoxRect.bottom = posY + rectCenter.y*2;
		}
		break;
	}
}


//< 외부 위치 받기
void PopupBox::setRectPos( RECT rect )
{
	//< 렉트 이동
	PopupBoxRect = rect;
}
