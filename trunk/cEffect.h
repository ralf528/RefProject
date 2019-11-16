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
	//< 생존 플래그
	BOOL			m_bLive;
	//< 루프 플래그
	BOOL			m_bLoop;

	//< 랜덤 스피드
	float			m_fRandSpeed;
	//< 랜덤 각도
	float			m_fRandAngle;

	//< 생성 시간
	DWORD			m_dwCreatTimer;
	DWORD			m_dwCreateTerm;

	//< 생성 갯수
	DWORD			m_dwCreateCount;

	//< 위치
	POINT			m_ptPos;

	//< 파티클의 기본 정보 구조체
	PARTICLEINFO	m_ParticleInfo;

	//< 파티클이 들어갈 리스트
	LIST_PARTICLE	m_ParticleList;

public:
	cEffect(void);
	~cEffect(void);

	//< 초기화
	void		Init(PARTICLEINFO &ParticleInfo,float fRandAngle,float RandSpeed,
		DWORD dwCount,BOOL bLoop,DWORD dwctTime);

	//< 삭제
	void		Release(void);

	//< 갱신
	void		Update(void);

	//< 랜더
	void		Render(HDC hdc);

	//< 시작
	void		Start(void);

	//< 이팩트 좌표 설정
	inline void SetEffectPos(POINT pt)		{	SetEffectPos(pt.x,pt.y);	}
	inline void SetEffectPos(LONG x,LONG y)	{	m_ptPos.x = x; m_ptPos.y = y; }

private:
	//< 파티클 생성
	void		CreateParticle(void);

	//< 생성 시간 초기화
	void		ResetTimer(void);

	//< 랜덤 벨류
	float		GetRandValue(float fValue,float fRand);
};
