#include "stdafx.h"

#include "../cProjectile.h"
//#include "skill_collum.h"
//#include "skill_destruction.h"
#include "Boss_gyuriel.h"


Gyuriel::Gyuriel(void)
	: ball(nullptr)
{
	init();
}
Gyuriel::~Gyuriel(void)
{
	release();
}

//< �ʱ�ȭ
bool Gyuriel::init(void)
{
	//�̹��� �߰�
	RC_MGR->addImage( imgID_BOSS_GYURIEL_IDLE, L"Data/Resource/monster/gyuriel/201-idle.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_BOSS_GYURIEL_MOVE, L"Data/Resource/monster/gyuriel/201-walk.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_GYURIEL_ATK, L"Data/Resource/monster/gyuriel/201-attack.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_GYURIEL_BEHIT, L"Data/Resource/monster/gyuriel/201-gethit.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_GYURIEL_DIE, L"Data/Resource/monster/gyuriel/201-die.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_BOSS_GYURIEL_SPECIAL, L"Data/Resource/monster/gyuriel/201-special.bmp", 0, 0 , RM_TRANS );
	//< ����
	m_stateFlag = STATE_IDLE;

	//< �������ͽ�
	//< ü��
	setMaxHP( 800 );
	setHP( 800 );
	//< ����
	setMaxMP( 100 );
	setMP( 100 );
	//< ����ġ
	m_exp = 100;

	//< �ν� ����
	m_recogRange = 500;
	//< ���� ��Ÿ�
	m_attRange = 400;
	//< �̵� �ӵ�
	setMoveSpeed( BOSS_1_MOVE_SPEED );
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< ���� �浹ü
	if( NULL == ball )
	{
		ball = new cProjectile(5, m_attRange);
	}
	//< ���� ��ų
	if( NULL == m_skill_collum )
	{
		m_skill_collum = new cProjectile(); //skill_collum();
	}
	//< ��ü ��ų
	if( NULL == m_skill_destruction )
	{
		m_skill_destruction = new cProjectile(); //skill_destruction();
	}

	//< ������
	attDeley.m_deley = attDeley.m_lastTime = 400;
	m_collum_deley.m_deley = m_collum_deley.m_lastTime = 360;
	m_destroy_deley.m_deley = m_destroy_deley.m_lastTime = 1000;

	//< ����
	m_kindNum = BOSS_GYURIEL;

	setAniInfo();
	
	return true;
}

//< ����
void Gyuriel::release(void)
{
	SAFE_DELETE( ball );
	SAFE_DELETE( m_skill_collum );
	SAFE_DELETE( m_skill_destruction );
	releaseAniInfo();
}

//< ������Ʈ
void Gyuriel::update(float fDeltaTime)
{
	//< �ִϸ��̼� ����
	AniMgr::UpdateAni(m_IdleAni_Info);
	AniMgr::UpdateAni(m_MoveAni_Info);
	AniMgr::UpdateAni(m_AtckAni_Info);
	AniMgr::UpdateAni(m_beHitAni_Info);
	AniMgr::UpdateAni(m_DieAni_Info);
	AniMgr::UpdateAni(m_HitAni_Info);
	AniMgr::UpdateAni(m_spclAni_info);
	//SOUND_MGR->soundUpdate();
}

//< ����
void Gyuriel::render(HDC hdc)
{
	if( m_beHitAni_Info->flag == true )
	{
		SIZE siz = m_beHitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_BOSS_GYURIEL_BEHIT,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
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
				RENDER_MGR->render( hdc, imgID_BOSS_GYURIEL_IDLE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
					siz.cx, siz.cy,
					m_IdleAni_Info->nowFrame *	siz.cx,	m_IdleAni_Info->nowFrameY * siz.cy,
					siz.cx, siz.cy);
			}
			break;
		case STATE_ATTACK:
			{
				if( m_spclAni_info->flag == true )
				{
					SIZE siz = m_spclAni_info->aniSize;
					RENDER_MGR->render( hdc, imgID_BOSS_GYURIEL_SPECIAL,
						m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
						siz.cx, siz.cy,
						m_spclAni_info->nowFrame *	siz.cx,	m_dir * siz.cy,
						siz.cx, siz.cy);
				}
				else
				{
					SIZE siz = m_AtckAni_Info->aniSize;
					RENDER_MGR->render( hdc, imgID_BOSS_GYURIEL_ATK,
						m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
						siz.cx, siz.cy,
						m_AtckAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
						siz.cx, siz.cy);
				}
			}
			break;
		case STATE_CHASE:
			{
				SIZE siz = m_MoveAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_BOSS_GYURIEL_MOVE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
					siz.cx, siz.cy,
					m_MoveAni_Info->nowFrame *	siz.cx,	m_dir * siz.cy,
					siz.cx, siz.cy);
			}
			break;
		case STATE_DIE:
			{
				SIZE siz = m_DieAni_Info->aniSize;
				RENDER_MGR->render( hdc, imgID_BOSS_GYURIEL_DIE,
					m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
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
		RENDER_MGR->render( hdc, imgID_HITEFF1,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
			siz.cx, siz.cy,
			m_HitAni_Info->nowFrame * siz.cx, 0,
			siz.cx, siz.cy);
	}

	//< ���� HP ǥ��
	renderHPbar(hdc);

	//�⺻ ���� ����
	ball->render(hdc);

	//< ��ų ����
	m_skill_collum->render(hdc);
	m_skill_destruction->render(hdc);
}

//< �浹 üũ
bool Gyuriel::collision( POINT &destPos )
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
void Gyuriel::attack( POINT &destPos )
{
	//< ��ų ������
	if (m_destroy_deley.m_deley <= m_destroy_deley.m_lastTime++)
	{
		//< ���� �����̸� ����
		if (m_stateFlag == STATE_ATTACK)
		{
			//< �����ϰ� ī��Ʈ �ʱ�ȭ
			m_destroy_deley.m_lastTime = 0;
			m_skill_destruction->shoot(m_pos, destPos);
			m_spclAni_info->flag = true;

			LOG_MGR->addLog("[SEND] P2P_GYURIEL_SKILL_01");
		}
	}
	if (m_collum_deley.m_deley <= m_collum_deley.m_lastTime++)
	{
		//< ���� �����̸� ����
		if (m_stateFlag == STATE_ATTACK)
		{
			//< �����ϰ� ī��Ʈ �ʱ�ȭ
			m_collum_deley.m_lastTime = 0;
			m_skill_collum->shoot(m_pos, destPos);
			m_spclAni_info->flag = true;

			LOG_MGR->addLog("[SEND] P2P_GYURIEL_SKILL_02");
		}
	}
	//< �⺻ ���� ������
	if (attDeley.m_deley <= attDeley.m_lastTime++)
	{
		//< ���� �����̸� ����
		if (m_stateFlag == STATE_ATTACK)
		{
			attDeley.m_lastTime = 0;
			ball->shoot(m_pos, destPos);
			m_AtckAni_Info->flag = true;
			//SOUND_MGR->soundPlay(BOSS_ATK);

			LOG_MGR->addLog("[SEND] P2P_GYURIEL_ATTACK");
		}
	}

	//�浹ü ����
	ball->update();
	m_skill_collum->update();
	m_skill_destruction->update();
}
//< �ν�
void Gyuriel::recog( POINT &destPos )
{
	//< ����ִٸ�
	if( m_stateFlag != STATE_DIE )
	{
		//< ��� �÷��̾���� �Ÿ� ���ϱ�
		float distance = math::distancePtToPt( m_pos, destPos );

		//< ĳ���Ͱ� ���� ���� �ȿ� ������ ���ݻ���
		if( distance <= m_attRange )
		{
			//< ���� ���
			calcDir(destPos);
			m_stateFlag = STATE_ATTACK;
		}
		else
		{
			//< ĳ���Ͱ� �ν� ���� �ȿ� ������ ���� ���·�
			if( distance <= m_recogRange )
			{
				//< ���� ���
				calcDir(destPos);
				//< ���� ���̸� ��ȭ ����
				if( m_spclAni_info->flag == false )
				{
					m_stateFlag = STATE_CHASE;
				}
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
bool Gyuriel::beHit(int damage)	
{
	//< �̹� �׾��ִٸ� false ����
	if( m_stateFlag == STATE_DIE )
	{
		return false;
	}
	//< ����ִٸ� HP ����
	m_state.m_nowHP -= damage;  
	//�ǰ� ����
	//SOUND_MGR->soundPlay(BOSS_HIT);
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
		//SOUND_MGR->soundPlay(BOSS_DIE);
		return true;
	}
	return false;
}

//< HP �� ����
void Gyuriel::renderHPbar(HDC hdc)
{
	if( hpRenderFlag == true )
	{
		//< �� ������Ʈ
		HPEN myPen, oldPen;
		myPen = CreatePen( PS_SOLID, 10, RGB(255,255,255) );
		oldPen = (HPEN)SelectObject(hdc, myPen);

		//< ��ü HP
		MoveToEx( hdc, m_pos.x - 80 - CAMERA->getX(), m_pos.y - 200 - CAMERA->getY(), NULL );
		LineTo( hdc, m_pos.x + 80 - CAMERA->getX() , m_pos.y - 200 - CAMERA->getY() );

		//< ������Ʈ ����
		DeleteObject( SelectObject(hdc, oldPen) );

		myPen = CreatePen( PS_SOLID, 7, RGB(255,0,0) );
		oldPen = (HPEN)SelectObject(hdc, myPen);

		//< HP �ۼ�������
		int HPper = static_cast<int>(150 * (getHP() / static_cast<float>(getMaxHP())));
		//< ���� HP
		//< 0�̻��� ���� ����
		if( HPper > 0 )
		{
			MoveToEx( hdc, m_pos.x - 75 - CAMERA->getX(), m_pos.y - 200 - CAMERA->getY(), NULL );
			LineTo( hdc, m_pos.x -75 + HPper - CAMERA->getX() , m_pos.y - 200 - CAMERA->getY() );
		}

		//< ������Ʈ ����
		DeleteObject( SelectObject(hdc, oldPen) );

		if( hpRenderDeley.m_lastTime + hpRenderDeley.m_deley < GetTickCount() )
		{
			hpRenderFlag = false;
		}
	}
}

//< ���� ��Ʈ ��ȯ
RECT Gyuriel::getRect( void )
{
	RECT rt;
	SetRect(&rt, 
		m_pos.x - MONSTER_SIZE*2, m_pos.y - MONSTER_SIZE*2,
		m_pos.x + MONSTER_SIZE*2, m_pos.y + MONSTER_SIZE*2);

	return rt;
}

//< ���� �浹ü ��Ʈ ��ȯ
RECT Gyuriel::getBallRect(void)
{
	if( m_skill_destruction->getFlag() == true )
	{
		return m_skill_destruction->getRect();
	}
	if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getRect();
	}
	return ball->getRect();
}

//< �浹ü ����
void Gyuriel::setBallFlag( bool flag )
{
	ball->setFlag( flag );
	ball->setPos(m_pos);
}
bool Gyuriel::getBallFlag( void )
{
	if( m_skill_destruction->getFlag() == true )
	{
		return m_skill_destruction->getFlag();
	}
	if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getFlag();
	}
	return ball->getFlag();
}
//< ������
int Gyuriel::getDamage(void)
{
	if( m_skill_destruction->getFlag() == true )
	{
		return m_skill_destruction->getDamage();
	}
	if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getDamage();
	}
	return ball->getDamage();
}

void Gyuriel::setAniInfo( void )
{
	//< ���̵� �ִϸ��̼�
	SAFE_DELETE( m_IdleAni_Info );
	m_IdleAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE idleAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_IDLE)->getSize();
	//< ������ ��
	m_IdleAni_Info->frameCntX = 16;
	m_IdleAni_Info->frameCntY = 1;
	//< �����Ӵ� �̹��� ������
	m_IdleAni_Info->aniSize.cx = idleAniSize.cx / m_IdleAni_Info->frameCntX;
	m_IdleAni_Info->aniSize.cy = idleAniSize.cy / m_IdleAni_Info->frameCntY;

	m_IdleAni_Info->frameSpeed = 50;
	m_IdleAni_Info->nowFrame = 0;
	m_IdleAni_Info->nowFrameY = 0;
	m_IdleAni_Info->lastTime = GetTickCount();
	m_IdleAni_Info->flag=true;
	m_IdleAni_Info->loop=true;
	m_IdleAni_Info->playAni=true;

	//< �̵� �ִϸ��̼�
	SAFE_DELETE( m_MoveAni_Info );
	m_MoveAni_Info = new ANI_INFO;
	//< �̹��� ������
	SIZE moveAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_MOVE)->getSize();
	//< ������ ��
	m_MoveAni_Info->frameCntX = 6;
	m_MoveAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_MoveAni_Info->aniSize.cx = moveAniSize.cx / m_MoveAni_Info->frameCntX;
	m_MoveAni_Info->aniSize.cy = moveAniSize.cy / m_MoveAni_Info->frameCntY;
	
	m_MoveAni_Info->frameSpeed = 100;
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
	SIZE atkAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_ATK)->getSize();
	//< ������ ��
	m_AtckAni_Info->frameCntX = 16;
	m_AtckAni_Info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_AtckAni_Info->aniSize.cx = atkAniSize.cx / m_AtckAni_Info->frameCntX;
	m_AtckAni_Info->aniSize.cy = atkAniSize.cy / m_AtckAni_Info->frameCntY;
	m_AtckAni_Info->frameSpeed = 70;
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
	SIZE behitAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_BEHIT)->getSize();
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
	SIZE dieAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_DIE)->getSize();
	//< ������ ��
	m_DieAni_Info->frameCntX = 16;
	m_DieAni_Info->frameCntY = 1;
	//< �����Ӵ� �̹��� ������
	m_DieAni_Info->aniSize.cx = dieAniSize.cx / m_DieAni_Info->frameCntX;
	m_DieAni_Info->aniSize.cy = dieAniSize.cy / m_DieAni_Info->frameCntY;
	m_DieAni_Info->frameSpeed = 100;
	m_DieAni_Info->nowFrame = 0;
	m_DieAni_Info->nowFrameY = 0;
	m_DieAni_Info->lastTime = GetTickCount();
	m_DieAni_Info->flag=false;
	m_DieAni_Info->loop=false;
	m_DieAni_Info->playAni=false;

	//< ����� �ִϸ��̼�
	SAFE_DELETE( m_spclAni_info );
	m_spclAni_info = new ANI_INFO;
	//< �̹��� ������
	SIZE spclAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_SPECIAL)->getSize();
	//< ������ ��
	m_spclAni_info->frameCntX = 16;
	m_spclAni_info->frameCntY = 8;
	//< �����Ӵ� �̹��� ������
	m_spclAni_info->aniSize.cx = spclAniSize.cx / m_spclAni_info->frameCntX;
	m_spclAni_info->aniSize.cy = spclAniSize.cy / m_spclAni_info->frameCntY;
	m_spclAni_info->frameSpeed = 80;
	m_spclAni_info->nowFrame = 0;
	m_spclAni_info->nowFrameY = DIR_D;
	m_spclAni_info->lastTime = GetTickCount();
	m_spclAni_info->flag=false;
	m_spclAni_info->loop=false;
	m_spclAni_info->playAni=true;

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

//����
void Gyuriel::releaseAniInfo( void )
{
	Monster::releaseAniInfo();
	SAFE_DELETE( m_spclAni_info );
}

//< ������ ���
//< ����
void Gyuriel::normalAttack(POINT &destPos)
{
	ball->shoot( m_pos , destPos );
	m_AtckAni_Info->flag=true;
}

//< ��ų 1
void Gyuriel::skill_01(POINT &destPos)
{
	m_skill_destruction->shoot( m_pos , destPos );
	m_spclAni_info->flag=true;
}

//< ��ų 2
void Gyuriel::skill_02(POINT &destPos)
{
	m_skill_collum->shoot( m_pos , destPos );
	m_spclAni_info->flag=true;
}
