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
    //< ĳ���� ��ǥ
    m_pos.x = CHARACTER_START_POSITION_X;
    m_pos.y = CHARACTER_START_POSITION_Y;
    //< �̵� �� ��ǥ
    m_prevPos = m_pos;
    //< ĳ���� ��������( �Ʒ� ������ )
    m_dir = DIR_D;
    //< ĳ���� ��Ʈ
    setRect();

    //< �κ��丮 ����
    if (NULL == m_inventory)
    {
        m_inventory = new Inventory;
    }

    m_hpCount = 0;
    m_mpCount = 0;
    //< ĳ���� �������ͽ�
    setMaxHP(CHARACTER_HP);
    setHP(CHARACTER_HP);
    setMaxMP(CHARACTER_MP);
    setMP(CHARACTER_MP);

    //< �ų�, ����, ����
    setBelief(BELIEF_GID);
    setTribe(TRIBE_WOLF);
    setJob(JOB_KNIGHT);

    //< ��,��,��
    setStrong(3);
    setAgility(3);
    setIntel(3);
    //< ���� ����
    setCondition(CONDITION_NORMAL);

    //< ĳ���� �ӵ� ����
    setMoveSpeed(10.f);
    m_moveDeley.m_lastTime = GetTickCount();
    m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

    //< �뽬 ī��Ʈ
    dash_count = 0;

    //< ĳ���� �̹���
    RC_MGR->addImage(imgID_WARRIOR_IDLE, "Data/Resource/Image/character/warrior_idle.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_MOVE, "Data/Resource/Image/character/warrior_walk.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_ATK, "Data/Resource/Image/character/warrior_atk.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_DASH, "Data/Resource/Image/character/dash.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_DIE, "Data/Resource/Image/character/warrior_die.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_BEHIT, "Data/Resource/Image/character/warrior-gethit.bmp", 0, 0, RM_TRANS);

    //< ���� �浹ü
    if (NULL == ball)
    {
        ball = new cProjectile(6, NORMAL_ATTACK_RANGE, 10, 0.3f);
    }
    //< ��ü ��ų
    if (NULL == skill)
    {
        skill = new skillWhole();
    }
    //< ���� ������
    attDeley.m_deley = attDeley.m_lastTime = 50;
    /*attDeley.m_deley = 60;
    attDeley.m_count = GetTickCount();*/
    wholeSkillDeley.m_deley = wholeSkillDeley.m_lastTime = 300;

    //< ������ų ������
    m_inbeatDeley.m_deley = 10000;
    m_inbeatDeley.m_lastTime = 0;

    //< ������ �ƴ�
    m_isAttacking = false;

    //< ���� ���� ����
    m_levelFlag = getLevelInfo().getNowLevel();

    //< �ִϸ��̼� ����
    InitAnimInfo();
    m_nowState = STATE_IDLE;

    return true;
}
//< ����
void cWarrior::release(void)
{
    SAFE_DELETE(m_inventory);
    SAFE_DELETE(ball);
    SAFE_DELETE(skill);
    //< �ִϸ��̼� ����
    releaseAniInfo();
}
//< ����
void cWarrior::update(float fDeltaTime)
{
    if (m_conDeley.m_lastTime + m_conDeley.m_deley < GetTickCount())
    {
        setCondition(CONDITION_NORMAL);
    }

    //< ���� �ʱ�ȭ
    if (m_nowState == STATE_DIE)
    {
        AniMgr::UpdateAni(m_DieAni_Info);
        return;
    }
    m_nowState = STATE_IDLE;
    //< ü�� ���� �ڵ� ���
    {
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
    }
    //< ���� Ȯ��
    int temp = getLevelInfo().getNowLevel();
    //< ������ �����ϸ� ���� ���� ����
    if (temp != m_levelFlag)
    {
        int stt = rand() % 6;
        switch (stt)
        {
        case 0: case 1: case 2: case 3:
            incStrong(1);
            break;
        case 4:
            incAgility(1);
            break;
        case 5:
            incIntel(1);
            break;
        }
        m_levelFlag = temp;
    }

    //< ĳ���� ����
    move(fDeltaTime);

    //ProcessInputKey();

    //< ����
    attack();
    
    //< ������
    useItem();

    dash();

    //< �ִϸ��̼� ����
    AniMgr::UpdateAni(m_IdleAni_Info);
    AniMgr::UpdateAni(m_MoveAni_Info);
    AniMgr::UpdateAni(m_AtckAni_Info);
    AniMgr::UpdateAni(m_HitEff_Info);
    AniMgr::UpdateAni(m_beHitAni_Info);
    AniMgr::UpdateAni(m_DashAni_Info);
}
//< ����
void cWarrior::render(HDC hdc)
{
    //< �׾��ٸ�
    if (m_nowState == STATE_DIE)
    {
        AniMgr::Render(hdc, m_DieAni_Info, m_pos, m_dir, imgID_WARRIOR_DIE);
    }
    //< �ǰ� �ִϸ��̼�
    else if (m_beHitAni_Info->flag == true)
    {
        AniMgr::Render(hdc, m_beHitAni_Info, m_pos, m_dir, imgID_WARRIOR_BEHIT);
    }
    //< �뽬 �ִϸ��̼�
    else if (m_DashAni_Info->flag == true)
    {
        AniMgr::Render(hdc, m_DashAni_Info, m_pos, 0, imgID_WARRIOR_DASH);
    }
    //< �������̸�
    else if (m_AtckAni_Info->flag == true)
    {
        AniMgr::Render(hdc, m_AtckAni_Info, m_pos, m_dir, imgID_WARRIOR_ATK);
    }
    //< �̵� ���̸�
    else if (m_nowState == STATE_MOVE)
    {
        AniMgr::Render(hdc, m_MoveAni_Info, m_pos, m_dir, imgID_WARRIOR_MOVE);
    }
    //< ������
    else
    {
        AniMgr::Render(hdc, m_IdleAni_Info, m_pos, m_dir, imgID_WARRIOR_IDLE);
    }
    //< �ǰ� ����Ʈ
    if (m_HitEff_Info->flag == true)
    {
        AniMgr::Render(hdc, m_HitEff_Info, m_pos, 0, imgID_GETHIT_1);
    }

    //���� ��ü ����
    ball->render(hdc);
    //< ��ų ����
    skill->render(hdc);

#ifdef _DEBUG
    //���� Ÿ��
    MoveToEx(hdc, vertex[3].x - CAMERA->getX(), vertex[3].y - CAMERA->getY(), NULL);
    LineTo(hdc, vertex[4].x - CAMERA->getX(), vertex[4].y - CAMERA->getY());
    MoveToEx(hdc, vertex[2].x - CAMERA->getX(), vertex[2].y - CAMERA->getY(), NULL);
    LineTo(hdc, vertex[5].x - CAMERA->getX(), vertex[5].y - CAMERA->getY());
#endif
}
//< �Ϲݽ� ����
void cWarrior::renderLower(HDC hdc)
{
    //RENDER_MGR->render( hdc, imgID_CHARACTER_LOWER, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
}

//< ����
void cWarrior::attack(void)
{
    //< ���� ���� ����
    if (m_AtckAni_Info->flag == false)
    {
        //< ������ �ƴ�
        m_isAttacking = false;
    }

    //�浹ü ����
    ball->update();
    skill->update();
}

//< Ÿ��
bool cWarrior::beHit(int damage)
{
    //< HP ���� (�������°� �ƴҰ�쿡��)
    if (getCondition() != CONDITION_INBEAT)
    {

        m_state.m_nowHP -= damage;
        //< ī�޶� ��鸮��
        if (damage > 10 && rand() % 3 == 0)
        {
            CAMERA->cameraShaking();
        }
        //�ǰ� ����
        //SOUND_MGR->soundPlay(CHAR_HIT);
        //< �ǰ� ����Ʈ
        if (rand() % 10 == 0)
        {
            m_HitEff_Info->flag = true;
        }
        m_beHitAni_Info->flag = true;

        LOG_MGR->addLog("m_state.m_nowHP : %d", m_state.m_nowHP);
        if (getHP() <= 0 && m_nowState != STATE_DIE)
        {
            LOG_MGR->addLog("PLAYER_DIE");
#ifdef _DEBUG
            setHP(1);
            return false;
#endif
            m_nowState = STATE_DIE;
            m_DieAni_Info->flag = true;
            //��� ����
            //SOUND_MGR->soundPlay(CHAR_DIE);
            return true;
        }
    }

    //SOUND_MGR->soundPlay(CHAR_HIT);
    //< �׾��ٸ� true ����
    if (getHP() <= 0 && m_nowState != STATE_DIE)
    {
        //#ifdef _DEBUG
        //		setHP( 1 );
        //		return false;
        //#endif
        setHP(0);
        m_nowState = STATE_DIE;
        m_DieAni_Info->flag = true;
        //��� ����
        //SOUND_MGR->soundPlay(CHAR_DIE);
        return true;
    }

    return false;
}

//< �̵�
void cWarrior::move(float fDeltaTime)
{
    //< �������̸� �̵� �Ұ�
    if (m_AtckAni_Info->flag == true || m_DashAni_Info->flag == true)
    {
        return;
    }

    //<���� ��ġ ���
    m_prevPos = m_pos;

    if (m_moveDeley.m_lastTime + m_moveDeley.m_deley < GetTickCount())
    {
        //< �̵��ӵ�
        float fMoveSpeed = getMoveSpeed() / fDeltaTime * 0.02f;

        //Ű�Է� & �̵�
        if (isKeyDown(VK_LEFT))
        {
            m_dir = DIR_L;
            m_pos.x -= static_cast<LONG>(fMoveSpeed*0.3f);
            CAMERA->moveCamera(static_cast<LONG>(-fMoveSpeed*0.3f), 0);
            m_nowState = STATE_MOVE;
        }
        if (isKeyDown(VK_RIGHT))
        {
            m_dir = DIR_R;
            m_pos.x += static_cast<LONG>(fMoveSpeed*0.3f);
            CAMERA->moveCamera(static_cast<LONG>(fMoveSpeed*0.3f), 0);
            m_nowState = STATE_MOVE;
        }
        if (isKeyDown(VK_UP))
        {
            m_dir = DIR_U;
            m_pos.y -= static_cast<LONG>(fMoveSpeed*0.2f);
            CAMERA->moveCamera(0, static_cast<LONG>(-fMoveSpeed*0.2f));
            m_nowState = STATE_MOVE;

            //< �밢�� ó��
            if (isKeyDown(VK_LEFT))
            {
                m_dir = DIR_LU;
            }
            else if (isKeyDown(VK_RIGHT))
            {
                m_dir = DIR_RU;
            }
        }
        if (isKeyDown(VK_DOWN))
        {

            m_dir = DIR_D;
            m_pos.y += static_cast<LONG>(fMoveSpeed*0.2f);
            CAMERA->moveCamera(0, static_cast<LONG>(fMoveSpeed*0.2f));
            m_nowState = STATE_MOVE;

            //< �밢�� ó��
            if (isKeyDown(VK_LEFT))
            {
                m_dir = DIR_LD;
            }
            else if (isKeyDown(VK_RIGHT))
            {
                m_dir = DIR_RD;
            }
        }
        m_moveDeley.m_lastTime = GetTickCount();
    }

    //< �̵����϶� �ִϸ��̼��� ������� �ʰ� ������ �ִϸ��̼� ����
    if (m_nowState == STATE_MOVE && m_MoveAni_Info->flag == false)
    {
        m_MoveAni_Info->flag = true;
    }
}

//< �뽬
void cWarrior::dash(void)
{
    //< �뽬 �Ÿ�
    int m_dashDist = CHARACTER_DASH_DIST / 5;
    if (m_AtckAni_Info->flag == true)
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

void cWarrior::AttackTrigger()
{
    if (m_isAttacking == true)
        return;

    m_nowState = STATE_ATTACK;
    m_AtckAni_Info->flag = true;

    POINT destPos = m_pos;
    int dist = 1000;
    //���� ���� ���
    //SOUND_MGR->soundPlay(CHAR_ATK);
    switch (m_dir)
    {
    case DIR_L:
        destPos.x = m_pos.x - dist;
        break;
    case DIR_LU:
        destPos.x = m_pos.x - dist;
        destPos.y = m_pos.y - dist;
        break;
    case DIR_U:
        destPos.y = m_pos.y - dist;
        break;
    case DIR_RU:
        destPos.x = m_pos.x + dist;
        destPos.y = m_pos.y - dist;
        break;
    case DIR_R:
        destPos.x = m_pos.x + dist;
        break;
    case DIR_RD:
        destPos.x = m_pos.x + dist;
        destPos.y = m_pos.y + dist;
        break;
    case DIR_D:
        destPos.y = m_pos.y + dist;
        break;
    case DIR_LD:
        destPos.x = m_pos.x - dist;
        destPos.y = m_pos.y + dist;
        break;
    }
    attDeley.m_lastTime = 0;
    //���� ����
    //SOUND_MGR->soundPlay(SOUND_BGM4);
    ball->shoot(m_pos, destPos);

    //< ������
    m_isAttacking = true;
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
        m_DashAni_Info->flag = true;
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

//< ������ ���
int cWarrior::getDamage(void)
{
    return ball->getDamage() + getStrong();
}

//< �浹ü ��� ( ������ ȹ�� )
void cWarrior::gainCollider(tileType &obj)
{
    //< ������Ʈ�� ���� ����
    //< �������̸� �κ��丮�� �߰�
    if (obj >= ITEM_FIRST && obj < ITEM_END)
    {
        //m_state.m_nowHP+=10;
        m_inventory->addItem(obj);
    }
    //< �� �ܿ��� �浹üũ
    else
    {
        setPosToPrev();
    }
}

//< ��Ʈ ����
void cWarrior::setRect(void)
{
    SetRect(&m_rect,
        m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
        m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}

void cWarrior::InitAnimInfo(void)
{
    //< ���̵� �ִϸ��̼�
    SAFE_DELETE(m_IdleAni_Info);
    m_IdleAni_Info = new ANI_INFO;
    SIZE idleAniSize = RC_MGR->findImage(imgID_WARRIOR_IDLE)->getSize();
    AniMgr::SetAnimInfo(m_IdleAni_Info, idleAniSize, 8, 8, 50, true, true, true);
    
    //< �̵� �ִϸ��̼�
    SAFE_DELETE(m_MoveAni_Info);
    m_MoveAni_Info = new ANI_INFO;
    SIZE moveAniSize = RC_MGR->findImage(imgID_WARRIOR_MOVE)->getSize();
    AniMgr::SetAnimInfo(m_MoveAni_Info, moveAniSize, 8, 8, 50, false, false, true);

    //< ���� �ִϸ��̼�
    SAFE_DELETE(m_AtckAni_Info);
    m_AtckAni_Info = new ANI_INFO;
    SIZE atkAniSize = RC_MGR->findImage(imgID_WARRIOR_ATK)->getSize();
    AniMgr::SetAnimInfo(m_AtckAni_Info, atkAniSize, 18, 8, 20, false, false, true);

    //< ��� �ִϸ��̼�
    SAFE_DELETE(m_DieAni_Info);
    m_DieAni_Info = new ANI_INFO;
    SIZE dieAniSize = RC_MGR->findImage(imgID_WARRIOR_DIE)->getSize();
    AniMgr::SetAnimInfo(m_DieAni_Info, dieAniSize, 20, 8, 200, false, false, false);

    //< �ǰ� �ִϸ��̼�
    SAFE_DELETE(m_beHitAni_Info);
    m_beHitAni_Info = new ANI_INFO;
    SIZE behitAniSize = RC_MGR->findImage(imgID_WARRIOR_BEHIT)->getSize();
    AniMgr::SetAnimInfo(m_beHitAni_Info, behitAniSize, 7, 8, 20, false, false, true);

    //< Ÿ�� �ִϸ��̼�
    SAFE_DELETE(m_HitEff_Info);
    m_HitEff_Info = new ANI_INFO;
    SIZE hitAniSize = RC_MGR->findImage(imgID_GETHIT_1)->getSize();
    AniMgr::SetAnimInfo(m_HitEff_Info, hitAniSize, 6, 1, 50, false, false, true);

    //< �뽬 �ִϸ��̼�
    SAFE_DELETE(m_DashAni_Info);
    m_DashAni_Info = new ANI_INFO;
    SIZE dashAniSize = RC_MGR->findImage(imgID_WARRIOR_DASH)->getSize();
    AniMgr::SetAnimInfo(m_DashAni_Info, dashAniSize, 5, 1, 40, false, false, true);
}

void cWarrior::releaseAniInfo(void)
{
    SAFE_DELETE(m_IdleAni_Info);
    SAFE_DELETE(m_MoveAni_Info);
    SAFE_DELETE(m_AtckAni_Info);
    SAFE_DELETE(m_DieAni_Info);
    SAFE_DELETE(m_HitEff_Info);
    SAFE_DELETE(m_beHitAni_Info);
    SAFE_DELETE(m_DashAni_Info);
}