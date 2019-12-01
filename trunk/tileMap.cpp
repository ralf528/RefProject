#include "stdafx.h"
#include "ImageNode.h"
//#include "goblin.h"
#include "Unitclass/mon_bug.h"
//#include "ghoul.h"
//#include "Dark_spider.h"
//#include "Ghost.h"
//#include "Human_thief.h"
//#include "Human_knight.h"
//#include "Boss_naid.h"
//#include "Boss_gyuriel.h"

#include "tileMap.h"

using namespace myUTIL;
using namespace collision;

//< �� ��ȣ ������� ����
int tileMap::m_mapNum[MAP_MAX_FLOOR]={1,2,3,4,5};

tileMap::tileMap(void)
{
	//< ���� �� ��ȣ �ο�
	//setMapNum();
}

tileMap::~tileMap(void)
{
	release();
}

//�ʱ�ȭ
bool tileMap::init( void )
{
	//< 1������
	m_nowFloor = 1;

	//< Ÿ�� �� �ε�
	loadMap( START_LOAD_MAP_PATH );

	//< Ÿ�� �̹���
	m_imgTile = new ImageNode[TILE_END];

	m_imgTile[TILE_NORMAL].load("Data/Resource/tileMap/Tile_Nomal.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_CHAR	].load("Data/Resource/tileMap/Tile_Char.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_ITEM	].load("Data/Resource/tileMap/Tile_Item.bmp",0,0,RM_TRANS);

	m_imgTile[TILE_MON].load("Data/Resource/tileMap/Tile_Mon.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_01].load("Data/Resource/tileMap/Mon01.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_02].load("Data/Resource/tileMap/Mon02.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_03].load("Data/Resource/tileMap/Mon03.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_04].load("Data/Resource/tileMap/Mon04.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_05].load("Data/Resource/tileMap/Mon05.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_06].load("Data/Resource/tileMap/Mon06.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_MON_07].load("Data/Resource/tileMap/Mon07.bmp",0,0,RM_TRANS);

	m_imgTile[TILE_ALTAR].load("Data/Resource/tileMap/Tile_Altar.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_BOOK_L].load("Data/Resource/tileMap/Wall_BOOK_Left.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_BOOK_R].load("Data/Resource/tileMap/Wall_BOOK_Right.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR_F].load("Data/Resource/tileMap/Stair_Front.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR].load("Data/Resource/tileMap/Stair.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR_L].load("Data/Resource/tileMap/Stair_Left.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_STAIR_R].load("Data/Resource/tileMap/Stair_Right.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_COLLUM].load("Data/Resource/tileMap/Collum.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_L_WALL].load("Data/Resource/tileMap/Wall_Left.bmp",0,0,RM_TRANS);
	m_imgTile[TILE_R_WALL].load("Data/Resource/tileMap/Wall_Right.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_ALTAR].load("Data/Resource/tileMap/ALTAR.bmp",0,0,RM_TRANS);
	m_imgTile[OBJ_ALTAR_DISABLE].load("Data/Resource/tileMap/ALTAR_disable.bmp",0,0,RM_TRANS);

	return true;
}
//����
void tileMap::release(void)
{
	releaseMap();
	SAFE_DELETE_ARR( m_imgTile );
}

//����
void tileMap::render( HDC hdc )
{
	//< Ÿ�� �׸���
	renderTile( hdc );
}

//< Ÿ�� �׸���
void tileMap::renderTile( HDC hdc )
{
#ifdef _DEBUG
	HPEN myPen, oldPen;
	myPen = CreatePen( PS_SOLID, 2, RGB(255,0,0) );
	oldPen = (HPEN)SelectObject(hdc, myPen);
#endif
	//< Ÿ�� �׸���
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< Ÿ���� �����Ѵٸ�
			if( NON_TILE != m_tile[i][j] )
			{			
				if( m_tile[i][j] <= NORMAL_TILE_END )
				{
#ifdef _DEBUG		
					if( m_tile[i][j] >= TILE_MON && m_tile[i][j] <= TILE_MON_20 )
					{   //< ���� Ÿ���� �Ϲ� Ÿ�Ϸ�
						m_imgTile[TILE_NORMAL].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
					}
					else
					{
						//< ������Ʈ ��ġ Ÿ���� ����� ��忡���� ����
						m_imgTile[m_tile[i][j]].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
							(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
					}
#else if _RELEASE	//< �Ϲ� Ÿ��
					m_imgTile[TILE_NORMAL].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
#endif				
				}
				else
				{
					//< ���, ��� ��
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
#ifdef _DEBUG
			//< ��(��) �׸���
			if( m_line[i][j] == TILE_L_WALL )
			{
				MoveToEx( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), i * TILE_SIZE_Y - CAMERA->getY(), NULL );
				LineTo( hdc, j * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
			}
			else if( m_line[i][j] == TILE_R_WALL )
			{
				MoveToEx( hdc, j * TILE_SIZE_X - CAMERA->getX(), i * TILE_SIZE_Y - CAMERA->getY(), NULL );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
			}
#endif
		}
	}

	//< ������Ʈ �׸���
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< ����
			if( m_obj[i][j] >= ITEM_FIRST && m_obj[i][j] < ITEM_END )
			{
				unsigned int id = m_obj[i][j] - ITEM_FIRST + imgID_POTION_1;
				RENDER_MGR->render( hdc, id, (TILE_SIZE_X * j) - POTION_SIZE_X/2 - CAMERA->getX() ,
									(TILE_SIZE_Y * i) - POTION_SIZE_Y/2 - CAMERA->getY() );
			}
			//< å��
			if( m_obj[i][j] == OBJ_BOOK_L )
			{
				m_imgTile[OBJ_BOOK_L].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X/2 - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - TILE_SIZE_Y/2 - CAMERA->getY() );
			}
			//< å��
			if( m_obj[i][j] == OBJ_BOOK_R )
			{
				m_imgTile[OBJ_BOOK_R].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X/2 - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - TILE_SIZE_Y/2 - CAMERA->getY() );
			}
		}
	}
#ifdef _DEBUG
	DeleteObject( SelectObject(hdc, oldPen) );
#endif
}
//< �� �׸���
void tileMap::renderWall( HDC hdc )
{
//#ifdef _DEBUG
//	HPEN myPen, oldPen;
//	myPen = CreatePen( PS_SOLID, 2, RGB(255,0,0) );
//	oldPen = (HPEN)SelectObject(hdc, myPen);
//#endif
//	//< �� �׸���
//	for(int i=0 ; i<mapSizeY ; i++)
//	{
//		for(int j=0 ; j<mapSizeX ; j++)
//		{
//			if( 0 != m_line[i][j] )
//			{
//				if( m_line[i][j] == TILE_L_WALL )
//				{
//					m_imgTile[TILE_L_WALL].render( hdc, (TILE_SIZE_X * j) - CAMERA->getX() ,
//						(TILE_SIZE_Y * i) + TILE_SIZE_X - m_imgTile[TILE_L_WALL].getSize().cy - CAMERA->getY() );
//				}
//				if( m_line[i][j] == TILE_R_WALL )
//				{
//					m_imgTile[TILE_R_WALL].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
//						(TILE_SIZE_Y * i) + (2*TILE_SIZE_Y) - m_imgTile[TILE_R_WALL].getSize().cy - CAMERA->getY() );
//				}
//			}
//#ifdef _DEBUG
//			//< ��(��) �׸���
//			if( m_line[i][j] == TILE_L_WALL )
//			{
//				MoveToEx( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), i * TILE_SIZE_Y - CAMERA->getY(), NULL );
//				LineTo( hdc, j * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
//			}
//			else if( m_line[i][j] == TILE_R_WALL )
//			{
//				MoveToEx( hdc, j * TILE_SIZE_X - CAMERA->getX(), i * TILE_SIZE_Y - CAMERA->getY(), NULL );
//				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
//			}	
//#endif
//		}
//	}
//
//#ifdef _DEBUG
//	DeleteObject( SelectObject(hdc, oldPen) );
//#endif
}

//�� �ε�
bool tileMap::loadMap( const char *path )
{
	//< ĳ���� ��ǥ �ʱ�ȭ
	m_charPos.x = 100;
	m_charPos.y = 100;

	FILE *fp=NULL;

	//< ���� ���� & ���� ó��
	if( NULL != fopen_s(&fp, path, "r") )
	{
		LOG_MGR->addLog("%s, %s : %d", "�� �ε� ����", "tileMap.cpp", __LINE__ );
		return false;
	}
	LOG_MGR->addLog("Ÿ�� �� �ε� : %s", path );
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

	int count = 0;
	//< ���� ���� �ʱ�ȭ
	MON_MGR->release();

	int itemCnt = 0;

	//< �� ���� �ҷ�����
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< �б�
			fscanf_s(fp, "%5d(%4d,%4d),", &m_tile[i][j], &m_line[i][j], &m_obj[i][j] );

			//< ĳ���� Ÿ���̸� ĳ������ ��ġ ����
			if( m_tile[i][j] == TILE_CHAR )
			{
				//< ���� ��ġ ����
				if( count++ == 0 )
				{
					m_charPos.x = j * TILE_SIZE_X;
					m_charPos.y = i * TILE_SIZE_Y;
				}
				else
				{
					//< �� �ٸ� Ÿ���� ������ ���� Ȯ���� ���ο� ������ ����
					if( rand()%2 == 0 )
					{
						m_charPos.x = j * TILE_SIZE_X;
						m_charPos.y = i * TILE_SIZE_Y;
					}
				}
			}
			if( rand()%2 == 0 )
			goto HERE;

            //< ���� Ÿ���̸� ���� ����
			if( m_tile[i][j] == TILE_MON_01)
			{
				//< ���� ����
                Monster *mon = new mon_bug();// boss_naid;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}
			else if( m_tile[i][j] == TILE_MON_02)
			{
				//< ���� ����
				Monster *mon = new mon_bug();//mon_bug;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}
			else if( m_tile[i][j] == TILE_MON_03)
			{
				//< ���� ����
				Monster *mon = new mon_bug();//ghoul;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}
			else if( m_tile[i][j] == TILE_MON_04)
			{
				//< ���� ����
				Monster *mon = new mon_bug();//Dark_spider;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}
			else if( m_tile[i][j] == TILE_MON_05)
			{
				//< ���� ����
				Monster *mon = new mon_bug();//Ghost;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}

			else if( m_tile[i][j] == TILE_MON_06)
			{
				//< ���� ����
				Monster *mon = new mon_bug();//Human_thief;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}

			else if( m_tile[i][j] == TILE_MON_07)
			{
				//< ���� ����
				Monster *mon = new mon_bug;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
			}
			else if( m_nowFloor%5 == 0 && m_tile[i][j] == TILE_MON_08)
			//else if( m_tile[i][j] == TILE_MON_08 && true == HOST_SERVER->getHostis())
			{
				//< 5�������� ���� ���� ����
				Monster *mon = new mon_bug;
				mon->setPos( j * TILE_SIZE_X, i * TILE_SIZE_Y );
				//< ����Ʈ�� �߰�
				MON_MGR->addMonster(mon);
				MON_MGR->setBossMonster(mon);
			}
			//< ���� �߰�

			HERE:
			//< ������ Ÿ���̸� ������ ���� ����
			if( m_tile[i][j] == TILE_ITEM)
			{
				m_obj[i][j] = ITEM_FIRST + rand()%((ITEM_END-1)-ITEM_FIRST);
				
				//< ������ �ִ� ����
				if(itemCnt != 100)
				{
					POINT index = {i, j};
					itemCnt++;
				}
			}
			//< ��� Ÿ�Ͽ� ��Ż ����
			if( m_tile[i][j] == TILE_STAIR )
			{
				m_portal.x = j * TILE_SIZE_X;
				m_portal.y = i * TILE_SIZE_Y;
			}
			//< ���, ����
			if( m_tile[i][j] == TILE_COLLUM || m_tile[i][j] == OBJ_ALTAR || m_tile[i][j] == OBJ_ALTAR_DISABLE )
			{
				m_obj[i-1][j] = m_tile[i][j];
			}
			
		}
		fscanf_s(fp, "\n");
	}
	fclose(fp);	
	return true;
}
//< �� ����
bool tileMap::releaseMap( void )
{
	for(int i=0;i<mapSizeY;i++)
	{
		SAFE_DELETE_ARR( m_tile[i] );
		SAFE_DELETE_ARR( m_line[i] );
		SAFE_DELETE_ARR( m_obj[i] );
	}
	SAFE_DELETE_ARR( m_tile );
	SAFE_DELETE_ARR( m_line );
	SAFE_DELETE_ARR( m_obj );

	return true;
}

//�浹üũ
bool tileMap::collision( POINT &destPos, POINT *vertex )
{
	//< ���� ��ġ�� Ÿ��
	int tileX = destPos.x/TILE_SIZE_X;
	int tileY = destPos.y/TILE_SIZE_Y;

	//< �� ������ ������ ������ �浹
	if( destPos.x <= 0 || destPos.y <= 0 ||
		destPos.x >= mapSizeX * TILE_SIZE_X || destPos.y >= mapSizeY * TILE_SIZE_Y )
	{
		return true;
	}

	//< ���� 9�� Ÿ�Ͽ� ���� �浹üũ
	//< Ÿ�� �ε��� x, y �� �Ѵ� ¦���ų� �� �� Ȧ�����
	if( (tileX % 2 == 0 && tileY % 2 == 0) || ( tileX % 2 == 1 && tileY % 2 == 1) )
	{
		//< ���� Ÿ�Ͽ� ���� �ִ��� Ȯ���ϰ�, �ִٸ� �浹 üũ
		if( ( tileX >= 1 && tileY >=1 )  && m_line[tileY-1][tileX-1] != 0 
			&& isColLineAndCir( vertex[2], vertex[0], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileY >=1 )  && m_line[tileY-1][tileX] != 0 
			&& isColLineAndCir( vertex[0], vertex[3], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX+1 < mapSizeX && tileY >=1 )  && m_line[tileY-1][tileX+1] != 0 
			&& isColLineAndCir( vertex[3], vertex[1], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX >= 1 )  && m_line[tileY][tileX-1] != 0 
			&& isColLineAndCir( vertex[2], vertex[4], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( m_line[tileY][tileX] != 0 
			&& isColLineAndCir( vertex[4], vertex[3], destPos, CHARACTER_SIZE_Y ) == true)
		{
			return true;
		}
		if( ( tileX+1 < mapSizeX ) && m_line[tileY][tileX+1] != 0 
			&& isColLineAndCir( vertex[3], vertex[5], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX >= 1 && tileY+1 < mapSizeY )  && m_line[tileY+1][tileX-1] != 0 
			&& isColLineAndCir( vertex[6], vertex[4], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileY+1 < mapSizeY ) && m_line[tileY+1][tileX] != 0 
			&& isColLineAndCir( vertex[4], vertex[7], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX+1 < mapSizeX && tileY+1 < mapSizeY ) && m_line[tileY+1][tileX+1] != 0 
			&& isColLineAndCir( vertex[7], vertex[5], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		return false;
	}
	else
	{
		if( ( tileX >= 1 && tileY >=1 )  && m_line[tileY-1][tileX-1] != 0 
			&& isColLineAndCir( vertex[2], vertex[0], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileY >=1 )  && m_line[tileY-1][tileX] != 0 
			&& isColLineAndCir( vertex[2], vertex[1], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX+1 < mapSizeX && tileY >=1 )  && m_line[tileY-1][tileX+1] != 0 
			&& isColLineAndCir( vertex[3], vertex[1], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX >= 1 )  && m_line[tileY][tileX-1] != 0 
			&& isColLineAndCir( vertex[2], vertex[4], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( m_line[tileY][tileX] != 0 
			&& isColLineAndCir( vertex[2], vertex[5], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX+1 < mapSizeX ) && m_line[tileY][tileX+1] != 0 
			&& isColLineAndCir( vertex[3], vertex[5], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX >= 1 && tileY+1 < mapSizeY )  && m_line[tileY+1][tileX-1] != 0 
			&& isColLineAndCir( vertex[6], vertex[4], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileY+1 < mapSizeY ) && m_line[tileY+1][tileX] != 0 
			&& isColLineAndCir( vertex[6], vertex[5], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
		if( ( tileX+1 < mapSizeX && tileY+1 < mapSizeY ) && m_line[tileY+1][tileX+1] != 0 
			&& isColLineAndCir( vertex[7], vertex[5], destPos, CHARACTER_SIZE_Y ) == true )
		{
			return true;
		}
	}
	return false;
}

//< ������ 8���� ���� üũ
void  tileMap::aroundLine( POINT &destPos, POINT *vertex )
{
	//< ���� ��ġ�� Ÿ��
	int tileX = destPos.x/TILE_SIZE_X;
	int tileY = destPos.y/TILE_SIZE_Y;

	//�Ѵ� ¦���ų� �Ѵ� Ȧ�����
	if( ( tileX % 2 == 0 && tileY % 2 == 0) || ( tileX % 2 == 1 && tileY % 2 == 1) )
	{
		vertex[0].x = (tileX) * TILE_SIZE_X;
		vertex[0].y = (tileY-1) * TILE_SIZE_Y;

		vertex[1].x = (tileX+2) * TILE_SIZE_X;
		vertex[1].y = (tileY-1) * TILE_SIZE_Y;

		vertex[2].x = (tileX-1) * TILE_SIZE_X;
		vertex[2].y = (tileY) * TILE_SIZE_Y;

		vertex[3].x = (tileX+1) * TILE_SIZE_X;
		vertex[3].y = (tileY) * TILE_SIZE_Y;

		vertex[4].x = (tileX) * TILE_SIZE_X;
		vertex[4].y = (tileY+1) * TILE_SIZE_Y;

		vertex[5].x = (tileX+2) * TILE_SIZE_X;
		vertex[5].y = (tileY+1) * TILE_SIZE_Y;

		vertex[6].x = (tileX-1) * TILE_SIZE_X;
		vertex[6].y = (tileY+2) * TILE_SIZE_Y;

		vertex[7].x = (tileX+1) * TILE_SIZE_X;
		vertex[7].y = (tileY+2) * TILE_SIZE_Y;
	}
	else
	{
		vertex[0].x = (tileX-1) * TILE_SIZE_X;
		vertex[0].y = (tileY-1) * TILE_SIZE_Y;

		vertex[1].x = (tileX+1) * TILE_SIZE_X;
		vertex[1].y = (tileY-1) * TILE_SIZE_Y;

		vertex[2].x = (tileX) * TILE_SIZE_X;
		vertex[2].y = (tileY) * TILE_SIZE_Y;

		vertex[3].x = (tileX+2) * TILE_SIZE_X;
		vertex[3].y = (tileY) * TILE_SIZE_Y;

		vertex[4].x = (tileX-1) * TILE_SIZE_X;
		vertex[4].y = (tileY+1) * TILE_SIZE_Y;

		vertex[5].x = (tileX+1) * TILE_SIZE_X;
		vertex[5].y = (tileY+1) * TILE_SIZE_Y;

		vertex[6].x = (tileX) * TILE_SIZE_X;
		vertex[6].y = (tileY+2) * TILE_SIZE_Y;

		vertex[7].x = (tileX+2) * TILE_SIZE_X;
		vertex[7].y = (tileY+2) * TILE_SIZE_Y;
	}
}

//< ������Ʈ�� �浹üũ
tileType tileMap::collisionObject( POINT &destPos )
{
	//< ���� ��ġ�� Ÿ��
	int tileX = destPos.x/TILE_SIZE_X;
	int tileY = destPos.y/TILE_SIZE_Y;

	//< �ӽ� ����( ������Ʈ ��Ʈ, ��ǥ )
	RECT rt;
	int x, y;

	if(0 >= tileX || 0 >= tileY)
	{
		return 0;
	}

	//< ���� Ÿ�� �˻� (���� �ƹ��� Ŀ���� ���� 9�� Ÿ�ϸ� �˻�)
	for( int i = tileY-1 ; i <= tileY + 1 ; i++ )
	{
		for( int j = tileX-1 ; j <= tileX + 1 ; j++ )
		{
//< �˻����� ���� ǥ��
#ifdef _DEBUG
			Ellipse( RENDER_MGR->getMainDC(), j*TILE_SIZE_X - 3 - CAMERA->getX(), i*TILE_SIZE_Y - 3 - CAMERA->getY(),
												j*TILE_SIZE_X + 3 - CAMERA->getX(), i*TILE_SIZE_Y + 3 - CAMERA->getY() );
#endif
			//������Ʈ�� �ִٸ� �˻� ����
			if( 0 != m_obj[i][j] )
			{
//< ������Ʈ ������ ũ�� ǥ��
#ifdef _DEBUG
				Ellipse( RENDER_MGR->getMainDC(), j*TILE_SIZE_X - 10 - CAMERA->getX(), i*TILE_SIZE_Y - 10 - CAMERA->getY(),
					j*TILE_SIZE_X + 10 - CAMERA->getX(), i*TILE_SIZE_Y + 10 - CAMERA->getY() );
#endif
				//< ������Ʈ ��ǥ ���ϱ�
				x = j * TILE_SIZE_X;
				y = i * TILE_SIZE_Y;
				//< ��Ʈ ����
				SetRect( &rt, x - CHARACTER_SIZE_Y, y - CHARACTER_SIZE_Y, x + CHARACTER_SIZE_Y, y + CHARACTER_SIZE_Y );
				//< �浹 üũ
				if( collision::isColPtInCircle( destPos, rt ) )
				{
					//< ���ϰ� ����
					tileType rtn = m_obj[i][j];
					//< å���̸�
					if( rtn == OBJ_BOOK_L || rtn == OBJ_BOOK_R )
					{
						//m_obj[i][j] = 0;
					}
					//< �������̸� �����
					else if( rtn >= ITEM_FIRST && rtn < ITEM_END )
					{
						//SOUND_MGR->soundPlay(SOUND_BGM9);
						m_obj[i][j] = 0;
					}
					//< ����̸� ��Ȱ��ȭ
					else if( rtn == OBJ_ALTAR )
					{
						m_obj[i][j] = OBJ_ALTAR_DISABLE;
						m_tile[i+1][j] = OBJ_ALTAR_DISABLE;
					}
					//< �浹�Ǹ� ������Ʈ ID ����
					return rtn;
				}
			}
//< ���� ������ ũ�� ǥ��
#ifdef _DEBUG
			if( TILE_L_WALL == m_line[i][j] || TILE_R_WALL == m_line[i][j] )
			{
				Ellipse( RENDER_MGR->getMainDC(), j*TILE_SIZE_X - 10 - CAMERA->getX(), i*TILE_SIZE_Y - 10 - CAMERA->getY(),
					j*TILE_SIZE_X + 10 - CAMERA->getX(), i*TILE_SIZE_Y + 10 - CAMERA->getY() );
			}
#endif
		}
	}
	return 0;
}

//��Ż
bool tileMap::inPortal( POINT &destPos )
{
	//< ��Ż(���)�� Ÿ�� �� �� ������
	if( IsColPortal(destPos) == true )
	{
		//< �� �� �ö󰡱� (���������̸� 1������)
		if( ++m_nowFloor > MAP_MAX_FLOOR )
		{
			m_nowFloor = 1;
		}
		//< ���� �� ����
		releaseMap();
		//< ���ο� �� �ҷ�����
		switch( m_mapNum[m_nowFloor-1] )
		{
		case 1:
			loadMap( LOAD_MAP_1_PATH );
			break;
		case 2:
			loadMap( LOAD_MAP_2_PATH );
			break;
		case 3:
			loadMap( LOAD_MAP_3_PATH );
			break;
		case 4:
			loadMap( LOAD_MAP_4_PATH );
			break;
		case 5:
			loadMap( LOAD_MAP_5_PATH );
			break;
		}
		//PACKET packet;
		//packet.m_map.m_length = sizeof(P2P_MAP);
		//packet.m_map.m_type = P2P_NEXT_STAGE;
		//packet.m_map.m_index = //< �ٲ���� ���ڸ� ���۷��� character �� �޾Ƽ� �޽��� ����
		//packet.m_map.mapId = m_mapNum[m_nowFloor-1];
		//packet.m_map.pos = this->getCharPos();

	}
	return true;
}

//< ���� �� ��ȣ �ο�
void tileMap::setMapNum(void)
{
	//< �������� ����
	for(int i = 0 ; i< 10 ; i++ )
	{
		int left = rand()%(MAP_MAX_FLOOR-1)+1;
		int right = rand()%(MAP_MAX_FLOOR-1)+1;

		int temp = m_mapNum[left];
		m_mapNum[left] = m_mapNum[right];
		m_mapNum[right] = temp;
    }
}

//< ȣ��Ʈ�� ���� �� ����
void tileMap::setMapNumByNetwork(const int *arr)
{
}
