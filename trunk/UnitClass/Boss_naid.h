#pragma once

#include "../monster.h"

class skill_naid_collum;

class boss_naid : public Monster
{
public:
	boss_naid(void);
	virtual ~boss_naid(void);

public:
//< 인터페이스
	//< 초기화
	virtual bool init(void);
	//< 해제
	virtual void release(void);
	//< 업데이트
	virtual void update( void );
	//< 랜더
	virtual void render(HDC hdc);

	//< 충돌 체크
	virtual bool collision( POINT &destPos );
	//< 공격
	virtual void attack( POINT &destPos );
	//< 인식
	virtual void recog( POINT &destPos );

	//< 타격
	virtual bool beHit(int damage); 
	//< 충돌체 렉트 반환
	virtual RECT getBallRect(void);
	//< 충돌체 상태
	virtual void setBallFlag( bool flag );
	virtual bool getBallFlag( void );
	//< 데미지
	virtual int getDamage(void);

	//애니메이션 설정
	void setAniInfo(void);

//< 멤버
private:
	//< 공격 충돌체
	cProjectile *ball;
	//< 공격 딜레이
	DELEY attDeley;	

	//< 스킬 충돌체
	//skill_naid_collum *m_skill_collum;
	//< 스킬 딜레이
	DELEY m_collum_deley;
};