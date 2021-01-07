#pragma once

#include "Singleton.h"

//< ���Ӿ� ����
enum
{
	SCENE_LOGIN,
	SCENE_TITLE,
	SCENE_LOBBY,
	SCENE_SELECT,
	SCENE_PLAYGAME,
	SCENE_RANK,	
};

class State;

//< ����(��)�޴���
class StateMgr
{
private:
	//�� ����Ʈ ��
	typedef std::map< unsigned int, State* >			StateList;
	//�� ����Ʈ �ݺ���
	typedef std::map< unsigned int, State* >::iterator	StateListIter;

private:
	StateMgr(void);
	~StateMgr(void);
	//�̱���
	SINGLETON( StateMgr );

public:
	//<�� �߰�
	template<typename T>
	bool	addState( unsigned int StateID )
	{
		//<�� ã��
		StateListIter iter = findState( StateID );
		//<������ ��ã�Ҵٸ�
		if( iter == m_stateList.end() )
		{
			State *pState = new T;
			//<�� �߰�
			insertState( StateID, pState );
			return true;
		}
		//<���� �ִٸ� false����
		return false;
	}

	//< �� ����
	void updateState( void );
	//< ���� ��
	void renderState( HDC hdc );
	//< �� �ٲٱ�
	bool changeState( unsigned int StateID );
	//< �� �����
	void deleteState( const unsigned int StateID );
	//< �̺�Ʈ ó��
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :

	//< ����
	void insertState( unsigned int StateID , State*	pState );
	//< ã��( ���� )
	StateListIter findState( unsigned int StateID );
	//< ã��( �� )
	State* findStatePtr( unsigned int StateID );
	//< ��� �����
	void deleteStateAll( void );

private :
	//< ���� ��
	State *m_State;
	//< �� ���� ����Ʈ
	StateList m_stateList;	
};

#define STATE_MGR Singleton<StateMgr>::getInstance()