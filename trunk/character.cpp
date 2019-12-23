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
	setBelief( 0 );
	setTribe( 0 );
	setJob( 0 );

	//< 힘,민,지
	setStrong(3);
	setAgility(3);
	setIntel(3);
	
	//< 캐릭터 속도 설정
	setMoveSpeed( 2 );
	//< 대쉬 카운트
	dash_count = 5;

	//< 공격 충돌체
	if( NULL == ball )
	{
		ball = new cProjectile(6,NORMAL_ATTACK_RANGE);
	}
	//< 전체 스킬
	if( NULL == skill )
	{
		skill = new skillWhole();
	}
	//< 공격 딜레이
	attDeley.m_deley = attDeley.m_lastTime = 30;
	wholeSkillDeley.m_deley = wholeSkillDeley.m_lastTime = 300;

	//< 컨디션 딜레이
	m_conDeley.m_deley = 0;
	m_conDeley.m_lastTime = 0;

	//< 호스트 캐릭터는 -1, 나머지는 커넥션 인데스 번호
	m_connectionIndex = -1;
	return true;
}
//< 해제
void character::release(void)
{
	//SAFE_DELETE( m_inventory );
	SAFE_DELETE( ball );
	SAFE_DELETE( skill );
}
//< 갱신
void character::update(float fDeltaTime)
{
	//< 캐릭터 무브
	move(fDeltaTime);
	//< 공격
	attack();
	//< 대쉬
	dash();
}
//< 랜더
void character::render(HDC hdc)
{
	//< 캐릭터 랜더(상반신)
	//RENDER_MGR->render( hdc, imgID_CHARACTER_1, m_rect.left - CAMERA->getX(),  m_rect.top - RENDER_OFFSET_Y - CAMERA->getY() );
		
	//< 공격중이면
	if( attDeley.m_lastTime < attDeley.m_deley )
	{
		//공격 애니메이션
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
		//케릭터 방향 애니메이션
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

	//마법 구체 렌더
	ball->render(hdc);
	//< 스킬 랜더
	skill->render(hdc);
#ifdef _DEBUG
	//주위 타일
	MoveToEx( hdc, vertex[3].x - CAMERA->getX(), vertex[3].y- CAMERA->getY() , NULL );
	LineTo( hdc, vertex[4].x - CAMERA->getX(), vertex[4].y- CAMERA->getY() );	
	MoveToEx( hdc, vertex[2].x - CAMERA->getX(), vertex[2].y- CAMERA->getY() , NULL );
	LineTo( hdc, vertex[5].x - CAMERA->getX(), vertex[5].y - CAMERA->getY() );
#endif
}

//< 충돌체 얻기 ( 아이템 획득 )
void character::gainCollider( tileType &obj )
{
	//< 오브젝트에 따른 반응
	//< 아이템이면 인벤토리에 추가
	if( obj >= ITEM_FIRST && obj < ITEM_END )
	{
		//m_state.m_nowHP+=10;
		//m_inventory->addItem( obj );
	}
	//< 그 외에는 충돌체크
	else
	{
		setPosToPrev();
	}
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