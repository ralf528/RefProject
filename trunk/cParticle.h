#pragma once

typedef struct tagParticleInfo
{
	//< 위치
	float fPosX;
	float fPosY;

	//< 각도
	float fAngle;
	//< 속도
	float fSpeed;

	//< 현재 중력
	float fGravity;
	//< 중력 가중치
	float fAddGravity;

	//< 생존 시간
	DWORD nLifeTime;

}PARTICLEINFO,*LPPARTICLEINFO;

class cParticle
{
public:

protected:
	//< 파티클 정보
	PARTICLEINFO m_ParticleInfo; 
	//< 시작시간
	DWORD		 m_nStartTime;
	//< 생명
	BOOL		 m_bLive;

private:
	//< 부모 좌표
	POINT		 m_ptParents;

public:
	cParticle(void);
	virtual ~cParticle(void);

protected:
	//< 움직이기
	void Move(void);
	//< 중력치 
	void GravityUpdate(void);
	//< 생명주기 확인
	BOOL isLifeTimeEnd(void);

public:
	//< 초기화
	virtual void Init(PARTICLEINFO &pParticle);
	//< 삭제
	virtual void Release(void);
	//< 갱신
	virtual void Update(void);
	//< 출력
	virtual void Render(HDC hdc);

	//< 생명
	inline BOOL GetLive(void)			{	return m_bLive;		}
	inline BOOL SetLive(BOOL bLive)		{	m_bLive = bLive;	}

	//< 부모 좌표
	inline void SetParentsPos(POINT pt)	{	m_ptParents = pt;	}
};
