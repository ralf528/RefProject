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


//< 초기화
bool cWarrior::init(void)
{
    //< 캐릭터 좌표
    m_pos.x = CHARACTER_START_POSITION_X;
    m_pos.y = CHARACTER_START_POSITION_Y;
    //< 이동 전 좌표
    m_prevPos = m_pos;
    //< 캐릭터 방향정보( 아래 보도록 )
    m_dir = DIR_D;
    //< 캐릭터 렉트
    setRect();

    //< 인벤토리 생성
    if (NULL == m_inventory)
    {
        m_inventory = new Inventory;
    }

    m_hpCount = 0;
    m_mpCount = 0;
    //< 캐릭터 스테이터스
    setMaxHP(CHARACTER_HP);
    setHP(CHARACTER_HP);
    setMaxMP(CHARACTER_MP);
    setMP(CHARACTER_MP);

    //< 신념, 종족, 직업
    setBelief(BELIEF_GID);
    setTribe(TRIBE_WOLF);
    setJob(JOB_KNIGHT);

    //< 힘,민,지
    setStrong(3);
    setAgility(3);
    setIntel(3);
    //< 현재 상태
    setCondition(CONDITION_NORMAL);

    //< 캐릭터 속도 설정
    setMoveSpeed(10.f);
    m_moveDeley.m_lastTime = GetTickCount();
    m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

    //< 대쉬 카운트
    dash_count = 0;

    //< 캐릭터 이미지
    RC_MGR->addImage(imgID_WARRIOR_IDLE, "Data/Resource/Image/character/warrior_idle.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_MOVE, "Data/Resource/Image/character/warrior_walk.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_ATK, "Data/Resource/Image/character/warrior_atk.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_DASH, "Data/Resource/Image/character/dash.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_DIE, "Data/Resource/Image/character/warrior_die.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_WARRIOR_BEHIT, "Data/Resource/Image/character/warrior-gethit.bmp", 0, 0, RM_TRANS);

    //< 공격 충돌체
    if (NULL == ball)
    {
        ball = new cProjectile(6, NORMAL_ATTACK_RANGE, 10, 0.3f);
    }
    //< 전체 스킬
    if (NULL == skill)
    {
        skill = new skillWhole();
    }
    //< 공격 딜레이
    attDeley.m_deley = attDeley.m_lastTime = 50;
    /*attDeley.m_deley = 60;
    attDeley.m_count = GetTickCount();*/
    wholeSkillDeley.m_deley = wholeSkillDeley.m_lastTime = 300;

    //< 무적스킬 딜레이
    m_inbeatDeley.m_deley = 10000;
    m_inbeatDeley.m_lastTime = 0;

    //< 공격중 아님
    m_isAttacking = false;

    //< 현재 레벨 저장
    m_levelFlag = getLevelInfo().getNowLevel();

    //< 애니메이션 설정
    InitAnimInfo();
    m_nowState = STATE_IDLE;

    return true;
}
//< 해제
void cWarrior::release(void)
{
    SAFE_DELETE(m_inventory);
    SAFE_DELETE(ball);
    SAFE_DELETE(skill);
    //< 애니메이션 삭제
    releaseAniInfo();
}
//< 갱신
void cWarrior::update(float fDeltaTime)
{
    if (m_conDeley.m_lastTime + m_conDeley.m_deley < GetTickCount())
    {
        setCondition(CONDITION_NORMAL);
    }

    //< 상태 초기화
    if (m_nowState == STATE_DIE)
    {
        AniMgr::UpdateAni(m_DieAni_Info);
        return;
    }
    m_nowState = STATE_IDLE;
    //< 체력 마력 자동 재생
    {
        if ((m_hpCount++ % 60) == 0)
        {
            if (getHP() < getMaxHP())
            {
                incHP(1);
            }
            //< 독상태 체력 깎임
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
    //< 레벨 확인
    int temp = getLevelInfo().getNowLevel();
    //< 레벨이 증가하면 스텟 랜덤 증가
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

    //< 캐릭터 무브
    move(fDeltaTime);

    //ProcessInputKey();

    //< 공격
    attack();
    
    //< 아이템
    useItem();

    dash();

    //< 애니메이션 갱신
    AniMgr::UpdateAni(m_IdleAni_Info);
    AniMgr::UpdateAni(m_MoveAni_Info);
    AniMgr::UpdateAni(m_AtckAni_Info);
    AniMgr::UpdateAni(m_HitEff_Info);
    AniMgr::UpdateAni(m_beHitAni_Info);
    AniMgr::UpdateAni(m_DashAni_Info);
}
//< 랜더
void cWarrior::render(HDC hdc)
{
    //< 죽었다면
    if (m_nowState == STATE_DIE)
    {
        AniMgr::Render(hdc, m_DieAni_Info, m_pos, m_dir, imgID_WARRIOR_DIE);
    }
    //< 피격 애니메이션
    else if (m_beHitAni_Info->flag == true)
    {
        AniMgr::Render(hdc, m_beHitAni_Info, m_pos, m_dir, imgID_WARRIOR_BEHIT);
    }
    //< 대쉬 애니메이션
    else if (m_DashAni_Info->flag == true)
    {
        AniMgr::Render(hdc, m_DashAni_Info, m_pos, 0, imgID_WARRIOR_DASH);
    }
    //< 공격중이면
    else if (m_AtckAni_Info->flag == true)
    {
        AniMgr::Render(hdc, m_AtckAni_Info, m_pos, m_dir, imgID_WARRIOR_ATK);
    }
    //< 이동 중이면
    else if (m_nowState == STATE_MOVE)
    {
        AniMgr::Render(hdc, m_MoveAni_Info, m_pos, m_dir, imgID_WARRIOR_MOVE);
    }
    //< 대기상태
    else
    {
        AniMgr::Render(hdc, m_IdleAni_Info, m_pos, m_dir, imgID_WARRIOR_IDLE);
    }
    //< 피격 이펙트
    if (m_HitEff_Info->flag == true)
    {
        AniMgr::Render(hdc, m_HitEff_Info, m_pos, 0, imgID_GETHIT_1);
    }

    //마법 구체 렌더
    ball->render(hdc);
    //< 스킬 랜더
    skill->render(hdc);

#ifdef _DEBUG
    //주위 타일
    MoveToEx(hdc, vertex[3].x - CAMERA->getX(), vertex[3].y - CAMERA->getY(), NULL);
    LineTo(hdc, vertex[4].x - CAMERA->getX(), vertex[4].y - CAMERA->getY());
    MoveToEx(hdc, vertex[2].x - CAMERA->getX(), vertex[2].y - CAMERA->getY(), NULL);
    LineTo(hdc, vertex[5].x - CAMERA->getX(), vertex[5].y - CAMERA->getY());
#endif
}
//< 하반신 랜더
void cWarrior::renderLower(HDC hdc)
{
    //RENDER_MGR->render( hdc, imgID_CHARACTER_LOWER, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
}

//< 공격
void cWarrior::attack(void)
{
    //< 공격 가능 상태
    if (m_AtckAni_Info->flag == false)
    {
        //< 공격중 아님
        m_isAttacking = false;
    }

    //충돌체 갱신
    ball->update();
    skill->update();
}

//< 타격
bool cWarrior::beHit(int damage)
{
    //< HP 감소 (무적상태가 아닐경우에만)
    if (getCondition() != CONDITION_INBEAT)
    {

        m_state.m_nowHP -= damage;
        //< 카메라 흔들리기
        if (damage > 10 && rand() % 3 == 0)
        {
            CAMERA->cameraShaking();
        }
        //피격 사운드
        //SOUND_MGR->soundPlay(CHAR_HIT);
        //< 피격 이펙트
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
            //사망 사운드
            //SOUND_MGR->soundPlay(CHAR_DIE);
            return true;
        }
    }

    //SOUND_MGR->soundPlay(CHAR_HIT);
    //< 죽었다면 true 리턴
    if (getHP() <= 0 && m_nowState != STATE_DIE)
    {
        //#ifdef _DEBUG
        //		setHP( 1 );
        //		return false;
        //#endif
        setHP(0);
        m_nowState = STATE_DIE;
        m_DieAni_Info->flag = true;
        //사망 사운드
        //SOUND_MGR->soundPlay(CHAR_DIE);
        return true;
    }

    return false;
}

//< 이동
void cWarrior::move(float fDeltaTime)
{
    //< 공격중이면 이동 불가
    if (m_AtckAni_Info->flag == true || m_DashAni_Info->flag == true)
    {
        return;
    }

    //<이전 위치 기억
    m_prevPos = m_pos;

    if (m_moveDeley.m_lastTime + m_moveDeley.m_deley < GetTickCount())
    {
        //< 이동속도
        float fMoveSpeed = getMoveSpeed() / fDeltaTime * 0.02f;

        //키입력 & 이동
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

            //< 대각선 처리
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

            //< 대각선 처리
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

    //< 이동중일때 애니메이션이 진행되지 않고 있으면 애니메이션 진행
    if (m_nowState == STATE_MOVE && m_MoveAni_Info->flag == false)
    {
        m_MoveAni_Info->flag = true;
    }
}

//< 대쉬
void cWarrior::dash(void)
{
    //< 대쉬 거리
    int m_dashDist = CHARACTER_DASH_DIST / 5;
    if (m_AtckAni_Info->flag == true)
    {
        //if (keyInput::isKeyDown(VK_SHIFT))
        m_dashDist *= -1;
    }

    //< 대쉬
    if (dash_count-- > 0)
    {
        //키입력 & 이동
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
    //어택 사운드 재생
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
    //공격 사운드
    //SOUND_MGR->soundPlay(SOUND_BGM4);
    ball->shoot(m_pos, destPos);

    //< 공격중
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
    //< 스킬 가능 상태
    if (wholeSkillDeley.m_deley <= wholeSkillDeley.m_lastTime++)
    {
        // 구체 이동
        if (getMP() >= 50)
        {
            incMP(-50);
            POINT pos = m_pos;
            //< 딜레이 카운트
            wholeSkillDeley.m_lastTime = 0;
            //공격 사운드
            //SOUND_MGR->soundPlay(SOUND_BGM4);
            //< 스킬 발동
            skill->shoot(m_pos, pos);
        }
    }
}

//< 데미지 얻기
int cWarrior::getDamage(void)
{
    return ball->getDamage() + getStrong();
}

//< 충돌체 얻기 ( 아이템 획득 )
void cWarrior::gainCollider(tileType &obj)
{
    //< 오브젝트에 따른 반응
    //< 아이템이면 인벤토리에 추가
    if (obj >= ITEM_FIRST && obj < ITEM_END)
    {
        //m_state.m_nowHP+=10;
        m_inventory->addItem(obj);
    }
    //< 그 외에는 충돌체크
    else
    {
        setPosToPrev();
    }
}

//< 렉트 설정
void cWarrior::setRect(void)
{
    SetRect(&m_rect,
        m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
        m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}

void cWarrior::InitAnimInfo(void)
{
    //< 아이들 애니메이션
    SAFE_DELETE(m_IdleAni_Info);
    m_IdleAni_Info = new ANI_INFO;
    SIZE idleAniSize = RC_MGR->findImage(imgID_WARRIOR_IDLE)->getSize();
    AniMgr::SetAnimInfo(m_IdleAni_Info, idleAniSize, 8, 8, 50, true, true, true);
    
    //< 이동 애니메이션
    SAFE_DELETE(m_MoveAni_Info);
    m_MoveAni_Info = new ANI_INFO;
    SIZE moveAniSize = RC_MGR->findImage(imgID_WARRIOR_MOVE)->getSize();
    AniMgr::SetAnimInfo(m_MoveAni_Info, moveAniSize, 8, 8, 50, false, false, true);

    //< 공격 애니메이션
    SAFE_DELETE(m_AtckAni_Info);
    m_AtckAni_Info = new ANI_INFO;
    SIZE atkAniSize = RC_MGR->findImage(imgID_WARRIOR_ATK)->getSize();
    AniMgr::SetAnimInfo(m_AtckAni_Info, atkAniSize, 18, 8, 20, false, false, true);

    //< 사망 애니메이션
    SAFE_DELETE(m_DieAni_Info);
    m_DieAni_Info = new ANI_INFO;
    SIZE dieAniSize = RC_MGR->findImage(imgID_WARRIOR_DIE)->getSize();
    AniMgr::SetAnimInfo(m_DieAni_Info, dieAniSize, 20, 8, 200, false, false, false);

    //< 피격 애니메이션
    SAFE_DELETE(m_beHitAni_Info);
    m_beHitAni_Info = new ANI_INFO;
    SIZE behitAniSize = RC_MGR->findImage(imgID_WARRIOR_BEHIT)->getSize();
    AniMgr::SetAnimInfo(m_beHitAni_Info, behitAniSize, 7, 8, 20, false, false, true);

    //< 타격 애니메이션
    SAFE_DELETE(m_HitEff_Info);
    m_HitEff_Info = new ANI_INFO;
    SIZE hitAniSize = RC_MGR->findImage(imgID_GETHIT_1)->getSize();
    AniMgr::SetAnimInfo(m_HitEff_Info, hitAniSize, 6, 1, 50, false, false, true);

    //< 대쉬 애니메이션
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