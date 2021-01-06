#include "stdafx.h"
#include "cProjectile.h"
#include "skillWhole.h"
#include "inventory.h"
#include "cWarrior.h"

using namespace keyInput;

cWarrior::cWarrior(void)
{
}
cWarrior::~cWarrior(void)
{
    release();
}


//< �ʱ�ȭ
bool cWarrior::init(void)
{
	character::init();

    m_hpCount = 0;
    m_mpCount = 0;

    //< ������ų ������
    m_inbeatDeley.m_deley = 10000;
    m_inbeatDeley.m_lastTime = 0;

    return true;
}

//< ����
void cWarrior::release(void)
{
	character::release();

    //< �ִϸ��̼� ����
    releaseAniInfo();
}

//< ����
void cWarrior::update(float fDeltaTime)
{
	character::update(fDeltaTime);

    //< ü�� ���� �ڵ� ���
	if ((m_hpCount++ % 60) == 0)
	{
		if (getHP() < getMaxHP())
		{
			incHP(1);
		}
		//< ������ ü�� ����
		if (getCondition() == CONDITION_POISON)
		{
			incHP(-5);
		}
	}
	if ((m_mpCount++ % 60) == 0)
	{
		if (getMP() < getMaxMP() - 1)
		{
			incMP(2);
		}
	}

    UpdateDash();
}

//< �뽬
void cWarrior::UpdateDash(void)
{
    //< �뽬 �Ÿ�
    int m_dashDist = CHARACTER_DASH_DIST / 5;
    if (IsPlayingAnimation(imgID_WARRIOR_ATK) == true)
    {
        //if (keyInput::isKeyDown(VK_SHIFT))
        m_dashDist *= -1;
    }

    //< �뽬
    if (dash_count-- > 0)
    {
        //Ű�Է� & �̵�
        if (m_dir == DIR_L || m_dir == DIR_LU || m_dir == DIR_LD)
        {
            m_pos.x -= m_dashDist * 2;
            CAMERA->moveCamera(-m_dashDist * 2, 0);
        }
        if (m_dir == DIR_R || m_dir == DIR_RU || m_dir == DIR_RD)
        {
            m_pos.x += m_dashDist * 2;
            CAMERA->moveCamera(m_dashDist * 2, 0);
        }
        if (m_dir == DIR_U || m_dir == DIR_LU || m_dir == DIR_RU)
        {
            m_pos.y -= m_dashDist;
            CAMERA->moveCamera(0, -m_dashDist);
        }
        if (m_dir == DIR_D || m_dir == DIR_LD || m_dir == DIR_RD)
        {
            m_pos.y += m_dashDist;
            CAMERA->moveCamera(0, m_dashDist);
        }
    }
    else
    {
        dash_count = 0;
    }
}

void cWarrior::ProcessSkill(int nIndex)
{
    switch (nIndex)
    {
    case 0:
        AttackTrigger();
        break;
    case 1:
        DashTrigger();
        break;
    case 2:
        ShootWholeSkill();
        break;
    case 3:
        Inbeatable();
        break;
    }
}

void cWarrior::Inbeatable(void)
{
    if (m_inbeatDeley.m_lastTime + m_inbeatDeley.m_deley < GetTickCount() && getMP() >= 10)
    {
        incMP(-10);
        setCondition(CONDITION_INBEAT);
        m_conDeley.m_deley = 300;
        m_conDeley.m_lastTime = GetTickCount();
        m_inbeatDeley.m_lastTime = GetTickCount();
    }
}

void cWarrior::DashTrigger()
{
    if (getMP() >= 5)
    {
#ifdef __RELEASE
        incMP(-5);
#endif
        dash_count = 5;
		StartAnimation(imgID_WARRIOR_DASH);
    }
}

void cWarrior::ShootWholeSkill()
{
    //< ��ų ���� ����
    if (wholeSkillDeley.m_deley <= wholeSkillDeley.m_lastTime++)
    {
        // ��ü �̵�
        if (getMP() >= 50)
        {
            incMP(-50);
            POINT pos = m_pos;
            //< ������ ī��Ʈ
            wholeSkillDeley.m_lastTime = 0;
            //���� ����
            //SOUND_MGR->soundPlay(SOUND_BGM4);
            //< ��ų �ߵ�
            skill->shoot(m_pos, pos);
        }
    }
}
