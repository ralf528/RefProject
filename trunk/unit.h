#pragma once;

struct StatusType
{
	std::map<ESTATUS_TYPE, int> m_value;

	StatusType();

	int GetValue();
	void SetValue(ESTATUS_TYPE eType, int value);
	void AddValue(ESTATUS_TYPE eType, int value);
};

struct Abnormal
{
	int AbnormalType;

	DELAY_TIME Delay;
};

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
	virtual void update(float fDeltaTime) = 0;
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
	inline int		getMoveSpeed(void) { return m_moveSpeed.GetValue(); } 
	inline void		setMoveSpeed(ESTATUS_TYPE type, int speed) { m_moveSpeed.SetValue(type, speed); }

	//< 체력
	inline int		getHP(void) { return m_nowHP; }
	inline void		setHP(int hp) { m_nowHP = hp; }
	void			incHP(int offset);
	
	//< 최대 체력
	inline int		getMaxHP(void) { return m_maxHP.GetValue(); }
	inline void		setMaxHP(ESTATUS_TYPE type, int mxhp) { m_maxHP.SetValue(type, mxhp); }

	//< 마력
	inline int		getMP(void) { return m_nowMP; }
	inline void		setMP(int mp) { m_nowMP = mp; }
	inline void		incMP(int offset) { m_nowMP += offset; }

	//< 최대 마력
	inline int		getMaxMP(void) { return m_maxMP.GetValue(); }
	inline void		setMaxMP(ESTATUS_TYPE type, int mxmp){ m_maxMP.SetValue(type, mxmp); }

	//< 힘
	inline int		getStrong(void) { return m_str.GetValue(); }
	inline void		setStrong(ESTATUS_TYPE type, int str) { m_str.SetValue(type, str); }
	inline void		incStrong(ESTATUS_TYPE type, int offset) { m_str.AddValue(type, offset); }
	//< 민
	inline int		getAgility(void) { return m_agl.GetValue(); }
	inline void		setAgility(ESTATUS_TYPE type, int agl) { m_agl.SetValue(type, agl); }
	inline void		incAgility(ESTATUS_TYPE type, int offset) { m_agl.AddValue(type, offset); }
	//< 지
	inline int		getIntel(void) { return m_int.GetValue(); }
	inline void		setIntel(ESTATUS_TYPE type, int intel) { m_int.SetValue(type,intel); }
	inline void		incIntel(ESTATUS_TYPE type, int offset) { m_int.AddValue(type, offset); }

	//< 신념
	inline void		setBelief(int belief) { m_belief = belief; }
	inline int		getBelief(void) { return m_belief; }
	//< 종족
	inline void		setTribe(int tribe) { m_tribe = tribe; }
	inline int		getTribe(void) { return m_tribe; }
	//< 직업
	inline void		setJob(int job) { m_job = job; }
	inline int		getJob(void) { return m_job; }

	//< 상태이상
	void			setCondition(int cond, int delay = 0);
	inline int		getCondition(void) { return m_Abnormal.AbnormalType; }
	void			UpdateCondition();


	//< 중점 반환
	inline virtual POINT getCenter( void ){ return m_pos; }

protected:
	//< 종류
	int m_kind;
	//< 위치
	POINT m_pos;
	//< 방향정보
	int m_dir;

	//< 신념
	unsigned int m_belief;
	//< 종족
	unsigned int m_tribe;
	//< 직업
	unsigned int m_job;

	//< 상태이상
	Abnormal m_Abnormal;

	StatusType m_maxHP;
	int m_nowHP;
	StatusType m_maxMP;
	int m_nowMP;
	
	StatusType m_str;
	StatusType m_agl;
	StatusType m_int;

	//< 이동속도
	StatusType m_moveSpeed;
};