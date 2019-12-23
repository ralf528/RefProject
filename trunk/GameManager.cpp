#include "stdafx.h"
#include "SceneIntro.h"
#include "SceneLobby.h"
#include "ScenePlayGame.h"
#include "GameManager.h"

GameManager::GameManager()
{

}
GameManager::~GameManager()
{
    Release();
}

bool GameManager::Init()
{   
    m_mainWnd = g_hWnd;
    m_mainInstance = g_hInst;

    srand(GetTickCount());

    LOG_MGR->logInit(JN_LOG_ALL);

    //< 경로얻기
    GetCurrentDirectory(_MAX_FNAME, m_path);

    //씬 추가
    //STATE_MGR->addState<SceneLobby>(SCENE_LOBBY);
    STATE_MGR->addState<ScenePlayGame>(SCENE_PLAYGAME);

    keyInput::initKey();

    //랜더 매니저 초기화 & 백 버퍼 이미지 생성
    RENDER_MGR->init();

    //fps초기화
    FpsTime::initFpsTime();

    //< 타이머 생성
    SetTimer(m_mainWnd, 1, 10, NULL);
    
    //< 메세지보내기 : 이걸보내면업데이트가 강제로 수행된다.(초기화다음에호출해라)
    SendMessage(m_mainWnd, WM_TIMER, 1, 0);
    LOG_MGR->addLog("윈도우 시작");

    STATE_MGR->changeState(SCENE_PLAYGAME);

    return true;
}

void GameManager::Release()
{
    KillTimer(m_mainWnd, 1);
}

void GameManager::Update()
{
    //씬 업데이트
    STATE_MGR->updateState(FpsTime::getElapsedTime());

    //fps 업데이트
    FpsTime::fpsTimeUpdate();

    if (STATE_MGR->nowScene() != STATE_MGR->findStatePtr(SCENE_INTRO))
    {
        //< 화면갱신
        InvalidateRect(m_mainWnd, NULL, FALSE);
    }
}

void GameManager::Render()
{
    //< 화면 클리어
    RENDER_MGR->clearBack();

    HDC backDC = RENDER_MGR->getBackDC();

    //씬 출력
    STATE_MGR->renderState(backDC);

    //< 실행경로
    TextOut( backDC, 0,0, m_path, strlen(m_path));

#ifdef _DEBUG
    //fps 출력
    FpsTime::renderFps(backDC, RGB(255, 0, 0));

    //< 마우스 위치 출력	
    char buff[50];
    sprintf_s(buff, 50, "X = %d", m_mousePos.x);
    TextOut(backDC, WINSIZE_X - 50, 0, buff, lstrlen(buff));
    sprintf_s(buff, 50, "Y = %d", m_mousePos.y);
    TextOut(backDC, WINSIZE_X - 50, 15, buff, lstrlen(buff));
#endif
    //< 프레임이 그려진 백버퍼를 출력
    RENDER_MGR->renderFrame();
}

WPARAM GameManager::MsgLoop()
{
    MSG			Message;		//메세지 구조체 선언	
                                //<GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterCrazy, UINT wMsgFilterMAx)메시지큐에서 읽어들인  메세지가 WM_QUIT면 false 리턴 나머지는 true 리턴
                                //<lpMsg : 메시지의 주소
                                //<hWnd : 윈도우의 핸들 0이면 모든 윈도우의 메시지를 가져오고, 핸들 값을 지정하면 그핸들값에 포함된 메시지만 가져온다.
                                //<wMsgFilterCrazy, wMsgFilterMAx : 메시지를 읽어들일 범위 최소값 최대값(사용할경우 시스템이 무한루프에 빠질수 있다.)
                                //< 4 메세지 루프(사용자로부터의 메시지를 처리한다 !메시지 구동시스템)
    while (true)
    {
        if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
        {
            if (Message.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
        else
        {
            Update();
        }
    }

    return Message.wParam;
}

LRESULT GameManager::WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT	ps;

    switch (msg)
    {
        //< 포커스처리
        case WM_SETFOCUS:
        {
            window::setFocusMainWindow(true);
        }
        break;
        case WM_KILLFOCUS:
        {
            window::setFocusMainWindow(false);
        }
        break;
        case WM_TIMER:
            break;

        case WM_PAINT:
            BeginPaint(wnd, &ps);
            Render();
            EndPaint(wnd, &ps);
            break;

        case WM_LBUTTONDOWN:
            break;

        case WM_MOUSEMOVE:
        {
            m_mousePos.x = LOWORD(lparam);
            m_mousePos.y = HIWORD(lparam);
        }
        break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
    }

    //< wndProc에서 처리 되지 않은 나머지 메시지들을 처리해준다.
    //< 윈도우크기 변경이나, 이동 등를 처리해준다.
    return STATE_MGR->StateProc(wnd, msg, wparam, lparam);
}