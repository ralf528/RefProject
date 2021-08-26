#include "stdafx.h"
#include "skillWhole.h"
#include "Sources/Template/TableManager.h"
#include "ScenePlayGame.h"
#include "PlayerController.h"
#include "character.h"

using namespace keyInput;

character::character(void)
	: SkillProjectile(NULL)
{
	m_JobType = JOB_ARCHER;

	static int CreatedObjectID = 0;
	ObjectID = ++CreatedObjectID;
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

	m_nowState = STATE_IDLE;

	const CharacterTemplate* Template = TABLE_MGR->GetCharacterTemplate(m_JobType);
	if (Template == nullptr)
	{
		return false;
	}

	m_Skills.clear();
	for (auto Each : Template->m_SkillDatas)
	{
		SkillTemplate& Template = Each.second;
		m_Skills.push_back(Each.first);
	}

	//< 캐릭터 스테이터스
	setMaxHP(EStatus_Base, CHARACTER_HP);
	setHP( CHARACTER_HP );
	setMaxMP(EStatus_Base, CHARACTER_MP);
	setMP( CHARACTER_MP );

	//< 신념, 종족, 직업
	setBelief(BELIEF_GID);
	setTribe(TRIBE_WOLF);
	setJob(m_JobType);

	//< 힘,민,지
	setStrong(EStatus_Base, 3);
	setAgility(EStatus_Base, 3);
	setIntel(EStatus_Base, 3);
	
	//< 상태이상
	setCondition(CONDITION_NORMAL);

	//< 캐릭터 속도 설정
	setMoveSpeed(EStatus_Base, 10);

	//< 이동 딜레이
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< 공격중 아님
	m_isAttacking = false;

	//< 공격 딜레이
	NormalAttackCooltime.m_deley = NormalAttackCooltime.m_lastTime = 50;

	//< 컨디션 딜레이
	m_conDeley.m_deley = 0;
	m_conDeley.m_lastTime = 0;

	//< 무적스킬 딜레이
	InbeatCoolTime.m_deley = 10000;
	InbeatCoolTime.m_lastTime = 0;

	//< 전체 스킬
	SAFE_DELETE(SkillProjectile);
	SkillProjectile = new skillWhole();

	//< 현재 레벨 저장
	m_PrefLevel = getLevelInfo().getNowLevel();

	//< 대쉬 카운트
	dash_count = 0;
	//< 회복 카운트
	m_hpCount = 0;
	m_mpCount = 0;

	//< 애니메이션 설정
	InitAnimInfo(Template);

	return true;
}

//< 해제
void character::release(void)
{
	m_Skills.clear();

	ClearProjectile();

	SAFE_DELETE( SkillProjectile );

	//< 애니메이션 삭제
	releaseAniInfo();
}

void character::update(float fDeltaTime)
{
	UpdateCondition();
	UpdateProjectile();

	if (m_nowState == STATE_DIE)
	{
		auto found = m_Animations.find(E_AnimationType::Die);
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
			incStrong(EStatus_Base, 1);
			break;
		case 4:
			incAgility(EStatus_Base, 1);
			break;
		case 5:
			incIntel(EStatus_Base, 1);
			break;
		}
		m_PrefLevel = curLevel;
	}

	//< 체력 마력 자동 재생
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

	//< 캐릭터 무브
	move(fDeltaTime);

	//ProcessInputKey();

	//< 공격
	attack();

	UpdateDash();

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
		RenderAnimation(hdc, E_AnimationType::Die);
	}
	//< 피격 애니메이션
	else if (IsPlayingAnimation(E_AnimationType::BeHit))
	{
		RenderAnimation(hdc, E_AnimationType::BeHit);
	}
	//< 대쉬 애니메이션
	else if (IsPlayingAnimation(E_AnimationType::Dash))
	{
		RenderAnimation(hdc, E_AnimationType::Dash);
	}
	//< 공격중이면
	else if (IsPlayingAnimation(E_AnimationType::Attack))
	{
		RenderAnimation(hdc, E_AnimationType::Attack);
	}
	//< 이동 중이면
	else if (m_nowState == STATE_MOVE)
	{
		RenderAnimation(hdc, E_AnimationType::Move);
	}
	//< 대기상태
	else
	{
		RenderAnimation(hdc, E_AnimationType::Idle);
	}

	//< 피격 이펙트
	if (IsPlayingAnimation(E_AnimationType::HitEff))
	{
		RenderAnimation(hdc, E_AnimationType::HitEff);
	}

	RenderProjectile(hdc);

	//< 스킬 랜더
	SkillProjectile->render(hdc);

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
	if (IsPlayingAnimation(E_AnimationType::Attack) == false)
	{
		//< 공격중 아님
		m_isAttacking = false;
	}

	//충돌체 갱신
	SkillProjectile->update();
}

//< 타격
bool character::beHit(int damage)
{
	//< HP 감소 (무적상태가 아닐경우에만)
	if (getCondition() != CONDITION_INBEAT)
	{

		incHP(-damage);
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
			StartAnimation(E_AnimationType::HitEff);
		}
		StartAnimation(E_AnimationType::BeHit);

		LOG_MGR->addLog("m_state.m_nowHP : %d", getHP());
		if (getHP() <= 0 && m_nowState != STATE_DIE)
		{
			LOG_MGR->addLog("PLAYER_DIE");
#ifdef _DEBUG
			setHP(1);
			return false;
#endif
			m_nowState = STATE_DIE;
			StartAnimation(E_AnimationType::Die);
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
		StartAnimation(E_AnimationType::Die);
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
	if (IsPlayingAnimation(E_AnimationType::Attack) == true || IsPlayingAnimation(E_AnimationType::Dash) == true)
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

	if (m_nowState == STATE_MOVE && IsPlayingAnimation(E_AnimationType::Move) == false)
	{
		StartAnimation(E_AnimationType::Move);
	}
}

void character::InitAnimInfo(const CharacterTemplate* Template)
{
	releaseAniInfo();

	if (Template == nullptr)
	{
		return;
	}

	for (auto each : Template->m_AnimationDatas)
	{
		E_AnimationType aniType = each.first;
		AnimationTemplate& ani = each.second;
		LPANI_INFO Info = new ANI_INFO;
		AniMgr::SetAnimInfo(Info, ani.rcid, ani.size, ani.countX, ani.countY, ani.speed, ani.bFlag, ani.bLoop, ani.bPlay);
		m_Animations.insert(make_pair(aniType, Info));
	}

	//< 타격 애니메이션
	LPANI_INFO HitEff_Info = new ANI_INFO;
	SIZE hitAniSize = RC_MGR->findImage(imgID_HITEFF1)->getSize();
	AniMgr::SetAnimInfo(HitEff_Info, imgID_HITEFF1, hitAniSize, 6, 1, 50, false, false, true);
	m_Animations.insert(make_pair(E_AnimationType::HitEff, HitEff_Info));
}

void character::releaseAniInfo(void)
{
	for (auto each : m_Animations)
	{
		SAFE_DELETE(each.second);
	}
	m_Animations.clear();
}

void character::RenderAnimation(HDC hdc, E_AnimationType eType)
{
	auto found = m_Animations.find(eType);
	if (found != m_Animations.end())
	{
		switch (eType)
		{
		case E_AnimationType::Dash:
		case E_AnimationType::HitEff:
			AniMgr::Render(hdc, found->second, m_pos, 0, found->second->RCID);
		default:
			AniMgr::Render(hdc, found->second, m_pos, m_dir, found->second->RCID);
			break;
		}
	}
}

void character::StartAnimation(E_AnimationType eType)
{
	auto found = m_Animations.find(eType);
	if (found == m_Animations.end())
	{
		return;
	}

	found->second->flag = true;
}

bool character::IsPlayingAnimation(E_AnimationType eType)
{
	auto found = m_Animations.find(eType);
	if (found == m_Animations.end())
	{
		return false;
	}

	return found->second->flag;
}

cProjectile* character::GetProjectile(E_SkillType SkillType)
{
	auto found = ProjectileMap.find(SkillType);
	if (found != ProjectileMap.end())
	{
		return found->second;
	}

	return nullptr;
}

bool character::CreateProjectile(E_SkillType SkillType, POINT StartPos, POINT TargetPos, int Direction)
{
	cProjectile* NewProjectile = nullptr;
	if (m_JobType == JOB_ARCHER)
	{
		NewProjectile = new cProjectile(6, BOW_ATTACK_RANGE, 10);
		NewProjectile->SetImage(imgID_ARCHER_ARROW, "Data/Resource/Image/character/archer/arrow.bmp");
	}
	else
	{
		NewProjectile = new cProjectile(6, NORMAL_ATTACK_RANGE, 10, 0.3f);
	}

	NewProjectile->shoot(StartPos, TargetPos, Direction);

	ProjectileMap.insert(std::make_pair(SkillType, NewProjectile));

	return true;
}

void character::ClearProjectile()
{
	for (auto EachProjectile : ProjectileMap)
	{
		SAFE_DELETE(EachProjectile.second);
	}

	ProjectileMap.clear();
}

void character::RemoveProjectile(E_SkillType SkillType)
{
	if (cProjectile* found = GetProjectile(SkillType))
	{
		SAFE_DELETE(found);
	}

	ProjectileMap.erase(SkillType);
}

void character::UpdateProjectile()
{
	std::vector<int> RemoveIndex;

	for (auto EachProjectile : ProjectileMap)
	{
		EachProjectile.second->update();

		if (EachProjectile.second->getFlag() == false)
		{
			RemoveIndex.push_back(EachProjectile.first);
		}
	}

	for (int index : RemoveIndex)
	{
		RemoveProjectile(static_cast<E_SkillType>(index));
	}
}

void character::RenderProjectile(HDC hdc)
{
	for (auto EachProjectile : ProjectileMap)
	{
		EachProjectile.second->render(hdc);
	}
}

RECT character::GetProjectileRect(E_SkillType SkillType)
{
	if (cProjectile* found = GetProjectile(SkillType))
	{
		return found->getRect();
	}

	RECT rect = { 0, 0, 0, 0};
	return rect;
}

bool character::IsPlayingProjectile(E_SkillType SkillType)
{
	if (cProjectile* NormalAttackProj = GetProjectile(SkillType))
	{
		return NormalAttackProj->getFlag();
	}
	return false;
}

void character::SetBallFlag(E_SkillType SkillType, bool flag)
{
	if (cProjectile* NormalAttackProj = GetProjectile(SkillType))
	{
		NormalAttackProj->setFlag(flag);
	}

	if (flag == false)
	{
		RemoveProjectile(SkillType);
	}
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
	return GetProjectileRect(E_SkillType_NormalAttack);
}

//< 스킬 렉트 반환
RECT character::getSkillRect(void)
{
	return SkillProjectile->getRect();
}

int character::getDamage(void)
{
	if (cProjectile* NormalAttackProj = GetProjectile(E_SkillType_NormalAttack))
	{
		return NormalAttackProj->getDamage() + getStrong();
	}

	return 0;
}

//< 충돌체 얻기 ( 아이템 획득 )
void character::gainCollider(E_TileBrush obj)
{
	//< 아이템이면 인벤토리에 추가
	if (obj >= ITEM_FIRST && obj < ITEM_END)
	{
		// 플레이어 컨트롤러를 어딘가에서 구해와
		ScenePlayGame* nowState = static_cast<ScenePlayGame*>(STATE_MGR->nowScene());
		if (nowState == nullptr)
		{
			return;
		}

		PlayerController* Player = nowState->GetPlayerController();
		if (Player == nullptr)
		{
			return;
		}

		Player->AddItem((int)obj);
	}
	//< 그 외에는 충돌체크
	else
	{
		setPosToPrev();
	}
}

//< 마법 충돌체 상태
void character::setSkillBallFlag( bool flag )	
{
	SkillProjectile->setFlag( flag );	
}
bool character::getSkillBallFlag( void )	
{	
	return SkillProjectile->getFlag();
}

void character::ProcessSkill(unsigned int nIndex)
{
	if (m_Skills.size() <= nIndex)
	{
		return;
	}

	E_SkillType SkillType = m_Skills[nIndex];

	switch (SkillType)
	{
	case E_SkillType_NormalAttack:
		AttackTrigger();
		break;
	case E_SkillType_Dash:
		DashTrigger();
		break;
	case E_SkillType_ShootWhole:
		ShootWholeSkill();
		break;
	case E_SkillType_Inbeatable:
		Inbeatable();
		break;
	}
}

void character::AttackTrigger()
{
	if (m_isAttacking == true)
		return;

	m_nowState = STATE_ATTACK;
	StartAnimation(E_AnimationType::Attack);

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
	NormalAttackCooltime.m_lastTime = 0;
	//공격 사운드
	//SOUND_MGR->soundPlay(SOUND_BGM4);

	CreateProjectile(E_SkillType_NormalAttack, m_pos, destPos, m_dir);

	//< 공격중
	m_isAttacking = true;
}

//< 대쉬
void character::UpdateDash(void)
{
	//< 대쉬 거리
	int m_dashDist = CHARACTER_DASH_DIST / 5;
	if (IsPlayingAnimation(E_AnimationType::Attack) == true)
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

void character::Inbeatable(void)
{
	if (InbeatCoolTime.m_lastTime + InbeatCoolTime.m_deley < GetTickCount() && getMP() >= 10)
	{
		incMP(-10);
		setCondition(CONDITION_INBEAT, 300);
		InbeatCoolTime.m_lastTime = GetTickCount();
	}
}

void character::DashTrigger()
{
	if (getMP() >= 5)
	{
#ifdef __RELEASE
		incMP(-5);
#endif
		dash_count = 5;
		StartAnimation(E_AnimationType::Dash);
	}
}

void character::ShootWholeSkill()
{
	//< 스킬 가능 상태
	if (wholeSkillCoolTime.m_deley <= wholeSkillCoolTime.m_lastTime++)
	{
		// 구체 이동
		if (getMP() >= 50)
		{
			incMP(-50);
			POINT pos = m_pos;
			//< 딜레이 카운트
			wholeSkillCoolTime.m_lastTime = 0;
			//공격 사운드
			//SOUND_MGR->soundPlay(SOUND_BGM4);
			//< 스킬 발동
			SkillProjectile->shoot(m_pos, pos);
			//CreateProjectile(E_SkillType_ShootWhole, m_pos, m_pos);
		}
	}
}