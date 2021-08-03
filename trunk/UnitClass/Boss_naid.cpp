#include "stdafx.h"

#include "../cProjectile.h"
//#include ".skill_naid_collum.h"
#include "Boss_naid.h"


boss_naid::boss_naid(void)
	: ball(NULL)
{
	init();
}
boss_naid::~boss_naid(void)
{
	release();
}

//< �ʱ�ȭ
bool boss_naid::init(void)
{

	//�̹��� �߰�
	RC_MGR->addImage( imgID_BOSS_NAID, L"Data/Resource/monster/naid/001-idle.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage(imgID_BOSS_MOVE, L"Data/Resource/monster/naid/001-walk.bmp",0,0,RM_TRANS);
	RC_MGR->addImage(imgID_BOSS_ATK, L"Data/Resource/monster/naid/001-special.bmp",0,0,RM_TRANS);
	RC_MGR->addImage(imgID_BOSS_BEHIT, L"Data/Resource/monster/naid/001-gethit.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_NAID_DIE, L"Data/Resource/monster/naid/001-die.bmp", 0, 0 , RM_TRANS );
	//< ����
	m_stateFlag = STATE_IDLE;

	//< �������ͽ�
	//< ü��
	setMaxHP(EStatus_Base, 200);
	setHP(getMaxHP());
	//< ����
	setMaxMP(EStatus_Base, 100);
	setMP( 100 );
	//< ����ġ
	m_exp = 100;

	//< �ν� ����
	m_recogRange = 700;
	//< ���� ��Ÿ�
	m_attRange = 70;
	//< �̵� �ӵ�
	setMoveSpeed(EStatus_Base, BOSS_1_MOVE_SPEED);
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< ���� �浹ü
	if( NULL == ball )
	{
		ball = new cProjectile(5, m_attRange);
	}
	//< ��ü ��ų
	/*if( NULL == m_skill_collum )
	{
		m_skill_collum = new skill_naid_collum();
	}*/

	//< ������
	attDeley.m_deley = attDeley.m_lastTime = 90;
	m_collum_deley.m_deley = m_collum_deley.m_lastTime = 360;

	//< ����
	m_kindNum = BOSS_NAID;

	setAniInfo();
	return true;
}
//< ����
void boss_naid::release(void)
{
	SAFE_DELETE( ball );
	//SAFE_DELETE( m_skill_collum );
	releaseAniInfo();
}
//< ������Ʈ
void boss_naid::update( void )
{
	//< �ִϸ��̼� ����
	AniMgr::UpdateAni( m_IdleAni_Info );
	AniMgr::UpdateAni( m_MoveAni_Info );
	AniMgr::UpdateAni( m_AtckAni_Info );
	AniMgr::UpdateAni( m_beHitAni_Info );
	AniMgr::UpdateAni( m_DieAni_Info );
	AniMgr::UpdateAni( m_HitAni_Info );
}
//< ����
void boss_naid::render(HDC hdc)
{
	if( m_beHitAni_Info->flag == true )
	{
		SIZE siz = m_beHitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_BOSS_BEHIT,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
			siz.cx, siz.cy,
			m_beHitAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
			siz.cx, siz.cy);
	}
	else
	{
		switch( m_stateFlag )
		{
		case STATE_IDLE:
			{
				SIZE siz = m_IdleAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_BOSS_NAID,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_IdleAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
				break;
			}
		case STATE_ATTACK:
			{
				SIZE siz = m_AtckAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_BOSS_ATK,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_AtckAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
				break;
			}
		case STATE_CHASE:
			{
				SIZE siz = m_MoveAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_BOSS_MOVE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_MoveAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
				break;
			}
		case STATE_DIE:
			{
				SIZE siz = m_DieAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_BOSS_NAID_DIE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_DieAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
			}
			break;
		}
	}
	//< �ǰ� ����Ʈ
	if( m_HitAni_Info->flag == true )
	{
		SIZE siz = m_HitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_HITEFF1,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - CAMERA->getY(),
			siz.cx, siz.cy,
			m_HitAni_Info->nowFrame * siz.cx, 0,
			siz.cx, siz.cy);
	}
	//< ���� HP ǥ��
	renderHPbar(hdc);

	//�⺻ ���� ����
	ball->render(hdc);
	//< ��ų ����
	//m_skill_collum->render(hdc);
}

//< �浹 üũ
bool boss_naid::collision( POINT &destPos )
{
	//< ��� �÷��̾���� �Ÿ� ���ϱ�
	float distance = math::distancePtToPt( m_pos, destPos );

	//< ĳ���Ϳ� �浹
	if( distance <= CHARACTER_SIZE + MONSTER_SIZE )
	{
		if( m_stateFlag == STATE_DIE )
		{
			//< ���Ͱ� �׾��ٸ� �浹ó������ ����
			return false;
		}
		else
		{
			//< ���Ͱ� ����ִٸ� �浹üũ
			return true;
		}
	}
	return false;
}

//< ����
void boss_naid::attack( POINT &destPos )
{
	//< ��ų ������
	if( m_collum_deley.m_deley <= m_collum_deley.m_lastTime++ )
	{
		//< ���� �����̸� ����
		if( m_stateFlag == STATE_ATTACK )
		{
			//< �����ϰ� ī��Ʈ �ʱ�ȭ
			m_collum_deley.m_lastTime = 0;
			//m_skill_collum->shoot( m_pos , destPos );
			m_AtckAni_Info->flag=true;
			//���� ����
			//SOUND_MGR->soundPlay(NAID_ATK);
		}
	}
	//< �⺻ ���� ������
	else if( attDeley.m_deley <= attDeley.m_lastTime++ )
	{
		//< ���� �����̸� ����
		if( m_stateFlag == STATE_ATTACK )
		{
			attDeley.m_lastTime = 0;
			ball->shoot( m_pos , destPos );
			m_AtckAni_Info->flag=true;
		}
	}
	//�浹ü ����
	ball->update();
	//m_skill_collum->update();
}
//< �ν�
void boss_naid::recog( POINT &destPos )
{
	//< ����ִٸ�
	if( m_stateFlag != STATE_DIE )
	{
		//< ��� �÷��̾���� �Ÿ� ���ϱ�
		float distance = math::distancePtToPt( m_pos, destPos );

		//< ĳ���Ͱ� ���� ���� �ȿ� ������ ���ݻ���
		if( distance <= m_attRange )
		{
			m_stateFlag = STATE_ATTACK;
		}
		else
		{
			//< ĳ���Ͱ� �ν� ���� �ȿ� ������ ���� ���·�
			if( distance <= m_recogRange )
			{
				//< ���� ���
				calcDir(destPos);
				m_stateFlag = STATE_CHASE;				
			}
			else
			{				
				//< ������ ������ �ٽ� �����·�
				m_stateFlag = STATE_IDLE ;				
			}
		}
	}
}

//< Ÿ��
bool boss_naid::beHit(int damage)	
{
	//< �̹� �׾��ִٸ� false ����
	if( m_stateFlag == STATE_DIE )
	{
		return false;
	}
	//< ����ִٸ� HP ����
	incHP(-damage);  
	//�ǰ� ����
	//SOUND_MGR->soundPlay(NAID_HIT);
	//< �ǰ� ����Ʈ
	m_HitAni_Info->flag=true;
	m_beHitAni_Info->flag=true;
	//< HP �� ���� ����
	hpRenderStart();
	//< �׾��ٸ� true ����
	if( getHP() <= 0 )
	{
    	setHP( 0 );
		m_stateFlag = STATE_DIE;
		m_DieAni_Info->flag = true;
		//��� ����
		//SOUND_MGR->soundPlay(NAID_DIE);
		return true;
	}
	return false;
}

//< ���� �浹ü ��Ʈ ��ȯ
RECT boss_naid::getBallRect(void)
{
	/*if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getRect();
	}*/
	return ball->getRect();
}

//< �浹ü ����
void boss_naid::setBallFlag( bool flag )
{
	ball->setFlag( flag );
	ball->setPos(m_pos);
}
bool boss_naid::getBallFlag( void )
{
	/*if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getFlag();
	}*/
	return ball->getFlag();
}
//< ������
int boss_naid::getDamage(void)
{
	/*if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getDamage();
	}*/
	return ball->getDamage();
}

void boss_naid::setAniInfo( void )
{
	//< ���̵� �ִϸ��̼�
	SAFE_DELETE( m_IdleAni_Info );
	m_IdleAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE idleAniSize = RC_MGR->findImage(imgID_BOSS_NAID)->getSize();
	//< ������ ��
	m_IdleAni_Info->frameCntX = 12;
	m_IdleAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_IdleAni_Info->aniSize.cx = idleAniSize.cx / m_IdleAni_Info->frameCntX;
	m_IdleAni_Info->aniSize.cy = idleAniSize.cy / m_IdleAni_Info->frameCntY;

	m_IdleAni_Info->frameSpeed = 50;
	m_IdleAni_Info->nowFrame = 0;
	m_IdleAni_Info->nowFrameY = DIR_D;
	m_IdleAni_Info->lastTime = GetTickCount();
	m_IdleAni_Info->flag=true;
	m_IdleAni_Info->loop=true;
	m_IdleAni_Info->playAni=true;

	//< �̵� �ִϸ��̼�
	SAFE_DELETE( m_MoveAni_Info );
	m_MoveAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE moveAniSize = RC_MGR->findImage(imgID_BOSS_MOVE)->getSize();
	//< ������ ��
	m_MoveAni_Info->frameCntX = 10;
	m_MoveAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_MoveAni_Info->aniSize.cx = moveAniSize.cx / m_MoveAni_Info->frameCntX;
	m_MoveAni_Info->aniSize.cy = moveAniSize.cy / m_MoveAni_Info->frameCntY;
	
	m_MoveAni_Info->frameSpeed = 50;
	m_MoveAni_Info->nowFrame = 0;
	m_MoveAni_Info->nowFrameY = DIR_D;
	m_MoveAni_Info->lastTime = GetTickCount();
	m_MoveAni_Info->flag=false;
	m_MoveAni_Info->loop=false;
	m_MoveAni_Info->playAni=true;

	//< ���� �ִϸ��̼�
	SAFE_DELETE( m_AtckAni_Info );
	m_AtckAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE atkAniSize = RC_MGR->findImage(imgID_BOSS_ATK)->getSize();
	//< ������ ��
	m_AtckAni_Info->frameCntX = 10;
	m_AtckAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_AtckAni_Info->aniSize.cx = atkAniSize.cx / m_AtckAni_Info->frameCntX;
	m_AtckAni_Info->aniSize.cy = atkAniSize.cy / m_AtckAni_Info->frameCntY;
	m_AtckAni_Info->frameSpeed = 50;
	m_AtckAni_Info->nowFrame = 0;
	m_AtckAni_Info->nowFrameY = DIR_D;
	m_AtckAni_Info->lastTime = GetTickCount();
	m_AtckAni_Info->flag=false;
	m_AtckAni_Info->loop=false;
	m_AtckAni_Info->playAni=true;

	//< �ǰ� �ִϸ��̼�
	SAFE_DELETE( m_beHitAni_Info );
	m_beHitAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE behitAniSize = RC_MGR->findImage(imgID_BOSS_BEHIT)->getSize();
	//< ������ ��
	m_beHitAni_Info->frameCntX = 7;
	m_beHitAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_beHitAni_Info->aniSize.cx = behitAniSize.cx / m_beHitAni_Info->frameCntX;
	m_beHitAni_Info->aniSize.cy = behitAniSize.cy / m_beHitAni_Info->frameCntY;
	m_beHitAni_Info->frameSpeed = 50;
	m_beHitAni_Info->nowFrame = 0;
	m_beHitAni_Info->nowFrameY = DIR_D;
	m_beHitAni_Info->lastTime = GetTickCount();
	m_beHitAni_Info->flag=false;
	m_beHitAni_Info->loop=false;
	m_beHitAni_Info->playAni=true;

	//< ��� �ִϸ��̼�
	SAFE_DELETE( m_DieAni_Info );
	m_DieAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE dieAniSize = RC_MGR->findImage(imgID_BOSS_NAID_DIE)->getSize();
	//< ������ ��
	m_DieAni_Info->frameCntX = 21;
	m_DieAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_DieAni_Info->aniSize.cx = dieAniSize.cx / m_DieAni_Info->frameCntX;
	m_DieAni_Info->aniSize.cy = dieAniSize.cy / m_DieAni_Info->frameCntY;
	m_DieAni_Info->frameSpeed = 50;
	m_DieAni_Info->nowFrame = 0;
	m_DieAni_Info->nowFrameY = DIR_D;
	m_DieAni_Info->lastTime = GetTickCount();
	m_DieAni_Info->flag=false;
	m_DieAni_Info->loop=false;
	m_DieAni_Info->playAni=false;

	//< Ÿ�� �ִϸ��̼�
	SAFE_DELETE( m_HitAni_Info );
	m_HitAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE hitAniSize = RC_MGR->findImage(imgID_HITEFF1)->getSize();
	//< ������ ��
	m_HitAni_Info->frameCntX = 6;
	m_HitAni_Info->frameCntY = 1;
	//< �����Ӵ� �̹��� ������
	m_HitAni_Info->aniSize.cx = hitAniSize.cx / m_HitAni_Info->frameCntX;
	m_HitAni_Info->aniSize.cy = hitAniSize.cy / m_HitAni_Info->frameCntY;
	m_HitAni_Info->frameSpeed = 50;
	m_HitAni_Info->nowFrame = 0;
	m_HitAni_Info->nowFrameY = 0;
	m_HitAni_Info->lastTime = GetTickCount();
	m_HitAni_Info->flag=false;
	m_HitAni_Info->loop=false;
	m_HitAni_Info->playAni=true;
}