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


//< �ʱ�ȭ
bool character::init(void)
{
	//< ĳ���� ��ǥ
	m_pos.x = CHARACTER_START_POSITION_X;
	m_pos.y = CHARACTER_START_POSITION_Y;
	//< �̵� �� ��ǥ
	m_prevPos = m_pos;
	//< ĳ���� ��Ʈ
	setRect();
	//< ĳ���� ��������( �Ʒ� ������ )
	m_dir = DIR_D;
	//< ĳ���� �ӵ� ����
	m_moveSpeed = 2;

	//< ĳ���� �̹���
	RC_MGR->addImage( imgID_CHARACTER_1, "Data/player32.bmp", 0, 0 , RM_ALPHA32 );

	return true;
}
//< ����
void character::release(void)
{
}
//< ����
void character::update(void)
{
}
//< ����
void character::render(HDC hdc)
{
	RENDER_MGR->render( hdc, imgID_CHARACTER_1, m_rect.left - CAMERA->getX(),  m_rect.top - CAMERA->getY() );
}

//< �̵�
void character::move( void )
{
	//<���� ��ġ ���
	m_prevPos = m_pos;

	//Ű�Է� & �̵�
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
	//��Ʈ �̵�
	SetRect(&m_rect, 
		m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
		m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}

//< ��ǥ ����
void character::setPos( POINT &pos )
{
	m_pos = pos;
	//��Ʈ �̵�
	setRect();
}
void character::setPos( LONG x, LONG y )
{
	m_pos.x = x;
	m_pos.y = y;
	//��Ʈ �̵�
	setRect();
}

//< ���� ��ġ�� �ǵ�����
void character::setPosToPrev(void)
{
	CAMERA->moveCamera( m_prevPos.x - m_pos.x , m_prevPos.y - m_pos.y );
	m_pos = m_prevPos;	
}

//< ���� ����
void character::setDir(int dir)
{
	m_dir = dir;
}

//< ��Ʈ ����
void character::setRect( void )
{
	SetRect(&m_rect, 
		m_pos.x - CHARACTER_SIZE, m_pos.y - CHARACTER_SIZE,
		m_pos.x + CHARACTER_SIZE, m_pos.y + CHARACTER_SIZE);
}