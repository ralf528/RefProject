#pragma once

#include "character.h"

//< 게임 캐릭터 클래스
class cWarrior : public character
{
//< 생성자 소멸자
public:
	cWarrior(void);
	~cWarrior(void);

//< 인터페이스
public:
	//< 초기화
	virtual bool init(void);
	//< 해제
	virtual void release(void);
	//< 갱신
	virtual void update(void);
	//< 랜더
	virtual void render(HDC hdc);
	//< 하반신 랜더
	void renderLower(HDC hdc);

	//< 공격
	virtual void attack( void );
	//< 타격
	virtual bool beHit(int damage);
	//< 이동
	virtual void move( void );
	//< 대쉬
	virtual void dash( void );

	//< 데미지 얻기
	virtual int getDamage(void);

	//< 커넥션 인덱스 설정, 얻기
	//virtual inline void setConnectionIndex(int index)	 { m_connectionIndex = index; }
	//virtual inline int getConnectionIndex(void)			 { return m_connectionIndex; }

	//< 충돌체(아이템 등) 얻기
	virtual void gainCollider( tileType &obj );
	//< 렉트 설정
	void setRect( void );

	//애니메이션 설정
	void setAniInfo(void);
	//갱신
	void updateAni( LPANI_INFO aniInfo );
	//해제
	void releaseAniInfo( void );

	//< 무적모드
	void inbeatable( void );

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
	LPANI_INFO		m_HitAni_Info;
	LPANI_INFO		m_DashAni_Info;

	//< 무적모드 딜레이
	DELEY m_inbeatDeley;
};