#include "stdafx.h"

#include "../sphereObject.h"
#include "mon_bug.h"


mon_bug::mon_bug(void)
	: ball(NULL)
{
	init();
}
mon_bug::~mon_bug(void)
{
	release();
}

//< �ʱ�ȭ
bool mon_bug::init(void)
{
	//< �̹��� �߰�
	RC_MGR->addImage( imgID_MONSTER_3_IDLE, "Data/Resource/monster/monster_bug/003-idle.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_MOVE, "Data/Resource/monster/monster_bug/003-walk.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_ATK, "Data/Resource/monster/monster_bug/003-attack.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_BEHIT, "Data/Resource/monster/monster_bug/003-gethit.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_DIE, "Data/Resource/monster/monster_bug/003-die.bmp", 0, 0 , RM_TRANS );
	//< ����
	m_stateFlag = STATE_IDLE;
	
	//< �������ͽ�
	//< ü��
	setMaxHP( 5 );
	setHP( 5 );
	//< ����
	setMaxMP( 50 );
	setMP( 50 );
	//< ����ġ
	m_exp = 3;

	//< �ν� ����
	m_recogRange = 400;
	//< ���� ��Ÿ�
	m_attRange = 55;
	//< �̵� �ӵ�
	setMoveSpeed( 4 );
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< ���� �浹ü
	if( NULL == ball )
	{
		ball = new cProjectile(10, m_attRange);
	}
	//< ������
	attDeley.m_deley = attDeley.m_lastTime = 30;

	//< ����
	m_kindNum = MON_BUG;

	//< �ִϸ��̼� ����
	setAniInfo();

	return true;
}
//< ����
void mon_bug::release(void)
{
	releaseAniInfo();
	SAFE_DELETE( ball );
}
//< ������Ʈ
void mon_bug::update(float fDeltaTime)
{
	//< �ִϸ��̼� ����
	updateAni( m_IdleAni_Info );
	updateAni( m_MoveAni_Info );
	updateAni( m_AtckAni_Info );
	updateAni( m_beHitAni_Info );
	updateAni( m_DieAni_Info );
	updateAni( m_HitAni_Info );
}
//< ����
void mon_bug::render(HDC hdc)
{
	if( m_beHitAni_Info->flag == true )
	{
		SIZE siz = m_beHitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_MONSTER_3_BEHIT,
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
				RENDER_MGR->render( hdc, imgID_MONSTER_3_IDLE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_IdleAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
				break;
			}
		case STATE_ATTACK:
			{
				SIZE siz = m_AtckAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_MONSTER_3_ATK,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_AtckAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
				break;
			}
		case STATE_CHASE:
			{
				SIZE siz = m_MoveAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_MONSTER_3_MOVE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_MoveAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
				break;
			}
		case STATE_DIE:
			{
				SIZE siz = m_DieAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_MONSTER_3_DIE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - RENDER_OFFSET_Y - CAMERA->getY(),
					siz.cx, siz.cy,
					m_DieAni_Info->nowFrame *	siz.cx,	m_DieAni_Info->nowFrameY * siz.cy,
					siz.cx, siz.cy);
			}
			break;
		}
	}
	//< �ǰ� ����Ʈ
	if( m_HitAni_Info->flag == true )
	{
		SIZE siz = m_HitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_GETHIT_3,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - CAMERA->getY(),
			siz.cx, siz.cy,
			m_HitAni_Info->nowFrame * siz.cx, 0,
			siz.cx, siz.cy);
	}
	//< ���� HP ǥ��
	renderHPbar(hdc);

	//���� �浹ü ����
	ball->render(hdc);
}

//< �浹 üũ
bool mon_bug::collision( POINT &destPos )
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
void mon_bug::attack( POINT &destPos )
{
	if( attDeley.m_deley <= attDeley.m_lastTime++ )
	{
		//< ���� �����̸� ����
		if( m_stateFlag == STATE_ATTACK )
		{
			attDeley.m_lastTime = 0;
			ball->shoot( m_pos , destPos );
			m_AtckAni_Info->flag = true;
			//SOUND_MGR->soundPlay(BUG_ATK);
		}
	}
	//��ü ����
	ball->update();
}
//< �ν�
void mon_bug::recog( POINT &destPos )
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
bool mon_bug::beHit(int damage)	
{
	//< �̹� �׾��ִٸ� false ����
	if( m_stateFlag == STATE_DIE )
	{
		return false;
	}
	//< ����ִٸ� HP ����
	m_state.m_nowHP -= damage; 
	//SOUND_MGR->soundPlay(BUG_HIT);
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
		//SOUND_MGR->soundPlay(BUG_DIE);
		return true;
	}
	return false;
}

//< ���� �浹ü ��Ʈ ��ȯ
RECT mon_bug::getBallRect(void)
{
	return ball->getRect();
}

//< �浹ü ����
void mon_bug::setBallFlag( bool flag )
{
	ball->setFlag( flag );
	ball->setPos(m_pos);
}
bool mon_bug::getBallFlag( void )
{
	return ball->getFlag();
}
//< ������
int mon_bug::getDamage(void)
{
	return ball->getDamage();
}

void mon_bug::setAniInfo( void )
{
	//< ���̵� �ִϸ��̼�
	SAFE_DELETE( m_IdleAni_Info );
	m_IdleAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE idleAniSize = RC_MGR->findImage(imgID_MONSTER_3_IDLE)->getSize();
	//< ������ ��
	m_IdleAni_Info->frameCntX = 10;
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
	SIZE moveAniSize = RC_MGR->findImage(imgID_MONSTER_3_MOVE)->getSize();
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
	SIZE atkAniSize = RC_MGR->findImage(imgID_MONSTER_3_ATK)->getSize();
	//< ������ ��
	m_AtckAni_Info->frameCntX = 12;
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
	SIZE behitAniSize = RC_MGR->findImage(imgID_MONSTER_3_BEHIT)->getSize();
	//< ������ ��
	m_beHitAni_Info->frameCntX = 6;
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
	SIZE dieAniSize = RC_MGR->findImage(imgID_MONSTER_3_DIE)->getSize();
	//< ������ ��
	m_DieAni_Info->frameCntX = 15;
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
	SIZE hitAniSize = RC_MGR->findImage(imgID_GETHIT_3)->getSize();
	//< ������ ��
	m_HitAni_Info->frameCntX = 6;
	m_HitAni_Info->frameCntY = 8;
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

void mon_bug::updateAni( LPANI_INFO info )
{
	if(NULL!=info && true == info->flag)
	{
		DWORD curTime = GetTickCount();

		if( info->lastTime + info->frameSpeed <= curTime )
		{
			info->nowFrame++;

			info->lastTime=curTime;

			if(info->frameCntX <= info->nowFrame)
			{
				if( info->playAni == false )
				{
					info->nowFrame=info->frameCntX-1;
					info->flag=false;
					return;
				}
				info->nowFrame=0;
				if( info->loop == false )
				{
					info->flag=false;
				}
			}
		}
	}
}