#include "stdafx.h"
#include "skillWhole.h"
#include "inventory.h"
#include "character.h"

using namespace keyInput;

character::character(void)
	: ball(NULL), skill(NULL), m_inventory(NULL)
{
}
character::~character(void)
{
	release();
}


//< 초기화
bool character::init(void)
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

	//< 캐릭터 스테이터스
	setMaxHP( CHARACTER_HP );
	setHP( CHARACTER_HP );
	setMaxMP( CHARACTER_MP );
	setMP( CHARACTER_MP );

	//< 신념, 종족, 직업
	setBelief(BELIEF_GID);
	setTribe(TRIBE_WOLF);
	setJob(JOB_KNIGHT);

	//< 힘,민,지
	setStrong(3);
	setAgility(3);
	setIntel(3);
	
	setCondition(CONDITION_NORMAL);

	//< 캐릭터 속도 설정
	setMoveSpeed(10.f); //2

	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< 대쉬 카운트
	dash_count = 0;

	//< 인벤토리 생성
	if (NULL == m_inventory)
	{
		m_inventory = new Inventory;
	}

	//< 공격 충돌체
	if( NULL == ball )
	{
		//ball = new cProjectile(6, NORMAL_ATTACK_RANGE);
		ball = new cProjectile(6, NORMAL_ATTACK_RANGE, 10, 0.3f);
	}

	//< 전체 스킬
	if( NULL == skill )
	{
		skill = new skillWhole();
	}

	//< 공격 딜레이
	attDeley.m_deley = attDeley.m_lastTime = 50; //30;

	//< 공격중 아님
	m_isAttacking = false;

	//< 컨디션 딜레이
	m_conDeley.m_deley = 0;
	m_conDeley.m_lastTime = 0;

	//< 현재 레벨 저장
	m_PrefLevel = getLevelInfo().getNowLevel();

	//< 애니메이션 설정
	InitAnimInfo();
	m_nowState = STATE_IDLE;

	return true;
}

//< 해제
void character::release(void)
{
	SAFE_DELETE( m_inventory );
	SAFE_DELETE( ball );
	SAFE_DELETE( skill );
}

void character::update(float fDeltaTime)
{
	if (m_conDeley.m_lastTime + m_conDeley.m_deley < GetTickCount())
	{
		setCondition(CONDITION_NORMAL);
	}

	if (m_nowState == STATE_DIE)
	{
		auto found = m_Animations.find(imgID_WARRIOR_DIE);
		if (found != m_Animations.end())
		{
			AniMgr::UpdateAni(found->second);
		}

		return;
	}

	m_nowState = STATE_IDLE;

	//< 레벨 확인
	int curLevel = getLevelInfo().getNowLevel();
	//< 레벨이 증가하면 스텟 랜덤 증가
	if (curLevel != m_PrefLevel)
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
		m_PrefLevel = curLevel;
	}

	//< 캐릭터 무브
	move(fDeltaTime);

	//ProcessInputKey();

	//< 공격
	attack();

	//< 아이템
	useItem();

	//< 애니메이션 갱신
	for (auto each : m_Animations)
	{
		if (each.first == imgID_WARRIOR_DIE)
		{
			continue;
		}

		AniMgr::UpdateAni(each.second);
	}
}

//< 랜더
void character::render(HDC hdc)
{
	//< 죽었다면
	if (m_nowState == STATE_DIE)
	{
		RenderAnimation(hdc, imgID_WARRIOR_DIE);
	}
	//< 피격 애니메이션
	else if (IsPlayingAnimation(imgID_WARRIOR_BEHIT))
	{
		RenderAnimation(hdc, imgID_WARRIOR_BEHIT);
	}
	//< 대쉬 애니메이션
	else if (IsPlayingAnimation(imgID_WARRIOR_DASH))
	{
		RenderAnimation(hdc, imgID_WARRIOR_DASH);
	}
	//< 공격중이면
	else if (IsPlayingAnimation(imgID_WARRIOR_ATK))
	{
		RenderAnimation(hdc, imgID_WARRIOR_ATK);
	}
	//< 이동 중이면
	else if (m_nowState == STATE_MOVE)
	{
		RenderAnimation(hdc, imgID_WARRIOR_MOVE);
	}
	//< 대기상태
	else
	{
		RenderAnimation(hdc, imgID_WARRIOR_IDLE);
	}

	//< 피격 이펙트
	if (IsPlayingAnimation(imgID_GETHIT_1))
	{
		RenderAnimation(hdc, imgID_GETHIT_1);
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
void character::renderLower(HDC hdc)
{
	//RENDER_MGR->render( hdc, imgID_CHARACTER_LOWER, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
}

//< 공격
void character::attack(void)
{
	//< 공격 가능 상태
	if (IsPlayingAnimation(imgID_WARRIOR_ATK) == false)
	{
		//< 공격중 아님
		m_isAttacking = false;
	}

	//충돌체 갱신
	ball->update();
	skill->update();
}

//< 타격
bool character::beHit(int damage)
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
			StartAnimation(imgID_GETHIT_1);
		}
		StartAnimation(imgID_WARRIOR_BEHIT);

		LOG_MGR->addLog("m_state.m_nowHP : %d", m_state.m_nowHP);
		if (getHP() <= 0 && m_nowState != STATE_DIE)
		{
			LOG_MGR->addLog("PLAYER_DIE");
#ifdef _DEBUG
			setHP(1);
			return false;
#endif
			m_nowState = STATE_DIE;
			StartAnimation(imgID_WARRIOR_DIE);
			//사망 사운드
			//SOUND_MGR->soundPlay(CHAR_DIE);
			return true;
		}
	}

	//SOUND_MGR->soundPlay(CHAR_HIT);
	//< 죽었다면 true 리턴
	if (getHP() <= 0 && m_nowState != STATE_DIE)
	{
#ifdef _DEBUG
		setHP(1);
		return false;
#endif
		setHP(0);
		m_nowState = STATE_DIE;
		StartAnimation(imgID_WARRIOR_DIE);
		//사망 사운드
		//SOUND_MGR->soundPlay(CHAR_DIE);
		return true;
	}

	return false;
}

//< 이동
void character::move(float fDeltaTime)
{
	//< 공격중이면 이동 불가
	if (IsPlayingAnimation(imgID_WARRIOR_ATK) == true || IsPlayingAnimation(imgID_WARRIOR_DASH) == true)
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
			CAMERA->moveCamera(static_cast<LONG>(-fMoveSpeed * 0.3f), 0);
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
			CAMERA->moveCamera(0, static_cast<LONG>(-fMoveSpeed * 0.2f));
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

	if (m_nowState == STATE_MOVE && IsPlayingAnimation(imgID_WARRIOR_MOVE) == false)
	{
		StartAnimation(imgID_WARRIOR_MOVE);
	}
}

void character::InitAnimInfo(void)
{
	releaseAniInfo();

	//< 캐릭터 이미지
	RC_MGR->addImage(imgID_WARRIOR_IDLE, "Data/Resource/Image/character/warrior_idle.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_MOVE, "Data/Resource/Image/character/warrior_walk.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_ATK, "Data/Resource/Image/character/warrior_atk.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_DASH, "Data/Resource/Image/character/dash.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_DIE, "Data/Resource/Image/character/warrior_die.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_BEHIT, "Data/Resource/Image/character/warrior-gethit.bmp", 0, 0, RM_TRANS);

	//< 아이들 애니메이션
	LPANI_INFO IdleAni_Info = new ANI_INFO;
	SIZE idleAniSize = RC_MGR->findImage(imgID_WARRIOR_IDLE)->getSize();
	AniMgr::SetAnimInfo(IdleAni_Info, idleAniSize, 8, 8, 50, true, true, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_IDLE, IdleAni_Info));

	//< 이동 애니메이션
	LPANI_INFO MoveAni_Info = new ANI_INFO;
	SIZE moveAniSize = RC_MGR->findImage(imgID_WARRIOR_MOVE)->getSize();
	AniMgr::SetAnimInfo(MoveAni_Info, moveAniSize, 8, 8, 50, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_MOVE, MoveAni_Info));

	//< 공격 애니메이션
	LPANI_INFO AtckAni_Info = new ANI_INFO;
	SIZE atkAniSize = RC_MGR->findImage(imgID_WARRIOR_ATK)->getSize();
	AniMgr::SetAnimInfo(AtckAni_Info, atkAniSize, 18, 8, 20, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_ATK, AtckAni_Info));

	//< 사망 애니메이션
	LPANI_INFO DieAni_Info = new ANI_INFO;
	SIZE dieAniSize = RC_MGR->findImage(imgID_WARRIOR_DIE)->getSize();
	AniMgr::SetAnimInfo(DieAni_Info, dieAniSize, 20, 8, 200, false, false, false);
	m_Animations.insert(make_pair(imgID_WARRIOR_DIE, DieAni_Info));

	//< 피격 애니메이션
	LPANI_INFO beHitAni_Info = new ANI_INFO;
	SIZE behitAniSize = RC_MGR->findImage(imgID_WARRIOR_BEHIT)->getSize();
	AniMgr::SetAnimInfo(beHitAni_Info, behitAniSize, 7, 8, 20, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_BEHIT, beHitAni_Info));

	//< 타격 애니메이션
	LPANI_INFO HitEff_Info = new ANI_INFO;
	SIZE hitAniSize = RC_MGR->findImage(imgID_GETHIT_1)->getSize();
	AniMgr::SetAnimInfo(HitEff_Info, hitAniSize, 6, 1, 50, false, false, true);
	m_Animations.insert(make_pair(imgID_GETHIT_1, HitEff_Info));

	//< 대쉬 애니메이션
	LPANI_INFO DashAni_Info = new ANI_INFO;
	SIZE dashAniSize = RC_MGR->findImage(imgID_WARRIOR_DASH)->getSize();
	AniMgr::SetAnimInfo(DashAni_Info, dashAniSize, 5, 1, 40, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_DASH, DashAni_Info));
}

void character::releaseAniInfo(void)
{
	for (auto each : m_Animations)
	{
		SAFE_DELETE(each.second);
	}
	m_Animations.clear();
}

void character::RenderAnimation(HDC hdc, imgID animation)
{
	auto found = m_Animations.find(animation);
	if (found != m_Animations.end())
	{
		switch (animation)
		{
		case imgID_WARRIOR_DASH:
		case imgID_GETHIT_1:
			AniMgr::Render(hdc, found->second, m_pos, 0, animation);
		default:
			AniMgr::Render(hdc, found->second, m_pos, m_dir, animation);
			break;
		}
	}
}

void character::StartAnimation(imgID animation)
{
	auto found = m_Animations.find(animation);
	if (found == m_Animations.end())
	{
		return;
	}

	found->second->flag = true;
}

bool character::IsPlayingAnimation(imgID animation)
{
	auto found = m_Animations.find(animation);
	if (found == m_Animations.end())
	{
		return false;
	}

	return found->second->flag;
}

//< 아이템 사용
void character::useItem( void )
{
	int useIndex = 0;
	if( onceKeyDown( '1' ) )	{		useIndex = 1;	}
	if( onceKeyDown( '2' ) )	{		useIndex = 2;	}
	if( onceKeyDown( '3' ) )	{		useIndex = 3;	}
	if( onceKeyDown( '4' ) )	{		useIndex = 4;	}
	//< 키가 눌리면 아이템 사용
	if( 0 != useIndex )
	{
		//< 해당 인덱스의 아이템 ID
        unsigned int itemID = m_inventory->useItem(useIndex);
		//< 아이템이 있다면 사용
		if( ITEM_END != itemID )
		{
			//<혼돈이면 랜덤 발동
			if( ITEM_POTION_VENOM == itemID)
			{
				itemID = ITEM_FIRST + rand()%(ITEM_END-ITEM_FIRST);
			}
			switch( itemID )
			{
			case ITEM_POTION_CONFUSION:	//< 치유
				//SOUND_MGR->soundPlay(SOUND_BGM9); //< 아이템이 있으면 효과음
				//< 체력 증가
				incHP( 20 );
				if( getHP() > getMaxHP() )
				{
					setHP( getMaxHP() );
				}
				//< 상태이상 치유
				m_state.m_condition = CONDITION_NORMAL;
				break;
			case ITEM_POSION_CURE:	//< 재생
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				//< 체력 증가
				incHP( 60 );
				if( getHP() > getMaxHP() )
				{
					setHP( getMaxHP() );
				}
				break;
			case ITEM_POTION_IDENTFY:	//< 독
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				//< 독 상태
				m_state.m_condition = CONDITION_POISON;
				m_conDeley.m_deley = 6000;
				m_conDeley.m_lastTime = GetTickCount();
				break;
			case ITEM_POTION_REGEN: //< 약화
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				m_state.m_str -= 3;
				if( getStrong() < 0 ) m_state.m_str = 1;
				m_state.m_agl -= 3;
				if( getAgility() < 0 ) m_state.m_agl = 1;
				m_state.m_int -= 3;
				if( getIntel() < 0 ) m_state.m_int = 1;
				break;
			case ITEM_POTION_UNKNOWN: //< 강화
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				m_state.m_str += 3;
				m_state.m_agl += 3;
				m_state.m_int += 3;
				break;
			}
		}
	}
}

//< 인벤토리 랜더
void character::renderInven(HDC hdc)
{
	//< 인벤토리 랜더
	m_inventory->renderInven(hdc);
}

//< 좌표 설정
void character::setPos( POINT &pos )
{
	m_pos = pos;
	//렉트 이동
	setRect();

	//< 카메라 위치 설정
	CAMERA->setPosition( m_pos.x - SCREEN_X/2 + CHARACTER_SIZE_X,
						m_pos.y - SCREEN_Y/2 + CHARACTER_SIZE_Y );
}
void character::setPos( LONG x, LONG y )
{
	m_pos.x = x;
	m_pos.y = y;
	//렉트 이동
	setRect();

	//< 카메라 위치 설정
	CAMERA->setPosition( m_pos.x - WINSIZE_X/2 + CHARACTER_SIZE_X,
						m_pos.y - WINSIZE_Y/2 + CHARACTER_SIZE_Y );
}

//< 이전 위치로 되돌리기
void character::setPosToPrev(void)
{
	CAMERA->moveCamera( m_prevPos.x - m_pos.x , m_prevPos.y - m_pos.y );
	m_pos = m_prevPos;	
}

//< 렉트 설정
void character::setRect( void )
{
	SetRect(&m_rect, 
		m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
		m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}

//< 공격 충돌체 렉트 반환
RECT character::getBallRect(void)	
{
	return ball->getRect();	
}

//< 스킬 렉트 반환
RECT character::getSkillRect(void)
{
	return skill->getRect();
}

int character::getDamage(void)
{
	return (ball->getDamage() + getStrong());
}

//< 충돌체 얻기 ( 아이템 획득 )
void character::gainCollider(E_TileBrush &obj)
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

//< 충돌체 상태
void character::setBallFlag( bool flag )
{
	ball->setFlag( flag );
}
bool character::getBallFlag( void )	
{
	return ball->getFlag();
}

//< 마법 충돌체 상태
void character::setSkillBallFlag( bool flag )	
{
	skill->setFlag( flag );	
}
bool character::getSkillBallFlag( void )	
{	
	return skill->getFlag();
}

void character::ProcessSkill(int nIndex)
{
	switch (nIndex)
	{
	case 0:
		AttackTrigger();
		break;
	}
}

void character::AttackTrigger()
{
	if (m_isAttacking == true)
		return;

	m_nowState = STATE_ATTACK;
	StartAnimation(imgID_WARRIOR_ATK);

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