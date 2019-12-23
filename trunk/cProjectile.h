#pragma once

//충돌 오브젝트(공격)
class cProjectile
{
public:
	//생성자 소멸자
	cProjectile( int damage = 1, int range = 5, int speed = 10 );
	virtual ~cProjectile(void);

public:
	//< 인터페이스	
	//초기화
	virtual bool init(int damage, int speed, int range);
	//해제
	virtual void release(void);
	//업데이트
	virtual void update(void);
	//그리기
	virtual void render(HDC hdc);

	//발사
	virtual void shoot( POINT &startPoint, POINT &destPos );

	//위치 설정
	virtual void setPos(POINT pos);
	virtual void setPos(LONG x, LONG y);

	//< 데미지 설정
	virtual void setDamage(int damage)	{ m_damage = damage; }
	virtual int getDamage(void)			{ return m_damage; }
	//< 이동 속도 설정
	virtual void setSpeed(int speed)	{ m_speed = speed; }
	virtual int getSpeed(void)			{ return m_speed;}
	//< 사거리 설정
	virtual void setRange(int range)	{ m_range = range; }
	virtual int getRange(void)			{ return m_range; }
	//위치 리턴
	virtual POINT getPos(void) { return m_pos; }
	//< 플래그 설정
	virtual bool getFlag(void) { return m_flag; }
	virtual void setFlag( bool flag ) { m_flag = flag; }
	//< 렉트
	virtual RECT getRect(void) { return m_rect; }

protected:
	//< 내부 함수
	//렉트 설정
	virtual void setRect(void);

protected:
	//< 발사된 위치
	POINT m_startPos;
	//< 현재 위치
	POINT m_pos;
	//< 목표 위치
	POINT m_destPos;

	//< 사각형(충돌체크 용)
	RECT m_rect;
	
	//< 데미지
	int m_damage;
	//< 살아있는지
	bool m_flag;
	//< 이동 속도
	int m_speed;
	//< 사거리
	int m_range;
};