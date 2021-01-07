#pragma once

class ImageNode;

//���� ��ü
class sphereObject
{
public:
	//������ �Ҹ���
	sphereObject(void);
	~sphereObject(void);

public:
	//< �������̽�	
	//�ʱ�ȭ
	bool init(void);
	//����
	void release(void);
	//������Ʈ
	void update(void);
	//�׸���
	void render(HDC hdc);

	//�߻�
	void shoot( POINT &startPoint, int dir );
	//

	//��ġ ����
	void setPos(POINT pos);
	void setPos(LONG x, LONG y);
	//��ġ ����
	POINT getPos(void) { return m_pos; }

private:
	//< ���� �Լ�
	//��Ʈ ����
	void setRect(void);

private:
	//�߻�� ��ġ
	POINT m_startPos;
	//���� ��ġ
	POINT m_pos;
	RECT m_rect;
	//����ִ���
	bool m_flag;
	//����
	int m_dir;
	//�ӵ�
	int m_speed;
	
	//�̹���
	ImageNode *m_img;
};