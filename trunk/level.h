#pragma once

class Level
{
//< 생성자 소멸자
public:
	Level(void);
	~Level(void);

//< 인터페이스
public:
	//< 초기화
	void init( void );
	//< 경험치 증가
	void incExp(unsigned int exp);

//< 프로퍼티즈
	//< 레벨
	unsigned int getNowLevel(void) { return m_nowLevel; }
	unsigned int getMaxLevel(void) { return m_maxLevel; }
	//< 경험치
	unsigned int getNowExp(void) { return m_nowExp; }
	unsigned int getMaxExp(void) { return m_maxExp; }

//< 맴버
private:
	//< 레벨
	unsigned int m_nowLevel;
	unsigned int m_maxLevel;
	//< 경험치
	unsigned int m_nowExp;
	unsigned int m_maxExp;
	//< 레벨업 당 경험치 증가율
	unsigned int m_expIncRate;
};