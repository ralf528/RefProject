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

//초기화
bool tileMap::init( void )
{
	//< 타일 이미지
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
//해제
void tileMap::release(void)
{
	releaseMap();
	SAFE_DELETE_ARR( m_imgTile );
}

//갱신
void tileMap::update(void)
{
}

//렌더
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

	//< 타일 그리기
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< 타일이 존재한다면
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
		}
	}

	//< 오브젝트 그리기
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

	//< 마우스가 올려진 타일의 선 그리기
	collisionTile( hdc );
	
	
	//< 마우스 좌표 얻기
	int x = keyInput::getMousePos().x;
	int y = keyInput::getMousePos().y;

	if (m_brush != NON_TILE)
	{
		//< 선택된 브러쉬 알파 블랜드
		m_imgTile[m_brush].renderAlpha(hdc, x - m_imgTile[m_brush].getSize().cx / 2, y - m_imgTile[m_brush].getSize().cy / 2, 150);
	}

	DeleteObject( SelectObject( hdc, oldPen ) );
}

//< 마우스가 올려진 타일 그리기
void tileMap::collisionTile( HDC hdc )
{
	//< 마우스 좌표 얻기
	int x = keyInput::getMousePos().x + CAMERA->getX();
	int y = keyInput::getMousePos().y + CAMERA->getY();

	// 타일의 선마다 기울기가 다르기 때문에
	// 반복문을 두 번 돌림
	for(int i=0 ; i<mapSizeY ; i+=2)
	{
		for(int j=0 ; j<mapSizeX ; j+=2)
		{
			//< 타일의 위치 구하기
			POINT m_position;
			m_position.x = (j+1) * TILE_SIZE_X;
			m_position.y = i * TILE_SIZE_Y;

			//< 마름모 구하는 식(?)
			int ax = static_cast<int>( (-TILE_SIZE_Y/(float)TILE_SIZE_X) * (x - m_position.x));
			int yPlusax = y + ax;
			int yMinusax = y - ax;
			int tileBottom = m_position.y + TILE_SIZE_Y*2;

			//< 점이 타일 내부에 있다면
			if(yMinusax - m_position.y > 0 &&
				yPlusax - m_position.y > 0 &&
				yMinusax - tileBottom < 0 &&
				yPlusax - tileBottom < 0)
			{
				//< 마름모 선 그리기
				MoveToEx( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i) * TILE_SIZE_Y - CAMERA->getY(), NULL );
				LineTo( hdc, (j+2) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i+2) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j) * TILE_SIZE_X - CAMERA->getX(), (i+1) * TILE_SIZE_Y - CAMERA->getY() );
				LineTo( hdc, (j+1) * TILE_SIZE_X - CAMERA->getX(), (i) * TILE_SIZE_Y - CAMERA->getY() );

				//< 타일 찍기
				stempBrush(i,j);
			}
		}
	}

	for(int i=1 ; i<mapSizeY-1 ; i+=2)
	{
		for(int j=1 ; j<mapSizeX-1 ; j+=2)
		{
			//< 타일의 위치 구하기
			POINT m_position;
			m_position.x = (j+1) * TILE_SIZE_X;
			m_position.y = i * TILE_SIZE_Y;

			//< 마름모 구하는 식(?)
			int ax = static_cast<int>( (-TILE_SIZE_Y/(float)TILE_SIZE_X) * (x - m_position.x));
			int yPlusax = y + ax;
			int yMinusax = y - ax;
			int tileBottom = m_position.y + TILE_SIZE_Y*2;

			//< 점이 타일 내부에 있다면
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

				//< 타일 찍기
				stempBrush(i,j);
			}
		}
	}
}

//<맵 생성
bool tileMap::newMap( int cx, int cy )
{
	//< 맵 정보 초기화
	releaseMap();

	//< 맵 크기 확인
	mapSizeX = cx;
	mapSizeY = cy;

	//< 포인터 할당
	if( m_tile == NULL && m_line == NULL )
	{
		//< 타일맵, 선, 오브젝트 2차 포인터 할당
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

	//< 맵 정보 초기화
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

//<맵 로드
bool tileMap::loadMap( const char *path )
{
	//< 맵 정보 초기화
	releaseMap();

	FILE *fp=NULL;

	//< 파일 오픈 & 에러 처리
	if( NULL != fopen_s(&fp, path, "r") )
	{
#ifdef _DEBUG
		LOG_MGR->addLog("%s, %s : %d", "맵 로드 실패", "tileMap.cpp", __LINE__ );
#endif
		return false;
	}
	//< 맵 크기 확인
	fscanf_s(fp, "%d,",&mapSizeX);
	fscanf_s(fp, "%d\n",&mapSizeY);

	//< 포인터 할당
	if( m_tile == NULL && m_line == NULL )
	{
		//< 타일맵, 선, 오브젝트 2차 포인터 할당
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

	//< 맵 정보 불러오기
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< 읽기
			fscanf_s(fp, "%5d(%4d,%4d),", &m_tile[i][j], &m_line[i][j], &m_obj[i][j] );
		}
		fscanf_s(fp, "\n");
	}
	fclose(fp);

#ifdef _DEBUG
	LOG_MGR->addLog("맵 로드 성공");
#endif
	return true;
}

//<맵 세이브
bool tileMap::saveMap( const char *path )
{
	FILE *fp=NULL;

	//< 파일 오픈 & 에러 처리
	if( NULL != fopen_s(&fp, path, "w") )
	{
#ifdef _DEBUG
		LOG_MGR->addLog("%s, %s : %d", "맵 저장 실패", "tileMap.cpp", __LINE__ );
#endif
		return false;
	}
	//< 맵 크기 저장
	fprintf_s(fp, "%5d,",mapSizeX);
	fprintf_s(fp, "%5d\n",mapSizeY);	

	//< 맵 정보 저장하기
	for(int i=0 ; i<mapSizeY ; i++)
	{
		for(int j=0 ; j<mapSizeX ; j++)
		{
			//< 쓰기
			fprintf_s(fp, "%5d(%4d,%4d),", m_tile[i][j], m_line[i][j], m_obj[i][j] );
		}
		fprintf_s(fp, "\n");
	}
	fclose(fp);

#ifdef _DEBUG
	LOG_MGR->addLog("맵 저장 완료 (%s)", path );
#endif
	return true;
}

//< 맵 해제
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
	LOG_MGR->addLog("맵 정보 정상 해제");
#endif
	return true;
}

//< 타일 브러쉬 바꾸기
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

//< 브러쉬 그리기
void tileMap::stempBrush( int i, int j )
{
	if( (GetAsyncKeyState(VK_LBUTTON) & 0x8000)? 1: 0 )
	{
		//< 왼쪽 벽이면
		if( m_brush == TILE_L_WALL )
		{
			m_line[i][j] = TILE_L_WALL;
		}
		//< 오른쪽 벽이면
		else if( m_brush == TILE_R_WALL )
		{
			m_line[i][j+1] = TILE_R_WALL;
		}
		//< 오브젝트면
		else if( m_brush == OBJ_BOOK_L || m_brush == OBJ_BOOK_R )
		{
			m_obj[i+1][j+1] = m_brush;
		}
		//< 그 외

		else
		{
			m_tile[i+1][j+1] = m_brush;
			//< 계단
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