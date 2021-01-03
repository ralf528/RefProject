#pragma once

#include"ImageNode.h"

class ImageNode;

class WorldManager
{
//< ������, �Ҹ���
public:
	WorldManager(void);
	~WorldManager(void);
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
	E_TileBrush collisionObject( POINT &destPos );

	//��Ż
	bool inPortal( POINT &destPos );
	//< �� �� ����
	int getNowFloor(void) { return m_nowFloor; }
	//< ���� �� ��ȣ �ο�
	void setMapNum(void);
	int getMapNum(int index) { return m_mapNum[index]; }

	//< ĳ���� ��ġ ����
	POINT GetSpawnPos(void){ return m_SpawnPos; }

	//< ��Ż ��ġ ���
	inline POINT &PortalPos(void) { return m_portalPos; }

	//> ��Ż �浹
	inline bool IsColPortal(POINT& playerPos)
	{
		if(math::distancePtToPt(playerPos, m_portalPos) <= 45 )
		{
			return true;
		}
		return false;
	}

	//< ������ ����
	inline void setItem(int i, int j, E_TileBrush type) { m_obj[i][j] = type; }

private:
	//< �� �� �� ��ȣ
	int m_mapNum[MAP_MAX_FLOOR];
	//< ���� �� ��
	int m_nowFloor;

	//< �� ũ��
	int mapSizeX,mapSizeY;

	//< Ÿ�ϸ�����
	E_TileBrush **m_tile;
	//< �� ����
	E_TileBrush **m_line;
	//< ������Ʈ ����
	E_TileBrush **m_obj;
	
	//< ������(��) ����
	//POINT vertex[8];

	//< Ÿ�� �̹���
	ImageNode *m_imgTile;

	//< ĳ���� ������ ��ġ
	POINT m_SpawnPos;

	// ��Ż ��ġ
	POINT m_portalPos;
};