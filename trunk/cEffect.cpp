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

//< 초기화
void		cEffect::Init(PARTICLEINFO &ParticleInfo,float fRandAngle,float fRandSpeed,
				 DWORD dwCount,BOOL bLoop,DWORD dwctTime)
{
	//< 구조체 대입
	m_ParticleInfo = ParticleInfo;

	//< 정보 대입
	m_fRandAngle	= fRandAngle;	//< 랜덤각
	m_fRandSpeed	= fRandSpeed;	//< 랜덤 스피드
	m_dwCreateCount = dwCount;		//< 생성 갯수
	m_dwCreateTerm	= dwctTime;		//< 생성 시간
	m_bLoop		    = bLoop;		//< 루프 여부

	//< 좌표
	m_ptPos.x = 0;
	m_ptPos.y = 0;
}

//< 삭제
void		cEffect::Release(void)
{
	//< 이터레이터 돌면서 삭제
	LIST_PARTICLE_ITER iter = m_ParticleList.begin();

	for(; iter != m_ParticleList.end(); )
	{
		(*iter)->Release();
		delete *iter;
		iter = m_ParticleList.erase(iter);
	}
}

//< 갱신
void		cEffect::Update(void)
{
	//<
	if(m_bLive == TRUE)
	{
		//< 이터레이터 돌며 갱신
		LIST_PARTICLE_ITER iter = m_ParticleList.begin();

		while( iter != m_ParticleList.end() )
		{
			//< 갱신
			(*iter)->Update();
			//< 로컬 좌표 갱신
			(*iter)->SetParentsPos(m_ptPos);

			//< 라이브가 FALSE면 삭제
			if((*iter)->GetLive() == FALSE)
			{
				(*iter)->Release();
				delete *iter;
				iter = m_ParticleList.erase(iter);
			}
			else
			{
				//< 삭제가 아닐때만 증가
				iter++;
			}
		}

		//< 갯수가 0개면 루프 확인
		if(m_ParticleList.size() <= 0)
		{
			//< 루프가 아니면 false
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

//< 랜더
void		cEffect::Render(HDC hdc)
{
	if(m_bLive == TRUE)
	{
		//< 이터레이터 돌며 랜더
		LIST_PARTICLE_ITER iter = m_ParticleList.begin();

		for(; iter != m_ParticleList.end(); iter++)
		{
			//< 갱신
			(*iter)->Render(hdc);
		}
	}
}

//< 시작
void		cEffect::Start(void)
{
	//< 한번 해제
	Release();

	//< 시간 설정
	ResetTimer();

	//< 파티클 생성
	CreateParticle();

	//< 생존 설정
	m_bLive = TRUE;
}

//< 파티클 생성
void		cEffect::CreateParticle(void)
{
	//< 생성 시간이 되었으면 갯수만큼 리스트에 추가
	if(m_dwCreatTimer <= GetTickCount())
	{
		//< 갯수만큼 생성
		for(DWORD i = 0; i < m_dwCreateCount; i++)
		{
			PARTICLEINFO	Info = m_ParticleInfo;
			//< 할당
			cParticle* pParticle = new cParticle;
			
			//< 랜덤 스피드
			Info.fSpeed = GetRandValue(Info.fSpeed,m_fRandSpeed);
			//< 랜덤 각도
			Info.fAngle = GetRandValue(Info.fAngle,m_fRandAngle);

			//< 초기화
			pParticle->Init(Info);

			//< 리스트에 추가
			m_ParticleList.push_back(pParticle);
		}

		ResetTimer();
	}
}

//< 생성 시간 초기화
void		cEffect::ResetTimer(void)
{
	//< 시간 설정
	m_dwCreatTimer = m_dwCreateTerm + GetTickCount();
}

//< 랜덤 벨류
float		cEffect::GetRandValue(float fValue,float fRand)
{
	if(fRand != 0)
	{
		fValue -= fRand/2;

		//< %연산자는 rand함수가 안되기 때문에 정수형으로 변환
		int	  nRand = static_cast<int>(fRand);
		fValue += rand() % nRand;
	}

	return fValue;
}