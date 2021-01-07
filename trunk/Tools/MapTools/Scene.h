#pragma once

#include "State.h"

//////////////////////////////////////////////////////////
//< �α��� ���� �̹���
enum IMG_LOGIN
{
	IMG_LOGIN_BACK,
	IMG_LOGIN_CRAZY,
	IMG_LOGIN_LOGIN,
	IMG_LOGIN_OK,
	IMG_LOGIN_JOIN,
	IMG_LOGIN_END
};

//< �α��� �˾� �̹���
enum IMG_LOGIN_SUB
{
	IMG_LOGIN_SUB_BACK,
	IMG_LOGIN_SUB_CRAZY,
	IMG_LOGIN_SUB_ALPA,
	IMG_LOGIN_SUB_LOGIN_LOGIN,
	IMG_LOGIN_SUB_OK,
	IMG_LOGIN_SUB_END
};

//< �κ� ���� �̹���
enum IMG_LOBBY
{
	IMG_LOBBY_BACK,
	IMG_LOBBY_CRAZY,
	IMG_LOBBY_BACKBLACK,
	IMG_LOBBY_SCORE,
	IMG_LOBBY_CHOICE,
	IMG_LOBBY_END
};

//< �κ� �˾� �̹���
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

//< ��ŷ ���� �̹���
enum IMG_RANK
{
	IMG_RANK_BACK,
	IMG_RANK_ALPA,
	IMG_RANK_STAR,
	IMG_RANK_RANK_CHECK,
	IMG_RANK_RANK,
	IMG_RANK_END
};

//< ���Ӱ�� ���� �̹���
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

//< �߻� �� Ŭ����
class Scene : public State
{
public:
	Scene(void);
	virtual ~Scene(void);

public :
	//< ���콺 ��ġ
	POINT mousePos;
};