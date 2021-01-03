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
	setBelief( 0 );
	setTribe( 0 );
	setJob( 0 );

	//< ��,��,��
	setStrong(3);
	setAgility(3);
	setIntel(3);
	
	//< ĳ���� �ӵ� ����
	setMoveSpeed( 2 );
	//< �뽬 ī��Ʈ
	dash_count = 0;

	//< ���� �浹ü
	if( NULL == ball )
	{
		ball = new cProjectile(6,NORMAL_ATTACK_RANGE);
	}
	//< ��ü ��ų
	if( NULL == skill )
	{
		skill = new skillWhole();
	}
	//< ���� ������
	attDeley.m_deley = attDeley.m_lastTime = 30;
	wholeSkillDeley.m_deley = wholeSkillDeley.m_lastTime = 300;

	//< ����� ������
	m_conDeley.m_deley = 0;
	m_conDeley.m_lastTime = 0;

	return true;
}
//< ����
void character::release(void)
{
	SAFE_DELETE( m_inventory );
	SAFE_DELETE( ball );
	SAFE_DELETE( skill );
}

//< �浹ü ��� ( ������ ȹ�� )
void character::gainCollider( E_TileBrush &obj )
{
	//< ������Ʈ�� ���� ����
	//< �������̸� �κ��丮�� �߰�
	if( obj >= ITEM_FIRST && obj < ITEM_END )
	{
		//m_state.m_nowHP+=10;
		m_inventory->addItem( obj );
	}
	//< �� �ܿ��� �浹üũ
	else
	{
		setPosToPrev();
	}
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