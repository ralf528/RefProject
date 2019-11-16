#pragma once

//< 이미지 노드 전방선언 
class ImageNode;

class RenderMgr
{
private:
	RenderMgr(void);
	~RenderMgr(void);
	//< 싱글톤
	SINGLETON( RenderMgr );
public:
	//< 초기화
	void			init( void );
	
	//< 렌더링
	//< 그냥 랜더
	void			render( HDC hdc , const unsigned int UID, int x, int y );
	//< 영역지정 랜더
	void			render( HDC hdc, const unsigned int UID, 
							int x , int y, int destWidth, int destHieght, 
							int srcX, int srcY, int srcWidth, int srcHeight,
							BYTE alphaValue = 0);

	//< 화면에 최종 출력 ( hdc 필요 없음 )
	void			renderFrame( void );
	//< 백버퍼 초기화
	void			clearBack( int brush = WHITE_BRUSH );
	//< 삭제
	void			release( void );

	//< 메인DC얻기
	HDC				getMainDC( void );
	//< 백DC얻기
	HDC				getBackDC( void );	
	
//< 멤버변수
private:
	//< 메인 DC
	HDC				m_mainDC;
	//< 백 버퍼 이미지
	ImageNode		*m_imgBack;
	// 윈도우 렉트(사이즈 변경시 갱신, update 호출 )
	RECT			m_winRect;
};

#define RENDER_MGR Singleton<RenderMgr>::GetInstance()
