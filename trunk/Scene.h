#pragma once

#include "State.h"

//////////////////////////////////////////////////////////
//< 로그인 정보 이미지
enum IMG_LOGIN
{
	IMG_LOGIN_BACK,
	IMG_LOGIN_CRAZY,
	IMG_LOGIN_LOGIN,
	IMG_LOGIN_OK,
	IMG_LOGIN_JOIN,
	IMG_LOGIN_END
};

//< 로그인 팝업 이미지
enum IMG_LOGIN_SUB
{
	IMG_LOGIN_SUB_BACK,
	IMG_LOGIN_SUB_CRAZY,
	IMG_LOGIN_SUB_ALPA,
	IMG_LOGIN_SUB_LOGIN_LOGIN,
	IMG_LOGIN_SUB_OK,
	IMG_LOGIN_SUB_END
};

//< 로비 정보 이미지
enum IMG_LOBBY
{
	IMG_LOBBY_BACK,
	IMG_LOBBY_CRAZY,
	IMG_LOBBY_BACKBLACK,
	IMG_LOBBY_SCORE,
	IMG_LOBBY_CHOICE,
	IMG_LOBBY_END
};

//< 로비 팝업 이미지
enum IMG_EXIT
{
	IMG_EXIT_BACK,
	IMG_EXIT_CRAZY,
	IMG_EXIT_BACKBLACK,
	IMG_EXIT_SCORE,
	IMG_EXIT_SUB_ALPA,
	IMG_EXIT_LOGIN,
	IMG_EXIT_CHAR,
	IMG_EXIT_YES,
	IMG_EXIT_NO,
	IMG_EXIT_CHOICE,
	IMG_EXIT_END
};

//< 랭킹 정보 이미지
enum IMG_RANK
{
	IMG_RANK_BACK,
	IMG_RANK_ALPA,
	IMG_RANK_STAR,
	IMG_RANK_RANK_CHECK,
	IMG_RANK_RANK,
	IMG_RANK_END
};

//< 게임결과 정보 이미지
enum IMG_RESULT
{
	IMG_RESULT_BACK,
	IMG_RESULT_ALPA,
	IMG_RESULT_CRAZY,
	IMG_RESULT_LINE,
	IMG_RESULT_END
};
//////////////////////////////////////////////////////////
enum SUB_SCENE
{
	SUB_FAIL = -1,
	SUB_USER_IN = 0,
	SUB_LOGIN_SUC,
	SUB_LOGIN_FAIL,
	SUB_ID_FAIL,
	SUB_PASS_FAIL
};

/////////////////////////////////////////////////////////

//< 추상 씬 클래스
class Scene : public State
{
public:
	Scene(void);
	virtual ~Scene(void);

public :
	//< 마우스 위치
	POINT mousePos;
};