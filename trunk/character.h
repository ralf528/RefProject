#pragma once

#include "unit.h"
#include "level.h"

//< 공격 충돌체
class sphereObject;
class skillWhole;
//< 인벤토리
class Inventory;

//< 게임 캐릭터 클래스
class character : public Unit
{
//< 생성자 소멸자
public:
	character(void);
	~character(void);

//< 인터페이스
public:
	//< 초기화
	virtual bool init(void) = 0;
	//< 해제
	virtual void release(void) = 0;
	//< 갱신
	virtual void update(void) = 0;
	//< 랜더
	virtual void render(HDC hdc) = 0;

	//< 공격
	virtual void attack( void ) = 0;
	//< 타격
	virtual bool beHit(int damage) = 0;
	//< 이동
	virtual void move( void ) = 0;
	//< 대쉬
	virtual void dash( void ) = 0;

	//< 충돌체(아이템 등) 얻기
	virtual void gainCollider( tileType &obj );
	//< 아이템 사용
	virtual void useItem( void );
	//< 인벤토리 랜더
	virtual void renderInven(HDC hdc);
	//< 경험치 획득
	void gainExp( unsigned int exp ){ m_level.incExp( exp ); }
	//< 레벨 정보 얻기
	Level& getLevelInfo(void) { return m_level; }

	//< 좌표 설정
	virtual void setPos( POINT &pos );
	virtual void setPos( LONG x, LONG y );
	//< 이전 위치로 되돌리기
	virtual void setPosToPrev(void);

	//< 렉트 설정
	virtual void setRect(void);

	//< 커넥션 인덱스 설정, 얻기
	inline void setConnectionIndex(int index) 	 { m_connectionIndex = index; }
	inline int getConnectionIndex(void) 		 { return m_connectionIndex; }

	//< 공격 충돌체 렉트 반환
	RECT getBallRect(void);
	//< 스킬 렉트 반환
	RECT getSkillRect(void);

	//< 데미지 얻기
	virtual int getDamage(void) { return getStrong(); };

	//< 충돌체 상태
	void setBallFlag( bool flag );
	bool getBallFlag( void );

	//< 마법 충돌체 상태
	void setSkillBallFlag( bool flag );
	bool getSkillBallFlag( void );

	//< 렉트 얻기
	RECT getRect(void) { return m_rect; }
	
	//< 주위의 맵 정보
	POINT *getAroundVertex(void) { return vertex; }

	//< skill 얻기
	inline skillWhole *getSkill(void) { return skill; }
	//< 공격중 얻기
	virtual inline bool isAttack(void) { return m_isAttacking; }

	//< 살았는지 플래그
	inline bool getIsLive(void){ return m_isLive; }

	//< 상태 딜레이 셋
	void setStateDelay(unsigned int deley) { m_conDeley.m_deley = deley; }
	void setDelayTick(void) { m_conDeley.m_lastTime = GetTickCount(); }

//< 멤버 변수
protected:
	//< 살았는지
	bool m_isLive;
	//< 레벨 정보
	Level m_level;
	//< 이동 전 좌표
	POINT m_prevPos;
	//< 캐릭터 렉트
	RECT m_rect;
	
	//< 인벤토리
	Inventory *m_inventory;

	//< 주위의 맵 정보
	POINT vertex[8];

	//< 공격 충돌체
	sphereObject *ball;
	//< 스킬 충돌체
	skillWhole *skill;

	//< 이동 딜레이
	DELEY m_moveDeley;
	
	//< 상태 딜레이
	DELEY m_conDeley;

	//< 공격 딜레이
	DELEY attDeley;
	//< 전체 마법 딜레이
	DELEY wholeSkillDeley;
	//< 대쉬
	unsigned int dash_count;

	//< 네트워크 커넥션 인덱스 번호
	int m_connectionIndex;
	//< 공격중
	bool m_isAttacking;
};