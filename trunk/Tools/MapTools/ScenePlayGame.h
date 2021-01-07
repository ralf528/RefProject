#pragma once

#include "Scene.h"

//폰트 매니저
class MY_FontMgr;
//이미지 노드
class ImageNode;
//< 맵
class tileMap;

class ScenePlayGame : public Scene
{
public:
	ScenePlayGame(void);
	virtual ~ScenePlayGame(void);

public :
	//< 초기화
	virtual bool init( void ) ;
	//< 업데이트
	virtual void update( void ) ;
	//< 랜더
	virtual void render( HDC hdc ) ;
	//< 해제
	virtual void release( void ) ;

	//< 이벤트처리
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//< 게임중인지 여부
	bool m_playingGame;

	//타일맵 정보
	tileMap *m_map;
};