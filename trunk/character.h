#pragma once

#include "unit.h"
#include "level.h"
#include "SkillModuleComponent.h"

//< ���� �浹ü
class cProjectile;
class skillWhole;
struct CharacterTemplate;

//< ���� ĳ���� Ŭ����
class character : public Unit
{
//< ������ �Ҹ���
public:
	character(void);
	virtual ~character(void);

//< �������̽�
public:
	//< �ʱ�ȭ
	virtual bool init(void);
	//< ����
	virtual void release(void);
	//< ����
	virtual void update(float fDeltaTime);
	//< ����
	virtual void render(HDC hdc);
	//< �Ϲݽ� ����
	virtual void renderLower(HDC hdc);

	//< ����
	virtual void attack(void);
	//< Ÿ��
	virtual bool beHit(int damage);
	//< �̵�
	virtual void move(float fDeltaTime);

	FORCEINLINE int GetObjectID() { return ObjectID; }

	// �ִϸ��̼�
	void InitAnimInfo(const CharacterTemplate* Template);
	void releaseAniInfo();

	void RenderAnimation(HDC hdc, E_AnimationType eType);
	void StartAnimation(E_AnimationType eType);
	bool IsPlayingAnimation(E_AnimationType eType);

	// ����ü
	cProjectile* GetProjectile(E_SkillSlot::Type SkillType);
	bool CreateProjectile(E_SkillSlot::Type SkillType, POINT StartPos, POINT TargetPos, int Direction = 6);
	void ClearProjectile();
	void RemoveProjectile(E_SkillSlot::Type SkillType);
	void UpdateProjectile();
	void RenderProjectile(HDC hdc);
	RECT GetProjectileRect(E_SkillSlot::Type SkillType);
	bool IsPlayingProjectile(E_SkillSlot::Type SkillType);
	void SetProjectileFlag(E_SkillSlot::Type SkillType, bool flag);
	bool GetProjectileFlag(E_SkillSlot::Type SkillType);

	//< ����ġ ȹ��
	void gainExp( unsigned int exp ){ m_level.incExp( exp ); }
	//< ���� ���� ���
	Level& getLevelInfo(void) { return m_level; }

	void SetJobType(E_JobType JobType) { m_JobType = JobType; }

	//< ��ǥ ����
	virtual void setPos( POINT &pos );
	virtual void setPos( LONG x, LONG y );
	//< ���� ��ġ�� �ǵ�����
	virtual void setPosToPrev(void);

	//< ��Ʈ ����
	virtual void setRect(void);

	//< ������ ���
	virtual int getDamage(void);

	//< �浹ü(������ ��) ���
	virtual void gainCollider(E_TileBrush obj);

	//< ��Ʈ ���
	RECT getRect(void) { return m_rect; }
	
	//< ������ �� ����
	POINT *getAroundVertex(void) { return vertex; }

	//< ������ ���
	virtual inline bool isAttack(void) { return m_isAttacking; }

	//< ��Ҵ��� �÷���
	inline bool getIsLive(void){ return m_isLive; }

	//< ��ų
    virtual void ProcessSkill(unsigned int nIndex);
	virtual bool ProcessPassiveSkill();

	//< ���� Ʈ����
	void AttackTrigger();

	//< �뽬
	void UpdateDash();

	void Inbeatable();
	void DashTrigger();
	void ShootWholeSkill();

	// �����̻�


private:
	int ObjectID;
	
	E_JobType m_JobType;

	Level m_level;
	int m_PrefLevel;

	//< �̵� �� ��ǥ
	POINT m_prevPos;
	//< ĳ���� ��Ʈ
	RECT m_rect;
	
	//< �ִϸ��̼� ����
	std::map<E_AnimationType, LPANI_INFO> m_Animations;


	//< ������ �� ����
	POINT vertex[8];

	//< ���� ���� ����
	int m_nowState;

	// state
	bool m_isLive;
	bool m_isAttacking;

	std::map<int, cProjectile*> ProjectileMap;

	//< �̵� ������
	DELAY_TIME m_moveDeley;
	//< ���� ������
	DELAY_TIME m_conDeley;
	//< ���� ��Ÿ��
	DELAY_TIME NormalAttackCooltime;
	//< ��ü ���� ��Ÿ��
	DELAY_TIME wholeSkillCoolTime;
	//< ������� ��Ÿ��
	DELAY_TIME InbeatCoolTime;
	
	//< �뽬
	unsigned int dash_count;
	//< ü�¸��� �ڵ���� ī��Ʈ
	int m_hpCount;
	int m_mpCount;

	std::vector<E_SkillSlot::Type> m_Skills;

	SkillModuleComponent SkillComponent;
};