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
	virtual void update(float fDeltaTime) = 0;
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
	inline int		getMoveSpeed(void) { return m_moveSpeed.GetValue(); } 
	inline void		setMoveSpeed(ESTATUS_TYPE type, int speed) { m_moveSpeed.SetValue(type, speed); }

	//< ü��
	inline int		getHP(void) { return m_nowHP; }
	inline void		setHP(int hp) { m_nowHP = hp; }
	void			incHP(int offset);
	
	//< �ִ� ü��
	inline int		getMaxHP(void) { return m_maxHP.GetValue(); }
	inline void		setMaxHP(ESTATUS_TYPE type, int mxhp) { m_maxHP.SetValue(type, mxhp); }

	//< ����
	inline int		getMP(void) { return m_nowMP; }
	inline void		setMP(int mp) { m_nowMP = mp; }
	inline void		incMP(int offset) { m_nowMP += offset; }

	//< �ִ� ����
	inline int		getMaxMP(void) { return m_maxMP.GetValue(); }
	inline void		setMaxMP(ESTATUS_TYPE type, int mxmp){ m_maxMP.SetValue(type, mxmp); }

	//< ��
	inline int		getStrong(void) { return m_str.GetValue(); }
	inline void		setStrong(ESTATUS_TYPE type, int str) { m_str.SetValue(type, str); }
	inline void		incStrong(ESTATUS_TYPE type, int offset) { m_str.AddValue(type, offset); }
	//< ��
	inline int		getAgility(void) { return m_agl.GetValue(); }
	inline void		setAgility(ESTATUS_TYPE type, int agl) { m_agl.SetValue(type, agl); }
	inline void		incAgility(ESTATUS_TYPE type, int offset) { m_agl.AddValue(type, offset); }
	//< ��
	inline int		getIntel(void) { return m_int.GetValue(); }
	inline void		setIntel(ESTATUS_TYPE type, int intel) { m_int.SetValue(type,intel); }
	inline void		incIntel(ESTATUS_TYPE type, int offset) { m_int.AddValue(type, offset); }

	//< �ų�
	inline void		setBelief(int belief) { m_belief = belief; }
	inline int		getBelief(void) { return m_belief; }
	//< ����
	inline void		setTribe(int tribe) { m_tribe = tribe; }
	inline int		getTribe(void) { return m_tribe; }
	//< ����
	inline void		setJob(int job) { m_job = job; }
	inline int		getJob(void) { return m_job; }

	//< �����̻�
	void			setCondition(int cond, int delay = 0);
	inline int		getCondition(void) { return m_Abnormal.AbnormalType; }
	void			UpdateCondition();


	//< ���� ��ȯ
	inline virtual POINT getCenter( void ){ return m_pos; }

protected:
	//< ����
	int m_kind;
	//< ��ġ
	POINT m_pos;
	//< ��������
	int m_dir;

	//< �ų�
	unsigned int m_belief;
	//< ����
	unsigned int m_tribe;
	//< ����
	unsigned int m_job;

	//< �����̻�
	Abnormal m_Abnormal;

	StatusType m_maxHP;
	int m_nowHP;
	StatusType m_maxMP;
	int m_nowMP;
	
	StatusType m_str;
	StatusType m_agl;
	StatusType m_int;

	//< �̵��ӵ�
	StatusType m_moveSpeed;
};