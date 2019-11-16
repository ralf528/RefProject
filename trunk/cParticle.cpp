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

//< �ʱ�ȭ
void cParticle::Init(PARTICLEINFO &pParticle)
{
	//< ���� ����
	m_ParticleInfo = pParticle;

	//< ���۽ð�
	m_nStartTime   = GetTickCount();
	m_bLive		   = TRUE;
}

//< ����
void cParticle::Release(void)
{
}

//< ����
void cParticle::Update(void)
{
	Move();
	GravityUpdate();

	//< ������
	if(isLifeTimeEnd() == FALSE)
	{
		m_bLive = FALSE;
	}
}

//< ���
void cParticle::Render(HDC hdc)
{
	LONG ptX = static_cast<LONG>(m_ParticleInfo.fPosX) + m_ptParents.x;
	LONG ptY = static_cast<LONG>(m_ParticleInfo.fPosY) + m_ptParents.y;

	int rad = 5;
	//< ��
	Ellipse(hdc,ptX-rad,ptY-rad,ptX+rad,ptY+rad);
}

//< �����̱�
void cParticle::Move(void)
{
	float rad = m_ParticleInfo.fAngle*(3.141592f/180.f);

	//< x�� �̵� ��ǥ
	m_ParticleInfo.fPosX += cosf(rad)*m_ParticleInfo.fSpeed;
	//< y�� �̵� ��ǥ
	m_ParticleInfo.fPosY += -sinf(rad)*m_ParticleInfo.fSpeed;
}

//< �߷�ġ 
void cParticle::GravityUpdate(void)
{
	//< �߷� ����
	m_ParticleInfo.fGravity += (m_ParticleInfo.fAddGravity/4.0f);
	//< �߷� �̵�
	m_ParticleInfo.fPosY += m_ParticleInfo.fGravity;
}

//< �����ֱ� Ȯ��
BOOL cParticle::isLifeTimeEnd(void)
{
	//< Ÿ�̸�
	if(m_nStartTime + m_ParticleInfo.nLifeTime >= GetTickCount())
	{
		return TRUE;
	}

	return FALSE;
}