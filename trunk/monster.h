#pragma once

#include "unit.h"

//< ���� �浹ü

class cProjectile; 

//< ����
enum
{
	STATE_DIE,
	STATE_IDLE,
	STATE_CHASE,
	STATE_MOVE = STATE_CHASE,
	STATE_ATTACK,
	STATE_BEHIT,
};

class Monster : public Unit
{
public:
//< ������ �Ҹ���
	Monster(void);
	virtual ~Monster(void);

public:
//< �������̽�
	//< �ʱ�ȭ
	virtual bool init(void) = 0;
	//< ����
	virtual void release(void) = 0;
	//< ������Ʈ
	virtual void update(float fDeltaTime) = 0;
	//< ����
	virtual void render(HDC hdc) = 0;

	//< �̵�
	virtual void move( POINT &destPos );
	//< �浹 üũ
	virtual bool collision( POINT &destPos ) = 0;
	//< ����
	virtual void attack( POINT &destPos ) = 0;
	//< �ν�
	virtual void recog( POINT &destPos ) = 0;

	//< Ÿ��
	virtual bool beHit(int damage) = 0; 
	
	//< HP �� ����
	virtual void renderHPbar(HDC hdc);
	//< HP �� ���� ī��Ʈ
	virtual void hpRenderStart(void);

//< ������Ƽ��
	//< �ν� ����
	virtual int getRecogRange(void)			{ return m_recogRange; } 
	virtual void  setRecogRange(int range)	{ m_recogRange = range; }
	//< ���� ��Ÿ�
	virtual int getAttRange(void)			{ return m_attRange; } 
	virtual void  setAttRange(int range)	{ m_attRange = range; }
	//< �ൿ �÷���
	virtual int getStateFlag(void)			{ return m_stateFlag; }
	virtual void setStateFlag( int state )	{ m_stateFlag = state; }
	//< ���� ��ġ�� ���ư���
	virtual void setPosToPrev( void )			{ m_pos = m_prevPos; }
	//< ���� ��Ʈ ��ȯ
	virtual RECT getRect(void);
	//< ���� ���
	void calcDir(POINT &destPos);

	//< �浹ü ��Ʈ ��ȯ
	virtual RECT getBallRect(void){ RECT rt; SetRect(&rt,0,0,0,0); return rt;}
	//< �浹ü ����
	virtual void setBallFlag( bool flag ){}
	virtual bool getBallFlag( void ){return false;}
	//< ������
	virtual int getDamage(void) = 0;

	//< ������ ���
	//< ����
	virtual void normalAttack(POINT &destPos) {}
	//< ��ų 1
	virtual void skill_01(POINT &destPos) {}
	//< ��ų 2
	virtual void skill_02(POINT &destPos) {}

	//< ����ġ
	virtual unsigned int getExp(void) { return m_exp;}
	
	//< ������ �� ����
	virtual POINT *getAroundVertex(void) { return vertex; }

	//< ���� ���� ���
	virtual int getMonsterKind(void) { return m_kindNum; }

	//����
	virtual void releaseAniInfo( void );

//< ���
protected:
	//< ���� ���� �ѹ�
	monsterKind m_kindNum;
	//< ���� ũ��
	int m_monSize;

	//< �νĹ���
	int m_recogRange;
	//< ���� ��Ÿ�
	int m_attRange;
	//< �ൿ�÷���
	int m_stateFlag;
	//< ���� ��ġ
	POINT m_prevPos;

	//< ���� ����
	int m_dir;

	//< ������ �� ����
	POINT vertex[8];
	
	//< ���� ����ġ
	unsigned int m_exp;

	//< hp�� ǥ�� ������
	bool hpRenderFlag;
	DELEY hpRenderDeley;

	//< �̵� ������
	DELEY m_moveDeley;

	//< �ִϸ��̼� ����
	LPANI_INFO		m_IdleAni_Info;
	LPANI_INFO		m_MoveAni_Info;
	LPANI_INFO		m_AtckAni_Info;
	LPANI_INFO		m_DieAni_Info;
	LPANI_INFO		m_beHitAni_Info;
	LPANI_INFO		m_HitAni_Info;
};