#pragma once

#include "character.h"

//< 게임 캐릭터 클래스
class cWarrior : public character
{
//< 생성자 소멸자
public:
	cWarrior();
	~cWarrior();

//< 인터페이스
public:
	//< 초기화
	virtual bool init();
	//< 해제
	virtual void release();
	//< 갱신
	virtual void update(float fDeltaTime);
	//< 랜더
	virtual void render(HDC hdc);
	//< 하반신 랜더
	void renderLower(HDC hdc);

	//< 공격
	virtual void attack();
	//< 타격
	virtual bool beHit(int damage);
	//< 이동
	virtual void move(float fDeltaTime);
	//< 대쉬
	virtual void dash();

	//< 데미지 얻기
	virtual int getDamage();

	//< 충돌체(아이템 등) 얻기
	virtual void gainCollider( tileType &obj );
	//< 렉트 설정
	void setRect();

	//애니메이션 설정
	void InitAnimInfo();
	//해제
	void releaseAniInfo();

    virtual void ProcessSkill(int nIndex);

    void AttackTrigger();
    void Inbeatable();
    void DashTrigger();
    void ShootWholeSkill();

//< 멤버 변수
protected:
	//< 체력마력 자동재생 카운트
	int m_hpCount;
	int m_mpCount;

	//< 현재 레벨
	int m_levelFlag;

	//< 현재 상태 정보
	int m_nowState;

    //< 애니메이션 정보
	LPANI_INFO		m_IdleAni_Info;
	LPANI_INFO		m_MoveAni_Info;
	LPANI_INFO		m_AtckAni_Info;
	LPANI_INFO		m_DieAni_Info;
	LPANI_INFO		m_beHitAni_Info;
	LPANI_INFO		m_HitEff_Info;
	LPANI_INFO		m_DashAni_Info;
    //std::map<int, LPANI_INFO> m_Animations;

	//< 무적모드 딜레이
	DELEY m_inbeatDeley;
};