#pragma once

#include"ImageNode.h"

class ImageNode;

class tileMap
{
//< ������, �Ҹ���
public:
	tileMap(void);
	~tileMap(void);
public:
	//�ʱ�ȭ
	bool init( void );
	//����
	void release(void);
	//����
	void render( HDC hdc );

	//< Ÿ�� �׸���
	void renderTile( HDC hdc );
	//< �� �׸���
	void renderWall( HDC hdc );

	//<�� �ε�
	bool loadMap( const char *path = START_LOAD_MAP_PATH );
	//< �� ����
	bool releaseMap(void);

	//< �浹üũ
	bool collision( POINT &destPos, POINT *vertex );
	//< ������ ���� üũ
	void aroundLine( POINT &destPos, POINT *vertex );

	//< ������Ʈ�� �浹üũ
	tileType collisionObject( POINT &destPos );

	//��Ż
	bool inPortal( POINT &destPos );
	//< �� �� ����
	int getNowFloor(void) { return m_nowFloor; }
	//< ���� �� ��ȣ �ο�
	static void setMapNum(void);
	//< ȣ��Ʈ�� ���� �� ����
	static void setMapNumByNetwork(const int *arr);
	static int getMapNum(int index) { return m_mapNum[index]; }

	//< ĳ���� ��ġ ����
	POINT getCharPos(void){ return m_charPos; }

	//< ��Ż ��ġ ���
	inline POINT &wherePortal(void) { return m_portal; }

	//> ��Ż �浹
	inline bool IsColPortal(POINT& playerPos) {
		if(math::distancePtToPt(playerPos, m_portal) <= 45 )
		{
			return true;
		}
		return false;
	}

	//< ������ ����(��Ʈ��ũ)
	inline void setItem(int i, int j, int type) { m_obj[i][j] = type; }

private:
	//< �� �� �� ��ȣ
	static int m_mapNum[MAP_MAX_FLOOR];
	//< ���� �� ��
	int m_nowFloor;

	//< �� ũ��
	int mapSizeX,mapSizeY;

	//< Ÿ�ϸ�����
	tileType **m_tile;
	//< �� ����
	tileType **m_line;
	//< ������Ʈ ����
	tileType **m_obj;
	
	//< ������(��) ����
	//POINT vertex[8];

	//< Ÿ�� �̹���
	ImageNode *m_imgTile;

	//< ĳ���� ������ ��ġ
	POINT m_charPos;

	// ��Ż ��ġ
	POINT m_portal;
};