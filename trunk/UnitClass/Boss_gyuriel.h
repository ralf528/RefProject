#pragma once

#include "../monster.h"

class Gyuriel : public Monster
{
public:
	Gyuriel(void);
	virtual ~Gyuriel(void);

public:
//< �������̽�
	//< �ʱ�ȭ
	virtual bool init(void);
	//< ����
	virtual void release(void);
	//< ������Ʈ
	virtual void update(float fDeltaTime);
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
	//< ���� ��Ʈ ��ȯ
	virtual RECT getRect( void );
	//< �浹ü ��Ʈ ��ȯ
	virtual RECT getBallRect(void);
	//< �浹ü ����
	virtual void setBallFlag( bool flag );
	virtual bool getBallFlag( void );
	//< ������
	virtual int getDamage(void);

	//< HP �� ����
	virtual void renderHPbar(HDC hdc);

	//�ִϸ��̼� ����
	void setAniInfo(void);
	//����
	void updateAni( LPANI_INFO aniInfo );
	//����
	virtual void releaseAniInfo( void );

	//< ������ ���
	//< ����
	virtual void normalAttack(POINT &destPos);
	//< ��ų 1
	virtual void skill_01(POINT &destPos);
	//< ��ų 2
	virtual void skill_02(POINT &destPos);

//< ���
private:
	//< ���� �浹ü
	cProjectile *ball;
	//< ���� ������
	DELEY attDeley;	

	//< ��ų �浹ü
	cProjectile *m_skill_collum;
	cProjectile *m_skill_destruction;

	//< ��ų ������
	DELEY m_collum_deley;
	DELEY m_destroy_deley;

	//< ����� �ִϸ��̼�
	LPANI_INFO m_spclAni_info;
};