#pragma once

#include "unit.h"
#include "level.h"

//< ���� �浹ü
class sphereObject;
class skillWhole;
//< �κ��丮
class Inventory;

//< ���� ĳ���� Ŭ����
class character : public Unit
{
//< ������ �Ҹ���
public:
	character(void);
	~character(void);

//< �������̽�
public:
	//< �ʱ�ȭ
	virtual bool init(void) = 0;
	//< ����
	virtual void release(void) = 0;
	//< ����
	virtual void update(void) = 0;
	//< ����
	virtual void render(HDC hdc) = 0;

	//< ����
	virtual void attack( void ) = 0;
	//< Ÿ��
	virtual bool beHit(int damage) = 0;
	//< �̵�
	virtual void move( void ) = 0;
	//< �뽬
	virtual void dash( void ) = 0;

	//< �浹ü(������ ��) ���
	virtual void gainCollider( tileType &obj );
	//< ������ ���
	virtual void useItem( void );
	//< �κ��丮 ����
	virtual void renderInven(HDC hdc);
	//< ����ġ ȹ��
	void gainExp( unsigned int exp ){ m_level.incExp( exp ); }
	//< ���� ���� ���
	Level& getLevelInfo(void) { return m_level; }

	//< ��ǥ ����
	virtual void setPos( POINT &pos );
	virtual void setPos( LONG x, LONG y );
	//< ���� ��ġ�� �ǵ�����
	virtual void setPosToPrev(void);

	//< ��Ʈ ����
	virtual void setRect(void);

	//< Ŀ�ؼ� �ε��� ����, ���
	inline void setConnectionIndex(int index) 	 { m_connectionIndex = index; }
	inline int getConnectionIndex(void) 		 { return m_connectionIndex; }

	//< ���� �浹ü ��Ʈ ��ȯ
	RECT getBallRect(void);
	//< ��ų ��Ʈ ��ȯ
	RECT getSkillRect(void);

	//< ������ ���
	virtual int getDamage(void) { return getStrong(); };

	//< �浹ü ����
	void setBallFlag( bool flag );
	bool getBallFlag( void );

	//< ���� �浹ü ����
	void setSkillBallFlag( bool flag );
	bool getSkillBallFlag( void );

	//< ��Ʈ ���
	RECT getRect(void) { return m_rect; }
	
	//< ������ �� ����
	POINT *getAroundVertex(void) { return vertex; }

	//< skill ���
	inline skillWhole *getSkill(void) { return skill; }
	//< ������ ���
	virtual inline bool isAttack(void) { return m_isAttacking; }

	//< ��Ҵ��� �÷���
	inline bool getIsLive(void){ return m_isLive; }

	//< ���� ������ ��
	void setStateDelay(unsigned int deley) { m_conDeley.m_deley = deley; }
	void setDelayTick(void) { m_conDeley.m_lastTime = GetTickCount(); }

//< ��� ����
protected:
	//< ��Ҵ���
	bool m_isLive;
	//< ���� ����
	Level m_level;
	//< �̵� �� ��ǥ
	POINT m_prevPos;
	//< ĳ���� ��Ʈ
	RECT m_rect;
	
	//< �κ��丮
	Inventory *m_inventory;

	//< ������ �� ����
	POINT vertex[8];

	//< ���� �浹ü
	sphereObject *ball;
	//< ��ų �浹ü
	skillWhole *skill;

	//< �̵� ������
	DELEY m_moveDeley;
	
	//< ���� ������
	DELEY m_conDeley;

	//< ���� ������
	DELEY attDeley;
	//< ��ü ���� ������
	DELEY wholeSkillDeley;
	//< �뽬
	unsigned int dash_count;

	//< ��Ʈ��ũ Ŀ�ؼ� �ε��� ��ȣ
	int m_connectionIndex;
	//< ������
	bool m_isAttacking;
};