#pragma once

class Popup_Loot;

//< �˾� ����
class PopupMgr
{
private :
	PopupMgr(void);
	~PopupMgr(void);

	//< �̱��� �����
	SINGLETON( PopupMgr );

public :
	//< ���� �������̽�
	//< �ʱ�ȭ
	void initPopup( void );
	//< �˾� ����
	void updatePopup( void );
	//< �˾� ����
	void renderPopup( HDC hdc );
	//< �˾� �ٲٱ�
	bool changePopup( unsigned int PopupID );
	//< �˾� �����
	void deletePopup( void );
	//< �̺�Ʈ ó��
	virtual LRESULT PopupProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

	//< ���� ��ư���� �˾� �Ҵ�
	int buttonStatePopup( void );

	//< ��ư ������
	void inButtonState( void )
	{
		if(NULL != nowPopup )
		{
			//< �˾� ��ư ������
			//nowPopup->inNextScene( );
		}
	}

	inline bool getCheckPopup_ON() {return m_checkPopup_ON;}

	inline int GetNowPopUp(void) { return nowPopupFlag; }
private :
	//< ���� �˾�
	Popup_Loot *nowPopup;

	//< ���콺
	POINT m_mousePos;

	//< ���� �˾� �÷���
	int nowPopupFlag;
	//< ���� �˾� �÷���
	int oldPopupFlag;

	bool m_checkPopup_ON;
};

#define POPUP_MGR Singleton<PopupMgr>::GetInstance()

