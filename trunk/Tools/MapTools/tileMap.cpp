#include "stdafx.h"
#include "ImageNode.h"
#include "tileMap.h"

using namespace myUTIL;
using namespace collision;
using namespace keyInput;

tileMap::tileMap(void)
	: m_brush(NON_TILE), mouseLButtonDown(false)
{

}
tileMap::~tileMap(void)
{
	release();
}

//�ʱ�ȭ
bool tileMap::init( void )
{
	//< Ÿ�� �̹���
	m_imgTile = new ImageNode[TILE_END];

	m_imgTile[TILE_NORMAL].load("Resources/TileMap/Tile_Nomal.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_CHAR	].load("Resources/TileMap/Tile_Char.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_ITEM	].load("Resources/TileMap/Tile_Item.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON	].load("Resources/TileMap/Tile_Mon.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_ALTAR].load("Resources/TileMap/Tile_Altar.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_BOOK_L].load("Resources/TileMap/Wall_BOOK_Left.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_BOOK_R].load("Resources/TileMap/Wall_BOOK_Right.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR_F].load("Resources/TileMap/Stair_Front.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR].load("Resources/TileMap/Stair.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR_L].load("Resources/TileMap/Stair_Left.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR_R].load("Resources/TileMap/Stair_Right.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_COLLUM].load("Resources/TileMap/Collum.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_L_WALL].load("Resources/TileMap/Wall_Left.bmp",0,0,RM_ALPHA32);
	m_imgTile[TILE_R_WALL].load("Resources/TileMap/Wall_Right.bmp",0,0,RM_ALPHA32);
	m_imgTile[OBJ_ALTAR].load("Resources/TileMap/ALTAR.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_ALTAR_DISABLE].load("Resources/TileMap/ALTAR_disable.bmp",0,0,RM_TRANS);

	return true;
}
//����
void tileMap::release(void)
{
	releaseMap();
	SAFE_DELETE_ARR( m_imgTile );
}

//����
void tileMap::update(void)
{
}

//����
void tileMap::render( HDC hdc )
{
	if (m_tile == nullptr)
	{
		return;
	}

	int count=0;

	HPEN myPen, oldPen;
	myPen = CreatePen( PS_SOLID, 5, RGB(255,0,0) );
	oldPen = (HPEN)SelectObject(hdc, myPen);

	//< Ÿ�� �׸���
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< Ÿ���� �����Ѵٸ�
			if( NON_TILE != m_tile[i][j] )
			{				
				if( m_tile[i][j] <= TILE_STAIR_F )
				{
					m_imgTile[m_tile[i][j]].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
				}
				else
				{
					m_imgTile[m_tile[i][j]].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y*4 - 13 - CAMERA->getY() );
				}
			}
		}
	}

	//< �� �׸���
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			if( 0 != m_line[i][j] )
			{
				if( m_line[i][j] == TILE_L_WALL )
				{
					m_imgTile[TILE_L_WALL].render( hdc, (TILE_SIZE_X * j) - CAMERA->getX() ,
						(TILE_SIZE_Y * i) + TILE_SIZE_X - m_imgTile[TILE_L_WALL].getSize().cy - CAMERA->getY() );
				}
				if( m_line[i][j] == TILE_R_WALL )
				{
					m_imgTile[TILE_R_WALL].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) + (2*TILE_SIZE_Y) - m_imgTile[TILE_R_WALL].getSize().cy - CAMERA->getY() );
				}
			}
		}
	}

	//< ������Ʈ �׸���
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			if( m_obj[i][j] == OBJ_BOOK_L )
			{
				m_imgTile[OBJ_BOOK_L].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X/2 - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - TILE_SIZE_Y/2 - CAMERA->getY() );
			}
			if( m_obj[i][j] == OBJ_BOOK_R )
			{
				m_imgTile[OBJ_BOOK_R].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X/2 - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - TILE_SIZE_Y/2 - CAMERA->getY() );
			}
		}
	}

	//< ���콺�� �÷��� Ÿ���� �� �׸���
	collisionTile( hdc );
	
	
	//< ���콺 ��ǥ ���
	int x = keyInput::getMousePos().x;
	int y = keyInput::getMousePos().y;

	if (m_brush != NON_TILE)
	{
		//< ���õ� �귯�� ���� ����
		m_imgTile[m_brush].renderAlpha(hdc, x - m_imgTile[m_brush].getSize().cx / 2, y - m_imgTile[m_brush].getSize().cy / 2, 150);
	}

	DeleteObject( SelectObject( hdc, oldPen ) );
}

//< ���콺�� �÷��� Ÿ�� �׸���
void tileMap::collisionTile( HDC hdc )
{
	//< ���콺 ��ǥ ���
	int x = keyInput::getMousePos().x + CAMERA->getX();
	int y = keyInput::getMousePos().y + CAMERA->getY();

	// Ÿ���� ������ ���Ⱑ �ٸ��� ������
	// �ݺ����� �� �� ����
	for(int i=0 ; i<mapSizeY ; i+=2)
	{
		for(int j=0 ; j<mapSizeX ; j+=2)
		{
			//< Ÿ���� ��ġ ���ϱ�
			POINT m_position;
			m_position.x = (j+1) * TILE_SIZE_X;
			m_position.y = i * TILE_SIZE_Y;

			//< ������ ���ϴ� ��(?)
			int ax = static_cast<int>( (-TILE_SIZE_Y/(float)TILE_SIZE_X) * (x - m_position.x));
			int yPlusax = y + ax;
			int yMinusax = y - ax;
			int tileBottom = m_position.y + TILE_SIZE_Y*2;

			//< ���� Ÿ�� ���ο� �ִٸ�
			if(yMinusax - m_position.y > 0 &&
				yPlusax - m_position.y > 0 &&
				yMinusax - tileBottom < 0 &&
				yPlusax - tileBottom < 0)
			{
				//< ������ �� �׸���
				MoveToEx( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i) * TILE_SIZE_Y - CAMERA->getY(), NULL );
				LineTo( hdc, (j+2) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i+2) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i) * TILE_SIZE_Y - CAMERA->getY() );

				//< Ÿ�� ���
				stempBrush(i,j);
			}
		}
	}

	for(int i=1 ; i<mapSizeY-1 ; i+=2)
	{
		for(int j=1 ; j<mapSizeX-1 ; j+=2)
		{
			//< Ÿ���� ��ġ ���ϱ�
			POINT m_position;
			m_position.x = (j+1) * TILE_SIZE_X;
			m_position.y = i * TILE_SIZE_Y;

			//< ������ ���ϴ� ��(?)
			int ax = static_cast<int>( (-TILE_SIZE_Y/(float)TILE_SIZE_X) * (x - m_position.x));
			int yPlusax = y + ax;
			int yMinusax = y - ax;
			int tileBottom = m_position.y + TILE_SIZE_Y*2;

			//< ���� Ÿ�� ���ο� �ִٸ�
			if(yMinusax - m_position.y > 0 &&
				yPlusax - m_position.y > 0 &&
				yMinusax - tileBottom < 0 &&
				yPlusax - tileBottom < 0)
			{
				MoveToEx( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i) * TILE_SIZE_Y - CAMERA->getY(), NULL );
				LineTo( hdc, (j+2) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i+2) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i) * TILE_SIZE_Y - CAMERA->getY() );

				//< Ÿ�� ���
				stempBrush(i,j);
			}
		}
	}
}

//<�� ����
bool tileMap::newMap( int cx, int cy )
{
	//< �� ���� �ʱ�ȭ
	releaseMap();

	//< �� ũ�� Ȯ��
	mapSizeX = cx;
	mapSizeY = cy;

	//< ������ �Ҵ�
	if( m_tile == NULL && m_line == NULL )
	{
		//< Ÿ�ϸ�, ��, ������Ʈ 2�� ������ �Ҵ�
		m_tile = new tileType*[mapSizeY];
		m_line = new tileType*[mapSizeY];
		m_obj  = new tileType*[mapSizeY];
		for(int i=0;i<mapSizeY;i++)
		{
			m_tile[i] = new tileType[mapSizeX];
			m_line[i] = new tileType[mapSizeX];
			m_obj[i]  = new tileType[mapSizeX];
		}
	}	

	//< �� ���� �ʱ�ȭ
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			m_tile[i][j] = NON_TILE;
			m_line[i][j] = 0;
			m_obj[i][j]  = 0;
		}
	}

	return true;
}

//<�� �ε�
bool tileMap::loadMap( const char *path )
{
	//< �� ���� �ʱ�ȭ
	releaseMap();

	FILE *fp=NULL;

	//< ���� ���� & ���� ó��
	if( NULL != fopen_s(&fp, path, "r") )
	{
#ifdef _DEBUG
		LOG_MGR->addLog("%s, %s : %d", "�� �ε� ����", "tileMap.cpp", __LINE__ );
#endif
		return false;
	}
	//< �� ũ�� Ȯ��
	fscanf_s(fp, "%d,",&mapSizeX);
	fscanf_s(fp, "%d\n",&mapSizeY);

	//< ������ �Ҵ�
	if( m_tile == NULL && m_line == NULL )
	{
		//< Ÿ�ϸ�, ��, ������Ʈ 2�� ������ �Ҵ�
		m_tile = new tileType*[mapSizeY];
		m_line = new tileType*[mapSizeY];
		m_obj  = new tileType*[mapSizeY];
		for(int i=0;i<mapSizeY;i++)
		{
			m_tile[i] = new tileType[mapSizeX];
			m_line[i] = new tileType[mapSizeX];
			m_obj[i]  = new tileType[mapSizeX];
		}
	}

	//< �� ���� �ҷ�����
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< �б�
			fscanf_s(fp, "%5d(%4d,%4d),", &m_tile[i][j], &m_line[i][j], &m_obj[i][j] );
		}
		fscanf_s(fp, "\n");
	}
	fclose(fp);

#ifdef _DEBUG
	LOG_MGR->addLog("�� �ε� ����");
#endif
	return true;
}

//<�� ���̺�
bool tileMap::saveMap( const char *path )
{
	FILE *fp=NULL;

	//< ���� ���� & ���� ó��
	if( NULL != fopen_s(&fp, path, "w") )
	{
#ifdef _DEBUG
		LOG_MGR->addLog("%s, %s : %d", "�� ���� ����", "tileMap.cpp", __LINE__ );
#endif
		return false;
	}
	//< �� ũ�� ����
	fprintf_s(fp, "%5d,",mapSizeX);
	fprintf_s(fp, "%5d\n",mapSizeY);	

	//< �� ���� �����ϱ�
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< ����
			fprintf_s(fp, "%5d(%4d,%4d),", m_tile[i][j], m_line[i][j], m_obj[i][j] );
		}
		fprintf_s(fp, "\n");
	}
	fclose(fp);

#ifdef _DEBUG
	LOG_MGR->addLog("�� ���� �Ϸ� (%s)", path );
#endif
	return true;
}

//< �� ����
bool tileMap::releaseMap( void )
{
	if( NULL == m_tile || NULL == m_line || NULL == m_obj)
	{
		return false;
	}
	for(int i=0;i<mapSizeY;i++)
	{
		SAFE_DELETE_ARR( m_tile[i] );
		SAFE_DELETE_ARR( m_line[i] );
		SAFE_DELETE_ARR( m_obj[i] );
	}
	SAFE_DELETE_ARR( m_tile );
	SAFE_DELETE_ARR( m_line );
	SAFE_DELETE_ARR( m_obj );

#ifdef _DEBUG
	LOG_MGR->addLog("�� ���� ���� ����");
#endif
	return true;
}

//< Ÿ�� �귯�� �ٲٱ�
void tileMap::nextBrush(void)
{
	if( m_brush == NON_TILE || TILE_END <= ++m_brush )
	{
		m_brush = TILE_NORMAL;
	}
}
void tileMap::prevBrush(void)
{
	if( NON_TILE == m_brush || TILE_NORMAL == m_brush )
	{
		m_brush = TILE_END-1;
	}
	else
	{
		m_brush--;
	}
}

//< �귯�� �׸���
void tileMap::stempBrush( int i, int j )
{
	if( (GetAsyncKeyState(VK_LBUTTON) & 0x8000)? 1: 0 )
	{
		//< ���� ���̸�
		if( m_brush == TILE_L_WALL )
		{
			m_line[i][j] = TILE_L_WALL;
		}
		//< ������ ���̸�
		else if( m_brush == TILE_R_WALL )
		{
			m_line[i][j+1] = TILE_R_WALL;
		}
		//< ������Ʈ��
		else if( m_brush == OBJ_BOOK_L || m_brush == OBJ_BOOK_R )
		{
			m_obj[i+1][j+1] = m_brush;
		}
		//< �� ��

		else
		{
			m_tile[i+1][j+1] = m_brush;
			//< ���
			if( m_brush == TILE_STAIR_L || m_brush == TILE_STAIR_R )
			{
				m_line[i][j+1] = m_brush;
				m_line[i+1][j+1] = m_brush;
			}
		}
	}
	if( (GetAsyncKeyState(VK_RBUTTON) & 0x8000)? 1: 0 )
	{
		if( m_brush == TILE_L_WALL )
		{
			m_line[i][j] = 0;
		}
		else if( m_brush == TILE_R_WALL )
		{
			m_line[i][j+1] = 0;
		}
		else if( m_brush == OBJ_BOOK_L || m_brush == OBJ_BOOK_R )
		{
			m_obj[i+1][j+1] = 0;
		}
		else
		{
			m_tile[i+1][j+1] = NON_TILE;
		}
	}
}