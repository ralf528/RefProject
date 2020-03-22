#pragma once

#include "../Scene.h"

class sceneLoading : public Scene
{
public:
	//> ������ 
	sceneLoading(void);
	//> �Ҹ���
	virtual ~sceneLoading(void);

	//> �ʱ�ȭ
	virtual bool init(void);
	//> ����
	virtual void release(void);
	//> ����
	virtual void update(float fDeltaTime);
	//> �׸���
	virtual void render(HDC hdc);

	//> �޽��� ���ν���
	virtual LRESULT StateProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	//> ��� �Լ�
private:
	//> �ε��� ����
	void drawLoadingBar(HDC hdc);

	//> ��� ����
	int m_loadScene;
private:
};