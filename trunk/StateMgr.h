#pragma once

#include "Singleton.h"

//< ���Ӿ� ����
enum
{
	SCENE_INTRO,
	SCENE_LOGIN,
	SCENE_TITLE,
	SCENE_LOBBY,
	SCENE_SELECT,
	SCENE_LOADING,
	SCENE_PLAYGAME,
	SCENE_RANK,	
};

class State;

#define ENTER_SECTION			EnterCriticalSection( STATE_MGR->getCS() )
#define LEAVE_SECTION			LeaveCriticalSection( STATE_MGR->getCS() )

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
	void updateState(float fDeltaTime);
	//< ���� ��
	void renderState( HDC hdc );
	//< �� �ٲٱ�
	bool changeState( unsigned int StateID );
	//< �� �����
	void deleteState( const unsigned int StateID );
	//< �̺�Ʈ ó��
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );
	//< ã��( �� )
	State* findStatePtr( unsigned int StateID );
	//< ���� �� ����
	State* nowScene(void) { return m_State; }

	//> �Ӱ迵�� ���
	inline CRITICAL_SECTION* getCS()				{ return &m_cs; }
	//> �ε��� ����
	inline void setLoading(float perLoading)		{ m_perLoading = perLoading; }
	//> �ε��� ���
	inline float getLoading()						{ return m_perLoading; }

	inline void setLoadID(int loadID)				{ m_curLoadID = loadID; }			
	inline int* getLoadID()							{ return &m_curLoadID; }

private :

	//< ����
	void insertState( unsigned int StateID , State*	pState );
	//< ã��( ���� )
	StateListIter findState( unsigned int StateID );
	
	//< ��� �����
	void deleteStateAll( void );

private :
	//< ���� ��
	State *m_State;
	//< �� ���� ����Ʈ
	StateList m_stateList;	

	//> �ε��� ����
	float		m_perLoading;

	//> �Ӱ� ����
	CRITICAL_SECTION	m_cs;

	//> ���� �ε��ϴ� �� ID
	int			m_curLoadID;
};

#define STATE_MGR Singleton<StateMgr>::GetInstance()