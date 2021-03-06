#pragma once

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 蛤だ檣, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

#define fPI 3.14f

//< п薯蛤だ檣
#define SAFE_DELETE(p) if(p != NULL) { delete p; p = NULL; }
#define SAFE_DELETE_ARR(p) if( p!= NULL ) { delete [] p; p = NULL; }
#define SAFE_RELEASE(h) if( h != NULL ) { h->Release(); h = NULL; }

// 孺紫辦曖 觼晦 
#define		WINSIZE_X	1280 
#define		WINSIZE_Y	720

//< 蝶觼萼 艙羲
#define		SCREEN_X	1280
#define		SCREEN_Y	720

//< 溶渦葭 綠お Ы楚斜
#define RM_NORMAL			0x01
#define RM_TRANS			0x02
#define RM_NORMAL_ALPHA24	0x03
#define RM_TRANS_ALPHA24	0x04
#define RM_ALPHA32			0x05
#define RM_MEMORY			0x06

//< 唳煎
const char *imgPath = "Data/Image/";
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 啪歜 蛤だ檣, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

////////////////////////////////////////////////////////////////////////
//< 議葛攪 婦溼

//< 議葛攪 餌檜鍔
#define		CHARACTER_SIZE 15
#define		CHARACTER_SIZE_X 37
#define		CHARACTER_SIZE_Y 36
//< 議葛攪 衛濛 嬪纂
#define		CHARACTER_START_POSITION_X	350
#define		CHARACTER_START_POSITION_Y	150
//< 議葛攪 奢問 彰嬪
#define		NORMAL_ATTACK_RANGE 80
#define		BOW_ATTACK_RANGE 200
//< 議葛攪 衛濛 羹溘
#define		CHARACTER_HP 100
#define		CHARACTER_MP 100
//< 議葛攪 渠蓮 剪葬
#define		CHARACTER_DASH_DIST 40
//< 議葛攪 瞪羹 葆徹 渠嘐雖
#define		WHOLE_SKILL_DAMAGE 100

////////////////////////////////////////////////////////////////////////
//< 跨蝶攪 婦溼

//< 跨蝶攪 餌檜鍔
#define		MONSTER_SIZE 15
//< 跨蝶攪 奢問 彰嬪
#define		MONSTER_1_ATTACK_RANGE 55
//< 跨蝶攪 蛔濰 �捕�
#define		MONSTER_APPEAR_PROB 1
//< 跨蝶攪 檜翕樓紫
#define		BOSS_1_MOVE_SPEED 2.f
#define		MON1_MOVE_SPEED 2.f
#define		MON2_MOVE_SPEED 1.1f

////////////////////////////////////////////////////////////////////////
//< 裘 婦溼

//< 裘 譆謙 類 熱
#define		MAP_MAX_FLOOR 5
//< 類 滌 裘 だ橾
#define		LOAD_MAP_1_PATH		"Data/Map/testMap-1.txt"
#define		LOAD_MAP_2_PATH		"Data/Map/testMap-2.txt"
#define		LOAD_MAP_3_PATH		"Data/Map/testMap-3.txt"
#define		LOAD_MAP_4_PATH		"Data/Map/testMap-4.txt"
#define		LOAD_MAP_5_PATH		"Data/Map/testMap-5.txt"

//< 顫橾 餌檜鍔
static const int TILE_SIZE_X = 64;
static const int TILE_SIZE_Y = 32;

//< 衛濛衛 煎萄й 裘 薑爾 唳煎
//#define START_LOAD_MAP_PATH		"Data/Map/BosstestMap.txt"
#define START_LOAD_MAP_PATH		"Data/Map/startMap.txt"
//#define		START_LOAD_MAP_PATH		"Data/Map/testMap-5.txt"
////////////////////////////////////////////////////////////////////////

//< 檜嘐雖 楠渦 螃Щ撢 (熱纂虜躑 嬪縑 楠渦)
static const int RENDER_OFFSET_Y = 15;

////////////////////////////////////////////////////////////////////////
//< 議葛攪 婦溼

//< 謙褶
enum
{
    TRIBE_WOLF,				//< 期渠檣除
    TRIBE_KENTA,			//< 騰顫辦煎蝶
    TRIBE_ELF,				//< 縣Щ
    TRIBE_UNDEAD			//< 樹等萄
};

//< 霜機
enum E_JobType
{
	JOB_NONE,
    JOB_KNIGHT,			//< 瞪餌
	JOB_ARCHER,			//< 嬴籀
    JOB_THIEF,			//< 紫瞳
    JOB_MAGICIAN,		//< 葆徹餌
};

//< 褐喃
enum
{
    BELIEF_GID,		//<雖萄
    BELIEF_MAGA,	//<葆陛隴纂
    BELIEF_NAA,		//<釭嬴酈
    BELIEF_BORE,	//<爾溯嬴蝶
    BELIEF_TANATO	//<顫釭饜
};

//< 議葛攪 鼻鷓 檜鼻
enum
{
    CONDITION_NORMAL = 0,	//< 薑鼻
    CONDITION_POISON,		//< 絮
    CONDITION_STRONG,		//< 鬼��
    CONDITION_WEAKEN,		//< 擒��
    CONDITION_INBEAT		//< 鼠瞳
};

////////////////////////////////////////////////////////////////////////
//< 嬴檜蠱 婦溼
//< 嬴檜蠱 餌檜鍔
#define POTION_SIZE_X 25
#define POTION_SIZE_Y 29
//< 嬴檜蠱 嬴檜蛤
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
//< 8寞
enum Direction
{
    DIR_L, DIR_LU, DIR_U, DIR_RU, DIR_R, DIR_RD, DIR_D, DIR_LD
};

//< 幗が, で機璽 薑溺晦遽
enum
{
    ALIGN_CENTER,			//< 醞除薑溺
    ALIGN_LEFT_TOP,			//< 豭薹嬪 薑溺
    ALIGN_RIGHT_TOP,		//< 豭薹 嬴楚 薑溺
    ALIGN_LEFT_BOTTOM,		//< 螃艇薹 嬪 薑溺
    ALIGN_RIGHT_BOTTOM		//< 螃艇薹 嬴楚 薑溺
};

//< 煎斜檣壁 で機
enum
{
    POPUP_NONE,								//< で機 摹鷗瞪
    POPUP_NO_POPUP,							//< で機 橈擠
    POPUP_NO_POPUP_GET_MAKE_ROOM,
    //----------------------------------------------------------
    POPUP_LOGIN_LOGIN_OVERLABID,			//< 醞犒 煎斜檣
    POPUP_LOGIN_LOGIN_FAILL,				//< 煎斜檣 褒ぬ
    POPUP_LOGIN_LOGIN_SUCCESS,				//< 煎斜檣 撩奢
    POPUP_LOGIN_EXIT,						//< 釭陛晦 で機
    POPUP_LOGIN_LOGIN_DISCORD_PASS,			//< 綠塵廓�ㄟ� 橾纂ж雖 彊擠
                                            //----------------------------------------------------------
                                            POPUP_LOGIN_JOIN,						//< �蛾灠㊣埼�
                                            POPUP_LOGIN_JOIN_SUCCESS,				//< �蛾灠㊣� 撩奢
                                            POPUP_LOGIN_JOIN_FAILL,					//< �蛾灠㊣� 褒ぬ
                                            POPUP_LOGIN_JOIN_FAIL_NONE,				//< 殮溘и 薑爾 睡褶
                                            POPUP_LOGIN_JOIN_FAIL_OVERLAP_ID,		//< 嬴檜蛤陛 啜蟻擊陽
                                            POPUP_LOGIN_JOIN_FAIL_DISCORD_PASS,		//< 營殮溘ぬ蝶錶萄 碳橾纂
                                                                                    //----------------------------------------------------------
                                                                                    POPUP_TITLE_RANK,						//< 楨韁 で機
                                                                                    POPUP_TITLE_COLLECTION,					//< 屬滓暮 で機
                                                                                    POPUP_TITLE_LOGOUT,						//< 煎斜嬴醒 で機
                                                                                                                            //----------------------------------------------------------
                                                                                                                            POPUP_LOBBY_FRIENDLIST,					//< 耀掘 跡煙
                                                                                                                            POPUP_LOBBY_MAKEROOM_OPEN,				//< 寞虜菟晦 奢偃
                                                                                                                            POPUP_LOBBY_MAKEROOM_CLOSE,				//< 寞葆菟晦 綠奢偃
                                                                                                                            POPUP_LOBBY_MAKEROOM_SUCCESS,			//< 寞虜菟晦 撩奢
                                                                                                                                                                    //----------------------------------------------------------
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_CLOSE,			//< 虜萇寞 綠奢偃
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_OPEN,			//< 虜萇寞 奢偃
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_SUCCESS,			//< 寞殮濰 撩奢
                                                                                                                                                                    POPUP_LOBBY_ENTER_ROOM_FAILL,			//< 寞殮濰 褒ぬ
                                                                                                                                                                                                            //----------------------------------------------------------
                                                                                                                                                                                                            POPUP_GAME_WAIT_USER,					//< 嶸盪 晦棻葬晦 で機
                                                                                                                                                                                                            POPUP_GAME_OVER,						//< 啪歜螃幗 で機
                                                                                                                                                                                                            POPUP_GAME_RANK,						//< 啪歜螃幗 楨韁で機
                                                                                                                                                                                                                                                    //----------------------------------------------------------
                                                                                                                                                                                                                                                    POPUP_END
};
//< 煎斜檣 鼻鷓
enum
{
    LOGIN_SUCCESS,
    LOGIN_FAIL,
};

//< 幗が 謙盟
enum
{
    BUTTON_OK,
    BUTTON_CANCEL,
    BUTTON_JOIN,
    BUTTON_EXIT,
};

//< �蛾灠㊣� Ы楚斜
enum
{
    JOIN_SUCCESS,
    JOIN_FAIL_NONE,
    JOIN_FAIL_OVERLAP_ID,
    JOIN_FAIL_DISCORD_PASS,
};

//< 綠お裘 顫殮
enum BITMAP_TYPE
{
    NONE_BITMAP,
    ALPA_BITMAP
};

//< 螃粽薛お 顫殮
enum
{
    OBJECT_ITEM,
    OBJECT_MONSTER,
    OBJECT_SKILL,
    OBJECT_SPEL
};

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 檜嘐雖 嬴檜蛤, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
//< 寥幗ぷ 檜嘐雖 堅薑
enum E_ImageID
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

    //< 塭檜お 裘ё
    imgID_LITE_MAPING,
    //< 衛撿 �膩�
    imgID_SIGHT,
    //< 顫問 檜めお 檜嘐雖
    imgID_HITEFF1,
    imgID_HITEFF2,
    imgID_HITEFF3,

    //< 議葛攪
    imgID_CHARACTER,

    imgID_WARRIOR_IDLE,
    imgID_WARRIOR_MOVE,
    imgID_WARRIOR_ATK,
    imgID_WARRIOR_DIE,
    imgID_WARRIOR_BEHIT,
    imgID_WARRIOR_DASH,

	imgID_ARCHER_IDLE,
	imgID_ARCHER_MOVE,
	imgID_ARCHER_ATK,
	imgID_ARCHER_DIE,
	imgID_ARCHER_BEHIT,
	imgID_ARCHER_DASH,

	imgID_ARCHER_ARROW,

    //< 堅綰萼
    imgID_MONSTER_1_IDLE,
    imgID_MONSTER_1_MOVE,
    imgID_MONSTER_1_ATK,
    imgID_MONSTER_1_DIE,
    //< 弊溯
    imgID_MONSTER_3_IDLE,
    imgID_MONSTER_3_MOVE,
    imgID_MONSTER_3_ATK,
    imgID_MONSTER_3_BEHIT,
    imgID_MONSTER_3_DIE,
    //< 掘選
    imgID_MONSTER_4_IDLE,
    imgID_MONSTER_4_MOVE,
    imgID_MONSTER_4_ATK,
    imgID_MONSTER_4_BEHIT,
    imgID_MONSTER_4_DIE,
    //< 棻觼 蝶だ檜渦
    imgID_MONSTER_6_IDLE,
    imgID_MONSTER_6_MOVE,
    imgID_MONSTER_6_ATK,
    imgID_MONSTER_6_BEHIT,
    imgID_MONSTER_6_DIE,
    //< 蜂滄
    imgID_MONSTER_7_IDLE,
    imgID_MONSTER_7_MOVE,
    imgID_MONSTER_7_ATK,
    imgID_MONSTER_7_BEHIT,
    imgID_MONSTER_7_DIE,
    //< 檣除紫舜
    imgID_MONSTER_9_IDLE,
    imgID_MONSTER_9_MOVE,
    imgID_MONSTER_9_ATK,
    imgID_MONSTER_9_BEHIT,
    imgID_MONSTER_9_DIE,
    //< 檣除瞪餌
    imgID_MONSTER_10_IDLE,
    imgID_MONSTER_10_MOVE,
    imgID_MONSTER_10_ATK,
    imgID_MONSTER_10_BEHIT,
    imgID_MONSTER_10_DIE,

    //< 餌薯 釭檜萄
    imgID_BOSS_NAID,
    imgID_BOSS_MOVE,
    imgID_BOSS_ATK,
    imgID_BOSS_BEHIT,
    imgID_BOSS_NAID_DIE,

    //< 敘葬縣
    imgID_BOSS_GYURIEL_IDLE,
    imgID_BOSS_GYURIEL_MOVE,
    imgID_BOSS_GYURIEL_ATK,
    imgID_BOSS_GYURIEL_BEHIT,
    imgID_BOSS_GYURIEL_DIE,
    imgID_BOSS_GYURIEL_SPECIAL,



    imgID_BUTTON1,
    imgID_BUTTON2,

    //< ん暮 檜嘐雖
    imgID_POTION_1,
    imgID_POTION_2,
    imgID_POTION_3,
    imgID_POTION_4,
    imgID_POTION_5,
    imgID_POTION_6,

    //< 嬴檜蠱 檣漸饜葬
    imgID_INVEN_POTION_1, //49
    imgID_INVEN_POTION_2,
    imgID_INVEN_POTION_3,
    imgID_INVEN_POTION_4,
    imgID_INVEN_POTION_5,
    imgID_INVEN_POTION_6,

    imgID_END
};

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 顫橾 粽楝蓮, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

//< 顫橾 顫殮 蛤だ檣
//typedef unsigned int E_TileBrush;

enum E_TileBrush
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

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 餌遴萄 婦葬, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

enum SoundKind
{
    SOUND_TITLE,
    SOUND_LOBBY,
    SOUND_INGAME,
    SOUND_BOSS,
    SOUND_POPUP,

    //馨葛攪
    CHAR_ATK,
    CHAR_HIT,
    CHAR_DIE,

    //堅綰萼 
    GLB_ATK,
    GLB_HIT,
    GLB_DIE,

    //弊溯
    BUG_ATK,
    BUG_HIT,
    BUG_DIE,

    //掘選
    GUL_ATK,
    GUL_HIT,
    GUL_DIE,

    //匐擎剪嘐
    SPIDER_ATK,
    SPIDER_HIT,
    SPIDER_DIE,

    //蜂滄
    STOR_ATK,
    STOR_HIT,
    STOR_DIE,

    //檣除瞪餌
    WARRIOR_ATK,
    WARRIOR_HIT,
    WARRIOR_DIE,

    //檣除紫瞳
    ROGUE_ATK,
    ROGUE_HIT,
    ROGUE_DIE,

    //啻檜萄
    NAID_ATK,
    NAID_HIT,
    NAID_DIE,

    //蝶鑒餌遴萄

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

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04,擁棲詭檜暮 婦葬, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

enum AniEffect
{
    ET_STR = 0,
    ET_STR1,
    ET_STR2,

    ET_STR3,
    //---檜翕賅暮---
    //嬴楚
    CHAR_D,
    //嬪
    CHAR_U,
    //豭薹
    CHAR_L,
    //螃艇薹
    CHAR_R,
    //豭薹 嬪
    CHAR_LU,
    //螃艇薹 嬪
    CHAR_RU,
    //豭薹 嬴楚
    CHAR_LD,
    //螃艇薹 嬴楚
    CHAR_RD,

    //---奢問賅暮---
    //豭薹 奢問
    ATK_L,
    //螃艇薹 奢問
    ATK_R,
    //嬪薹奢問
    ATK_U,
    //嬴楚薹 奢問
    ATK_D,
    //豭薹 嬪 奢問
    ATK_LU,
    //豭薹 嬴楚 奢問
    ATK_LD,
    //螃艇薹 嬪 奢問
    ATK_RU,
    //螃艇薹 嬴楚 奢問
    ATK_RD,

    //掙熱馨葛
    //---檜翕賅暮---
    //嬴楚
    WCHAR_D,
    //嬪
    WCHAR_U,
    //豭薹
    WCHAR_L,
    //螃艇薹
    WCHAR_R,
    //豭薹 嬪
    WCHAR_LU,
    //螃艇薹 嬪
    WCHAR_RU,
    //豭薹 嬴楚
    WCHAR_LD,
    //螃艇薹 嬴楚
    WCHAR_RD,

    //---奢問賅暮---
    //豭薹 奢問
    WATK_L,
    //螃艇薹 奢問
    WATK_R,
    //嬪薹奢問
    WATK_U,
    //嬴楚薹 奢問
    WATK_D,
    //豭薹 嬪 奢問
    WATK_LU,
    //豭薹 嬴楚 奢問
    WATK_LD,
    //螃艇薹 嬪 奢問
    WATK_RU,
    //螃艇薹 嬴楚 奢問
    WATK_RD,
    //堅綰萼 橫臢
    GBL_ATK,

    //堅綰萼Я問
    ET_END
};

enum monsterKind
{
    GOBLIN,	//< 堅綰萼

    MON_BUG, //< 弊溯
    GHOUL,	//< 掘選

    DARK_SPIDER, // 匐擎 剪嘐
    GHOST, // 蜂滄 
    HUMAN_THIEF, // 檣除紫舜
    HUMAN_KNIGHT,//檣除瞪餌
    BOSS_NAID,	//< 爾蝶 NAID
    BOSS_GYURIEL //< 爾蝶 GURIEL
};

const int MAX_SKILL_COUNT = 4;

// 寞 薑爾
typedef struct roomInfo
{
    int  m_roomNum;
    char m_roomName[64];
    char m_roomPW[64];
    bool m_isTrespass;
    bool m_isSecret;
    int m_userCount;
    char m_hostIP[16];
    unsigned short m_hostPort;
    char m_userName[2][16];
    bool m_isCharSelect;
}ROOM_INFO, *LPROOM_INFO;