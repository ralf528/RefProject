#include "StdAfx.h"
#include <cmath>
#include "cParticle.h"

cParticle::cParticle(void)
:m_bLive(FALSE)
{
}

cParticle::~cParticle(void)
{
}

//< 초기화
void cParticle::Init(PARTICLEINFO &pParticle)
{
	//< 정보 대입
	m_ParticleInfo = pParticle;

	//< 시작시간
	m_nStartTime   = GetTickCount();
	m_bLive		   = TRUE;
}

//< 삭제
void cParticle::Release(void)
{
}

//< 갱신
void cParticle::Update(void)
{
	Move();
	GravityUpdate();

	//< 생명설정
	if(isLifeTimeEnd() == FALSE)
	{
		m_bLive = FALSE;
	}
}

//< 출력
void cParticle::Render(HDC hdc)
{
	LONG ptX = static_cast<LONG>(m_ParticleInfo.fPosX) + m_ptParents.x;
	LONG ptY = static_cast<LONG>(m_ParticleInfo.fPosY) + m_ptParents.y;

	int rad = 5;
	//< 원
	Ellipse(hdc,ptX-rad,ptY-rad,ptX+rad,ptY+rad);
}

//< 움직이기
void cParticle::Move(void)
{
	float rad = m_ParticleInfo.fAngle*(3.141592f/180.f);

	//< x축 이동 좌표
	m_ParticleInfo.fPosX += cosf(rad)*m_ParticleInfo.fSpeed;
	//< y축 이동 좌표
	m_ParticleInfo.fPosY += -sinf(rad)*m_ParticleInfo.fSpeed;
}

//< 중력치 
void cParticle::GravityUpdate(void)
{
	//< 중력 증가
	m_ParticleInfo.fGravity += (m_ParticleInfo.fAddGravity/4.0f);
	//< 중력 이동
	m_ParticleInfo.fPosY += m_ParticleInfo.fGravity;
}

//< 생명주기 확인
BOOL cParticle::isLifeTimeEnd(void)
{
	//< 타이머
	if(m_nStartTime + m_ParticleInfo.nLifeTime >= GetTickCount())
	{
		return TRUE;
	}

	return FALSE;
}