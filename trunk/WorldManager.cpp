#include "stdafx.h"
#include "ImageNode.h"
#include "WorldManager.h"

using namespace myUTIL;
using namespace collision;


WorldManager::WorldManager(void)
{
	for (int i = 0; i < MAP_MAX_FLOOR; i++)
	{
		m_mapNum[i] = i + 1;
	}

	//< 랜덤 맵 번호 부여
#ifndef _DEBUG
	setMapNum();
#endif // DEBUG
}

WorldManager::~WorldManager(void)
{
	release();
}

//초기화
bool WorldManager::init( void )
{
	//< 1층으로
	m_nowFloor = 1;

	//< 타일 맵 로드
	loadMap( START_LOAD_MAP_PATH );

	//< 타일 이미지
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
//해제
void WorldManager::release(void)
{
	releaseMap();
	SAFE_DELETE_ARR( m_imgTile );
}

//렌더
void WorldManager::render( HDC hdc )
{
	//< 타일 그리기
	renderTile( hdc );
}

//< 타일 그리기
void WorldManager::renderTile( HDC hdc )
{
#ifdef _DEBUG
	HPEN myPen, oldPen;
	myPen = CreatePen( PS_SOLID, 2, RGB(255,0,0) );
	oldPen = (HPEN)SelectObject(hdc, myPen);
#endif
	//< 타일 그리기
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< 타일이 존재한다면
			if( NON_TILE != m_tile[i][j] )
			{			
				if( m_tile[i][j] <= NORMAL_TILE_END )
				{
#ifdef _DEBUG		
					if( m_tile[i][j] >= TILE_MON && m_tile[i][j] <= TILE_MON_20 )
					{   //< 몬스터 타일은 일반 타일로
						m_imgTile[TILE_NORMAL].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
					}
					else
					{
						//< 오브젝트 배치 타일은 디버그 모드에서만 랜더
						m_imgTile[m_tile[i][j]].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
							(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
					}
#else if _RELEASE	//< 일반 타일
					m_imgTile[TILE_NORMAL].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - CAMERA->getY() );
#endif				
				}
				else
				{
					//< 기둥, 계단 등
					m_imgTile[m_tile[i][j]].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y*4 - 13 - CAMERA->getY() );
				}
			}
		}
	}

	//< 벽 그리기
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
			//< 선(벽) 그리기
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

	//< 오브젝트 그리기
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< 포션
			if( m_obj[i][j] >= ITEM_FIRST && m_obj[i][j] < ITEM_END )
			{
				unsigned int id = m_obj[i][j] - ITEM_FIRST + imgID_POTION_1;
				RENDER_MGR->render( hdc, id, (TILE_SIZE_X * j) - POTION_SIZE_X/2 - CAMERA->getX() ,
									(TILE_SIZE_Y * i) - POTION_SIZE_Y/2 - CAMERA->getY() );
			}
			//< 책장
			if( m_obj[i][j] == OBJ_BOOK_L )
			{
				m_imgTile[OBJ_BOOK_L].render( hdc, (TILE_SIZE_X * j) - TILE_SIZE_X/2 - CAMERA->getX() ,
						(TILE_SIZE_Y * i) - TILE_SIZE_Y - TILE_SIZE_Y/2 - CAMERA->getY() );
			}
			//< 책장
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
//< 벽 그리기
void WorldManager::renderWall( HDC hdc )
{
//#ifdef _DEBUG
//	HPEN myPen, oldPen;
//	myPen = CreatePen( PS_SOLID, 2, RGB(255,0,0) );
//	oldPen = (HPEN)SelectObject(hdc, myPen);
//#endif
//	//< 벽 그리기
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
//			//< 선(벽) 그리기
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

//맵 로드
bool WorldManager::loadMap( const char *path )
{
	//< 캐릭터 좌표 초기화
	m_SpawnPos.x = 100;
	m_SpawnPos.y = 100;

	FILE *fp=NULL;

	//< 파일 오픈 & 에러 처리
	if( NULL != fopen_s(&fp, path, "r") )
	{
		LOG_MGR->addLog("%s, %s : %d", "맵 로드 실패", "tileMap.cpp", __LINE__ );
		return false;
	}
	LOG_MGR->addLog("타일 맵 로드 : %s", path );
	//< 맵 크기 확인
	fscanf_s(fp, "%d,",&mapSizeX);
	fscanf_s(fp, "%d\n",&mapSizeY);

	//< 포인터 할당
	if( m_tile == NULL && m_line == NULL )
	{
		//< 타일맵, 선, 오브젝트 2차 포인터 할당
		m_tile = new E_TileBrush*[mapSizeY];
		m_line = new E_TileBrush*[mapSizeY];
		m_obj  = new E_TileBrush*[mapSizeY];
		for(int i=0;i<mapSizeY;i++)
		{
			m_tile[i] = new E_TileBrush[mapSizeX];
			m_line[i] = new E_TileBrush[mapSizeX];
			m_obj[i]  = new E_TileBrush[mapSizeX];
		}
	}

	int count = 0;
	//< 몬스터 정보 초기화
	MON_MGR->release();

	int itemCnt = 0;

	//< 맵 정보 불러오기
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< 읽기
			fscanf_s(fp, "%5d(%4d,%4d),", &m_tile[i][j], &m_line[i][j], &m_obj[i][j] );

			//< 캐릭터 타일이면 캐릭터의 위치 지정
			if( m_tile[i][j] == TILE_CHAR )
			{
				//< 최초 위치 갱신
				if( count++ == 0 )
				{
					m_SpawnPos.x = j * TILE_SIZE_X;
					m_SpawnPos.y = i * TILE_SIZE_Y;
				}
				else
				{
					//< 또 다른 타일이 나오면 일정 확률로 새로운 곳으로 지정
					if( rand()%2 == 0 )
					{
						m_SpawnPos.x = j * TILE_SIZE_X;
						m_SpawnPos.y = i * TILE_SIZE_Y;
					}
				}
			}

			//< 몬스터 추가
			MON_MGR->CreateMonster(m_tile[i][j], j * TILE_SIZE_X, i * TILE_SIZE_Y);

			//< 아이템 타일이면 아이템 랜덤 생성
			if( m_tile[i][j] == TILE_ITEM)
			{
				m_obj[i][j] = static_cast<E_TileBrush>(ITEM_FIRST + rand()%((ITEM_END-1)-ITEM_FIRST));
				
				//< 아이템 최대 개수
				if(itemCnt != 100)
				{
					POINT index = {i, j};
					itemCnt++;
				}
			}

			//< 계단 타일에 포탈 생성
			if( m_tile[i][j] == TILE_STAIR )
			{
				m_portalPos.x = j * TILE_SIZE_X;
				m_portalPos.y = i * TILE_SIZE_Y;
			}

			//< 기둥, 제단
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

//< 맵 해제
bool WorldManager::releaseMap( void )
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

//충돌체크
bool WorldManager::collision( POINT &destPos, POINT *vertex )
{
	//< 현재 위치한 타일
	int tileX = destPos.x/TILE_SIZE_X;
	int tileY = destPos.y/TILE_SIZE_Y;

	//< 맵 사이즈 밖으로 나가면 충돌
	if( destPos.x <= 0 || destPos.y <= 0 ||
		destPos.x >= mapSizeX * TILE_SIZE_X || destPos.y >= mapSizeY * TILE_SIZE_Y )
	{
		return true;
	}

	//< 주위 9개 타일에 대한 충돌체크
	//< 타일 인덱스 x, y 가 둘다 짝수거나 둘 다 홀수라면
	if( (tileX % 2 == 0 && tileY % 2 == 0) || ( tileX % 2 == 1 && tileY % 2 == 1) )
	{
		//< 먼저 타일에 선이 있는지 확인하고, 있다면 충돌 체크
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

//< 주위의 8개의 정점 체크
void  WorldManager::aroundLine( POINT &destPos, POINT *vertex )
{
	//< 현재 위치한 타일
	int tileX = destPos.x/TILE_SIZE_X;
	int tileY = destPos.y/TILE_SIZE_Y;

	//둘다 짝수거나 둘다 홀수라면
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

//< 오브젝트와 충돌체크
E_TileBrush WorldManager::collisionObject( POINT &destPos )
{
	//< 현재 위치한 타일
	int tileX = destPos.x/TILE_SIZE_X;
	int tileY = destPos.y/TILE_SIZE_Y;

	//< 임시 변수( 오브젝트 렉트, 좌표 )
	RECT rt;
	int x, y;

	if(0 >= tileX || 0 >= tileY)
	{
		return TILE_NORMAL;
	}

	//< 주위 타일 검색 (맵이 아무리 커져도 주위 9개 타일만 검사)
	for( int i = tileY-1 ; i <= tileY + 1 ; i++ )
	{
		for( int j = tileX-1 ; j <= tileX + 1 ; j++ )
		{
//< 검사중인 영역 표시
#ifdef _DEBUG
			Ellipse( RENDER_MGR->getMainDC(), j*TILE_SIZE_X - 3 - CAMERA->getX(), i*TILE_SIZE_Y - 3 - CAMERA->getY(),
												j*TILE_SIZE_X + 3 - CAMERA->getX(), i*TILE_SIZE_Y + 3 - CAMERA->getY() );
#endif
			//오브젝트가 있다면 검사 시작
			if( 0 != m_obj[i][j] )
			{
//< 오브젝트 있으면 크게 표시
#ifdef _DEBUG
				Ellipse( RENDER_MGR->getMainDC(), j*TILE_SIZE_X - 10 - CAMERA->getX(), i*TILE_SIZE_Y - 10 - CAMERA->getY(),
					j*TILE_SIZE_X + 10 - CAMERA->getX(), i*TILE_SIZE_Y + 10 - CAMERA->getY() );
#endif
				//< 오브젝트 좌표 구하기
				x = j * TILE_SIZE_X;
				y = i * TILE_SIZE_Y;
				//< 렉트 생성
				SetRect( &rt, x - CHARACTER_SIZE_Y, y - CHARACTER_SIZE_Y, x + CHARACTER_SIZE_Y, y + CHARACTER_SIZE_Y );
				//< 충돌 체크
				if( collision::isColPtInCircle( destPos, rt ) )
				{
					//< 리턴값 저장
					E_TileBrush rtn = m_obj[i][j];
					//< 책장이면
					if( rtn == OBJ_BOOK_L || rtn == OBJ_BOOK_R )
					{
						//m_obj[i][j] = 0;
					}
					//< 아이템이면 사라짐
					else if( rtn >= ITEM_FIRST && rtn < ITEM_END )
					{
						//SOUND_MGR->soundPlay(SOUND_BGM9);
						m_obj[i][j] = TILE_NORMAL;
					}
					//< 재단이면 비활성화
					else if( rtn == OBJ_ALTAR )
					{
						m_obj[i][j] = OBJ_ALTAR_DISABLE;
						m_tile[i+1][j] = OBJ_ALTAR_DISABLE;
					}
					//< 충돌되면 오브젝트 ID 리턴
					return rtn;
				}
			}

#ifdef _DEBUG
			//< 벽이 있으면 크게 표시
			if( TILE_L_WALL == m_line[i][j] || TILE_R_WALL == m_line[i][j] )
			{
				Ellipse(RENDER_MGR->getMainDC(),
					j*TILE_SIZE_X - 10 - CAMERA->getX(), i*TILE_SIZE_Y - 10 - CAMERA->getY(),
					j*TILE_SIZE_X + 10 - CAMERA->getX(), i*TILE_SIZE_Y + 10 - CAMERA->getY());
			}
#endif
		}
	}
	return TILE_NORMAL;
}

//포탈
bool WorldManager::inPortal( POINT &destPos )
{
	//< 포탈(계단)을 타면 한 층 오르기
	if( IsColPortal(destPos) == true )
	{
		//< 층 수 올라가기 (마지막층이면 1층으로)
		if( ++m_nowFloor > MAP_MAX_FLOOR )
		{
			m_nowFloor = 1;
		}

		//< 이전 맵 해제
		releaseMap();
		//< 새로운 맵 불러오기
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
	}
	return true;
}

//< 랜덤 맵 번호 부여
void WorldManager::setMapNum(void)
{
	//< 랜덤으로 섞기
	for (int i = 0; i < 10; i++)
	{
		int left = rand()%(MAP_MAX_FLOOR-1)+1;
		int right = rand()%(MAP_MAX_FLOOR-1)+1;

		int temp = m_mapNum[left];
		m_mapNum[left] = m_mapNum[right];
		m_mapNum[right] = temp;
    }
}
