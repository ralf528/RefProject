#pragma once
#include <list>

#include "cParticle.h"

class cEffect
{
private:
	//< list
	typedef std::list<cParticle*>   LIST_PARTICLE;
	typedef LIST_PARTICLE::iterator LIST_PARTICLE_ITER;

private:
	//< ���� �÷���
	BOOL			m_bLive;
	//< ���� �÷���
	BOOL			m_bLoop;

	//< ���� ���ǵ�
	float			m_fRandSpeed;
	//< ���� ����
	float			m_fRandAngle;

	//< ���� �ð�
	DWORD			m_dwCreatTimer;
	DWORD			m_dwCreateTerm;

	//< ���� ����
	DWORD			m_dwCreateCount;

	//< ��ġ
	POINT			m_ptPos;

	//< ��ƼŬ�� �⺻ ���� ����ü
	PARTICLEINFO	m_ParticleInfo;

	//< ��ƼŬ�� �� ����Ʈ
	LIST_PARTICLE	m_ParticleList;

public:
	cEffect(void);
	~cEffect(void);

	//< �ʱ�ȭ
	void		Init(PARTICLEINFO &ParticleInfo,float fRandAngle,float RandSpeed,
		DWORD dwCount,BOOL bLoop,DWORD dwctTime);

	//< ����
	void		Release(void);

	//< ����
	void		Update(void);

	//< ����
	void		Render(HDC hdc);

	//< ����
	void		Start(void);

	//< ����Ʈ ��ǥ ����
	inline void SetEffectPos(POINT pt)		{	SetEffectPos(pt.x,pt.y);	}
	inline void SetEffectPos(LONG x,LONG y)	{	m_ptPos.x = x; m_ptPos.y = y; }

private:
	//< ��ƼŬ ����
	void		CreateParticle(void);

	//< ���� �ð� �ʱ�ȭ
	void		ResetTimer(void);

	//< ���� ����
	float		GetRandValue(float fValue,float fRand);
};
