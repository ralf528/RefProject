#include "StdAfx.h"
#include "cEffect.h"

cEffect::cEffect(void)
:m_bLive(FALSE),m_bLoop(FALSE),m_fRandSpeed(0),m_fRandAngle(0),
m_dwCreatTimer(0),m_dwCreateTerm(0),m_dwCreateCount(0)
{
}

cEffect::~cEffect(void)
{
	Release();
}

//< �ʱ�ȭ
void		cEffect::Init(PARTICLEINFO &ParticleInfo,float fRandAngle,float fRandSpeed,
				 DWORD dwCount,BOOL bLoop,DWORD dwctTime)
{
	//< ����ü ����
	m_ParticleInfo = ParticleInfo;

	//< ���� ����
	m_fRandAngle	= fRandAngle;	//< ������
	m_fRandSpeed	= fRandSpeed;	//< ���� ���ǵ�
	m_dwCreateCount = dwCount;		//< ���� ����
	m_dwCreateTerm	= dwctTime;		//< ���� �ð�
	m_bLoop		    = bLoop;		//< ���� ����

	//< ��ǥ
	m_ptPos.x = 0;
	m_ptPos.y = 0;
}

//< ����
void		cEffect::Release(void)
{
	//< ���ͷ����� ���鼭 ����
	LIST_PARTICLE_ITER iter = m_ParticleList.begin();

	for(; iter != m_ParticleList.end(); )
	{
		(*iter)->Release();
		delete *iter;
		iter = m_ParticleList.erase(iter);
	}
}

//< ����
void		cEffect::Update(void)
{
	//<
	if(m_bLive == TRUE)
	{
		//< ���ͷ����� ���� ����
		LIST_PARTICLE_ITER iter = m_ParticleList.begin();

		while( iter != m_ParticleList.end() )
		{
			//< ����
			(*iter)->Update();
			//< ���� ��ǥ ����
			(*iter)->SetParentsPos(m_ptPos);

			//< ���̺갡 FALSE�� ����
			if((*iter)->GetLive() == FALSE)
			{
				(*iter)->Release();
				delete *iter;
				iter = m_ParticleList.erase(iter);
			}
			else
			{
				//< ������ �ƴҶ��� ����
				iter++;
			}
		}

		//< ������ 0���� ���� Ȯ��
		if(m_ParticleList.size() <= 0)
		{
			//< ������ �ƴϸ� false
			if(m_bLoop == FALSE)
			{
				m_bLive = FALSE;
			}
		}

		if(m_bLoop == TRUE)
		{
			CreateParticle();
		}
	}
}

//< ����
void		cEffect::Render(HDC hdc)
{
	if(m_bLive == TRUE)
	{
		//< ���ͷ����� ���� ����
		LIST_PARTICLE_ITER iter = m_ParticleList.begin();

		for(; iter != m_ParticleList.end(); iter++)
		{
			//< ����
			(*iter)->Render(hdc);
		}
	}
}

//< ����
void		cEffect::Start(void)
{
	//< �ѹ� ����
	Release();

	//< �ð� ����
	ResetTimer();

	//< ��ƼŬ ����
	CreateParticle();

	//< ���� ����
	m_bLive = TRUE;
}

//< ��ƼŬ ����
void		cEffect::CreateParticle(void)
{
	//< ���� �ð��� �Ǿ����� ������ŭ ����Ʈ�� �߰�
	if(m_dwCreatTimer <= GetTickCount())
	{
		//< ������ŭ ����
		for(DWORD i = 0; i < m_dwCreateCount; i++)
		{
			PARTICLEINFO	Info = m_ParticleInfo;
			//< �Ҵ�
			cParticle* pParticle = new cParticle;
			
			//< ���� ���ǵ�
			Info.fSpeed = GetRandValue(Info.fSpeed,m_fRandSpeed);
			//< ���� ����
			Info.fAngle = GetRandValue(Info.fAngle,m_fRandAngle);

			//< �ʱ�ȭ
			pParticle->Init(Info);

			//< ����Ʈ�� �߰�
			m_ParticleList.push_back(pParticle);
		}

		ResetTimer();
	}
}

//< ���� �ð� �ʱ�ȭ
void		cEffect::ResetTimer(void)
{
	//< �ð� ����
	m_dwCreatTimer = m_dwCreateTerm + GetTickCount();
}

//< ���� ����
float		cEffect::GetRandValue(float fValue,float fRand)
{
	if(fRand != 0)
	{
		fValue -= fRand/2;

		//< %�����ڴ� rand�Լ��� �ȵǱ� ������ ���������� ��ȯ
		int	  nRand = static_cast<int>(fRand);
		fValue += rand() % nRand;
	}

	return fValue;
}