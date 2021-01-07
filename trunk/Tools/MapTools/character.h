#pragma once

//< ���� ĳ���� Ŭ����
class character
{
//< ������ �Ҹ���
public:
	character(void);
	~character(void);

//< �������̽�
public:
	//< �ʱ�ȭ
	bool init(void);
	//< ����
	void release(void);
	//< ����
	void update(void);
	//< ����
	void render(HDC hdc);

	//< �̵�
	void move( void );
	//< ��ǥ ����
	void setPos( POINT &pos );
	void setPos( LONG x, LONG y );
	POINT getPos(void) { return m_pos; }
	//< ���� ��ġ�� �ǵ�����
	void setPosToPrev(void);
	//< ���� ����
	void setDir(int dir);
	int getDir(void) { return m_dir; }

//< ���� �Լ�
private:
	//< ��Ʈ ����
	void setRect(void);

//< ��� ����
private:
	//< ĳ���� ��ǥ
	POINT m_pos;
	//< �̵� �� ��ǥ
	POINT m_prevPos;
	//< ĳ���� ��Ʈ
	RECT m_rect;

	//< ĳ���� �̵� �ӵ�
	int m_moveSpeed;
	//< ĳ���� ��������
	int m_dir;
};