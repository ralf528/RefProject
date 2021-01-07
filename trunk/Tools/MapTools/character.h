#pragma once

//< 게임 캐릭터 클래스
class character
{
//< 생성자 소멸자
public:
	character(void);
	~character(void);

//< 인터페이스
public:
	//< 초기화
	bool init(void);
	//< 해제
	void release(void);
	//< 갱신
	void update(void);
	//< 랜더
	void render(HDC hdc);

	//< 이동
	void move( void );
	//< 좌표 설정
	void setPos( POINT &pos );
	void setPos( LONG x, LONG y );
	POINT getPos(void) { return m_pos; }
	//< 이전 위치로 되돌리기
	void setPosToPrev(void);
	//< 방향 설정
	void setDir(int dir);
	int getDir(void) { return m_dir; }

//< 내부 함수
private:
	//< 렉트 설정
	void setRect(void);

//< 멤버 변수
private:
	//< 캐릭터 좌표
	POINT m_pos;
	//< 이동 전 좌표
	POINT m_prevPos;
	//< 캐릭터 렉트
	RECT m_rect;

	//< 캐릭터 이동 속도
	int m_moveSpeed;
	//< 캐릭터 방향정보
	int m_dir;
};