#pragma once

#include "character.h"

//< ���� ĳ���� Ŭ����
class cWarrior : public character
{
//< ������ �Ҹ���
public:
	cWarrior();
	~cWarrior();

//< �������̽�
public:
	//< �ʱ�ȭ
	virtual bool init();
	//< ����
	virtual void release();
	//< ����
	virtual void update(float fDeltaTime);
	//< ����
	virtual void render(HDC hdc);
	//< �Ϲݽ� ����
	void renderLower(HDC hdc);

	//< ����
	virtual void attack();
	//< Ÿ��
	virtual bool beHit(int damage);
	//< �̵�
	virtual void move(float fDeltaTime);
	//< �뽬
	virtual void dash();

	//< ������ ���
	virtual int getDamage();

	//< �浹ü(������ ��) ���
	virtual void gainCollider( tileType &obj );
	//< ��Ʈ ����
	void setRect();

	//�ִϸ��̼� ����
	void InitAnimInfo();
	//����
	void releaseAniInfo();

    virtual void ProcessSkill(int nIndex);

    void AttackTrigger();
    void Inbeatable();
    void DashTrigger();
    void ShootWholeSkill();

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
	LPANI_INFO		m_HitEff_Info;
	LPANI_INFO		m_DashAni_Info;
    //std::map<int, LPANI_INFO> m_Animations;

	//< ������� ������
	DELEY m_inbeatDeley;
};