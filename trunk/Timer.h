#pragma once

class Timer
{
private:
	bool			m_isHardWare;		//< ���� Ÿ�̸� ���� ����
	float			m_timeScale;		//< �ð��� ������� ����
	float			m_timeElapsed;		//< ������ �ð��� ���� �ð��� �����
	__int64			m_currentTime;		//< ���� �ð�
	__int64			m_lastTime;			//< ���� �ð�
	__int64			m_periodFrequency;	//< �ð��� �ֱ�

	unsigned long	m_frameRate;		//< FPS
	unsigned long	m_fpsFrameCount;	//< FPS ī��Ʈ
	float			m_fpsTimeElapsed;	//< FPS Ÿ�� �����
	float			m_worldTime;		//< ���� ������ �귯�� ��ü �ð�
	float			m_timeRate;			//< ����ȭ ó��
public:
	Timer(void)	{}
	~Timer(void);

	//< �ʱ�ȭ
	void			init(void);

	//< ������ �ð��� ����Ѵ�.
	void			tick( float fLockFPS = 0.0f );

	//< ������ FPS�� ���´�
	unsigned long	getFrameRate( TCHAR* str = NULL ) CONST;

	//< ������ �ð��� ���� �ð��� ������� ���´�.
	inline float	getElapsedTime( void ) CONST
	{
		return m_timeElapsed;
	}

	//< ��ü ��� �ð��� ���´�
	inline float	getWorldTime( void ) CONST
	{
		return m_worldTime;
	}
	//< �ð� ����ȭ ����
	inline float	getTimeRate( void ) CONST	{	return m_timeRate;  }
};
