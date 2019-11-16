#pragma once

class Level
{
//< ������ �Ҹ���
public:
	Level(void);
	~Level(void);

//< �������̽�
public:
	//< �ʱ�ȭ
	void init( void );
	//< ����ġ ����
	void incExp(unsigned int exp);

//< ������Ƽ��
	//< ����
	unsigned int getNowLevel(void) { return m_nowLevel; }
	unsigned int getMaxLevel(void) { return m_maxLevel; }
	//< ����ġ
	unsigned int getNowExp(void) { return m_nowExp; }
	unsigned int getMaxExp(void) { return m_maxExp; }

//< �ɹ�
private:
	//< ����
	unsigned int m_nowLevel;
	unsigned int m_maxLevel;
	//< ����ġ
	unsigned int m_nowExp;
	unsigned int m_maxExp;
	//< ������ �� ����ġ ������
	unsigned int m_expIncRate;
};