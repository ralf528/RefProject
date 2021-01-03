#pragma once

#include "../monster.h"

class Gyuriel : public Monster
{
public:
	Gyuriel(void);
	virtual ~Gyuriel(void);

public:
//< 인터페이스
	//< 초기화
	virtual bool init(void);
	//< 해제
	virtual void release(void);
	//< 업데이트
	virtual void update(float fDeltaTime);
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
	//< 몬스터 렉트 반환
	virtual RECT getRect( void );
	//< 충돌체 렉트 반환
	virtual RECT getBallRect(void);
	//< 충돌체 상태
	virtual void setBallFlag( bool flag );
	virtual bool getBallFlag( void );
	//< 데미지
	virtual int getDamage(void);

	//< HP 바 랜더
	virtual void renderHPbar(HDC hdc);

	//애니메이션 설정
	void setAniInfo(void);
	//갱신
	void updateAni( LPANI_INFO aniInfo );
	//해제
	virtual void releaseAniInfo( void );

	//< 보스만 사용
	//< 공격
	virtual void normalAttack(POINT &destPos);
	//< 스킬 1
	virtual void skill_01(POINT &destPos);
	//< 스킬 2
	virtual void skill_02(POINT &destPos);

//< 멤버
private:
	//< 공격 충돌체
	cProjectile *ball;
	//< 공격 딜레이
	DELEY attDeley;	

	//< 스킬 충돌체
	cProjectile *m_skill_collum;
	cProjectile *m_skill_destruction;

	//< 스킬 딜레이
	DELEY m_collum_deley;
	DELEY m_destroy_deley;

	//< 스페셜 애니메이션
	LPANI_INFO m_spclAni_info;
};