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

    //< ��ξ��
    GetCurrentDirectory(_MAX_FNAME, m_path);

    //�� �߰�
    //STATE_MGR->addState<SceneLobby>(SCENE_LOBBY);
    STATE_MGR->addState<ScenePlayGame>(SCENE_PLAYGAME);

    keyInput::initKey();

    //���� �Ŵ��� �ʱ�ȭ & �� ���� �̹��� ����
    RENDER_MGR->init();

    //fps�ʱ�ȭ
    FpsTime::initFpsTime();

    //< Ÿ�̸� ����
    SetTimer(m_mainWnd, 1, 10, NULL);
    
    //< �޼��������� : �̰ɺ����������Ʈ�� ������ ����ȴ�.(�ʱ�ȭ������ȣ���ض�)
    SendMessage(m_mainWnd, WM_TIMER, 1, 0);
    LOG_MGR->addLog("������ ����");

    STATE_MGR->changeState(SCENE_PLAYGAME);

    return true;
}

void GameManager::Release()
{
    KillTimer(m_mainWnd, 1);
}

void GameManager::Update()
{
    //�� ������Ʈ
    STATE_MGR->updateState(FpsTime::getElapsedTime());

    //fps ������Ʈ
    FpsTime::fpsTimeUpdate();

    if (STATE_MGR->nowScene() != STATE_MGR->findStatePtr(SCENE_INTRO))
    {
        //< ȭ�鰻��
        InvalidateRect(m_mainWnd, NULL, FALSE);
    }
}

void GameManager::Render()
{
    //< ȭ�� Ŭ����
    RENDER_MGR->clearBack();

    HDC backDC = RENDER_MGR->getBackDC();

    //�� ���
    STATE_MGR->renderState(backDC);

    //< ������
    TextOut( backDC, 0,0, m_path, strlen(m_path));

#ifdef _DEBUG
    //fps ���
    FpsTime::renderFps(backDC, RGB(255, 0, 0));

    //< ���콺 ��ġ ���	
    char buff[50];
    sprintf_s(buff, 50, "X = %d", m_mousePos.x);
    TextOut(backDC, WINSIZE_X - 50, 0, buff, lstrlen(buff));
    sprintf_s(buff, 50, "Y = %d", m_mousePos.y);
    TextOut(backDC, WINSIZE_X - 50, 15, buff, lstrlen(buff));
#endif
    //< �������� �׷��� ����۸� ���
    RENDER_MGR->renderFrame();
}

WPARAM GameManager::MsgLoop()
{
    MSG			Message;		//�޼��� ����ü ����	
                                //<GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterCrazy, UINT wMsgFilterMAx)�޽���ť���� �о����  �޼����� WM_QUIT�� false ���� �������� true ����
                                //<lpMsg : �޽����� �ּ�
                                //<hWnd : �������� �ڵ� 0�̸� ��� �������� �޽����� ��������, �ڵ� ���� �����ϸ� ���ڵ鰪�� ���Ե� �޽����� �����´�.
                                //<wMsgFilterCrazy, wMsgFilterMAx : �޽����� �о���� ���� �ּҰ� �ִ밪(����Ұ�� �ý����� ���ѷ����� ������ �ִ�.)
                                //< 4 �޼��� ����(����ڷκ����� �޽����� ó���Ѵ� !�޽��� �����ý���)
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
        //< ��Ŀ��ó��
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

    //< wndProc���� ó�� ���� ���� ������ �޽������� ó�����ش�.
    //< ������ũ�� �����̳�, �̵� � ó�����ش�.
    return STATE_MGR->StateProc(wnd, msg, wparam, lparam);
}