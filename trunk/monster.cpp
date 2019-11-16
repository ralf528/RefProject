#include "stdafx.h"

//#include "sphereObject.h"
#include "monster.h"


Monster::Monster(void)
	: hpRenderFlag(false), m_dir(DIR_D), m_kindNum(monsterKind::MON_BUG)
{
	//< HP 바 정보
	hpRenderDeley.m_deley = 1500;
	hpRenderDeley.m_lastTime = GetTickCount();
}
Monster::~Monster(void)
{
	//< 애니메이션 정보 삭제
	releaseAniInfo();
}

//< 이동
void Monster::move( POINT &destPos )
{	
	//< 추적 상태면 이동
	if( m_stateFlag == STATE_CHASE )
	{
		//< 이전 위치 기억
		m_prevPos = m_pos;
		//< 목표(플레이어)를 향해 이동
		if( m_moveDeley.m_lastTime + m_moveDeley.m_deley < GetTickCount() )
		{
			math::moveToPt( &m_pos, &destPos , getMoveSpeed() );
			m_moveDeley.m_lastTime = GetTickCount();
		}
		m_MoveAni_Info->flag=true;
	}		
}

//< 몬스터 렉트 반환
RECT Monster::getRect( void )
{
	RECT rt;
	SetRect(&rt, 
		m_pos.x - MONSTER_SIZE, m_pos.y - MONSTER_SIZE,
		m_pos.x + MONSTER_SIZE, m_pos.y + MONSTER_SIZE);

	return rt;
}

//< 방향 계산
void Monster::calcDir(POINT &destPos)
{
	float theta = math::calcAnglePtToPt(&destPos,&m_pos);
	theta = (theta/180) * fPI;
	if( theta > fPI/8 && theta <= 3*fPI/8)
	{
		m_dir = DIR_RD;
	}
	else if( theta > 3*fPI/8 && theta <= 5*fPI/8)
	{
		m_dir = DIR_D;
	}
	else if( theta > 5*fPI/8 && theta <= 7*fPI/8)
	{
		m_dir = DIR_LD;
	}
	else if( theta > 7*fPI/8 && theta <= 9*fPI/8)
	{
		m_dir = DIR_L;
	}
	else if( theta > 9*fPI/8 && theta <= 11*fPI/8)
	{
		m_dir = DIR_LU;
	}
	else if( theta > 11*fPI/8 && theta <= 13*fPI/8)
	{
		m_dir = DIR_U;
	}
	else if( theta > 13*fPI/8 && theta <= 15*fPI/8)
	{
		m_dir = DIR_RU;
	}
	else
	{
		m_dir = DIR_R;
	}

}

////< 공격 충돌체 렉트 반환
//RECT Monster::getBallRect(void)
//{
//	return ball->getRect();
//}
//
////< 충돌체 상태
//void Monster::setBallFlag( bool flag )
//{
//	ball->setFlag( flag );
//	ball->setPos(m_pos);
//}
//bool Monster::getBallFlag( void )
//{
//	return ball->getFlag();
//}

//< HP 바 랜더
void Monster::renderHPbar(HDC hdc)
{
	if( hpRenderFlag == true )
	{
		//< 펜 오브젝트
		HPEN myPen, oldPen;
		myPen = CreatePen( PS_SOLID, 10, RGB(255,255,255) );
		oldPen = (HPEN)SelectObject(hdc, myPen);

		//< 전체 HP
		//MoveToEx( hdc, m_pos.x - 30 - CAMERA->getX(), m_pos.y - 45 - CAMERA->getY(), NULL );
		//LineTo( hdc, m_pos.x + 30 - CAMERA->getX() , m_pos.y - 45 - CAMERA->getY() );

		//< 오브젝트 삭제
		DeleteObject( SelectObject(hdc, oldPen) );

		myPen = CreatePen( PS_SOLID, 7, RGB(255,0,0) );
		oldPen = (HPEN)SelectObject(hdc, myPen);

		//< HP 퍼센테이지
		int HPper = static_cast<int>(50 * (getHP() / static_cast<float>(getMaxHP())));
		//< 남은 HP
		//< 0이상일 때만 랜더
		if( HPper > 0 )
		{
			//MoveToEx( hdc, m_pos.x - 27 - CAMERA->getX(), m_pos.y - 45 - CAMERA->getY(), NULL );
			//LineTo( hdc, m_pos.x -27 + HPper - CAMERA->getX() , m_pos.y - 45 - CAMERA->getY() );
		}

		//< 오브젝트 삭제
		DeleteObject( SelectObject(hdc, oldPen) );

		if( hpRenderDeley.m_lastTime + hpRenderDeley.m_deley < GetTickCount() )
		{
			hpRenderFlag = false;
		}
	}
}
//< HP 바 랜더 카운트
void Monster::hpRenderStart(void)
{
	//< 시작시간 저장
	hpRenderDeley.m_lastTime = GetTickCount();
	//< 랜더 시작
	hpRenderFlag = true;
}

//애니메이션 해제
void Monster::releaseAniInfo( void )
{
	SAFE_DELETE( m_IdleAni_Info );
	SAFE_DELETE( m_MoveAni_Info );
	SAFE_DELETE( m_AtckAni_Info );
	SAFE_DELETE( m_DieAni_Info );
	SAFE_DELETE( m_beHitAni_Info );
	SAFE_DELETE( m_HitAni_Info );
}