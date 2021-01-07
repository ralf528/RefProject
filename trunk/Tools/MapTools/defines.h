#pragma once

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ������, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

//< ����������
#define SAFE_DELETE(p) if(p != NULL) { delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if( p!= NULL ) { delete [] p; p = NULL; }
#define SAFE_RELEASE(h) if( h != NULL ) { h->Release(); h = NULL; }

// �������� ũ�� 
#define		WINSIZE_X	1280 
#define		WINSIZE_Y	720

//< ������ ��Ʈ �÷���
#define RM_NORMAL			0x01
#define RM_TRANS			0x02
#define RM_NORMAL_ALPHA24	0x03
#define RM_TRANS_ALPHA24	0x04
#define RM_ALPHA32			0x05
#define RM_MEMORY			0x06

//< ���
const char *imgPath="Resources/";
//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ���� ������, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

//< ĳ���� ������
#define		CHARACTER_SIZE 25
//#define		CHARACTER_SIZE_X 25
//#define		CHARACTER_SIZE_Y 25
//< ĳ���� ���� ��ġ
#define		CHARACTER_START_POSITION_X	350
#define		CHARACTER_START_POSITION_Y	150

//< Ÿ�� ������
#define		TILE_SIZE_X 64
#define		TILE_SIZE_Y 32

//< ���۽� �ε��� �� ���� ���
#define START_LOAD_MAP_PATH		"Resources/TestMap/map1.txt"

enum Direction
{
	DIR_L, DIR_LU, DIR_U, DIR_RU, DIR_R, DIR_RD, DIR_D, DIR_LD
};

//< ��ư, �˾�â ���ı���
enum
{
	ALIGN_CENTER,			//< �߰�����
	ALIGN_LEFT_TOP,			//< ������ ����
	ALIGN_LEFT_BOTTOM,		//< ���� �Ʒ� ����
	ALIGN_RIGHT_TOP,		//< ������ �� ����
	ALIGN_RIGHT_BOTTOM		//< ������ �Ʒ� ����
};

//< ��Ʈ�� Ÿ��
enum BITMAP_TYPE
{
	NONE_BITMAP,
	ALPA_BITMAP
};

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, �̹��� ���̵�, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������
//< ����� �̹��� ����
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

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, Ÿ�� �귯��, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

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