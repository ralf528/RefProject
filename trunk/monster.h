#pragma once

#include "unit.h"

//< 공격 충돌체

class cProjectile; 

//< 상태
enum
{
	STATE_DIE,
	STATE_IDLE,
	STATE_CHASE,
	STATE_MOVE = STATE_CHASE,
	STATE_ATTACK,
	STATE_BEHIT,
};

class Monster : public Unit
{
public:
//< 생성자 소멸자
	Monster(void);
	virtual ~Monster(void);

public:
//< 인터페이스
	//< 초기화
	virtual bool init(void) = 0;
	//< 해제
	virtual void release(void) = 0;
	//< 업데이트
	virtual void update(float fDeltaTime) = 0;
	//< 랜더
	virtual void render(HDC hdc) = 0;

	//< 이동
	virtual void move( POINT &destPos );
	//< 충돌 체크
	virtual bool collision( POINT &destPos ) = 0;
	//< 공격
	virtual void attack( POINT &destPos ) = 0;
	//< 인식
	virtual void recog( POINT &destPos ) = 0;

	//< 타격
	virtual bool beHit(int damage) = 0; 
	
	//< HP 바 랜더
	virtual void renderHPbar(HDC hdc);
	//< HP 바 랜더 카운트
	virtual void hpRenderStart(void);

//< 프로퍼티즈
	//< 인식 범위
	virtual int getRecogRange(void)			{ return m_recogRange; } 
	virtual void  setRecogRange(int range)	{ m_recogRange = range; }
	//< 공격 사거리
	virtual int getAttRange(void)			{ return m_attRange; } 
	virtual void  setAttRange(int range)	{ m_attRange = range; }
	//< 행동 플래그
	virtual int getStateFlag(void)			{ return m_stateFlag; }
	virtual void setStateFlag( int state )	{ m_stateFlag = state; }
	//< 이전 위치로 돌아가기
	virtual void setPosToPrev( void )			{ m_pos = m_prevPos; }
	//< 몬스터 렉트 반환
	virtual RECT getRect(void);
	//< 방향 계산
	void calcDir(POINT &destPos);

	//< 충돌체 렉트 반환
	virtual RECT getBallRect(void){ RECT rt; SetRect(&rt,0,0,0,0); return rt;}
	//< 충돌체 상태
	virtual void setBallFlag( bool flag ){}
	virtual bool getBallFlag( void ){return false;}
	//< 데미지
	virtual int getDamage(void) = 0;

	//< 보스만 사용
	//< 공격
	virtual void normalAttack(POINT &destPos) {}
	//< 스킬 1
	virtual void skill_01(POINT &destPos) {}
	//< 스킬 2
	virtual void skill_02(POINT &destPos) {}

	//< 경험치
	virtual unsigned int getExp(void) { return m_exp;}
	
	//< 주위의 맵 정보
	virtual POINT *getAroundVertex(void) { return vertex; }

	//< 몬스터 종류 얻기
	virtual int getMonsterKind(void) { return m_kindNum; }

	//해제
	virtual void releaseAniInfo( void );

//< 멤버
protected:
	//< 몬스터 종류 넘버
	monsterKind m_kindNum;
	//< 몬스터 크기
	int m_monSize;

	//< 인식범위
	int m_recogRange;
	//< 공격 사거리
	int m_attRange;
	//< 행동플래그
	int m_stateFlag;
	//< 이전 위치
	POINT m_prevPos;

	//< 현재 방향
	int m_dir;

	//< 주위의 맵 정보
	POINT vertex[8];
	
	//< 몬스터 경험치
	unsigned int m_exp;

	//< hp바 표시 딜레이
	bool hpRenderFlag;
	DELEY hpRenderDeley;

	//< 이동 딜레이
	DELEY m_moveDeley;

	//< 애니메이션 정보
	LPANI_INFO		m_IdleAni_Info;
	LPANI_INFO		m_MoveAni_Info;
	LPANI_INFO		m_AtckAni_Info;
	LPANI_INFO		m_DieAni_Info;
	LPANI_INFO		m_beHitAni_Info;
	LPANI_INFO		m_HitAni_Info;
};