#pragma once

#include "unit.h"
#include "level.h"

//< 공격 충돌체
class cProjectile;
class skillWhole;
struct CharacterTemplate;

//< 게임 캐릭터 클래스
class character : public Unit
{
//< 생성자 소멸자
public:
	character(void);
	virtual ~character(void);

//< 인터페이스
public:
	//< 초기화
	virtual bool init(void);
	//< 해제
	virtual void release(void);
	//< 갱신
	virtual void update(float fDeltaTime);
	//< 랜더
	virtual void render(HDC hdc);
	//< 하반신 랜더
	virtual void renderLower(HDC hdc);

	//< 공격
	virtual void attack(void);
	//< 타격
	virtual bool beHit(int damage);
	//< 이동
	virtual void move(float fDeltaTime);

	FORCEINLINE int GetObjectID() { return ObjectID; }

	// 애니메이션
	void InitAnimInfo(const CharacterTemplate* Template);
	void releaseAniInfo();

	void RenderAnimation(HDC hdc, E_AnimationType eType);
	void StartAnimation(E_AnimationType eType);
	bool IsPlayingAnimation(E_AnimationType eType);

	//< 경험치 획득
	void gainExp( unsigned int exp ){ m_level.incExp( exp ); }
	//< 레벨 정보 얻기
	Level& getLevelInfo(void) { return m_level; }

	void SetJobType(E_JobType JobType) { m_JobType = JobType; }

	//< 좌표 설정
	virtual void setPos( POINT &pos );
	virtual void setPos( LONG x, LONG y );
	//< 이전 위치로 되돌리기
	virtual void setPosToPrev(void);

	//< 렉트 설정
	virtual void setRect(void);

	//< 공격 충돌체 렉트 반환
	RECT getBallRect(void);
	//< 스킬 렉트 반환
	RECT getSkillRect(void);

	//< 데미지 얻기
	virtual int getDamage(void);

	//< 충돌체(아이템 등) 얻기
	virtual void gainCollider(E_TileBrush obj);

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
	inline cProjectile *getSkill(void) { return SkillProjectile; }
	//< 공격중 얻기
	virtual inline bool isAttack(void) { return m_isAttacking; }

	//< 살았는지 플래그
	inline bool getIsLive(void){ return m_isLive; }

	//< 스킬
    virtual void ProcessSkill(unsigned int nIndex);

	//< 공격 트리거
	void AttackTrigger();

	//< 대쉬
	void UpdateDash();

	void Inbeatable();
	void DashTrigger();
	void ShootWholeSkill();

	// 상태이상


private:
	int ObjectID;
	
	E_JobType m_JobType;

	Level m_level;
	int m_PrefLevel;

	//< 이동 전 좌표
	POINT m_prevPos;
	//< 캐릭터 렉트
	RECT m_rect;
	
	//< 애니메이션 정보
	std::map<E_AnimationType, LPANI_INFO> m_Animations;


	//< 주위의 맵 정보
	POINT vertex[8];

	//< 현재 상태 정보
	int m_nowState;

	// state
	bool m_isLive;
	bool m_isAttacking;

	//< 공격 투사체
	cProjectile *AttackProjectile;
	//< 스킬 투사체
	cProjectile *SkillProjectile;

	//< 이동 딜레이
	DELAY_TIME m_moveDeley;
	//< 상태 딜레이
	DELAY_TIME m_conDeley;
	//< 공격 쿨타임
	DELAY_TIME NormalAttackCooltime;
	//< 전체 마법 쿨타임
	DELAY_TIME wholeSkillCoolTime;
	//< 무적모드 쿨타임
	DELAY_TIME InbeatCoolTime;
	
	//< 대쉬
	unsigned int dash_count;
	//< 체력마력 자동재생 카운트
	int m_hpCount;
	int m_mpCount;

	std::vector<E_SkillType> m_Skills;
};