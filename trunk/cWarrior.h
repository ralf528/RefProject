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

	//< ��ų
    virtual void ProcessSkill(int nIndex) override;

	//< �뽬
	void UpdateDash();

	void Inbeatable();
    void DashTrigger();
    void ShootWholeSkill();

//< ��� ����
protected:
	//< ü�¸��� �ڵ���� ī��Ʈ
	int m_hpCount;
	int m_mpCount;

	//< ������� ������
	DELEY m_inbeatDeley;
};