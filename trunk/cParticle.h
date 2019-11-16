#pragma once

typedef struct tagParticleInfo
{
	//< ��ġ
	float fPosX;
	float fPosY;

	//< ����
	float fAngle;
	//< �ӵ�
	float fSpeed;

	//< ���� �߷�
	float fGravity;
	//< �߷� ����ġ
	float fAddGravity;

	//< ���� �ð�
	DWORD nLifeTime;

}PARTICLEINFO,*LPPARTICLEINFO;

class cParticle
{
public:

protected:
	//< ��ƼŬ ����
	PARTICLEINFO m_ParticleInfo; 
	//< ���۽ð�
	DWORD		 m_nStartTime;
	//< ����
	BOOL		 m_bLive;

private:
	//< �θ� ��ǥ
	POINT		 m_ptParents;

public:
	cParticle(void);
	virtual ~cParticle(void);

protected:
	//< �����̱�
	void Move(void);
	//< �߷�ġ 
	void GravityUpdate(void);
	//< �����ֱ� Ȯ��
	BOOL isLifeTimeEnd(void);

public:
	//< �ʱ�ȭ
	virtual void Init(PARTICLEINFO &pParticle);
	//< ����
	virtual void Release(void);
	//< ����
	virtual void Update(void);
	//< ���
	virtual void Render(HDC hdc);

	//< ����
	inline BOOL GetLive(void)			{	return m_bLive;		}
	inline BOOL SetLive(BOOL bLive)		{	m_bLive = bLive;	}

	//< �θ� ��ǥ
	inline void SetParentsPos(POINT pt)	{	m_ptParents = pt;	}
};
