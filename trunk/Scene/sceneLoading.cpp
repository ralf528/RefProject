#include "stdafx.h"
#include "../ScenePlayGame.h"
#include "sceneLoading.h"

//> 로딩 텍스트 사이즈
const int TEXT_WIDTH = 38;
const int TEXT_HEIGHT = 13;

//> 로딩바 사이즈
const int LOADBAR_WIDTH = 825-450;
const int LOADBAR_HEIGHT = 15;

enum
{
	IMAGE_BG,
	IMAGE_END,
};

//> 생성자 
sceneLoading::sceneLoading()
{
}
//> 소멸자
sceneLoading::~sceneLoading()
{
	release();
}

//> 초기화
bool sceneLoading::init()
{
	//> 이미지 할당
	RC_MGR->addImage( imgID_GAME_LOADING , "Data/Resource/gameUI/loading.bmp");
	//> 배경 이미지 초기화

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
//> 해제
void sceneLoading::release()
{
}
//> 갱신
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
//> 그리기
void sceneLoading::render(HDC hdc)
{
	
	//> 배경 이미지 렌더
	RENDER_MGR->render( hdc, imgID_GAME_LOADING, 0, 0 );
	//> 로딩바 렌더
	drawLoadingBar(hdc);
}

//> 로딩바 렌더
void sceneLoading::drawLoadingBar(HDC hdc)
{
	//< 로딩 배경화면
//> 로딩율 문자
	TCHAR szBuf[_MAX_FNAME];
	sprintf_s(szBuf, _MAX_FNAME, _T("%.1f"), STATE_MGR->getLoading());
//	sprintf_s(szBuf, _MAX_FNAME, _T("%.1f"), 100.f);

	float percent = (LOADBAR_WIDTH / 100.f) * STATE_MGR->getLoading();

	int startX = 450;
	int startY = 540;

	//> 로딩바 출력
	Rectangle(hdc, startX, startY, (int)(startX+percent), startY+LOADBAR_HEIGHT);

	//> 로딩율 문자 출력
	RECT tectRt = {(LONG)(startX+percent)-TEXT_WIDTH, startY-15, (LONG)(startX+percent), startY-15+TEXT_HEIGHT};

	//> 글자 뒷 배경 투명
	SetBkMode(hdc, TRANSPARENT);
	//>
	SetTextColor(hdc, RGB(255, 0, 0));

	DrawText(hdc, szBuf, -1, &tectRt, DT_LEFT | DT_SINGLELINE);

	//> 글자 뒷배경 복구
	SetBkMode(hdc, OPAQUE);
}

//> 메시지 프로시져
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