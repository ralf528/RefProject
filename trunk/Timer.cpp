#include "stdafx.h"
//TimeGetTime �ý��� �Լ��� ����ϱ� ���� ���
#include <MMSystem.h>

#include "Timer.h"

//TimeGetTime �Լ��� ����ϱ� ���� ���̺귯��
#pragma comment( lib, "winmm.lib" )

Timer::~Timer(void)
{
	if( m_isHardWare == false )
	{
		//<	���е��� ���󺹱� ��Ų��.
		timeEndPeriod(1);
	}
}

//< �ʱ�ȭ
void			Timer::init(void)
{
	//< ���� Ÿ�̸� �������� üũ
	//< ���ÿ� ���� ���̸� ������ �ȴٸ� m_periodFrequency ����
	//< �ʴ� �ľ��Ҽ� �ִ� �ð��� ���� ���´�.
	//< ���� ��� �ʴ� �и�����Ʈ���� ����� �����ϴٸ�
	//< 1000 ���� ���� �ȴ�
	if( QueryPerformanceFrequency( reinterpret_cast<LARGE_INTEGER*> ( &m_periodFrequency ) ))
	{
		m_isHardWare		= TRUE;
		QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*>( &m_lastTime ));

		//< �ʴ� �ð��� ������� �����ϱ� ���� ����( �ɷ� )
		m_timeScale		= 1.0f / m_periodFrequency;
	}
	else
	{
		m_isHardWare		= FALSE;
		m_lastTime			= timeGetTime();	//< GetTickCount()�� ��ü ����	
		m_timeScale			= 0.001f;			//< timeGetTime() �� �и� ������ ������ �ð����� �ʴ� 1000 ī����̴� 
		timeBeginPeriod(1);						//<	timeGettime �� ���е��� 1/1000 �� �����.
	}

	m_timeRate			= 1.0f;
	m_frameRate			= 0;
	m_fpsFrameCount		= 0;
	m_fpsTimeElapsed	= 0.0f;
	m_worldTime			= 0.0f;

}

//< ������ �ð��� ����Ѵ�.
void			Timer::tick( float fLockFPS  )
{
	//< ������ �ð��� ���´�
	if( m_isHardWare == true )
	{
		//< �����е� ����ũ�� �� ( ������ ��� )
		//< QueryPerformanceCounter �� ��Ƽ �ھ�� ����ȭ ������ �ִ�.
		QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*> ( &m_currentTime ) );
	}
	else
	{
		//< �������� ������� Time �Լ��� �̿��Ѵ�
		m_currentTime = timeGetTime();
	}

	//< ������ �ð��� �����ð��� ����� ����
	m_timeElapsed = ( m_currentTime - m_lastTime ) * m_timeScale;

	//< ���� ������ ó�� ( ������ ��Ű�� )
	if( fLockFPS > 0.0f )
	{
		//< ������������ �ð��� �����Ҷ� ���� ������ ����.
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

			//< ������ �ð��� ���� �ð��� ����� ����
			m_timeElapsed = ( m_currentTime - m_lastTime ) * m_timeScale;
		}
	}

	//< ������ �ð��� ���
	m_lastTime = m_currentTime;

	//< �ʴ� ������ ī��Ʈ ����
	m_fpsFrameCount++;

	//< �ʴ� ������ �ð� ����� ����
	m_fpsTimeElapsed += m_timeElapsed;

	//< ��ü �ð� ����� ����
	m_worldTime += m_timeElapsed;

	//< ������ �ʱ�ȭ ( 1 �ʸ��� )
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

//< ������ FPS�� ���´�
unsigned long	Timer::getFrameRate( TCHAR* str  ) CONST
{
	if( NULL == str )
	{
		return m_frameRate;
	}

	//sprintf_s( str , strlen(str), "FPS : %d", m_frameRate );

	return m_frameRate;
}

