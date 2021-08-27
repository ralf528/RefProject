#pragma once

#include "cProjectile.h"

class skillWhole : public cProjectile
{
public:
	skillWhole(void);
	virtual ~skillWhole(void);

//< 인터페이스	
	//업데이트
	virtual void update(void) override;
	//그리기
	virtual void render(HDC hdc) override;

	//발사
	virtual void shoot( POINT &startPoint, POINT &destPos, int dir = DIR_D) override;

	virtual bool IsPlaying() override { return m_AniFlag; }

private:
	//애니메이션 설정
	void setAniInfo(void);
	//갱신
	void updateAni( LPANI_INFO aniInfo );
	//해제
	void releaseAniInfo( void );

protected:
	//렉트 설정
	virtual void setRect(void);
public:
	//< 카운트
	int m_count;
	//< 애니메이션 플래그
	bool m_AniFlag;

	//< 애니메이션 정보
	LPANI_INFO m_Ani_Info;
};