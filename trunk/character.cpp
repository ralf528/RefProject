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
	dash_count = 5;

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

	//< ȣ��Ʈ ĳ���ʹ� -1, �������� Ŀ�ؼ� �ε��� ��ȣ
	m_connectionIndex = -1;
	return true;
}
//< ����
void character::release(void)
{
	//SAFE_DELETE( m_inventory );
	SAFE_DELETE( ball );
	SAFE_DELETE( skill );
}
//< ����
void character::update(float fDeltaTime)
{
	//< ĳ���� ����
	move(fDeltaTime);
	//< ����
	attack();
	//< �뽬
	dash();
}
//< ����
void character::render(HDC hdc)
{
	//< ĳ���� ����(��ݽ�)
	//RENDER_MGR->render( hdc, imgID_CHARACTER_1, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
		
	//< �������̸�
	if( attDeley.m_lastTime < attDeley.m_deley )
	{
		//���� �ִϸ��̼�
		switch(m_dir)
			{		
			case DIR_L:
				ANI_MGR->render(hdc,ATK_L, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			case DIR_LU:
				ANI_MGR->render(hdc,ATK_LU, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			case DIR_U:
				ANI_MGR->render(hdc,ATK_U, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			case DIR_RU:
				ANI_MGR->render(hdc,ATK_RU, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());;
				break;
			case DIR_R:
				ANI_MGR->render(hdc,ATK_R, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			case DIR_RD:
				ANI_MGR->render(hdc,ATK_RD, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			case DIR_D:
				ANI_MGR->render(hdc,ATK_D, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			case DIR_LD:
				ANI_MGR->render(hdc,ATK_LD, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
				break;
			}
	}
	else
	{
		//�ɸ��� ���� �ִϸ��̼�
		switch( m_dir )
		{
		case DIR_L:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_L, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_R:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_R, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_U:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_U, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_D:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_D, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_LU:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_LU, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_RU:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_RU, m_pos.x - CAMERA->getX(),  m_pos.y- RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_LD:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_LD, m_pos.x - CAMERA->getX(),  m_pos.y - RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		case DIR_RD:
			{
				ANI_MGR->render(hdc,AniEffect::CHAR_RD, m_pos.x - CAMERA->getX(),  m_pos.y - RENDER_OFFSET_Y - CAMERA->getY());
			}
			break;
		}
	}

	//���� ��ü ����
	ball->render(hdc);
	//< ��ų ����
	skill->render(hdc);
#ifdef _DEBUG
	//���� Ÿ��
	MoveToEx( hdc, vertex[3].x - CAMERA->getX(), vertex[3].y- CAMERA->getY() , NULL );
	LineTo( hdc, vertex[4].x - CAMERA->getX(), vertex[4].y- CAMERA->getY() );	
	MoveToEx( hdc, vertex[2].x - CAMERA->getX(), vertex[2].y- CAMERA->getY() , NULL );
	LineTo( hdc, vertex[5].x - CAMERA->getX(), vertex[5].y - CAMERA->getY() );
#endif
}

//< �浹ü ��� ( ������ ȹ�� )
void character::gainCollider( tileType &obj )
{
	//< ������Ʈ�� ���� ����
	//< �������̸� �κ��丮�� �߰�
	if( obj >= ITEM_FIRST && obj < ITEM_END )
	{
		//m_state.m_nowHP+=10;
		//m_inventory->addItem( obj );
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