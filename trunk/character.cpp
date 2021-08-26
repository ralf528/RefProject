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


//< �ʱ�ȭ
bool character::init(void)
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

	//< ĳ���� �������ͽ�
	setMaxHP(EStatus_Base, CHARACTER_HP);
	setHP( CHARACTER_HP );
	setMaxMP(EStatus_Base, CHARACTER_MP);
	setMP( CHARACTER_MP );

	//< �ų�, ����, ����
	setBelief(BELIEF_GID);
	setTribe(TRIBE_WOLF);
	setJob(m_JobType);

	//< ��,��,��
	setStrong(EStatus_Base, 3);
	setAgility(EStatus_Base, 3);
	setIntel(EStatus_Base, 3);
	
	//< �����̻�
	setCondition(CONDITION_NORMAL);

	//< ĳ���� �ӵ� ����
	setMoveSpeed(EStatus_Base, 10);

	//< �̵� ������
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< ������ �ƴ�
	m_isAttacking = false;

	//< ���� ������
	NormalAttackCooltime.m_deley = NormalAttackCooltime.m_lastTime = 50;

	//< ����� ������
	m_conDeley.m_deley = 0;
	m_conDeley.m_lastTime = 0;

	//< ������ų ������
	InbeatCoolTime.m_deley = 10000;
	InbeatCoolTime.m_lastTime = 0;

	//< ��ü ��ų
	SAFE_DELETE(SkillProjectile);
	SkillProjectile = new skillWhole();

	//< ���� ���� ����
	m_PrefLevel = getLevelInfo().getNowLevel();

	//< �뽬 ī��Ʈ
	dash_count = 0;
	//< ȸ�� ī��Ʈ
	m_hpCount = 0;
	m_mpCount = 0;

	//< �ִϸ��̼� ����
	InitAnimInfo(Template);

	return true;
}

//< ����
void character::release(void)
{
	m_Skills.clear();

	ClearProjectile();

	SAFE_DELETE( SkillProjectile );

	//< �ִϸ��̼� ����
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

	//< ���� Ȯ��
	int curLevel = getLevelInfo().getNowLevel();
	//< ������ �����ϸ� ���� ���� ����
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

	//< ĳ���� ����
	move(fDeltaTime);

	//ProcessInputKey();

	//< ����
	attack();

	UpdateDash();

	//< �ִϸ��̼� ����
	for (auto each : m_Animations)
	{
		if (each.first == imgID_WARRIOR_DIE)
		{
			continue;
		}

		AniMgr::UpdateAni(each.second);
	}
}

//< ����
void character::render(HDC hdc)
{
	//< �׾��ٸ�
	if (m_nowState == STATE_DIE)
	{
		RenderAnimation(hdc, E_AnimationType::Die);
	}
	//< �ǰ� �ִϸ��̼�
	else if (IsPlayingAnimation(E_AnimationType::BeHit))
	{
		RenderAnimation(hdc, E_AnimationType::BeHit);
	}
	//< �뽬 �ִϸ��̼�
	else if (IsPlayingAnimation(E_AnimationType::Dash))
	{
		RenderAnimation(hdc, E_AnimationType::Dash);
	}
	//< �������̸�
	else if (IsPlayingAnimation(E_AnimationType::Attack))
	{
		RenderAnimation(hdc, E_AnimationType::Attack);
	}
	//< �̵� ���̸�
	else if (m_nowState == STATE_MOVE)
	{
		RenderAnimation(hdc, E_AnimationType::Move);
	}
	//< ������
	else
	{
		RenderAnimation(hdc, E_AnimationType::Idle);
	}

	//< �ǰ� ����Ʈ
	if (IsPlayingAnimation(E_AnimationType::HitEff))
	{
		RenderAnimation(hdc, E_AnimationType::HitEff);
	}

	RenderProjectile(hdc);

	//< ��ų ����
	SkillProjectile->render(hdc);

#ifdef _DEBUG
	//���� Ÿ��
	MoveToEx(hdc, vertex[3].x - CAMERA->getX(), vertex[3].y - CAMERA->getY(), NULL);
	LineTo(hdc, vertex[4].x - CAMERA->getX(), vertex[4].y - CAMERA->getY());
	MoveToEx(hdc, vertex[2].x - CAMERA->getX(), vertex[2].y - CAMERA->getY(), NULL);
	LineTo(hdc, vertex[5].x - CAMERA->getX(), vertex[5].y - CAMERA->getY());
#endif
}

//< �Ϲݽ� ����
void character::renderLower(HDC hdc)
{
	//RENDER_MGR->render( hdc, imgID_CHARACTER_LOWER, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
}

//< ����
void character::attack(void)
{
	//< ���� ���� ����
	if (IsPlayingAnimation(E_AnimationType::Attack) == false)
	{
		//< ������ �ƴ�
		m_isAttacking = false;
	}

	//�浹ü ����
	SkillProjectile->update();
}

//< Ÿ��
bool character::beHit(int damage)
{
	//< HP ���� (�������°� �ƴҰ�쿡��)
	if (getCondition() != CONDITION_INBEAT)
	{

		incHP(-damage);
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
			//��� ����
			//SOUND_MGR->soundPlay(CHAR_DIE);
			return true;
		}
	}

	//SOUND_MGR->soundPlay(CHAR_HIT);
	//< �׾��ٸ� true ����
	if (getHP() <= 0 && m_nowState != STATE_DIE)
	{
#ifdef _DEBUG
		setHP(1);
		return false;
#endif
		setHP(0);
		m_nowState = STATE_DIE;
		StartAnimation(E_AnimationType::Die);
		//��� ����
		//SOUND_MGR->soundPlay(CHAR_DIE);
		return true;
	}

	return false;
}

//< �̵�
void character::move(float fDeltaTime)
{
	//< �������̸� �̵� �Ұ�
	if (IsPlayingAnimation(E_AnimationType::Attack) == true || IsPlayingAnimation(E_AnimationType::Dash) == true)
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

	//< Ÿ�� �ִϸ��̼�
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

//< ��ǥ ����
void character::setPos( POINT &pos )
{
	m_pos = pos;
	//��Ʈ �̵�
	setRect();

	//< ī�޶� ��ġ ����
	CAMERA->setPosition( m_pos.x - SCREEN_X/2 + CHARACTER_SIZE_X,
						m_pos.y - SCREEN_Y/2 + CHARACTER_SIZE_Y );
}
void character::setPos( LONG x, LONG y )
{
	m_pos.x = x;
	m_pos.y = y;
	//��Ʈ �̵�
	setRect();

	//< ī�޶� ��ġ ����
	CAMERA->setPosition( m_pos.x - WINSIZE_X/2 + CHARACTER_SIZE_X,
						m_pos.y - WINSIZE_Y/2 + CHARACTER_SIZE_Y );
}

//< ���� ��ġ�� �ǵ�����
void character::setPosToPrev(void)
{
	CAMERA->moveCamera( m_prevPos.x - m_pos.x , m_prevPos.y - m_pos.y );
	m_pos = m_prevPos;	
}

//< ��Ʈ ����
void character::setRect( void )
{
	SetRect(&m_rect, 
		m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
		m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}

//< ���� �浹ü ��Ʈ ��ȯ
RECT character::getBallRect(void)	
{
	return GetProjectileRect(E_SkillType_NormalAttack);
}

//< ��ų ��Ʈ ��ȯ
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

//< �浹ü ��� ( ������ ȹ�� )
void character::gainCollider(E_TileBrush obj)
{
	//< �������̸� �κ��丮�� �߰�
	if (obj >= ITEM_FIRST && obj < ITEM_END)
	{
		// �÷��̾� ��Ʈ�ѷ��� ��򰡿��� ���ؿ�
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
	//< �� �ܿ��� �浹üũ
	else
	{
		setPosToPrev();
	}
}

//< ���� �浹ü ����
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
	NormalAttackCooltime.m_lastTime = 0;
	//���� ����
	//SOUND_MGR->soundPlay(SOUND_BGM4);

	CreateProjectile(E_SkillType_NormalAttack, m_pos, destPos, m_dir);

	//< ������
	m_isAttacking = true;
}

//< �뽬
void character::UpdateDash(void)
{
	//< �뽬 �Ÿ�
	int m_dashDist = CHARACTER_DASH_DIST / 5;
	if (IsPlayingAnimation(E_AnimationType::Attack) == true)
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
	//< ��ų ���� ����
	if (wholeSkillCoolTime.m_deley <= wholeSkillCoolTime.m_lastTime++)
	{
		// ��ü �̵�
		if (getMP() >= 50)
		{
			incMP(-50);
			POINT pos = m_pos;
			//< ������ ī��Ʈ
			wholeSkillCoolTime.m_lastTime = 0;
			//���� ����
			//SOUND_MGR->soundPlay(SOUND_BGM4);
			//< ��ų �ߵ�
			SkillProjectile->shoot(m_pos, pos);
			//CreateProjectile(E_SkillType_ShootWhole, m_pos, m_pos);
		}
	}
}