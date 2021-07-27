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

//< 초기화
bool Gyuriel::init(void)
{
	//이미지 추가
	RC_MGR->addImage( imgID_BOSS_GYURIEL_IDLE, L"Data/Resource/monster/gyuriel/201-idle.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_BOSS_GYURIEL_MOVE, L"Data/Resource/monster/gyuriel/201-walk.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_GYURIEL_ATK, L"Data/Resource/monster/gyuriel/201-attack.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_GYURIEL_BEHIT, L"Data/Resource/monster/gyuriel/201-gethit.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_GYURIEL_DIE, L"Data/Resource/monster/gyuriel/201-die.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_BOSS_GYURIEL_SPECIAL, L"Data/Resource/monster/gyuriel/201-special.bmp", 0, 0 , RM_TRANS );
	//< 상태
	m_stateFlag = STATE_IDLE;

	//< 스테이터스
	//< 체력
	setMaxHP( 800 );
	setHP( 800 );
	//< 마력
	setMaxMP( 100 );
	setMP( 100 );
	//< 경험치
	m_exp = 100;

	//< 인식 범위
	m_recogRange = 500;
	//< 공격 사거리
	m_attRange = 400;
	//< 이동 속도
	setMoveSpeed( BOSS_1_MOVE_SPEED );
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< 공격 충돌체
	if( NULL == ball )
	{
		ball = new cProjectile(5, m_attRange);
	}
	//< 공격 스킬
	if( NULL == m_skill_collum )
	{
		m_skill_collum = new cProjectile(); //skill_collum();
	}
	//< 전체 스킬
	if( NULL == m_skill_destruction )
	{
		m_skill_destruction = new cProjectile(); //skill_destruction();
	}

	//< 딜레이
	attDeley.m_deley = attDeley.m_lastTime = 400;
	m_collum_deley.m_deley = m_collum_deley.m_lastTime = 360;
	m_destroy_deley.m_deley = m_destroy_deley.m_lastTime = 1000;

	//< 종류
	m_kindNum = BOSS_GYURIEL;

	setAniInfo();
	
	return true;
}

//< 해제
void Gyuriel::release(void)
{
	SAFE_DELETE( ball );
	SAFE_DELETE( m_skill_collum );
	SAFE_DELETE( m_skill_destruction );
	releaseAniInfo();
}

//< 업데이트
void Gyuriel::update(float fDeltaTime)
{
	//< 애니메이션 갱신
	AniMgr::UpdateAni(m_IdleAni_Info);
	AniMgr::UpdateAni(m_MoveAni_Info);
	AniMgr::UpdateAni(m_AtckAni_Info);
	AniMgr::UpdateAni(m_beHitAni_Info);
	AniMgr::UpdateAni(m_DieAni_Info);
	AniMgr::UpdateAni(m_HitAni_Info);
	AniMgr::UpdateAni(m_spclAni_info);
	//SOUND_MGR->soundUpdate();
}

//< 랜더
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

	//< 피격 이펙트
	if( m_HitAni_Info->flag == true )
	{
		SIZE siz = m_HitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_HITEFF1,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - 100 - CAMERA->getY(),
			siz.cx, siz.cy,
			m_HitAni_Info->nowFrame * siz.cx, 0,
			siz.cx, siz.cy);
	}

	//< 남은 HP 표시
	renderHPbar(hdc);

	//기본 공격 랜더
	ball->render(hdc);

	//< 스킬 랜더
	m_skill_collum->render(hdc);
	m_skill_destruction->render(hdc);
}

//< 충돌 체크
bool Gyuriel::collision( POINT &destPos )
{
	//< 대상 플레이어와의 거리 구하기
	float distance = math::distancePtToPt( m_pos, destPos );

	//< 캐릭터와 충돌
	if( distance <= CHARACTER_SIZE + MONSTER_SIZE )
	{
		if( m_stateFlag == STATE_DIE )
		{
			//< 몬스터가 죽었다면 충돌처리하지 않음
			return false;
		}
		else
		{
			//< 몬스터가 살아있다면 충돌체크
			return true;
		}
	}
	return false;
}

//< 공격
void Gyuriel::attack( POINT &destPos )
{
	//< 스킬 딜레이
	if (m_destroy_deley.m_deley <= m_destroy_deley.m_lastTime++)
	{
		//< 공격 상태이면 공격
		if (m_stateFlag == STATE_ATTACK)
		{
			//< 공격하고 카운트 초기화
			m_destroy_deley.m_lastTime = 0;
			m_skill_destruction->shoot(m_pos, destPos);
			m_spclAni_info->flag = true;

			LOG_MGR->addLog("[SEND] P2P_GYURIEL_SKILL_01");
		}
	}
	if (m_collum_deley.m_deley <= m_collum_deley.m_lastTime++)
	{
		//< 공격 상태이면 공격
		if (m_stateFlag == STATE_ATTACK)
		{
			//< 공격하고 카운트 초기화
			m_collum_deley.m_lastTime = 0;
			m_skill_collum->shoot(m_pos, destPos);
			m_spclAni_info->flag = true;

			LOG_MGR->addLog("[SEND] P2P_GYURIEL_SKILL_02");
		}
	}
	//< 기본 공격 딜레이
	if (attDeley.m_deley <= attDeley.m_lastTime++)
	{
		//< 공격 상태이면 공격
		if (m_stateFlag == STATE_ATTACK)
		{
			attDeley.m_lastTime = 0;
			ball->shoot(m_pos, destPos);
			m_AtckAni_Info->flag = true;
			//SOUND_MGR->soundPlay(BOSS_ATK);

			LOG_MGR->addLog("[SEND] P2P_GYURIEL_ATTACK");
		}
	}

	//충돌체 갱신
	ball->update();
	m_skill_collum->update();
	m_skill_destruction->update();
}
//< 인식
void Gyuriel::recog( POINT &destPos )
{
	//< 살아있다면
	if( m_stateFlag != STATE_DIE )
	{
		//< 대상 플레이어와의 거리 구하기
		float distance = math::distancePtToPt( m_pos, destPos );

		//< 캐릭터가 공격 범위 안에 들어오면 공격상태
		if( distance <= m_attRange )
		{
			//< 방향 계산
			calcDir(destPos);
			m_stateFlag = STATE_ATTACK;
		}
		else
		{
			//< 캐릭터가 인식 범위 안에 들어오면 추적 상태로
			if( distance <= m_recogRange )
			{
				//< 방향 계산
				calcDir(destPos);
				//< 공격 중이면 변화 없음
				if( m_spclAni_info->flag == false )
				{
					m_stateFlag = STATE_CHASE;
				}
			}
			else
			{				
				//< 밖으로 나가면 다시 원상태로
				m_stateFlag = STATE_IDLE ;				
			}
		}
	}
}

//< 타격
bool Gyuriel::beHit(int damage)	
{
	//< 이미 죽어있다면 false 리턴
	if( m_stateFlag == STATE_DIE )
	{
		return false;
	}
	//< 살아있다면 HP 감소
	m_state.m_nowHP -= damage;  
	//피격 사운드
	//SOUND_MGR->soundPlay(BOSS_HIT);
	//< 피격 이펙트
	m_HitAni_Info->flag=true;
	m_beHitAni_Info->flag=true;
	//< HP 바 랜더 시작
	hpRenderStart();
	//< 죽었다면 true 리턴
	if( getHP() <= 0 )
	{
    	setHP( 0 );
		m_stateFlag = STATE_DIE;
		m_DieAni_Info->flag = true;
		//사망 사운드
		//SOUND_MGR->soundPlay(BOSS_DIE);
		return true;
	}
	return false;
}

//< HP 바 랜더
void Gyuriel::renderHPbar(HDC hdc)
{
	if( hpRenderFlag == true )
	{
		//< 펜 오브젝트
		HPEN myPen, oldPen;
		myPen = CreatePen( PS_SOLID, 10, RGB(255,255,255) );
		oldPen = (HPEN)SelectObject(hdc, myPen);

		//< 전체 HP
		MoveToEx( hdc, m_pos.x - 80 - CAMERA->getX(), m_pos.y - 200 - CAMERA->getY(), NULL );
		LineTo( hdc, m_pos.x + 80 - CAMERA->getX() , m_pos.y - 200 - CAMERA->getY() );

		//< 오브젝트 삭제
		DeleteObject( SelectObject(hdc, oldPen) );

		myPen = CreatePen( PS_SOLID, 7, RGB(255,0,0) );
		oldPen = (HPEN)SelectObject(hdc, myPen);

		//< HP 퍼센테이지
		int HPper = static_cast<int>(150 * (getHP() / static_cast<float>(getMaxHP())));
		//< 남은 HP
		//< 0이상일 때만 랜더
		if( HPper > 0 )
		{
			MoveToEx( hdc, m_pos.x - 75 - CAMERA->getX(), m_pos.y - 200 - CAMERA->getY(), NULL );
			LineTo( hdc, m_pos.x -75 + HPper - CAMERA->getX() , m_pos.y - 200 - CAMERA->getY() );
		}

		//< 오브젝트 삭제
		DeleteObject( SelectObject(hdc, oldPen) );

		if( hpRenderDeley.m_lastTime + hpRenderDeley.m_deley < GetTickCount() )
		{
			hpRenderFlag = false;
		}
	}
}

//< 몬스터 렉트 반환
RECT Gyuriel::getRect( void )
{
	RECT rt;
	SetRect(&rt, 
		m_pos.x - MONSTER_SIZE*2, m_pos.y - MONSTER_SIZE*2,
		m_pos.x + MONSTER_SIZE*2, m_pos.y + MONSTER_SIZE*2);

	return rt;
}

//< 공격 충돌체 렉트 반환
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

//< 충돌체 상태
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
//< 데미지
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
	//< 아이들 애니메이션
	SAFE_DELETE( m_IdleAni_Info );
	m_IdleAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE idleAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_IDLE)->getSize();
	//< 프레임 수
	m_IdleAni_Info->frameCntX = 16;
	m_IdleAni_Info->frameCntY = 1;
	//< 프레임당 이미지 사이즈
	m_IdleAni_Info->aniSize.cx = idleAniSize.cx / m_IdleAni_Info->frameCntX;
	m_IdleAni_Info->aniSize.cy = idleAniSize.cy / m_IdleAni_Info->frameCntY;

	m_IdleAni_Info->frameSpeed = 50;
	m_IdleAni_Info->nowFrame = 0;
	m_IdleAni_Info->nowFrameY = 0;
	m_IdleAni_Info->lastTime = GetTickCount();
	m_IdleAni_Info->flag=true;
	m_IdleAni_Info->loop=true;
	m_IdleAni_Info->playAni=true;

	//< 이동 애니메이션
	SAFE_DELETE( m_MoveAni_Info );
	m_MoveAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE moveAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_MOVE)->getSize();
	//< 프레임 수
	m_MoveAni_Info->frameCntX = 6;
	m_MoveAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_MoveAni_Info->aniSize.cx = moveAniSize.cx / m_MoveAni_Info->frameCntX;
	m_MoveAni_Info->aniSize.cy = moveAniSize.cy / m_MoveAni_Info->frameCntY;
	
	m_MoveAni_Info->frameSpeed = 100;
	m_MoveAni_Info->nowFrame = 0;
	m_MoveAni_Info->nowFrameY = DIR_D;
	m_MoveAni_Info->lastTime = GetTickCount();
	m_MoveAni_Info->flag=false;
	m_MoveAni_Info->loop=false;
	m_MoveAni_Info->playAni=true;

	//< 공격 애니메이션
	SAFE_DELETE( m_AtckAni_Info );
	m_AtckAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE atkAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_ATK)->getSize();
	//< 프레임 수
	m_AtckAni_Info->frameCntX = 16;
	m_AtckAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_AtckAni_Info->aniSize.cx = atkAniSize.cx / m_AtckAni_Info->frameCntX;
	m_AtckAni_Info->aniSize.cy = atkAniSize.cy / m_AtckAni_Info->frameCntY;
	m_AtckAni_Info->frameSpeed = 70;
	m_AtckAni_Info->nowFrame = 0;
	m_AtckAni_Info->nowFrameY = DIR_D;
	m_AtckAni_Info->lastTime = GetTickCount();
	m_AtckAni_Info->flag=false;
	m_AtckAni_Info->loop=false;
	m_AtckAni_Info->playAni=true;

	//< 피격 애니메이션
	SAFE_DELETE( m_beHitAni_Info );
	m_beHitAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE behitAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_BEHIT)->getSize();
	//< 프레임 수
	m_beHitAni_Info->frameCntX = 6;
	m_beHitAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_beHitAni_Info->aniSize.cx = behitAniSize.cx / m_beHitAni_Info->frameCntX;
	m_beHitAni_Info->aniSize.cy = behitAniSize.cy / m_beHitAni_Info->frameCntY;
	m_beHitAni_Info->frameSpeed = 50;
	m_beHitAni_Info->nowFrame = 0;
	m_beHitAni_Info->nowFrameY = DIR_D;
	m_beHitAni_Info->lastTime = GetTickCount();
	m_beHitAni_Info->flag=false;
	m_beHitAni_Info->loop=false;
	m_beHitAni_Info->playAni=true;

	//< 사망 애니메이션
	SAFE_DELETE( m_DieAni_Info );
	m_DieAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE dieAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_DIE)->getSize();
	//< 프레임 수
	m_DieAni_Info->frameCntX = 16;
	m_DieAni_Info->frameCntY = 1;
	//< 프레임당 이미지 사이즈
	m_DieAni_Info->aniSize.cx = dieAniSize.cx / m_DieAni_Info->frameCntX;
	m_DieAni_Info->aniSize.cy = dieAniSize.cy / m_DieAni_Info->frameCntY;
	m_DieAni_Info->frameSpeed = 100;
	m_DieAni_Info->nowFrame = 0;
	m_DieAni_Info->nowFrameY = 0;
	m_DieAni_Info->lastTime = GetTickCount();
	m_DieAni_Info->flag=false;
	m_DieAni_Info->loop=false;
	m_DieAni_Info->playAni=false;

	//< 스페셜 애니메이션
	SAFE_DELETE( m_spclAni_info );
	m_spclAni_info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE spclAniSize = RC_MGR->findImage(imgID_BOSS_GYURIEL_SPECIAL)->getSize();
	//< 프레임 수
	m_spclAni_info->frameCntX = 16;
	m_spclAni_info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_spclAni_info->aniSize.cx = spclAniSize.cx / m_spclAni_info->frameCntX;
	m_spclAni_info->aniSize.cy = spclAniSize.cy / m_spclAni_info->frameCntY;
	m_spclAni_info->frameSpeed = 80;
	m_spclAni_info->nowFrame = 0;
	m_spclAni_info->nowFrameY = DIR_D;
	m_spclAni_info->lastTime = GetTickCount();
	m_spclAni_info->flag=false;
	m_spclAni_info->loop=false;
	m_spclAni_info->playAni=true;

	//< 타격 애니메이션
	SAFE_DELETE( m_HitAni_Info );
	m_HitAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE hitAniSize = RC_MGR->findImage(imgID_HITEFF1)->getSize();
	//< 프레임 수
	m_HitAni_Info->frameCntX = 6;
	m_HitAni_Info->frameCntY = 1;
	//< 프레임당 이미지 사이즈
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

//해제
void Gyuriel::releaseAniInfo( void )
{
	Monster::releaseAniInfo();
	SAFE_DELETE( m_spclAni_info );
}

//< 보스만 사용
//< 공격
void Gyuriel::normalAttack(POINT &destPos)
{
	ball->shoot( m_pos , destPos );
	m_AtckAni_Info->flag=true;
}

//< 스킬 1
void Gyuriel::skill_01(POINT &destPos)
{
	m_skill_destruction->shoot( m_pos , destPos );
	m_spclAni_info->flag=true;
}

//< 스킬 2
void Gyuriel::skill_02(POINT &destPos)
{
	m_skill_collum->shoot( m_pos , destPos );
	m_spclAni_info->flag=true;
}
