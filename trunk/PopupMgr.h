#pragma once

class Popup_Loot;

//< 팝업 관리
class PopupMgr
{
private :
	PopupMgr(void);
	~PopupMgr(void);

	//< 싱글톤 만들기
	SINGLETON( PopupMgr );

public :
	//< 공용 인터페이스
	//< 초기화
	void initPopup( void );
	//< 팝업 업뎃
	void updatePopup( void );
	//< 팝업 랜더
	void renderPopup( HDC hdc );
	//< 팝업 바꾸기
	bool changePopup( unsigned int PopupID );
	//< 팝업 지우기
	void deletePopup( void );
	//< 이벤트 처리
	virtual LRESULT PopupProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

	//< 눌린 버튼으로 팝업 할당
	int buttonStatePopup( void );

	//< 버튼 돌리기
	void inButtonState( void )
	{
		if(NULL != nowPopup )
		{
			//< 팝업 버튼 돌리기
			//nowPopup->inNextScene( );
		}
	}

	inline bool getCheckPopup_ON() {return m_checkPopup_ON;}

	inline int GetNowPopUp(void) { return nowPopupFlag; }
private :
	//< 현재 팝업
	Popup_Loot *nowPopup;

	//< 마우스
	POINT m_mousePos;

	//< 현재 팝업 플래그
	int nowPopupFlag;
	//< 선택 팝업 플래그
	int oldPopupFlag;

	bool m_checkPopup_ON;
};

#define POPUP_MGR Singleton<PopupMgr>::GetInstance()

