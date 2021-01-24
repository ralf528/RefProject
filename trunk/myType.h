#ifndef __MYTYPE_H__
#define __MYTYPE_H__
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 전역 구조체 및 전역 타입, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

typedef struct tagAni_Info
{
	E_ImageID RCID;

    //프레임 가로세로 크기
    SIZE			aniSize;
    //프레임 개수
    int				frameCntX;
    int				frameCntY;
    //애니메이션 스피드
    int				frameSpeed;
    //현재 프레임
    int				nowFrame;
    int				nowFrameY;
    //< 방향
    //마지막 갱신 타임
    DWORD			lastTime;
    //플래그
    bool			flag;
    bool			playAni;
    bool			loop;

}ANI_INFO, *LPANI_INFO;

enum E_AnimationType
{
    None = 0,
    Idle,
    Move,
    Attack,
    Die,
    BeHit,
	Dash,
    HitEff,
};

enum DIR
{
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP
};


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 캐릭터 스테이터스, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

//< 스테이터스
typedef struct tagStates
{
    //< 신념
    unsigned int m_belief;
    //< 종족
    unsigned int m_tribe;
    //< 직업
    unsigned int m_job;

    //< 최대 체력
    unsigned int m_maxHP;
    //< 현재 체력
    unsigned int m_nowHP;
    //< 최대 마력
    unsigned int m_maxMP;
    //< 현재 마력
    unsigned int m_nowMP;

    //< 힘
    unsigned int m_str;
    //< 민
    unsigned int m_agl;
    //< 지
    unsigned int m_int;

    //< 이동속도
    float m_moveSpeed;

    //< 상태이상
    unsigned int m_condition;

}STATES;

//< 딜레이
typedef struct tagDeley
{
    //< 딜레이
    unsigned int m_deley;
    //< 카운트
    unsigned int m_lastTime;
}DELEY;


#endif