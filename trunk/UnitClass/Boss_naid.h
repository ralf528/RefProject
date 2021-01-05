#pragma once

#include "../monster.h"

class skill_naid_collum;

class boss_naid : public Monster
{
public:
	boss_naid(void);
	virtual ~boss_naid(void);

public:
//< �������̽�
	//< �ʱ�ȭ
	virtual bool init(void);
	//< ����
	virtual void release(void);
	//< ������Ʈ
	virtual void update( void );
	//< ����
	virtual void render(HDC hdc);

	//< �浹 üũ
	virtual bool collision( POINT &destPos );
	//< ����
	virtual void attack( POINT &destPos );
	//< �ν�
	virtual void recog( POINT &destPos );

	//< Ÿ��
	virtual bool beHit(int damage); 
	//< �浹ü ��Ʈ ��ȯ
	virtual RECT getBallRect(void);
	//< �浹ü ����
	virtual void setBallFlag( bool flag );
	virtual bool getBallFlag( void );
	//< ������
	virtual int getDamage(void);

	//�ִϸ��̼� ����
	void setAniInfo(void);

//< ���
private:
	//< ���� �浹ü
	cProjectile *ball;
	//< ���� ������
	DELEY attDeley;	

	//< ��ų �浹ü
	//skill_naid_collum *m_skill_collum;
	//< ��ų ������
	DELEY m_collum_deley;
};