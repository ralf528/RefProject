#pragma once

#include "Object.h"

class ImageNode : public Object
{
public:
	ImageNode( void );
	ImageNode( unsigned int id );
	virtual ~ImageNode(void);

	//< 로딩
	unsigned int load( const TCHAR *imagePath , int cx = 0, int cy = 0 , BYTE mode = RM_NORMAL );
	//< RC로딩
	unsigned int load( const int resourceID , BYTE mode = RM_NORMAL );
	//< 빈이미지만들기(해당 크기로 빈이미지 만들기 )디폴트로 흰색으로 칠한다.
	unsigned int load( int cx , int cy, BYTE mode = RM_NORMAL  );

	//< 렌더
	void		render( HDC hdc, int x , int y );
	void		render( HDC hdc, int x , int y, int destCX , int destCY, 
						int scrX , int srcY , int srcCX, int srcCY );
	//< 알파블렌드
	void		renderAlpha( HDC hdc, int x , int y, BYTE alpha = 150 );

	//< 크기수정용 랜더
	void renderSize( HDC hdc, int x, int y, int width, int height );

	//< 해제
	void		release( void );

	//< 외부에서 MEMDC얻기
	inline HDC	getMemDC( void )	{ return m_memDC;	}
	//< 사이즈얻기
	inline SIZE getSize( void )		{ return m_size;	}

	//< 지정색으로 DC초기화하기
	void			clearDC( DWORD color );

private:
	//< 초기화
	void		init( void );
	//< 정보설정
	bool		setImageInfo( void );

private:
	//< 메모리DC
	HDC			m_memDC;
	//< 비트맵핸들
	HBITMAP		m_bit,m_obit;
	//< 가로세로사이즈
	SIZE		m_size;
	//< 경로
	TCHAR		m_path[ _MAX_FNAME ];
	//< 이미지 랜더 모드
	BYTE		m_renderMode;
	//< 컬러키
	DWORD		m_colorKey;
	//< 파일 로딩 타입
	BYTE		m_fileloadType;
};

