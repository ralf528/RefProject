#pragma once

#include "character.h"

//< 게임 캐릭터 클래스
class cWarrior : public character
{
public:
	cWarrior(void);
	virtual ~cWarrior(void);

public:
	//< 초기화
	virtual bool init() override;
	//< 해제
	virtual void release() override;
	//< 갱신
	virtual void update(float fDeltaTime) override;
	//< 랜더
	virtual void render(HDC hdc) override;
	//< 하반신 랜더
	void renderLower(HDC hdc);

	//< 공격
	virtual void attack() override;
	//< 타격
	virtual bool beHit(int damage) override;
	//< 이동
	virtual void move(float fDeltaTime) override;
	//< 대쉬
	virtual void dash() override;

	//< 데미지 얻기
	virtual int getDamage();

	//애니메이션 설정
	void InitAnimInfo();
	//해제
	void releaseAniInfo();

	void RenderAnimation(HDC hdc, imgID animation);
	void StartAnimation(imgID animation);
	bool IsPlayingAnimation(imgID animation);

    virtual void ProcessSkill(int nIndex) override;

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
	int m_PrefLevel;

	//< 현재 상태 정보
	int m_nowState;

    //< 애니메이션 정보
    std::map<imgID, LPANI_INFO> m_Animations;

	//< 무적모드 딜레이
	DELEY m_inbeatDeley;
};