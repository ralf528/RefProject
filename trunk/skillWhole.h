#pragma once

#include "cProjectile.h"

class skillWhole : public cProjectile
{
public:
	skillWhole(void);
	virtual ~skillWhole(void);

//< �������̽�	
	//������Ʈ
	virtual void update(void);
	//�׸���
	virtual void render(HDC hdc);

	//�߻�
	virtual void shoot( POINT &startPoint, POINT &destPos );

	//�ִϸ��̼� ����
	void setAniInfo(void);
	//����
	void updateAni( LPANI_INFO aniInfo );
	//����
	void releaseAniInfo( void );

protected:
	//��Ʈ ����
	virtual void setRect(void);
public:
	//< ī��Ʈ
	int m_count;
	//< �ִϸ��̼� �÷���
	bool m_AniFlag;

	//< �ִϸ��̼� ����
	LPANI_INFO m_Ani_Info;
};