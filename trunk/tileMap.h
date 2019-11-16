#pragma once

#include"ImageNode.h"

class ImageNode;

class tileMap
{
//< 생성자, 소멸자
public:
	tileMap(void);
	~tileMap(void);
public:
	//초기화
	bool init( void );
	//해제
	void release(void);
	//렌더
	void render( HDC hdc );

	//< 타일 그리기
	void renderTile( HDC hdc );
	//< 벽 그리기
	void renderWall( HDC hdc );

	//<맵 로드
	bool loadMap( const char *path = START_LOAD_MAP_PATH );
	//< 맵 해제
	bool releaseMap(void);

	//< 충돌체크
	bool collision( POINT &destPos, POINT *vertex );
	//< 주위의 정점 체크
	void aroundLine( POINT &destPos, POINT *vertex );

	//< 오브젝트와 충돌체크
	tileType collisionObject( POINT &destPos );

	//포탈
	bool inPortal( POINT &destPos );
	//< 층 수 리턴
	int getNowFloor(void) { return m_nowFloor; }
	//< 랜덤 맵 번호 부여
	static void setMapNum(void);
	//< 호스트에 의해 맵 설정
	static void setMapNumByNetwork(const int *arr);
	static int getMapNum(int index) { return m_mapNum[index]; }

	//< 캐릭터 위치 리턴
	POINT getCharPos(void){ return m_charPos; }

	//< 포탈 위치 얻기
	inline POINT &wherePortal(void) { return m_portal; }

	//> 포탈 충돌
	inline bool IsColPortal(POINT& playerPos) {
		if(math::distancePtToPt(playerPos, m_portal) <= 45 )
		{
			return true;
		}
		return false;
	}

	//< 아이템 설정(네트워크)
	inline void setItem(int i, int j, int type) { m_obj[i][j] = type; }

private:
	//< 층 별 맵 번호
	static int m_mapNum[MAP_MAX_FLOOR];
	//< 현재 층 수
	int m_nowFloor;

	//< 맵 크기
	int mapSizeX,mapSizeY;

	//< 타일맵정보
	tileType **m_tile;
	//< 벽 정보
	tileType **m_line;
	//< 오브젝트 정보
	tileType **m_obj;
	
	//< 꼭지점(벽) 정보
	//POINT vertex[8];

	//< 타일 이미지
	ImageNode *m_imgTile;

	//< 캐릭터 생성될 위치
	POINT m_charPos;

	// 포탈 위치
	POINT m_portal;
};