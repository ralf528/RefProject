#pragma once;

class Unit
{
public:
//< 생성자, 소멸자
	Unit(void)
		: m_dir( DIR_D ), m_kind(0)
	{}
	virtual ~Unit(void){}

public:
//< 인터페이스
	//< 초기화
	virtual bool init(void) = 0;
	//< 해제
	virtual void release(void) = 0;
	//< 업데이트
	virtual void update(void) = 0;
	//< 랜더
	virtual void render(HDC hdc) = 0;

//< 프로퍼티즈
	//< 종류
	inline virtual int		getKind(void) { return m_kind; }
	inline virtual void		setKind( int kind ) { m_kind = kind; }
	
	//< 위치 좌표
	inline virtual POINT	getPos(void) { return m_pos; }
	inline virtual void		setPos(POINT &pos) { m_pos = pos; }
	inline virtual void		setPos(LONG x, LONG y)  { m_pos.x = x, m_pos.y = y; }
	//< 방향 설정
	inline virtual void		setDir(int dir) { m_dir = dir;}
	inline virtual int		getDir(void) { return m_dir; }
	
	//< 이동 속도
	inline float	getMoveSpeed(void) { return m_state.m_moveSpeed; } 
	inline void		setMoveSpeed(float speed) { m_state.m_moveSpeed = speed; }

	//< 체력
	inline int		getHP(void) { return m_state.m_nowHP; }
	inline void		setHP(int hp) { m_state.m_nowHP = hp; }
	inline void		incHP(int offset) { m_state.m_nowHP += offset; } 
	
	//< 최대 체력
	inline int		getMaxHP(void) { return m_state.m_maxHP; }
	inline void		setMaxHP(int mxhp){ m_state.m_maxHP = mxhp; }

	//< 마력
	inline int		getMP(void) { return m_state.m_nowMP; }
	inline void		setMP(int mp) { m_state.m_nowMP = mp; }
	inline void		incMP(int offset) { m_state.m_nowMP += offset; }

	//< 최대 마력
	inline int		getMaxMP(void) { return m_state.m_maxMP; }
	inline void		setMaxMP(int mxmp){ m_state.m_maxMP = mxmp; }

	//< 힘
	inline int		getStrong(void) { return m_state.m_str; }
	inline void		setStrong(int str) { m_state.m_str = str; }
	inline void		incStrong(int offset) { m_state.m_str += offset; }
	//< 민
	inline int		getAgility(void) { return m_state.m_agl; }
	inline void		setAgility(int agl) { m_state.m_agl = agl; }
	inline void		incAgility(int offset) {m_state. m_agl += offset; }
	//< 지
	inline int		getIntel(void) { return m_state.m_int; }
	inline void		setIntel(int intel) { m_state.m_int = intel; }
	inline void		incIntel(int offset) {m_state. m_int += offset; }

	//< 신념
	inline void		setBelief(int belief) { m_state.m_belief = belief; }
	inline int		getBelief(void) { return m_state.m_belief; }
	//< 종족
	inline void		setTribe(int tribe) { m_state.m_tribe = tribe; }
	inline int		getTribe(void) { return m_state.m_tribe; }
	//< 직업
	inline void		setJob(int job) { m_state.m_job = job; }
	inline int		getJob(void) { return m_state.m_job; }

	//< 상태이상
	inline void		setCondition(int cond) { m_state.m_condition = cond; }
	inline int		getCondition(void) { return m_state.m_condition; }


	//< 중점 반환
	inline virtual POINT getCenter( void ){ return m_pos; }

protected:
	//< 종류
	int m_kind;
	//< 위치
	POINT m_pos;
	//< 방향정보
	int m_dir;

	//< 스테이터스
	STATES m_state;
};