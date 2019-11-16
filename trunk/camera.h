#pragma once

#include "singleton.h"

class Camera
{
private:
	Camera(void);
	~Camera(void);

	SINGLETON(Camera);
public:
	//< 초기화
	void init(void);
	//< 카메라 갱신
	void update(void);
	//< 카메라 이동
	void moveCamera( LONG cx, LONG cy );
	//< 위치 설정
	void setPosition( LONG x, LONG y );

	//< 카메라 진동
	void cameraShaking( unsigned int count = 60 );

	LONG getX(void) { return m_viewOffSetX; }
	LONG getY(void) { return m_viewOffSetY; }

private:
	//< 뷰 오프셋
	LONG m_viewOffSetX;
	LONG m_viewOffSetY;

	//< 카메라 셰이킹 플래그
	bool m_isShaking;

	//< 이전 위치
	LONG prevPosX;
	LONG prevPosY;

	//< 셰이킹 시작 시작
	DWORD m_shakeStart;
	//< 셰이킹 카운트
	unsigned int m_shakeCount;
};

#define CAMERA Singleton<Camera>::GetInstance()