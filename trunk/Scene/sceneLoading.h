#pragma once

#include "../Scene.h"

class sceneLoading : public Scene
{
public:
	//> 생성자 
	sceneLoading(void);
	//> 소멸자
	virtual ~sceneLoading(void);

	//> 초기화
	virtual bool init(void);
	//> 해제
	virtual void release(void);
	//> 갱신
	virtual void update(float fDeltaTime);
	//> 그리기
	virtual void render(HDC hdc);

	//> 메시지 프로시져
	virtual LRESULT StateProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	//> 멤버 함수
private:
	//> 로딩바 렌더
	void drawLoadingBar(HDC hdc);

	//> 멤버 변수
	int m_loadScene;
private:
};