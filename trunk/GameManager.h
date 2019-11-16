#pragma once

#include "Singleton.h"
#include <Windows.h>

class GameManager
{
private:
    GameManager();
    ~GameManager();

    SINGLETON(GameManager);

public:
    bool Init();
    void Release();
    void Update();
    void Render();

    WPARAM MsgLoop();
    LRESULT WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

    //< ������ �ڵ� ���
    inline HWND			GetHwnd(void) { return m_mainWnd; }
    //< ���� ������ �ν��Ͻ� �ڵ���
    inline HINSTANCE	GetInst(void) { return m_mainInstance; }

    HWND		m_mainWnd;
    HINSTANCE	m_mainInstance;

    POINT m_mousePos;
    char m_path[_MAX_FNAME];
};

#define GAME_MGR Singleton<GameManager>::GetInstance()