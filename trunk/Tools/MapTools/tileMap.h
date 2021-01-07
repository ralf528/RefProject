#pragma once

#include "Singleton.h"

class ImageNode;

class tileMap
{
//< ������, �Ҹ���
private:
	tileMap(void);
	~tileMap(void);

	SINGLETON(tileMap);

public:
	//�ʱ�ȭ
	bool init( void );
	//����
	void release(void);
	//����
	void update(void);
	//����
	void render( HDC hdc );

	//<�� ����
	bool newMap( int cx, int cy );
	//<�� �ε�
	bool loadMap( const char *path );
	//<�� ���̺�
	bool saveMap( const char *path );
	//< �� ����
	bool releaseMap(void);

	//< ���콺�� �÷��� Ÿ�� �׸���
	void collisionTile( HDC hdc );

	//< �귯�� �׸���
	void stempBrush( int i, int j );

	//< Ÿ�� �귯�� �ٲٱ�
	void nextBrush(void);
	void prevBrush(void);

private:
	//< Ÿ�� �귯��
	int m_brush;
	
	//< �� ��ȣ
	int m_mapNum;

	//< �� ũ��
	int mapSizeX,mapSizeY;

	typedef int tileType;
	//< Ÿ�ϸ�����
	tileType **m_tile;
	//< �� ����
	tileType **m_line;
	//< ������Ʈ ����
	tileType **m_obj;
	
	//< ������(��) ����
	POINT vertex[8];

	//< Ÿ�� �̹���
	ImageNode *m_imgTile;
	//< �� �̹���
	ImageNode *m_imgWall;

	//< ���콺��ư�÷���
	bool mouseLButtonDown;
};

#define MAP_EDITER Singleton<tileMap>::getInstance()