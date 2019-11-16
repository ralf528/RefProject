#pragma once

class Timer
{
private:
	bool			m_isHardWare;		//< 고성능 타이머 지원 여부
	float			m_timeScale;		//< 시간의 경과량을 조절
	float			m_timeElapsed;		//< 마지막 시간과 현재 시간의 경과량
	__int64			m_currentTime;		//< 현재 시간
	__int64			m_lastTime;			//< 이전 시간
	__int64			m_periodFrequency;	//< 시간의 주기

	unsigned long	m_frameRate;		//< FPS
	unsigned long	m_fpsFrameCount;	//< FPS 카운트
	float			m_fpsTimeElapsed;	//< FPS 타임 경과량
	float			m_worldTime;		//< 게임 시작후 흘러간 전체 시간
	float			m_timeRate;			//< 동기화 처리
public:
	Timer(void)	{}
	~Timer(void);

	//< 초기화
	void			init(void);

	//< 현재의 시간을 계산한다.
	void			tick( float fLockFPS = 0.0f );

	//< 현재의 FPS를 얻어온다
	unsigned long	getFrameRate( TCHAR* str = NULL ) CONST;

	//< 마지막 시간과 현재 시간의 경과량을 얻어온다.
	inline float	getElapsedTime( void ) CONST
	{
		return m_timeElapsed;
	}

	//< 전체 경과 시간을 얻어온다
	inline float	getWorldTime( void ) CONST
	{
		return m_worldTime;
	}
	//< 시간 동기화 변수
	inline float	getTimeRate( void ) CONST	{	return m_timeRate;  }
};
