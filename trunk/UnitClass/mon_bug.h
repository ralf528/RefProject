#pragma once

#include "../monster.h"

class mon_bug : public Monster
{
public:
//< 생성자 소멸자
	mon_bug(void);
	virtual ~mon_bug(void);

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

	//< 충돌체 렉트 반환
	virtual RECT getBallRect(void);
	//< 충돌체 상태
	virtual void setBallFlag( bool flag );
	virtual bool getBallFlag( void );
	//< 데미지
	virtual int getDamage(void);

	//애니메이션 설정
	void setAniInfo(void);
	//갱신
	void updateAni( LPANI_INFO aniInfo );

//< 멤버
private:
	//< 공격 충돌체
	cProjectile *ball;
	//< 공격 딜레이
	DELEY attDeley;
};