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

	//< 스킬
    virtual void ProcessSkill(int nIndex) override;

	//< 대쉬
	void UpdateDash();

	void Inbeatable();
    void DashTrigger();
    void ShootWholeSkill();

//< 멤버 변수
protected:
	//< 체력마력 자동재생 카운트
	int m_hpCount;
	int m_mpCount;

	//< 무적모드 딜레이
	DELEY m_inbeatDeley;
};