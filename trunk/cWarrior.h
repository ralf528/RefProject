#pragma once

#include "character.h"

//< ���� ĳ���� Ŭ����
class cWarrior : public character
{
public:
	cWarrior(void);
	virtual ~cWarrior(void);

public:
	//< �ʱ�ȭ
	virtual bool init() override;
	//< ����
	virtual void release() override;
	//< ����
	virtual void update(float fDeltaTime) override;
	//< ����
	virtual void render(HDC hdc) override;
	//< �Ϲݽ� ����
	void renderLower(HDC hdc);

	//< ����
	virtual void attack() override;
	//< Ÿ��
	virtual bool beHit(int damage) override;
	//< �̵�
	virtual void move(float fDeltaTime) override;
	//< �뽬
	virtual void dash() override;

	//< ������ ���
	virtual int getDamage();

	//�ִϸ��̼� ����
	void InitAnimInfo();
	//����
	void releaseAniInfo();

	void RenderAnimation(HDC hdc, imgID animation);
	void StartAnimation(imgID animation);
	bool IsPlayingAnimation(imgID animation);

    virtual void ProcessSkill(int nIndex) override;

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
	int m_PrefLevel;

	//< ���� ���� ����
	int m_nowState;

    //< �ִϸ��̼� ����
    std::map<imgID, LPANI_INFO> m_Animations;

	//< ������� ������
	DELEY m_inbeatDeley;
};