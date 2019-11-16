#include "stdafx.h"
//TimeGetTime 시스템 함수를 사용하기 위한 헤더
#include <MMSystem.h>

#include "Timer.h"

//TimeGetTime 함수를 사용하기 위한 라이브러리
#pragma comment( lib, "winmm.lib" )

Timer::~Timer(void)
{
	if( m_isHardWare == false )
	{
		//<	정밀도를 원상복귀 시킨다.
		timeEndPeriod(1);
	}
}

//< 초기화
void			Timer::init(void)
{
	//< 고성능 타이머 지원여부 체크
	//< 동시에 고성능 다이머 지원이 된다면 m_periodFrequency 값에
	//< 초당 파악할수 있는 시간의 값이 들어온다.
	//< 예를 들어 초당 밀리세컨트까지 계산이 가능하다면
	//< 1000 값이 들어가게 된다
	if( QueryPerformanceFrequency( reinterpret_cast<LARGE_INTEGER*> ( &m_periodFrequency ) ))
	{
		m_isHardWare		= TRUE;
		QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*>( &m_lastTime ));

		//< 초당 시간의 경과량을 조절하기 위한 여력( 능력 )
		m_timeScale		= 1.0f / m_periodFrequency;
	}
	else
	{
		m_isHardWare		= FALSE;
		m_lastTime			= timeGetTime();	//< GetTickCount()로 대체 가능	
		m_timeScale			= 0.001f;			//< timeGetTime() 은 밀리 세컨드 단위의 시간으로 초당 1000 카운드이다 
		timeBeginPeriod(1);						//<	timeGettime 의 정밀도를 1/1000 로 만든다.
	}

	m_timeRate			= 1.0f;
	m_frameRate			= 0;
	m_fpsFrameCount		= 0;
	m_fpsTimeElapsed	= 0.0f;
	m_worldTime			= 0.0f;

}

//< 현재의 시간을 계산한다.
void			Timer::tick( float fLockFPS  )
{
	//< 현재의 시간을 얻어온다
	if( m_isHardWare == true )
	{
		//< 초정밀도 마이크로 초 ( 단위로 계산 )
		//< QueryPerformanceCounter 는 멀티 코어에서 동기화 문제가 있다.
		QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*> ( &m_currentTime ) );
	}
	else
	{
		//< 지원하지 않을경우 Time 함수를 이용한다
		m_currentTime = timeGetTime();
	}

	//< 마지막 시간과 현제시간의 경과량 측정
	m_timeElapsed = ( m_currentTime - m_lastTime ) * m_timeScale;

	//< 고정 프레임 처리 ( 프레임 스키핑 )
	if( fLockFPS > 0.0f )
	{
		//< 고정프레임의 시간을 충족할때 까지 루프를 돈다.
		while( m_timeElapsed < ( 1.0f / fLockFPS ) )
		{
            break;
			if( m_isHardWare )
			{
				QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*> (&m_currentTime) );
			}

			else
			{
				m_currentTime = timeGetTime();
			}

			//< 마지막 시간과 현재 시간의 경과량 측정
			m_timeElapsed = ( m_currentTime - m_lastTime ) * m_timeScale;
		}
	}

	//< 마지막 시간을 기록
	m_lastTime = m_currentTime;

	//< 초당 프레임 카운트 증가
	m_fpsFrameCount++;

	//< 초당 프레임 시간 경과량 증가
	m_fpsTimeElapsed += m_timeElapsed;

	//< 전체 시간 경과량 증가
	m_worldTime += m_timeElapsed;

	//< 프레임 초기화 ( 1 초마다 )
	if( m_fpsTimeElapsed > 1.0f )
	{
		m_frameRate			= m_fpsFrameCount;
		m_fpsFrameCount		= 0;
		m_fpsTimeElapsed		= 0.0f;
		//< 
		if( m_frameRate < fLockFPS - 5 )
		{
			m_timeRate = fLockFPS / m_frameRate;
		}
		else
		{
			m_timeRate = 1.0f;
		}
	}
}

//< 현재의 FPS를 얻어온다
unsigned long	Timer::getFrameRate( TCHAR* str  ) CONST
{
	if( NULL == str )
	{
		return m_frameRate;
	}

	//sprintf_s( str , strlen(str), "FPS : %d", m_frameRate );

	return m_frameRate;
}

