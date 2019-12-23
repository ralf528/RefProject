#pragma once

//�浹 ������Ʈ(����)
class cProjectile
{
public:
	//������ �Ҹ���
	cProjectile( int damage = 1, int range = 5, int speed = 10 );
	virtual ~cProjectile(void);

public:
	//< �������̽�	
	//�ʱ�ȭ
	virtual bool init(int damage, int speed, int range);
	//����
	virtual void release(void);
	//������Ʈ
	virtual void update(void);
	//�׸���
	virtual void render(HDC hdc);

	//�߻�
	virtual void shoot( POINT &startPoint, POINT &destPos );

	//��ġ ����
	virtual void setPos(POINT pos);
	virtual void setPos(LONG x, LONG y);

	//< ������ ����
	virtual void setDamage(int damage)	{ m_damage = damage; }
	virtual int getDamage(void)			{ return m_damage; }
	//< �̵� �ӵ� ����
	virtual void setSpeed(int speed)	{ m_speed = speed; }
	virtual int getSpeed(void)			{ return m_speed;}
	//< ��Ÿ� ����
	virtual void setRange(int range)	{ m_range = range; }
	virtual int getRange(void)			{ return m_range; }
	//��ġ ����
	virtual POINT getPos(void) { return m_pos; }
	//< �÷��� ����
	virtual bool getFlag(void) { return m_flag; }
	virtual void setFlag( bool flag ) { m_flag = flag; }
	//< ��Ʈ
	virtual RECT getRect(void) { return m_rect; }

protected:
	//< ���� �Լ�
	//��Ʈ ����
	virtual void setRect(void);

protected:
	//< �߻�� ��ġ
	POINT m_startPos;
	//< ���� ��ġ
	POINT m_pos;
	//< ��ǥ ��ġ
	POINT m_destPos;

	//< �簢��(�浹üũ ��)
	RECT m_rect;
	
	//< ������
	int m_damage;
	//< ����ִ���
	bool m_flag;
	//< �̵� �ӵ�
	int m_speed;
	//< ��Ÿ�
	int m_range;
};