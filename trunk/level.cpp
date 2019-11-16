#include "stdafx.h"
#include "level.h"

//< ������ �Ҹ���
Level::Level(void)
{
	init();
}
Level::~Level(void)
{
}

//< �������̽�

//< �ʱ�ȭ
void Level::init( void )
{
	m_nowLevel=1;
	m_maxLevel=99;
	
	m_nowExp=0;
	m_maxExp=10;

	m_expIncRate = 10;
}
//< ����ġ ����
void Level::incExp(unsigned int exp)
{
	//< ���� ����ġ ����
	m_nowExp += exp;

	//< �ִ� ����ġ���� �������� ������
	while( m_nowExp >= m_maxExp )
	{
		//< �ִ� �����̸� �׳� ����
		if( m_nowLevel >= m_maxLevel )
		{
			m_nowLevel = m_maxLevel;
			return;
		}
		else
		{
			//< ���� ��
			m_nowLevel++;
			//< ������ �� �ܿ� ����ġ
			m_nowExp -= m_maxExp;
			//< �ִ� ����ġ ����
			m_maxExp += static_cast<unsigned int>(m_maxExp * (m_expIncRate/100.f));
		}
	}
}