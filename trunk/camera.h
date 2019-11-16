#pragma once

#include "singleton.h"

class Camera
{
private:
	Camera(void);
	~Camera(void);

	SINGLETON(Camera);
public:
	//< �ʱ�ȭ
	void init(void);
	//< ī�޶� ����
	void update(void);
	//< ī�޶� �̵�
	void moveCamera( LONG cx, LONG cy );
	//< ��ġ ����
	void setPosition( LONG x, LONG y );

	//< ī�޶� ����
	void cameraShaking( unsigned int count = 60 );

	LONG getX(void) { return m_viewOffSetX; }
	LONG getY(void) { return m_viewOffSetY; }

private:
	//< �� ������
	LONG m_viewOffSetX;
	LONG m_viewOffSetY;

	//< ī�޶� ����ŷ �÷���
	bool m_isShaking;

	//< ���� ��ġ
	LONG prevPosX;
	LONG prevPosY;

	//< ����ŷ ���� ����
	DWORD m_shakeStart;
	//< ����ŷ ī��Ʈ
	unsigned int m_shakeCount;
};

#define CAMERA Singleton<Camera>::GetInstance()