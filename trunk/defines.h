#pragma once
#pragma once

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, µðÆÄÀÎ, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬

#define fPI 3.14f

//< ÇØÁ¦µðÆÄÀÎ
#define SAFE_DELETE(p) if(p != NULL) { delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if( p!= NULL ) { delete [] p; p = NULL; }
#define SAFE_RELEASE(h) if( h != NULL ) { h->Release(); h = NULL; }

// À©µµ¿ìÀÇ Å©±â 
#define		WINSIZE_X	1280 
#define		WINSIZE_Y	720

//< ½ºÅ©¸° ¿µ¿ª
#define		SCREEN_X	1280
#define		SCREEN_Y	720

//< ·»´õ¸µ ºñÆ® ÇÃ·¡±×
#define RM_NORMAL			0x01
#define RM_TRANS			0x02
#define RM_NORMAL_ALPHA24	0x03
#define RM_TRANS_ALPHA24	0x04
#define RM_ALPHA32			0x05
#define RM_MEMORY			0x06

//< °æ·Î
const char *imgPath = "Data/Image/";
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, °ÔÀÓ µðÆÄÀÎ, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬

////////////////////////////////////////////////////////////////////////
//< Ä³¸¯ÅÍ °ü·Ã

//< Ä³¸¯ÅÍ »çÀÌÁî
#define		CHARACTER_SIZE 25
#define		CHARACTER_SIZE_X 37
#define		CHARACTER_SIZE_Y 36
//< Ä³¸¯ÅÍ ½ÃÀÛ À§Ä¡
#define		CHARACTER_START_POSITION_X	350
#define		CHARACTER_START_POSITION_Y	150
//< Ä³¸¯ÅÍ °ø°Ý ¹üÀ§
#define		NORMAL_ATTACK_RANGE 80
//< Ä³¸¯ÅÍ ½ÃÀÛ Ã¼·Â
#define		CHARACTER_HP 100
#define		CHARACTER_MP 100
//< Ä³¸¯ÅÍ ´ë½¬ °Å¸®
#define		CHARACTER_DASH_DIST 40
//< Ä³¸¯ÅÍ ÀüÃ¼ ¸¶¹ý ´ë¹ÌÁö
#define		WHOLE_SKILL_DAMAGE 100

////////////////////////////////////////////////////////////////////////
//< ¸ó½ºÅÍ °ü·Ã

//< ¸ó½ºÅÍ »çÀÌÁî
#define		MONSTER_SIZE 25
//< ¸ó½ºÅÍ °ø°Ý ¹üÀ§
#define		MONSTER_1_ATTACK_RANGE 55
//< ¸ó½ºÅÍ µîÀå È®·ü
#define		MONSTER_APPEAR_PROB 1
//< ¸ó½ºÅÍ ÀÌµ¿¼Óµµ
#define		BOSS_1_MOVE_SPEED 2.f
#define		MON1_MOVE_SPEED 2.f
#define		MON2_MOVE_SPEED 1.1f

////////////////////////////////////////////////////////////////////////
//< ¸Ê °ü·Ã

//< ¸Ê ÃÖÁ¾ Ãþ ¼ö
#define		MAP_MAX_FLOOR 5
//< Ãþ º° ¸Ê ÆÄÀÏ
#define		LOAD_MAP_1_PATH		"Data/Map/testMap-1.txt"
#define		LOAD_MAP_2_PATH		"Data/Map/testMap-2.txt"
#define		LOAD_MAP_3_PATH		"Data/Map/testMap-3.txt"
#define		LOAD_MAP_4_PATH		"Data/Map/testMap-4.txt"
#define		LOAD_MAP_5_PATH		"Data/Map/testMap-5.txt"

//< Å¸ÀÏ »çÀÌÁî
#define		TILE_SIZE_X 64
#define		TILE_SIZE_Y 32

//< ½ÃÀÛ½Ã ·ÎµåÇÒ ¸Ê Á¤º¸ °æ·Î
//#define START_LOAD_MAP_PATH		"Data/Map/BosstestMap.txt"
#define START_LOAD_MAP_PATH		"Data/Map/startMap.txt"
//#define		START_LOAD_MAP_PATH		"Data/Map/testMap-5.txt"
////////////////////////////////////////////////////////////////////////

//< ÀÌ¹ÌÁö ·£´õ ¿ÀÇÁ¼Â (¼öÄ¡¸¸Å­ À§¿¡ ·£´õ)
#define		RENDER_OFFSET_Y 15

////////////////////////////////////////////////////////////////////////
//< Ä³¸¯ÅÍ °ü·Ã

//< Á¾Á·
enum
{
    TRIBE_WOLF,				//< ´Á´ëÀÎ°£
    TRIBE_KENTA,			//< ÄËÅ¸¿ì·Î½º
    TRIBE_ELF,				//< ¿¤ÇÁ
    TRIBE_UNDEAD			//< ¾ðµ¥µå
};

//< Á÷¾÷
enum
{
    JOB_KNIGHT,			//< Àü»ç
    JOB_THIEF,			//< µµÀû
    JOB_ARCHER,			//< ¾ÆÃ³
    JOB_MAGICIAN,		//< ¸¶¹ý»ç
};

//< ½Å³ä
enum
{
    BELIEF_GID,		//<Áöµå
    BELIEF_MAGA,	//<¸¶°¡Ã÷Ä¡
    BELIEF_NAA,		//<³ª¾ÆÅ°
    BELIEF_BORE,	//<º¸·¹¾Æ½º
    BELIEF_TANATO	//<Å¸³ªÅä
};

//< Ä³¸¯ÅÍ »óÅÂ ÀÌ»ó
enum
{
    CONDITION_NORMAL = 0,	//< Á¤»ó
    CONDITION_POISON,		//< µ¶
    CONDITION_STRONG,		//< °­È­
    CONDITION_WEAKEN,		//< ¾àÈ­
    CONDITION_INBEAT		//< ¹«Àû
};

////////////////////////////////////////////////////////////////////////
//< ¾ÆÀÌÅÛ °ü·Ã
//< ¾ÆÀÌÅÛ »çÀÌÁî
#define POTION_SIZE_X 25
#define POTION_SIZE_Y 29
//< ¾ÆÀÌÅÛ ¾ÆÀÌµð
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
//< 8¹æ
enum Direction
{
    DIR_L, DIR_LU, DIR_U, DIR_RU, DIR_R, DIR_RD, DIR_D, DIR_LD
};

//< ¹öÆ°, ÆË¾÷Ã¢ Á¤·Ä±âÁØ
enum
{
    ALIGN_CENTER,			//< Áß°£Á¤·Ä
    ALIGN_LEFT_TOP,			//< ¿ÞÂÊÀ§ Á¤·Ä
    ALIGN_RIGHT_TOP,		//< ¿ÞÂÊ ¾Æ·¡ Á¤·Ä
    ALIGN_LEFT_BOTTOM,		//< ¿À¸¥ÂÊ À§ Á¤·Ä
    ALIGN_RIGHT_BOTTOM		//< ¿À¸¥ÂÊ ¾Æ·¡ Á¤·Ä
};

//< ·Î±×ÀÎ¾À ÆË¾÷
enum
{
    POPUP_NONE,								//< ÆË¾÷ ¼±ÅÃÀü
    POPUP_NO_POPUP,							//< ÆË¾÷ ¾øÀ½
    POPUP_NO_POPUP_GET_MAKE_ROOM,
    //----------------------------------------------------------
    POPUP_LOGIN_LOGIN_OVERLABID,			//< Áßº¹ ·Î±×ÀÎ
    POPUP_LOGIN_LOGIN_FAILL,				//< ·Î±×ÀÎ ½ÇÆÐ
    POPUP_LOGIN_LOGIN_SUCCESS,				//< ·Î±×ÀÎ ¼º°ø
    POPUP_LOGIN_EXIT,						//< ³ª°¡±â ÆË¾÷
    POPUP_LOGIN_LOGIN_DISCORD_PASS,			//< ºñ¹Ð¹øÈ£°¡ ÀÏÄ¡ÇÏÁö ¾ÊÀ½
                                            //----------------------------------------------------------
                                            POPUP_LOGIN_JOIN,						//< È¸¿ø°¡ÀÔÃ¢
                                            POPUP_LOGIN_JOIN_SUCCESS,				//< È¸¿ø°¡ÀÔ ¼º°ø
                                            POPUP_LOGIN_JOIN_FAILL,					//< È¸¿ø°¡ÀÔ ½ÇÆÐ
                                            POPUP_LOGIN_JOIN_FAIL_NONE,				//< ÀÔ·ÂÇÑ Á¤º¸ ºÎÁ·
                                            POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID,		//< ¾ÆÀÌµð°¡ °ãÃÆÀ»¶§
                                            POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS,		//< ÀçÀÔ·ÂÆÐ½º¿öµå ºÒÀÏÄ¡
                                                                                    //----------------------------------------------------------
                                                                                    POPUP_TITLE_RANK,						//< ·©Å· ÆË¾÷
                                                                                    POPUP_TITLE_COLLECTION,					//< ÄÝ·º¼Ç ÆË¾÷
                                                                                    POPUP_TITLE_LOGOUT,						//< ·Î±×¾Æ¿ô ÆË¾÷
                                                                                                                            //----------------------------------------------------------
                                                                                                                            POPUP_LOBBY_FRIENDLIST,					//< Ä£±¸ ¸ñ·Ï
                                                                                                                            POPUP_LOBBY_MAKEROOM_OPEN,				//< ¹æ¸¸µé±â °ø°³
                                                                                                                            POPUP_LOBBY_MAKEROOM_CLOSE,				//< ¹æ¸¶µé±â ºñ°ø°³
                                                                                                                            POPUP_LOBBY_MAKEROOM_SUCCESS,			//< ¹æ¸¸µé±â ¼º°ø
                                                                                                                                                                    //----------------------------------------------------------
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_CLOSE,			//< ¸¸µç¹æ ºñ°ø°³
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_OPEN,			//< ¸¸µç¹æ °ø°³
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_SUCCESS,			//< ¹æÀÔÀå ¼º°ø
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_FAILL,			//< ¹æÀÔÀå ½ÇÆÐ
                                                                                                                                                                                                            //----------------------------------------------------------
                                                                                                                                                                                                            POPUP_GAME_WAIT_USER,					//< À¯Àú ±â´Ù¸®±â ÆË¾÷
                                                                                                                                                                                                            POPUP_GAME_OVER,						//< °ÔÀÓ¿À¹ö ÆË¾÷
                                                                                                                                                                                                            POPUP_GAME_RANK,						//< °ÔÀÓ¿À¹ö ·©Å·ÆË¾÷
                                                                                                                                                                                                                                                    //----------------------------------------------------------
                                                                                                                                                                                                                                                    POPUP_END
};
//< ·Î±×ÀÎ »óÅÂ
enum
{
    LOGIN_SUCCESS,
    LOGIN_FAIL,
};

//< ¹öÆ° Á¾·ù
enum
{
    BUTTON_OK,
    BUTTON_CANCEL,
    BUTTON_JOIN,
    BUTTON_EXIT,
};

//< È¸¿ø°¡ÀÔ ÇÃ·¡±×
enum
{
    JOIN_SUCCESS,
    JOIN_FAIL_NONE,
    JOIN_FAIL_OVERLAP_ID,
    JOIN_FAIL_DISCORD_PASS,
};

//< ºñÆ®¸Ê Å¸ÀÔ
enum BITMAP_TYPE
{
    NONE_BITMAP,
    ALPA_BITMAP
};

//< ¿ÀºêÁ§Æ® Å¸ÀÔ
enum
{
    OBJECT_ITEM,
    OBJECT_MONSTER,
    OBJECT_SKILL,
    OBJECT_SPEL
};

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, ÀÌ¹ÌÁö ¾ÆÀÌµð, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
//< ¹é¹öÆÛ ÀÌ¹ÌÁö °íÁ¤
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

    //< ¶óÀÌÆ® ¸ÊÇÎ
    imgID_LITE_MAPING,
    //< ½Ã¾ß È¿°ú
    imgID_SIGHT,
    //< Å¸°Ý ÀÌÆåÆ® ÀÌ¹ÌÁö
    imgID_GETHIT_1,
    imgID_GETHIT_2,
    imgID_GETHIT_3,

    //< Ä³¸¯ÅÍ
    imgID_CHARACTER_1,

    imgID_WARRIOR_IDLE,
    imgID_WARRIOR_MOVE,
    imgID_WARRIOR_ATK,
    imgID_WARRIOR_DIE,
    imgID_WARRIOR_BEHIT,
    imgID_WARRIOR_DASH,

    //< °íºí¸°
    imgID_MONSTER_1_IDLE,
    imgID_MONSTER_1_MOVE,
    imgID_MONSTER_1_ATK,
    imgID_MONSTER_1_DIE,
    //< ¹ú·¹
    imgID_MONSTER_3_IDLE,
    imgID_MONSTER_3_MOVE,
    imgID_MONSTER_3_ATK,
    imgID_MONSTER_3_BEHIT,
    imgID_MONSTER_3_DIE,
    //< ±¸¿ï
    imgID_MONSTER_4_IDLE,
    imgID_MONSTER_4_MOVE,
    imgID_MONSTER_4_ATK,
    imgID_MONSTER_4_BEHIT,
    imgID_MONSTER_4_DIE,
    //< ´ÙÅ© ½ºÆÄÀÌ´õ
    imgID_MONSTER_6_IDLE,
    imgID_MONSTER_6_MOVE,
    imgID_MONSTER_6_ATK,
    imgID_MONSTER_6_BEHIT,
    imgID_MONSTER_6_DIE,
    //< ¸Á·É
    imgID_MONSTER_7_IDLE,
    imgID_MONSTER_7_MOVE,
    imgID_MONSTER_7_ATK,
    imgID_MONSTER_7_BEHIT,
    imgID_MONSTER_7_DIE,
    //< ÀÎ°£µµµÏ
    imgID_MONSTER_9_IDLE,
    imgID_MONSTER_9_MOVE,
    imgID_MONSTER_9_ATK,
    imgID_MONSTER_9_BEHIT,
    imgID_MONSTER_9_DIE,
    //< ÀÎ°£Àü»ç
    imgID_MONSTER_10_IDLE,
    imgID_MONSTER_10_MOVE,
    imgID_MONSTER_10_ATK,
    imgID_MONSTER_10_BEHIT,
    imgID_MONSTER_10_DIE,

    //< »çÁ¦ ³ªÀÌµå
    imgID_BOSS_NAID,
    imgID_BOSS_MOVE,
    imgID_BOSS_ATK,
    imgID_BOSS_BEHIT,
    imgID_BOSS_NAID_DIE,

    //< ±Ô¸®¿¤
    imgID_BOSS_GYURIEL_IDLE,
    imgID_BOSS_GYURIEL_MOVE,
    imgID_BOSS_GYURIEL_ATK,
    imgID_BOSS_GYURIEL_BEHIT,
    imgID_BOSS_GYURIEL_DIE,
    imgID_BOSS_GYURIEL_SPECIAL,



    imgID_BUTTON1,
    imgID_BUTTON2,

    //< Æ÷¼Ç ÀÌ¹ÌÁö
    imgID_POTION_1,
    imgID_POTION_2,
    imgID_POTION_3,
    imgID_POTION_4,
    imgID_POTION_5,
    imgID_POTION_6,

    //< ¾ÆÀÌÅÛ ÀÎº¥Åä¸®
    imgID_INVEN_POTION_1, //49
    imgID_INVEN_POTION_2,
    imgID_INVEN_POTION_3,
    imgID_INVEN_POTION_4,
    imgID_INVEN_POTION_5,
    imgID_INVEN_POTION_6,

    imgID_END
};

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, Å¸ÀÏ ºê·¯½¬, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬

//< Å¸ÀÏ Å¸ÀÔ µðÆÄÀÎ
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

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, »ç¿îµå °ü¸®, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬

enum SoundKind
{
    SOUND_TITLE,
    SOUND_LOBBY,
    SOUND_INGAME,
    SOUND_BOSS,
    SOUND_POPUP,

    //ÄÉ¸¯ÅÍ
    CHAR_ATK,
    CHAR_HIT,
    CHAR_DIE,

    //°íºí¸° 
    GLB_ATK,
    GLB_HIT,
    GLB_DIE,

    //¹ú·¹
    BUG_ATK,
    BUG_HIT,
    BUG_DIE,

    //±¸¿ï
    GUL_ATK,
    GUL_HIT,
    GUL_DIE,

    //°ËÀº°Å¹Ì
    SPIDER_ATK,
    SPIDER_HIT,
    SPIDER_DIE,

    //¸Á·É
    STOR_ATK,
    STOR_HIT,
    STOR_DIE,

    //ÀÎ°£Àü»ç
    WARRIOR_ATK,
    WARRIOR_HIT,
    WARRIOR_DIE,

    //ÀÎ°£µµÀû
    ROGUE_ATK,
    ROGUE_HIT,
    ROGUE_DIE,

    //³×ÀÌµå
    NAID_ATK,
    NAID_HIT,
    NAID_DIE,

    //½ºÅ³»ç¿îµå

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

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04,¾Ö´Ï¸ÞÀÌ¼Ç °ü¸®, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬

enum AniEffect
{
    ET_STR = 0,
    ET_STR1,
    ET_STR2,

    ET_STR3,
    //---ÀÌµ¿¸ð¼Ç---
    //¾Æ·¡
    CHAR_D,
    //À§
    CHAR_U,
    //¿ÞÂÊ
    CHAR_L,
    //¿À¸¥ÂÊ
    CHAR_R,
    //¿ÞÂÊ À§
    CHAR_LU,
    //¿À¸¥ÂÊ À§
    CHAR_RU,
    //¿ÞÂÊ ¾Æ·¡
    CHAR_LD,
    //¿À¸¥ÂÊ ¾Æ·¡
    CHAR_RD,

    //---°ø°Ý¸ð¼Ç---
    //¿ÞÂÊ °ø°Ý
    ATK_L,
    //¿À¸¥ÂÊ °ø°Ý
    ATK_R,
    //À§ÂÊ°ø°Ý
    ATK_U,
    //¾Æ·¡ÂÊ °ø°Ý
    ATK_D,
    //¿ÞÂÊ À§ °ø°Ý
    ATK_LU,
    //¿ÞÂÊ ¾Æ·¡ °ø°Ý
    ATK_LD,
    //¿À¸¥ÂÊ À§ °ø°Ý
    ATK_RU,
    //¿À¸¥ÂÊ ¾Æ·¡ °ø°Ý
    ATK_RD,

    //±Ã¼öÄÉ¸¯
    //---ÀÌµ¿¸ð¼Ç---
    //¾Æ·¡
    WCHAR_D,
    //À§
    WCHAR_U,
    //¿ÞÂÊ
    WCHAR_L,
    //¿À¸¥ÂÊ
    WCHAR_R,
    //¿ÞÂÊ À§
    WCHAR_LU,
    //¿À¸¥ÂÊ À§
    WCHAR_RU,
    //¿ÞÂÊ ¾Æ·¡
    WCHAR_LD,
    //¿À¸¥ÂÊ ¾Æ·¡
    WCHAR_RD,

    //---°ø°Ý¸ð¼Ç---
    //¿ÞÂÊ °ø°Ý
    WATK_L,
    //¿À¸¥ÂÊ °ø°Ý
    WATK_R,
    //À§ÂÊ°ø°Ý
    WATK_U,
    //¾Æ·¡ÂÊ °ø°Ý
    WATK_D,
    //¿ÞÂÊ À§ °ø°Ý
    WATK_LU,
    //¿ÞÂÊ ¾Æ·¡ °ø°Ý
    WATK_LD,
    //¿À¸¥ÂÊ À§ °ø°Ý
    WATK_RU,
    //¿À¸¥ÂÊ ¾Æ·¡ °ø°Ý
    WATK_RD,
    //°íºí¸° ¾îÅØ
    GBL_ATK,

    //°íºí¸°ÇÇ°Ý
    ET_END
};

enum monsterKind
{
    GOBLIN,	//< °íºí¸°

    MON_BUG, //< ¹ú·¹
    GHOUL,	//< ±¸¿ï

    DARK_SPIDER, // °ËÀº °Å¹Ì
    GHOST, // ¸Á·É 
    HUMAN_THIEF, // ÀÎ°£µµµÏ
    HUMAN_KNIGHT,//ÀÎ°£Àü»ç
    BOSS_NAID,	//< º¸½º NAID
    BOSS_GYURIEL //< º¸½º GURIEL
};

const int MAX_SKILL_COUNT = 4;