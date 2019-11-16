#pragma once;

class Unit
{
public:
//< ������, �Ҹ���
	Unit(void)
		: m_dir( DIR_D ), m_kind(0)
	{}
	virtual ~Unit(void){}

public:
//< �������̽�
	//< �ʱ�ȭ
	virtual bool init(void) = 0;
	//< ����
	virtual void release(void) = 0;
	//< ������Ʈ
	virtual void update(void) = 0;
	//< ����
	virtual void render(HDC hdc) = 0;

//< ������Ƽ��
	//< ����
	inline virtual int		getKind(void) { return m_kind; }
	inline virtual void		setKind( int kind ) { m_kind = kind; }
	
	//< ��ġ ��ǥ
	inline virtual POINT	getPos(void) { return m_pos; }
	inline virtual void		setPos(POINT &pos) { m_pos = pos; }
	inline virtual void		setPos(LONG x, LONG y)  { m_pos.x = x, m_pos.y = y; }
	//< ���� ����
	inline virtual void		setDir(int dir) { m_dir = dir;}
	inline virtual int		getDir(void) { return m_dir; }
	
	//< �̵� �ӵ�
	inline float	getMoveSpeed(void) { return m_state.m_moveSpeed; } 
	inline void		setMoveSpeed(float speed) { m_state.m_moveSpeed = speed; }

	//< ü��
	inline int		getHP(void) { return m_state.m_nowHP; }
	inline void		setHP(int hp) { m_state.m_nowHP = hp; }
	inline void		incHP(int offset) { m_state.m_nowHP += offset; } 
	
	//< �ִ� ü��
	inline int		getMaxHP(void) { return m_state.m_maxHP; }
	inline void		setMaxHP(int mxhp){ m_state.m_maxHP = mxhp; }

	//< ����
	inline int		getMP(void) { return m_state.m_nowMP; }
	inline void		setMP(int mp) { m_state.m_nowMP = mp; }
	inline void		incMP(int offset) { m_state.m_nowMP += offset; }

	//< �ִ� ����
	inline int		getMaxMP(void) { return m_state.m_maxMP; }
	inline void		setMaxMP(int mxmp){ m_state.m_maxMP = mxmp; }

	//< ��
	inline int		getStrong(void) { return m_state.m_str; }
	inline void		setStrong(int str) { m_state.m_str = str; }
	inline void		incStrong(int offset) { m_state.m_str += offset; }
	//< ��
	inline int		getAgility(void) { return m_state.m_agl; }
	inline void		setAgility(int agl) { m_state.m_agl = agl; }
	inline void		incAgility(int offset) {m_state. m_agl += offset; }
	//< ��
	inline int		getIntel(void) { return m_state.m_int; }
	inline void		setIntel(int intel) { m_state.m_int = intel; }
	inline void		incIntel(int offset) {m_state. m_int += offset; }

	//< �ų�
	inline void		setBelief(int belief) { m_state.m_belief = belief; }
	inline int		getBelief(void) { return m_state.m_belief; }
	//< ����
	inline void		setTribe(int tribe) { m_state.m_tribe = tribe; }
	inline int		getTribe(void) { return m_state.m_tribe; }
	//< ����
	inline void		setJob(int job) { m_state.m_job = job; }
	inline int		getJob(void) { return m_state.m_job; }

	//< �����̻�
	inline void		setCondition(int cond) { m_state.m_condition = cond; }
	inline int		getCondition(void) { return m_state.m_condition; }


	//< ���� ��ȯ
	inline virtual POINT getCenter( void ){ return m_pos; }

protected:
	//< ����
	int m_kind;
	//< ��ġ
	POINT m_pos;
	//< ��������
	int m_dir;

	//< �������ͽ�
	STATES m_state;
};