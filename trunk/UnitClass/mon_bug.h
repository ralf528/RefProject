#pragma once

#include "../monster.h"

class mon_bug : public Monster
{
public:
//< ������ �Ҹ���
	mon_bug(void);
	virtual ~mon_bug(void);

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

	//< �浹ü ��Ʈ ��ȯ
	virtual RECT getBallRect(void);
	//< �浹ü ����
	virtual void setBallFlag( bool flag );
	virtual bool getBallFlag( void );
	//< ������
	virtual int getDamage(void);

	//�ִϸ��̼� ����
	void setAniInfo(void);
	//����
	void updateAni( LPANI_INFO aniInfo );

//< ���
private:
	//< ���� �浹ü
	cProjectile *ball;
	//< ���� ������
	DELEY attDeley;
};