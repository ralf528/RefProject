#pragma once
#pragma once

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ������, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

#define fPI 3.14f

//< ����������
#define SAFE_DELETE(p) if(p != NULL) { delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if( p!= NULL ) { delete [] p; p = NULL; }
#define SAFE_RELEASE(h) if( h != NULL ) { h->Release(); h = NULL; }

// �������� ũ�� 
#define		WINSIZE_X	1280 
#define		WINSIZE_Y	720

//< ��ũ�� ����
#define		SCREEN_X	1280
#define		SCREEN_Y	720

//< ������ ��Ʈ �÷���
#define RM_NORMAL			0x01
#define RM_TRANS			0x02
#define RM_NORMAL_ALPHA24	0x03
#define RM_TRANS_ALPHA24	0x04
#define RM_ALPHA32			0x05
#define RM_MEMORY			0x06

//< ���
const char *imgPath = "Data/Image/";
//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ���� ������, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

////////////////////////////////////////////////////////////////////////
//< ĳ���� ����

//< ĳ���� ������
#define		CHARACTER_SIZE 25
#define		CHARACTER_SIZE_X 37
#define		CHARACTER_SIZE_Y 36
//< ĳ���� ���� ��ġ
#define		CHARACTER_START_POSITION_X	350
#define		CHARACTER_START_POSITION_Y	150
//< ĳ���� ���� ����
#define		NORMAL_ATTACK_RANGE 80
//< ĳ���� ���� ü��
#define		CHARACTER_HP 100
#define		CHARACTER_MP 100
//< ĳ���� �뽬 �Ÿ�
#define		CHARACTER_DASH_DIST 40
//< ĳ���� ��ü ���� �����
#define		WHOLE_SKILL_DAMAGE 100

////////////////////////////////////////////////////////////////////////
//< ���� ����

//< ���� ������
#define		MONSTER_SIZE 25
//< ���� ���� ����
#define		MONSTER_1_ATTACK_RANGE 55
//< ���� ���� Ȯ��
#define		MONSTER_APPEAR_PROB 1
//< ���� �̵��ӵ�
#define		BOSS_1_MOVE_SPEED 2.f
#define		MON1_MOVE_SPEED 2.f
#define		MON2_MOVE_SPEED 1.1f

////////////////////////////////////////////////////////////////////////
//< �� ����

//< �� ���� �� ��
#define		MAP_MAX_FLOOR 5
//< �� �� �� ����
#define		LOAD_MAP_1_PATH		"Data/Map/testMap-1.txt"
#define		LOAD_MAP_2_PATH		"Data/Map/testMap-2.txt"
#define		LOAD_MAP_3_PATH		"Data/Map/testMap-3.txt"
#define		LOAD_MAP_4_PATH		"Data/Map/testMap-4.txt"
#define		LOAD_MAP_5_PATH		"Data/Map/testMap-5.txt"

//< Ÿ�� ������
#define		TILE_SIZE_X 64
#define		TILE_SIZE_Y 32

//< ���۽� �ε��� �� ���� ���
//#define START_LOAD_MAP_PATH		"Data/Map/BosstestMap.txt"
#define START_LOAD_MAP_PATH		"Data/Map/startMap.txt"
//#define		START_LOAD_MAP_PATH		"Data/Map/testMap-5.txt"
////////////////////////////////////////////////////////////////////////

//< �̹��� ���� ������ (��ġ��ŭ ���� ����)
#define		RENDER_OFFSET_Y 15

////////////////////////////////////////////////////////////////////////
//< ĳ���� ����

//< ����
enum
{
    TRIBE_WOLF,				//< �����ΰ�
    TRIBE_KENTA,			//< ��Ÿ��ν�
    TRIBE_ELF,				//< ����
    TRIBE_UNDEAD			//< �𵥵�
};

//< ����
enum
{
    JOB_KNIGHT,			//< ����
    JOB_THIEF,			//< ����
    JOB_ARCHER,			//< ��ó
    JOB_MAGICIAN,		//< ������
};

//< �ų�
enum
{
    BELIEF_GID,		//<����
    BELIEF_MAGA,	//<������ġ
    BELIEF_NAA,		//<����Ű
    BELIEF_BORE,	//<�����ƽ�
    BELIEF_TANATO	//<Ÿ����
};

//< ĳ���� ���� �̻�
enum
{
    CONDITION_NORMAL = 0,	//< ����
    CONDITION_POISON,		//< ��
    CONDITION_STRONG,		//< ��ȭ
    CONDITION_WEAKEN,		//< ��ȭ
    CONDITION_INBEAT		//< ����
};

////////////////////////////////////////////////////////////////////////
//< ������ ����
//< ������ ������
#define POTION_SIZE_X 25
#define POTION_SIZE_Y 29
//< ������ ���̵�
enum
{
    ITEM_FIRST = 500,
    ITEM_POTION_CONFUSION = 500,
    ITEM_POSION_CURE,
    ITEM_POTION_IDENTFY,
    ITEM_POTION_REGEN,
    ITEM_POTION_UNKNOWN,
    ITEM_POTION_VENOM,
    ITEM_END
};

////////////////////////////////////////////////////////////////////////
//< 8��
enum Direction
{
    DIR_L, DIR_LU, DIR_U, DIR_RU, DIR_R, DIR_RD, DIR_D, DIR_LD
};

//< ��ư, �˾�â ���ı���
enum
{
    ALIGN_CENTER,			//< �߰�����
    ALIGN_LEFT_TOP,			//< ������ ����
    ALIGN_RIGHT_TOP,		//< ���� �Ʒ� ����
    ALIGN_LEFT_BOTTOM,		//< ������ �� ����
    ALIGN_RIGHT_BOTTOM		//< ������ �Ʒ� ����
};

//< �α��ξ� �˾�
enum
{
    POPUP_NONE,								//< �˾� ������
    POPUP_NO_POPUP,							//< �˾� ����
    POPUP_NO_POPUP_GET_MAKE_ROOM,
    //----------------------------------------------------------
    POPUP_LOGIN_LOGIN_OVERLABID,			//< �ߺ� �α���
    POPUP_LOGIN_LOGIN_FAILL,				//< �α��� ����
    POPUP_LOGIN_LOGIN_SUCCESS,				//< �α��� ����
    POPUP_LOGIN_EXIT,						//< ������ �˾�
    POPUP_LOGIN_LOGIN_DISCORD_PASS,			//< ��й�ȣ�� ��ġ���� ����
                                            //----------------------------------------------------------
                                            POPUP_LOGIN_JOIN,						//< ȸ������â
                                            POPUP_LOGIN_JOIN_SUCCESS,				//< ȸ������ ����
                                            POPUP_LOGIN_JOIN_FAILL,					//< ȸ������ ����
                                            POPUP_LOGIN_JOIN_FAIL_NONE,				//< �Է��� ���� ����
                                            POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID,		//< ���̵� ��������
                                            POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS,		//< ���Է��н����� ����ġ
                                                                                    //----------------------------------------------------------
                                                                                    POPUP_TITLE_RANK,						//< ��ŷ �˾�
                                                                                    POPUP_TITLE_COLLECTION,					//< �ݷ��� �˾�
                                                                                    POPUP_TITLE_LOGOUT,						//< �α׾ƿ� �˾�
                                                                                                                            //----------------------------------------------------------
                                                                                                                            POPUP_LOBBY_FRIENDLIST,					//< ģ�� ���
                                                                                                                            POPUP_LOBBY_MAKEROOM_OPEN,				//< �游��� ����
                                                                                                                            POPUP_LOBBY_MAKEROOM_CLOSE,				//< �渶��� �����
                                                                                                                            POPUP_LOBBY_MAKEROOM_SUCCESS,			//< �游��� ����
                                                                                                                                                                    //----------------------------------------------------------
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_CLOSE,			//< ����� �����
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_OPEN,			//< ����� ����
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_SUCCESS,			//< ������ ����
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_FAILL,			//< ������ ����
                                                                                                                                                                                                            //----------------------------------------------------------
                                                                                                                                                                                                            POPUP_GAME_WAIT_USER,					//< ���� ��ٸ��� �˾�
                                                                                                                                                                                                            POPUP_GAME_OVER,						//< ���ӿ��� �˾�
                                                                                                                                                                                                            POPUP_GAME_RANK,						//< ���ӿ��� ��ŷ�˾�
                                                                                                                                                                                                                                                    //----------------------------------------------------------
                                                                                                                                                                                                                                                    POPUP_END
};
//< �α��� ����
enum
{
    LOGIN_SUCCESS,
    LOGIN_FAIL,
};

//< ��ư ����
enum
{
    BUTTON_OK,
    BUTTON_CANCEL,
    BUTTON_JOIN,
    BUTTON_EXIT,
};

//< ȸ������ �÷���
enum
{
    JOIN_SUCCESS,
    JOIN_FAIL_NONE,
    JOIN_FAIL_OVERLAP_ID,
    JOIN_FAIL_DISCORD_PASS,
};

//< ��Ʈ�� Ÿ��
enum BITMAP_TYPE
{
    NONE_BITMAP,
    ALPA_BITMAP
};

//< ������Ʈ Ÿ��
enum
{
    OBJECT_ITEM,
    OBJECT_MONSTER,
    OBJECT_SKILL,
    OBJECT_SPEL
};

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, �̹��� ���̵�, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������
//< ����� �̹��� ����
enum imgID
{
    imgID_NONID = -1,
    imgID_BACKBUFFER = 0,
    imgID_GAME_UI,
    imgID_GAME_LOADING,
    imgID_SCREENBUFFER,

    imgID_SKILL_SCREEN,
    imgID_SKILL_GOD_COLLUM,
    imgID_SKILL_NAID_COLLUM,
    imgID_SKILL_DESTRUCTION,
    imgID_TILE_1,

    //< ����Ʈ ����
    imgID_LITE_MAPING,
    //< �þ� ȿ��
    imgID_SIGHT,
    //< Ÿ�� ����Ʈ �̹���
    imgID_GETHIT_1,
    imgID_GETHIT_2,
    imgID_GETHIT_3,

    //< ĳ����
    imgID_CHARACTER_1,

    imgID_WARRIOR_IDLE,
    imgID_WARRIOR_MOVE,
    imgID_WARRIOR_ATK,
    imgID_WARRIOR_DIE,
    imgID_WARRIOR_BEHIT,
    imgID_WARRIOR_DASH,

    //< ���
    imgID_MONSTER_1_IDLE,
    imgID_MONSTER_1_MOVE,
    imgID_MONSTER_1_ATK,
    imgID_MONSTER_1_DIE,
    //< ����
    imgID_MONSTER_3_IDLE,
    imgID_MONSTER_3_MOVE,
    imgID_MONSTER_3_ATK,
    imgID_MONSTER_3_BEHIT,
    imgID_MONSTER_3_DIE,
    //< ����
    imgID_MONSTER_4_IDLE,
    imgID_MONSTER_4_MOVE,
    imgID_MONSTER_4_ATK,
    imgID_MONSTER_4_BEHIT,
    imgID_MONSTER_4_DIE,
    //< ��ũ �����̴�
    imgID_MONSTER_6_IDLE,
    imgID_MONSTER_6_MOVE,
    imgID_MONSTER_6_ATK,
    imgID_MONSTER_6_BEHIT,
    imgID_MONSTER_6_DIE,
    //< ����
    imgID_MONSTER_7_IDLE,
    imgID_MONSTER_7_MOVE,
    imgID_MONSTER_7_ATK,
    imgID_MONSTER_7_BEHIT,
    imgID_MONSTER_7_DIE,
    //< �ΰ�����
    imgID_MONSTER_9_IDLE,
    imgID_MONSTER_9_MOVE,
    imgID_MONSTER_9_ATK,
    imgID_MONSTER_9_BEHIT,
    imgID_MONSTER_9_DIE,
    //< �ΰ�����
    imgID_MONSTER_10_IDLE,
    imgID_MONSTER_10_MOVE,
    imgID_MONSTER_10_ATK,
    imgID_MONSTER_10_BEHIT,
    imgID_MONSTER_10_DIE,

    //< ���� ���̵�
    imgID_BOSS_NAID,
    imgID_BOSS_MOVE,
    imgID_BOSS_ATK,
    imgID_BOSS_BEHIT,
    imgID_BOSS_NAID_DIE,

    //< �Ը���
    imgID_BOSS_GYURIEL_IDLE,
    imgID_BOSS_GYURIEL_MOVE,
    imgID_BOSS_GYURIEL_ATK,
    imgID_BOSS_GYURIEL_BEHIT,
    imgID_BOSS_GYURIEL_DIE,
    imgID_BOSS_GYURIEL_SPECIAL,



    imgID_BUTTON1,
    imgID_BUTTON2,

    //< ���� �̹���
    imgID_POTION_1,
    imgID_POTION_2,
    imgID_POTION_3,
    imgID_POTION_4,
    imgID_POTION_5,
    imgID_POTION_6,

    //< ������ �κ��丮
    imgID_INVEN_POTION_1, //49
    imgID_INVEN_POTION_2,
    imgID_INVEN_POTION_3,
    imgID_INVEN_POTION_4,
    imgID_INVEN_POTION_5,
    imgID_INVEN_POTION_6,

    imgID_END
};

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, Ÿ�� �귯��, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

//< Ÿ�� Ÿ�� ������
typedef unsigned int tileType;

enum tileBRUSH
{
    NON_TILE = 255,
    TILE_NORMAL = 0,
    TILE_CHAR,
    TILE_ITEM,

    TILE_MON,
    TILE_MON_01,
    TILE_MON_02,
    TILE_MON_03,
    TILE_MON_04,
    TILE_MON_05,
    TILE_MON_06,
    TILE_MON_07,
    TILE_MON_08,
    TILE_MON_09,
    TILE_MON_10,
    TILE_MON_11,
    TILE_MON_12,
    TILE_MON_13,
    TILE_MON_14,
    TILE_MON_15,
    TILE_MON_16,
    TILE_MON_17,
    TILE_MON_18,
    TILE_MON_19,
    TILE_MON_20,
    TILE_ALTAR,

    TILE_STAIR_F,
    NORMAL_TILE_END = TILE_STAIR_F,

    TILE_STAIR,
    TILE_STAIR_L,
    TILE_STAIR_R,
    TILE_COLLUM,
    TILE_L_WALL,
    TILE_R_WALL,
    OBJ_ALTAR,
    OBJ_ALTAR_DISABLE,
    OBJ_BOOK_L,
    OBJ_BOOK_R,
    TILE_END
};


#define LT_WALL 0x0008
#define RT_WALL 0x0004

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ���� ����, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

enum SoundKind
{
    SOUND_TITLE,
    SOUND_LOBBY,
    SOUND_INGAME,
    SOUND_BOSS,
    SOUND_POPUP,

    //�ɸ���
    CHAR_ATK,
    CHAR_HIT,
    CHAR_DIE,

    //��� 
    GLB_ATK,
    GLB_HIT,
    GLB_DIE,

    //����
    BUG_ATK,
    BUG_HIT,
    BUG_DIE,

    //����
    GUL_ATK,
    GUL_HIT,
    GUL_DIE,

    //�����Ź�
    SPIDER_ATK,
    SPIDER_HIT,
    SPIDER_DIE,

    //����
    STOR_ATK,
    STOR_HIT,
    STOR_DIE,

    //�ΰ�����
    WARRIOR_ATK,
    WARRIOR_HIT,
    WARRIOR_DIE,

    //�ΰ�����
    ROGUE_ATK,
    ROGUE_HIT,
    ROGUE_DIE,

    //���̵�
    NAID_ATK,
    NAID_HIT,
    NAID_DIE,

    //��ų����

    BOSS_BGM,
    BOSS_ATK,
    BOSS_HIT,
    BOSS_DIE,
    BOSS_SKILL1,
    BOSS_SKILL2,

    SKILL_START,
    SKILL_END,

    SOUND_BGM5,
    SOUND_BGM6,
    SOUND_BGM7,
    SOUND_BGM8,
    SOUND_BGM9,
    SOUND_END
};

//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04,�ִϸ��̼� ����, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

enum AniEffect
{
    ET_STR = 0,
    ET_STR1,
    ET_STR2,

    ET_STR3,
    //---�̵����---
    //�Ʒ�
    CHAR_D,
    //��
    CHAR_U,
    //����
    CHAR_L,
    //������
    CHAR_R,
    //���� ��
    CHAR_LU,
    //������ ��
    CHAR_RU,
    //���� �Ʒ�
    CHAR_LD,
    //������ �Ʒ�
    CHAR_RD,

    //---���ݸ��---
    //���� ����
    ATK_L,
    //������ ����
    ATK_R,
    //���ʰ���
    ATK_U,
    //�Ʒ��� ����
    ATK_D,
    //���� �� ����
    ATK_LU,
    //���� �Ʒ� ����
    ATK_LD,
    //������ �� ����
    ATK_RU,
    //������ �Ʒ� ����
    ATK_RD,

    //�ü��ɸ�
    //---�̵����---
    //�Ʒ�
    WCHAR_D,
    //��
    WCHAR_U,
    //����
    WCHAR_L,
    //������
    WCHAR_R,
    //���� ��
    WCHAR_LU,
    //������ ��
    WCHAR_RU,
    //���� �Ʒ�
    WCHAR_LD,
    //������ �Ʒ�
    WCHAR_RD,

    //---���ݸ��---
    //���� ����
    WATK_L,
    //������ ����
    WATK_R,
    //���ʰ���
    WATK_U,
    //�Ʒ��� ����
    WATK_D,
    //���� �� ����
    WATK_LU,
    //���� �Ʒ� ����
    WATK_LD,
    //������ �� ����
    WATK_RU,
    //������ �Ʒ� ����
    WATK_RD,
    //��� ����
    GBL_ATK,

    //����ǰ�
    ET_END
};

enum monsterKind
{
    GOBLIN,	//< ���

    MON_BUG, //< ����
    GHOUL,	//< ����

    DARK_SPIDER, // ���� �Ź�
    GHOST, // ���� 
    HUMAN_THIEF, // �ΰ�����
    HUMAN_KNIGHT,//�ΰ�����
    BOSS_NAID,	//< ���� NAID
    BOSS_GYURIEL //< ���� GURIEL
};

const int MAX_SKILL_COUNT = 4;