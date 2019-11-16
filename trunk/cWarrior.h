#pragma once

#include "character.h"

//< ���� ĳ���� Ŭ����
class cWarrior : public character
{
//< ������ �Ҹ���
public:
	cWarrior(void);
	~cWarrior(void);

//< �������̽�
public:
	//< �ʱ�ȭ
	virtual bool init(void);
	//< ����
	virtual void release(void);
	//< ����
	virtual void update(void);
	//< ����
	virtual void render(HDC hdc);
	//< �Ϲݽ� ����
	void renderLower(HDC hdc);

	//< ����
	virtual void attack( void );
	//< Ÿ��
	virtual bool beHit(int damage);
	//< �̵�
	virtual void move( void );
	//< �뽬
	virtual void dash( void );

	//< ������ ���
	virtual int getDamage(void);

	//< Ŀ�ؼ� �ε��� ����, ���
	//virtual inline void setConnectionIndex(int index)	 { m_connectionIndex = index; }
	//virtual inline int getConnectionIndex(void)			 { return m_connectionIndex; }

	//< �浹ü(������ ��) ���
	virtual void gainCollider( tileType &obj );
	//< ��Ʈ ����
	void setRect( void );

	//�ִϸ��̼� ����
	void setAniInfo(void);
	//����
	void updateAni( LPANI_INFO aniInfo );
	//����
	void releaseAniInfo( void );

	//< �������
	void inbeatable( void );

//< ��� ����
protected:
	//< ü�¸��� �ڵ���� ī��Ʈ
	int m_hpCount;
	int m_mpCount;

	//< ���� ����
	int m_levelFlag;

	//< ���� ���� ����
	int m_nowState;

	//< �ִϸ��̼� ����
	LPANI_INFO		m_IdleAni_Info;
	LPANI_INFO		m_MoveAni_Info;
	LPANI_INFO		m_AtckAni_Info;
	LPANI_INFO		m_DieAni_Info;
	LPANI_INFO		m_beHitAni_Info;
	LPANI_INFO		m_HitAni_Info;
	LPANI_INFO		m_DashAni_Info;

	//< ������� ������
	DELEY m_inbeatDeley;
};