#pragma once

#include "cProjectile.h"

class skillWhole : public cProjectile
{
public:
	skillWhole(void);
	virtual ~skillWhole(void);

//< �������̽�	
	//������Ʈ
	virtual void update(void) override;
	//�׸���
	virtual void render(HDC hdc) override;

	//�߻�
	virtual void shoot( POINT &startPoint, POINT &destPos, int dir = DIR_D) override;

	virtual bool IsPlaying() override { return m_AniFlag; }

private:
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