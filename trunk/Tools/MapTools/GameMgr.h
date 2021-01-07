#pragma once

#include "Singleton.h"

//��Ʈ �Ŵ���
class MY_FontMgr;
//�̹��� ���
class ImageNode;
//< ��
class tileMap;

class GameMgr
{
private:
	GameMgr(void);
	~GameMgr(void);

	//< �̱������� ������
	SINGLETON( GameMgr );

public:
	//////////////////////////////////////////////////////////////////////////
	//<�ܺ� �������̽�
	//////////////////////////////////////////////////////////////////////////
	//< �ʱ�ȭ
	bool	init( void );
	//< ������Ʈ
	void	update( void );
	//< ����
	void	render( void );
	//< ����
	void	release( void );

	//< �޽�������
	WPARAM	msgLoop( void );
	//< ���ν���
	LRESULT WndProc(HWND wnd ,UINT msg ,WPARAM wparam, LPARAM lparam );

	//< ������ �ڵ� ���
	inline HWND			getHwnd(void)		{ return m_mainWnd; }
	//< ���� ������ �ν��Ͻ� �ڵ���
	inline HINSTANCE	getInst( void )		{ return m_mainInstance; }

	//< ���̾�α� ���ν���
	friend BOOL CALLBACK newMapDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	//////////////////////////////////////////////////////////////////////////
	//< ���� �Լ�	
	//////////////////////////////////////////////////////////////////////////
	void	clearScreen( void );

private:
	//////////////////////////////////////////////////////////////////////////
	//< �������
	//////////////////////////////////////////////////////////////////////////
	//< ���� ������ �ڵ�
	HWND		m_mainWnd;
	HINSTANCE	m_mainInstance;	
	
	//< ������
	char	m_path[ _MAX_FNAME ];

	//< ��ǥ
	POINT		m_mousePos;
};

//< �����Ŵ���
#define GAME_MGR	Singleton<GameMgr>::getInstance()
