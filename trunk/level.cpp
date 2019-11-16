#include "stdafx.h"
#include "level.h"

//< 생성자 소멸자
Level::Level(void)
{
	init();
}
Level::~Level(void)
{
}

//< 인터페이스

//< 초기화
void Level::init( void )
{
	m_nowLevel=1;
	m_maxLevel=99;
	
	m_nowExp=0;
	m_maxExp=10;

	m_expIncRate = 10;
}
//< 경험치 증가
void Level::incExp(unsigned int exp)
{
	//< 현재 경험치 증가
	m_nowExp += exp;

	//< 최대 경험치보다 높아지면 레벨업
	while( m_nowExp >= m_maxExp )
	{
		//< 최대 레벨이면 그냥 종료
		if( m_nowLevel >= m_maxLevel )
		{
			m_nowLevel = m_maxLevel;
			return;
		}
		else
		{
			//< 레벨 업
			m_nowLevel++;
			//< 레벨업 후 잔여 경험치
			m_nowExp -= m_maxExp;
			//< 최대 경험치 증가
			m_maxExp += static_cast<unsigned int>(m_maxExp * (m_expIncRate/100.f));
		}
	}
}