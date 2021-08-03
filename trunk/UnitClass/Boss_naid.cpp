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

//< 초기화
bool boss_naid::init(void)
{

	//이미지 추가
	RC_MGR->addImage( imgID_BOSS_NAID, L"Data/Resource/monster/naid/001-idle.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage(imgID_BOSS_MOVE, L"Data/Resource/monster/naid/001-walk.bmp",0,0,RM_TRANS);
	RC_MGR->addImage(imgID_BOSS_ATK, L"Data/Resource/monster/naid/001-special.bmp",0,0,RM_TRANS);
	RC_MGR->addImage(imgID_BOSS_BEHIT, L"Data/Resource/monster/naid/001-gethit.bmp",0,0,RM_TRANS);
	RC_MGR->addImage( imgID_BOSS_NAID_DIE, L"Data/Resource/monster/naid/001-die.bmp", 0, 0 , RM_TRANS );
	//< 상태
	m_stateFlag = STATE_IDLE;

	//< 스테이터스
	//< 체력
	setMaxHP(EStatus_Base, 200);
	setHP(getMaxHP());
	//< 마력
	setMaxMP(EStatus_Base, 100);
	setMP( 100 );
	//< 경험치
	m_exp = 100;

	//< 인식 범위
	m_recogRange = 700;
	//< 공격 사거리
	m_attRange = 70;
	//< 이동 속도
	setMoveSpeed(EStatus_Base, BOSS_1_MOVE_SPEED);
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< 공격 충돌체
	if( NULL == ball )
	{
		ball = new cProjectile(5, m_attRange);
	}
	//< 전체 스킬
	/*if( NULL == m_skill_collum )
	{
		m_skill_collum = new skill_naid_collum();
	}*/

	//< 딜레이
	attDeley.m_deley = attDeley.m_lastTime = 90;
	m_collum_deley.m_deley = m_collum_deley.m_lastTime = 360;

	//< 종류
	m_kindNum = BOSS_NAID;

	setAniInfo();
	return true;
}
//< 해제
void boss_naid::release(void)
{
	SAFE_DELETE( ball );
	//SAFE_DELETE( m_skill_collum );
	releaseAniInfo();
}
//< 업데이트
void boss_naid::update( void )
{
	//< 애니메이션 갱신
	AniMgr::UpdateAni( m_IdleAni_Info );
	AniMgr::UpdateAni( m_MoveAni_Info );
	AniMgr::UpdateAni( m_AtckAni_Info );
	AniMgr::UpdateAni( m_beHitAni_Info );
	AniMgr::UpdateAni( m_DieAni_Info );
	AniMgr::UpdateAni( m_HitAni_Info );
}
//< 랜더
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
	//< 피격 이펙트
	if( m_HitAni_Info->flag == true )
	{
		SIZE siz = m_HitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_HITEFF1,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - CAMERA->getY(),
			siz.cx, siz.cy,
			m_HitAni_Info->nowFrame * siz.cx, 0,
			siz.cx, siz.cy);
	}
	//< 남은 HP 표시
	renderHPbar(hdc);

	//기본 공격 랜더
	ball->render(hdc);
	//< 스킬 랜더
	//m_skill_collum->render(hdc);
}

//< 충돌 체크
bool boss_naid::collision( POINT &destPos )
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
void boss_naid::attack( POINT &destPos )
{
	//< 스킬 딜레이
	if( m_collum_deley.m_deley <= m_collum_deley.m_lastTime++ )
	{
		//< 공격 상태이면 공격
		if( m_stateFlag == STATE_ATTACK )
		{
			//< 공격하고 카운트 초기화
			m_collum_deley.m_lastTime = 0;
			//m_skill_collum->shoot( m_pos , destPos );
			m_AtckAni_Info->flag=true;
			//공격 사운드
			//SOUND_MGR->soundPlay(NAID_ATK);
		}
	}
	//< 기본 공격 딜레이
	else if( attDeley.m_deley <= attDeley.m_lastTime++ )
	{
		//< 공격 상태이면 공격
		if( m_stateFlag == STATE_ATTACK )
		{
			attDeley.m_lastTime = 0;
			ball->shoot( m_pos , destPos );
			m_AtckAni_Info->flag=true;
		}
	}
	//충돌체 갱신
	ball->update();
	//m_skill_collum->update();
}
//< 인식
void boss_naid::recog( POINT &destPos )
{
	//< 살아있다면
	if( m_stateFlag != STATE_DIE )
	{
		//< 대상 플레이어와의 거리 구하기
		float distance = math::distancePtToPt( m_pos, destPos );

		//< 캐릭터가 공격 범위 안에 들어오면 공격상태
		if( distance <= m_attRange )
		{
			m_stateFlag = STATE_ATTACK;
		}
		else
		{
			//< 캐릭터가 인식 범위 안에 들어오면 추적 상태로
			if( distance <= m_recogRange )
			{
				//< 방향 계산
				calcDir(destPos);
				m_stateFlag = STATE_CHASE;				
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
bool boss_naid::beHit(int damage)	
{
	//< 이미 죽어있다면 false 리턴
	if( m_stateFlag == STATE_DIE )
	{
		return false;
	}
	//< 살아있다면 HP 감소
	incHP(-damage);  
	//피격 사운드
	//SOUND_MGR->soundPlay(NAID_HIT);
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
		//SOUND_MGR->soundPlay(NAID_DIE);
		return true;
	}
	return false;
}

//< 공격 충돌체 렉트 반환
RECT boss_naid::getBallRect(void)
{
	/*if( m_skill_collum->getFlag() == true )
	{
		return m_skill_collum->getRect();
	}*/
	return ball->getRect();
}

//< 충돌체 상태
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
//< 데미지
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
	//< 아이들 애니메이션
	SAFE_DELETE( m_IdleAni_Info );
	m_IdleAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE idleAniSize = RC_MGR->findImage(imgID_BOSS_NAID)->getSize();
	//< 프레임 수
	m_IdleAni_Info->frameCntX = 12;
	m_IdleAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_IdleAni_Info->aniSize.cx = idleAniSize.cx / m_IdleAni_Info->frameCntX;
	m_IdleAni_Info->aniSize.cy = idleAniSize.cy / m_IdleAni_Info->frameCntY;

	m_IdleAni_Info->frameSpeed = 50;
	m_IdleAni_Info->nowFrame = 0;
	m_IdleAni_Info->nowFrameY = DIR_D;
	m_IdleAni_Info->lastTime = GetTickCount();
	m_IdleAni_Info->flag=true;
	m_IdleAni_Info->loop=true;
	m_IdleAni_Info->playAni=true;

	//< 이동 애니메이션
	SAFE_DELETE( m_MoveAni_Info );
	m_MoveAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE moveAniSize = RC_MGR->findImage(imgID_BOSS_MOVE)->getSize();
	//< 프레임 수
	m_MoveAni_Info->frameCntX = 10;
	m_MoveAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_MoveAni_Info->aniSize.cx = moveAniSize.cx / m_MoveAni_Info->frameCntX;
	m_MoveAni_Info->aniSize.cy = moveAniSize.cy / m_MoveAni_Info->frameCntY;
	
	m_MoveAni_Info->frameSpeed = 50;
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
	SIZE atkAniSize = RC_MGR->findImage(imgID_BOSS_ATK)->getSize();
	//< 프레임 수
	m_AtckAni_Info->frameCntX = 10;
	m_AtckAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_AtckAni_Info->aniSize.cx = atkAniSize.cx / m_AtckAni_Info->frameCntX;
	m_AtckAni_Info->aniSize.cy = atkAniSize.cy / m_AtckAni_Info->frameCntY;
	m_AtckAni_Info->frameSpeed = 50;
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
	SIZE behitAniSize = RC_MGR->findImage(imgID_BOSS_BEHIT)->getSize();
	//< 프레임 수
	m_beHitAni_Info->frameCntX = 7;
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
	SIZE dieAniSize = RC_MGR->findImage(imgID_BOSS_NAID_DIE)->getSize();
	//< 프레임 수
	m_DieAni_Info->frameCntX = 21;
	m_DieAni_Info->frameCntY = 8;
	//< 프레임당 이미지 사이즈
	m_DieAni_Info->aniSize.cx = dieAniSize.cx / m_DieAni_Info->frameCntX;
	m_DieAni_Info->aniSize.cy = dieAniSize.cy / m_DieAni_Info->frameCntY;
	m_DieAni_Info->frameSpeed = 50;
	m_DieAni_Info->nowFrame = 0;
	m_DieAni_Info->nowFrameY = DIR_D;
	m_DieAni_Info->lastTime = GetTickCount();
	m_DieAni_Info->flag=false;
	m_DieAni_Info->loop=false;
	m_DieAni_Info->playAni=false;

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