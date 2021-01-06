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

	//< ĳ���� �������ͽ�
	setMaxHP( CHARACTER_HP );
	setHP( CHARACTER_HP );
	setMaxMP( CHARACTER_MP );
	setMP( CHARACTER_MP );

	//< �ų�, ����, ����
	setBelief(BELIEF_GID);
	setTribe(TRIBE_WOLF);
	setJob(JOB_KNIGHT);

	//< ��,��,��
	setStrong(3);
	setAgility(3);
	setIntel(3);
	
	setCondition(CONDITION_NORMAL);

	//< ĳ���� �ӵ� ����
	setMoveSpeed(10.f); //2

	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< �뽬 ī��Ʈ
	dash_count = 0;

	//< �κ��丮 ����
	if (NULL == m_inventory)
	{
		m_inventory = new Inventory;
	}

	//< ���� �浹ü
	if( NULL == ball )
	{
		//ball = new cProjectile(6, NORMAL_ATTACK_RANGE);
		ball = new cProjectile(6, NORMAL_ATTACK_RANGE, 10, 0.3f);
	}

	//< ��ü ��ų
	if( NULL == skill )
	{
		skill = new skillWhole();
	}

	//< ���� ������
	attDeley.m_deley = attDeley.m_lastTime = 50; //30;

	//< ������ �ƴ�
	m_isAttacking = false;

	//< ����� ������
	m_conDeley.m_deley = 0;
	m_conDeley.m_lastTime = 0;

	//< ���� ���� ����
	m_PrefLevel = getLevelInfo().getNowLevel();

	//< �ִϸ��̼� ����
	InitAnimInfo();
	m_nowState = STATE_IDLE;

	return true;
}

//< ����
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

	//< ���� Ȯ��
	int curLevel = getLevelInfo().getNowLevel();
	//< ������ �����ϸ� ���� ���� ����
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

	//< ĳ���� ����
	move(fDeltaTime);

	//ProcessInputKey();

	//< ����
	attack();

	//< ������
	useItem();

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
		RenderAnimation(hdc, imgID_WARRIOR_DIE);
	}
	//< �ǰ� �ִϸ��̼�
	else if (IsPlayingAnimation(imgID_WARRIOR_BEHIT))
	{
		RenderAnimation(hdc, imgID_WARRIOR_BEHIT);
	}
	//< �뽬 �ִϸ��̼�
	else if (IsPlayingAnimation(imgID_WARRIOR_DASH))
	{
		RenderAnimation(hdc, imgID_WARRIOR_DASH);
	}
	//< �������̸�
	else if (IsPlayingAnimation(imgID_WARRIOR_ATK))
	{
		RenderAnimation(hdc, imgID_WARRIOR_ATK);
	}
	//< �̵� ���̸�
	else if (m_nowState == STATE_MOVE)
	{
		RenderAnimation(hdc, imgID_WARRIOR_MOVE);
	}
	//< ������
	else
	{
		RenderAnimation(hdc, imgID_WARRIOR_IDLE);
	}

	//< �ǰ� ����Ʈ
	if (IsPlayingAnimation(imgID_GETHIT_1))
	{
		RenderAnimation(hdc, imgID_GETHIT_1);
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
void character::renderLower(HDC hdc)
{
	//RENDER_MGR->render( hdc, imgID_CHARACTER_LOWER, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
}

//< ����
void character::attack(void)
{
	//< ���� ���� ����
	if (IsPlayingAnimation(imgID_WARRIOR_ATK) == false)
	{
		//< ������ �ƴ�
		m_isAttacking = false;
	}

	//�浹ü ����
	ball->update();
	skill->update();
}

//< Ÿ��
bool character::beHit(int damage)
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
		StartAnimation(imgID_WARRIOR_DIE);
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
	if (IsPlayingAnimation(imgID_WARRIOR_ATK) == true || IsPlayingAnimation(imgID_WARRIOR_DASH) == true)
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

	if (m_nowState == STATE_MOVE && IsPlayingAnimation(imgID_WARRIOR_MOVE) == false)
	{
		StartAnimation(imgID_WARRIOR_MOVE);
	}
}

void character::InitAnimInfo(void)
{
	releaseAniInfo();

	//< ĳ���� �̹���
	RC_MGR->addImage(imgID_WARRIOR_IDLE, "Data/Resource/Image/character/warrior_idle.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_MOVE, "Data/Resource/Image/character/warrior_walk.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_ATK, "Data/Resource/Image/character/warrior_atk.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_DASH, "Data/Resource/Image/character/dash.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_DIE, "Data/Resource/Image/character/warrior_die.bmp", 0, 0, RM_TRANS);
	RC_MGR->addImage(imgID_WARRIOR_BEHIT, "Data/Resource/Image/character/warrior-gethit.bmp", 0, 0, RM_TRANS);

	//< ���̵� �ִϸ��̼�
	LPANI_INFO IdleAni_Info = new ANI_INFO;
	SIZE idleAniSize = RC_MGR->findImage(imgID_WARRIOR_IDLE)->getSize();
	AniMgr::SetAnimInfo(IdleAni_Info, idleAniSize, 8, 8, 50, true, true, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_IDLE, IdleAni_Info));

	//< �̵� �ִϸ��̼�
	LPANI_INFO MoveAni_Info = new ANI_INFO;
	SIZE moveAniSize = RC_MGR->findImage(imgID_WARRIOR_MOVE)->getSize();
	AniMgr::SetAnimInfo(MoveAni_Info, moveAniSize, 8, 8, 50, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_MOVE, MoveAni_Info));

	//< ���� �ִϸ��̼�
	LPANI_INFO AtckAni_Info = new ANI_INFO;
	SIZE atkAniSize = RC_MGR->findImage(imgID_WARRIOR_ATK)->getSize();
	AniMgr::SetAnimInfo(AtckAni_Info, atkAniSize, 18, 8, 20, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_ATK, AtckAni_Info));

	//< ��� �ִϸ��̼�
	LPANI_INFO DieAni_Info = new ANI_INFO;
	SIZE dieAniSize = RC_MGR->findImage(imgID_WARRIOR_DIE)->getSize();
	AniMgr::SetAnimInfo(DieAni_Info, dieAniSize, 20, 8, 200, false, false, false);
	m_Animations.insert(make_pair(imgID_WARRIOR_DIE, DieAni_Info));

	//< �ǰ� �ִϸ��̼�
	LPANI_INFO beHitAni_Info = new ANI_INFO;
	SIZE behitAniSize = RC_MGR->findImage(imgID_WARRIOR_BEHIT)->getSize();
	AniMgr::SetAnimInfo(beHitAni_Info, behitAniSize, 7, 8, 20, false, false, true);
	m_Animations.insert(make_pair(imgID_WARRIOR_BEHIT, beHitAni_Info));

	//< Ÿ�� �ִϸ��̼�
	LPANI_INFO HitEff_Info = new ANI_INFO;
	SIZE hitAniSize = RC_MGR->findImage(imgID_GETHIT_1)->getSize();
	AniMgr::SetAnimInfo(HitEff_Info, hitAniSize, 6, 1, 50, false, false, true);
	m_Animations.insert(make_pair(imgID_GETHIT_1, HitEff_Info));

	//< �뽬 �ִϸ��̼�
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

//< ������ ���
void character::useItem( void )
{
	int useIndex = 0;
	if( onceKeyDown( '1' ) )	{		useIndex = 1;	}
	if( onceKeyDown( '2' ) )	{		useIndex = 2;	}
	if( onceKeyDown( '3' ) )	{		useIndex = 3;	}
	if( onceKeyDown( '4' ) )	{		useIndex = 4;	}
	//< Ű�� ������ ������ ���
	if( 0 != useIndex )
	{
		//< �ش� �ε����� ������ ID
        unsigned int itemID = m_inventory->useItem(useIndex);
		//< �������� �ִٸ� ���
		if( ITEM_END != itemID )
		{
			//<ȥ���̸� ���� �ߵ�
			if( ITEM_POTION_VENOM == itemID)
			{
				itemID = ITEM_FIRST + rand()%(ITEM_END-ITEM_FIRST);
			}
			switch( itemID )
			{
			case ITEM_POTION_CONFUSION:	//< ġ��
				//SOUND_MGR->soundPlay(SOUND_BGM9); //< �������� ������ ȿ����
				//< ü�� ����
				incHP( 20 );
				if( getHP() > getMaxHP() )
				{
					setHP( getMaxHP() );
				}
				//< �����̻� ġ��
				m_state.m_condition = CONDITION_NORMAL;
				break;
			case ITEM_POSION_CURE:	//< ���
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				//< ü�� ����
				incHP( 60 );
				if( getHP() > getMaxHP() )
				{
					setHP( getMaxHP() );
				}
				break;
			case ITEM_POTION_IDENTFY:	//< ��
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				//< �� ����
				m_state.m_condition = CONDITION_POISON;
				m_conDeley.m_deley = 6000;
				m_conDeley.m_lastTime = GetTickCount();
				break;
			case ITEM_POTION_REGEN: //< ��ȭ
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				m_state.m_str -= 3;
				if( getStrong() < 0 ) m_state.m_str = 1;
				m_state.m_agl -= 3;
				if( getAgility() < 0 ) m_state.m_agl = 1;
				m_state.m_int -= 3;
				if( getIntel() < 0 ) m_state.m_int = 1;
				break;
			case ITEM_POTION_UNKNOWN: //< ��ȭ
				//SOUND_MGR->soundPlay(SOUND_BGM9);
				m_state.m_str += 3;
				m_state.m_agl += 3;
				m_state.m_int += 3;
				break;
			}
		}
	}
}

//< �κ��丮 ����
void character::renderInven(HDC hdc)
{
	//< �κ��丮 ����
	m_inventory->renderInven(hdc);
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
	return ball->getRect();	
}

//< ��ų ��Ʈ ��ȯ
RECT character::getSkillRect(void)
{
	return skill->getRect();
}

int character::getDamage(void)
{
	return (ball->getDamage() + getStrong());
}

//< �浹ü ��� ( ������ ȹ�� )
void character::gainCollider(E_TileBrush &obj)
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

//< �浹ü ����
void character::setBallFlag( bool flag )
{
	ball->setFlag( flag );
}
bool character::getBallFlag( void )	
{
	return ball->getFlag();
}

//< ���� �浹ü ����
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