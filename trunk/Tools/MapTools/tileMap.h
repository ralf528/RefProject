#pragma once

#include "Singleton.h"

class ImageNode;

class tileMap
{
//< 생성자, 소멸자
private:
	tileMap(void);
	~tileMap(void);

	SINGLETON(tileMap);

public:
	//초기화
	bool init( void );
	//해제
	void release(void);
	//갱신
	void update(void);
	//렌더
	void render( HDC hdc );

	//<맵 생성
	bool newMap( int cx, int cy );
	//<맵 로드
	bool loadMap( const char *path );
	//<맵 세이브
	bool saveMap( const char *path );
	//< 맵 해제
	bool releaseMap(void);

	//< 마우스가 올려진 타일 그리기
	void collisionTile( HDC hdc );

	//< 브러쉬 그리기
	void stempBrush( int i, int j );

	//< 타일 브러쉬 바꾸기
	void nextBrush(void);
	void prevBrush(void);

private:
	//< 타일 브러쉬
	int m_brush;
	
	//< 맵 번호
	int m_mapNum;

	//< 맵 크기
	int mapSizeX,mapSizeY;

	typedef int tileType;
	//< 타일맵정보
	tileType **m_tile;
	//< 벽 정보
	tileType **m_line;
	//< 오브젝트 정보
	tileType **m_obj;
	
	//< 꼭지점(벽) 정보
	POINT vertex[8];

	//< 타일 이미지
	ImageNode *m_imgTile;
	//< 벽 이미지
	ImageNode *m_imgWall;

	//< 마우스버튼플레그
	bool mouseLButtonDown;
};

#define MAP_EDITER Singleton<tileMap>::getInstance()