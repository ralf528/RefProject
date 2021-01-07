#pragma once

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 디파인, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//< 해제디파인
#define SAFE_DELETE(p) if(p != NULL) { delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if( p!= NULL ) { delete [] p; p = NULL; }
#define SAFE_RELEASE(h) if( h != NULL ) { h->Release(); h = NULL; }

// 윈도우의 크기 
#define		WINSIZE_X	1280 
#define		WINSIZE_Y	720

//< 렌더링 비트 플래그
#define RM_NORMAL			0x01
#define RM_TRANS			0x02
#define RM_NORMAL_ALPHA24	0x03
#define RM_TRANS_ALPHA24	0x04
#define RM_ALPHA32			0x05
#define RM_MEMORY			0x06

//< 경로
const char *imgPath="Resources/";
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 게임 디파인, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//< 캐릭터 사이즈
#define		CHARACTER_SIZE 25
//#define		CHARACTER_SIZE_X 25
//#define		CHARACTER_SIZE_Y 25
//< 캐릭터 시작 위치
#define		CHARACTER_START_POSITION_X	350
#define		CHARACTER_START_POSITION_Y	150

//< 타일 사이즈
#define		TILE_SIZE_X 64
#define		TILE_SIZE_Y 32

//< 시작시 로드할 맵 정보 경로
#define START_LOAD_MAP_PATH		"Resources/TestMap/map1.txt"

enum Direction
{
	DIR_L, DIR_LU, DIR_U, DIR_RU, DIR_R, DIR_RD, DIR_D, DIR_LD
};

//< 버튼, 팝업창 정렬기준
enum
{
	ALIGN_CENTER,			//< 중간정렬
	ALIGN_LEFT_TOP,			//< 왼쪽위 정렬
	ALIGN_LEFT_BOTTOM,		//< 왼쪽 아래 정렬
	ALIGN_RIGHT_TOP,		//< 오른쪽 위 정렬
	ALIGN_RIGHT_BOTTOM		//< 오른쪽 아래 정렬
};

//< 비트맵 타입
enum BITMAP_TYPE
{
	NONE_BITMAP,
	ALPA_BITMAP
};

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 이미지 아이디, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//< 백버퍼 이미지 고정
enum imgID
{
	imgID_NONID = -1,
	imgID_BACKBUFFER = 0,
	imgID_TILE_1,

	imgID_CHARACTER_1,

	imgID_BUTTON1,
	imgID_BUTTON2,


	imgID_SPHERE,
	imgID_END
};

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 타일 브러쉬, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

enum tileBRUSH
{
	NON_TILE = 255,
	TILE_NORMAL = 0,
	TILE_CHAR,
	TILE_ITEM,
	TILE_MON,
	TILE_ALTAR,
	OBJ_BOOK_L,
	OBJ_BOOK_R,
	TILE_STAIR_F,
	TILE_STAIR,
	TILE_STAIR_L,
	TILE_STAIR_R,
	TILE_COLLUM,
	TILE_L_WALL,
	TILE_R_WALL,
	OBJ_ALTAR,
	OBJ_ALTAR_DISABLE,
	TILE_END
};

#define LT_WALL 0x0008
#define RT_WALL 0x0004