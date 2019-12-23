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

//< 초기화
bool mon_bug::init(void)
{
	//< 이미지 추가
	RC_MGR->addImage( imgID_MONSTER_3_IDLE, "Data/Resource/monster/monster_bug/003-idle.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_MOVE, "Data/Resource/monster/monster_bug/003-walk.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_ATK, "Data/Resource/monster/monster_bug/003-attack.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_BEHIT, "Data/Resource/monster/monster_bug/003-gethit.bmp", 0, 0 , RM_TRANS );
	RC_MGR->addImage( imgID_MONSTER_3_DIE, "Data/Resource/monster/monster_bug/003-die.bmp", 0, 0 , RM_TRANS );
	//< 상태
	m_stateFlag = STATE_IDLE;
	
	//< 스테이터스
	//< 체력
	setMaxHP( 5 );
	setHP( 5 );
	//< 마력
	setMaxMP( 50 );
	setMP( 50 );
	//< 경험치
	m_exp = 3;

	//< 인식 범위
	m_recogRange = 400;
	//< 공격 사거리
	m_attRange = 55;
	//< 이동 속도
	setMoveSpeed( 4 );
	m_moveDeley.m_lastTime = GetTickCount();
	m_moveDeley.m_deley = static_cast<unsigned int>(getMoveSpeed());

	//< 공격 충돌체
	if( NULL == ball )
	{
		ball = new cProjectile(10, m_attRange);
	}
	//< 딜레이
	attDeley.m_deley = attDeley.m_lastTime = 30;

	//< 종류
	m_kindNum = MON_BUG;

	//< 애니메이션 설정
	setAniInfo();

	return true;
}
//< 해제
void mon_bug::release(void)
{
	releaseAniInfo();
	SAFE_DELETE( ball );
}
//< 업데이트
void mon_bug::update(float fDeltaTime)
{
	//< 애니메이션 갱신
	updateAni( m_IdleAni_Info );
	updateAni( m_MoveAni_Info );
	updateAni( m_AtckAni_Info );
	updateAni( m_beHitAni_Info );
	updateAni( m_DieAni_Info );
	updateAni( m_HitAni_Info );
}
//< 랜더
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
	//< 피격 이펙트
	if( m_HitAni_Info->flag == true )
	{
		SIZE siz = m_HitAni_Info->aniSize;
		RENDER_MGR->render( hdc, imgID_GETHIT_3,
			m_pos.x - siz.cx/2 - CAMERA->getX(), m_pos.y - siz.cy/2 - CAMERA->getY(),
			siz.cx, siz.cy,
			m_HitAni_Info->nowFrame * siz.cx, 0,
			siz.cx, siz.cy);
	}
	//< 남은 HP 표시
	renderHPbar(hdc);

	//공격 충돌체 렌더
	ball->render(hdc);
}

//< 충돌 체크
bool mon_bug::collision( POINT &destPos )
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
void mon_bug::attack( POINT &destPos )
{
	if( attDeley.m_deley <= attDeley.m_lastTime++ )
	{
		//< 공격 상태이면 공격
		if( m_stateFlag == STATE_ATTACK )
		{
			attDeley.m_lastTime = 0;
			ball->shoot( m_pos , destPos );
			m_AtckAni_Info->flag = true;
			//SOUND_MGR->soundPlay(BUG_ATK);
		}
	}
	//구체 갱신
	ball->update();
}
//< 인식
void mon_bug::recog( POINT &destPos )
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
bool mon_bug::beHit(int damage)	
{
	//< 이미 죽어있다면 false 리턴
	if( m_stateFlag == STATE_DIE )
	{
		return false;
	}
	//< 살아있다면 HP 감소
	m_state.m_nowHP -= damage; 
	//SOUND_MGR->soundPlay(BUG_HIT);
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
		//SOUND_MGR->soundPlay(BUG_DIE);
		return true;
	}
	return false;
}

//< 공격 충돌체 렉트 반환
RECT mon_bug::getBallRect(void)
{
	return ball->getRect();
}

//< 충돌체 상태
void mon_bug::setBallFlag( bool flag )
{
	ball->setFlag( flag );
	ball->setPos(m_pos);
}
bool mon_bug::getBallFlag( void )
{
	return ball->getFlag();
}
//< 데미지
int mon_bug::getDamage(void)
{
	return ball->getDamage();
}

void mon_bug::setAniInfo( void )
{
	//< 아이들 애니메이션
	SAFE_DELETE( m_IdleAni_Info );
	m_IdleAni_Info = new ANI_INFO;
	//< 이미지 사이즈
	SIZE idleAniSize = RC_MGR->findImage(imgID_MONSTER_3_IDLE)->getSize();
	//< 프레임 수
	m_IdleAni_Info->frameCntX = 10;
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
	SIZE moveAniSize = RC_MGR->findImage(imgID_MONSTER_3_MOVE)->getSize();
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
	SIZE atkAniSize = RC_MGR->findImage(imgID_MONSTER_3_ATK)->getSize();
	//< 프레임 수
	m_AtckAni_Info->frameCntX = 12;
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
	SIZE behitAniSize = RC_MGR->findImage(imgID_MONSTER_3_BEHIT)->getSize();
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
	SIZE dieAniSize = RC_MGR->findImage(imgID_MONSTER_3_DIE)->getSize();
	//< 프레임 수
	m_DieAni_Info->frameCntX = 15;
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
	SIZE hitAniSize = RC_MGR->findImage(imgID_GETHIT_3)->getSize();
	//< 프레임 수
	m_HitAni_Info->frameCntX = 6;
	m_HitAni_Info->frameCntY = 8;
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