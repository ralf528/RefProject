#include "stdafx.h"
#include "character.h"

using namespace myUTIL;
using namespace keyInput;

character::character(void)
	: m_dir( DIR_D )
{
	init();
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
	//< 캐릭터 렉트
	setRect();
	//< 캐릭터 방향정보( 아래 보도록 )
	m_dir = DIR_D;
	//< 캐릭터 속도 설정
	m_moveSpeed = 2;

	//< 캐릭터 이미지
	RC_MGR->addImage( imgID_CHARACTER_1, "Data/player32.bmp", 0, 0 , RM_ALPHA32 );

	return true;
}
//< 해제
void character::release(void)
{
}
//< 갱신
void character::update(void)
{
}
//< 랜더
void character::render(HDC hdc)
{
	RENDER_MGR->render( hdc, imgID_CHARACTER_1, m_rect.left - CAMERA->getX(),  m_rect.top - CAMERA->getY() );
}

//< 이동
void character::move( void )
{
	//<이전 위치 기억
	m_prevPos = m_pos;

	//키입력 & 이동
	if( isKeyDown( VK_LEFT ) )
	{
		m_dir = DIR_L;
		m_pos.x -= m_moveSpeed*2;
		CAMERA->moveCamera( -m_moveSpeed*2 , 0 );
	}
	if( isKeyDown( VK_RIGHT ) )
	{
		m_dir = DIR_R;
		m_pos.x += m_moveSpeed*2;
		CAMERA->moveCamera( m_moveSpeed*2 , 0 );
	}
	if( isKeyDown( VK_UP ) )
	{
		m_dir = DIR_U;
		m_pos.y -= m_moveSpeed;
		CAMERA->moveCamera( 0, -m_moveSpeed );
	}
	if( isKeyDown( VK_DOWN ) )
	{
		m_dir = DIR_D;
		m_pos.y += m_moveSpeed;
		CAMERA->moveCamera( 0, m_moveSpeed );
	}
	//렉트 이동
	SetRect(&m_rect, 
		m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
		m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}

//< 좌표 설정
void character::setPos( POINT &pos )
{
	m_pos = pos;
	//렉트 이동
	setRect();
}
void character::setPos( LONG x, LONG y )
{
	m_pos.x = x;
	m_pos.y = y;
	//렉트 이동
	setRect();
}

//< 이전 위치로 되돌리기
void character::setPosToPrev(void)
{
	CAMERA->moveCamera( m_prevPos.x - m_pos.x , m_prevPos.y - m_pos.y );
	m_pos = m_prevPos;	
}

//< 방향 설정
void character::setDir(int dir)
{
	m_dir = dir;
}

//< 렉트 설정
void character::setRect( void )
{
	SetRect(&m_rect, 
		m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
		m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}