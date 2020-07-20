#include "stdafx.h"
#include "../ScenePlayGame.h"
#include "sceneLoading.h"

//> �ε� �ؽ�Ʈ ������
const int TEXT_WIDTH = 38;
const int TEXT_HEIGHT = 13;

//> �ε��� ������
const int LOADBAR_WIDTH = 825-450;
const int LOADBAR_HEIGHT = 15;

enum
{
	IMAGE_BG,
	IMAGE_END,
};

//> ������ 
sceneLoading::sceneLoading()
{
}
//> �Ҹ���
sceneLoading::~sceneLoading()
{
	release();
}

//> �ʱ�ȭ
bool sceneLoading::init()
{
	//> �̹��� �Ҵ�
	RC_MGR->addImage( imgID_GAME_LOADING , "Data/Resource/gameUI/loading.bmp");
	//> ��� �̹��� �ʱ�ȭ

	m_loadScene = *STATE_MGR->getLoadID();
	switch(m_loadScene)
	{
	case SCENE_PLAYGAME:
		{
			/*if(false == HOST_SERVER->getHostis())
			{
				TCPIP_CLIENT->serverConnect(GAME_DATA->getHostAddr(), GAME_DATA->getHostPort());
			}*/
		}
		break;
	}
	return true;
}
//> ����
void sceneLoading::release()
{
}
//> ����
void sceneLoading::update(float fDeltaTime)
{
	switch(m_loadScene)
	{
	case SCENE_PLAYGAME:
		{
			ScenePlayGame* gameScene = dynamic_cast<ScenePlayGame*>(STATE_MGR->findStatePtr(SCENE_PLAYGAME));
			if(NULL != gameScene)
			{
				/*if(false == TCPIP_CLIENT->emptyQueue())
				{
					LOG_MGR->addLog("[OTHER] PACKET GET");
					PACKET packet;
					TCPIP_CLIENT->getPacket(packet);
					gameScene->packetProcess(&packet);
					TCPIP_CLIENT->popPacket();
				}*/
			}
		}
		break;
	}
}
//> �׸���
void sceneLoading::render(HDC hdc)
{
	
	//> ��� �̹��� ����
	RENDER_MGR->render( hdc, imgID_GAME_LOADING, 0, 0 );
	//> �ε��� ����
	drawLoadingBar(hdc);
}

//> �ε��� ����
void sceneLoading::drawLoadingBar(HDC hdc)
{
	//< �ε� ���ȭ��
//> �ε��� ����
	TCHAR szBuf[_MAX_FNAME];
	sprintf_s(szBuf, _MAX_FNAME, _T("%.1f"), STATE_MGR->getLoading());
//	sprintf_s(szBuf, _MAX_FNAME, _T("%.1f"), 100.f);

	float percent = (LOADBAR_WIDTH / 100.f) * STATE_MGR->getLoading();

	int startX = 450;
	int startY = 540;

	//> �ε��� ���
	Rectangle(hdc, startX, startY, (int)(startX+percent), startY+LOADBAR_HEIGHT);

	//> �ε��� ���� ���
	RECT tectRt = {(LONG)(startX+percent)-TEXT_WIDTH, startY-15, (LONG)(startX+percent), startY-15+TEXT_HEIGHT};

	//> ���� �� ��� ����
	SetBkMode(hdc, TRANSPARENT);
	//>
	SetTextColor(hdc, RGB(255, 0, 0));

	DrawText(hdc, szBuf, -1, &tectRt, DT_LEFT | DT_SINGLELINE);

	//> ���� �޹�� ����
	SetBkMode(hdc, OPAQUE);
}

//> �޽��� ���ν���
LRESULT sceneLoading::StateProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	/*switch(iMessage)
	{
	case WM_MYSOCKET_NOTIFY:
		{
			TCPIP_CLIENT->onMySocketNotify(wParam, lParam);
		}
		break;
	}*/
	return DefWindowProc( hWnd, iMessage, wParam, lParam);
}