#pragma once

#include "Singleton.h"

//< 게임씬 상태
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

//< 상태(씬)메니저
class StateMgr
{
private:
	//씬 리스트 맵
	typedef std::map< unsigned int, State* >			StateList;
	//씬 리스트 반복자
	typedef std::map< unsigned int, State* >::iterator	StateListIter;

private:
	StateMgr(void);
	~StateMgr(void);

	SINGLETON( StateMgr );

public:
	//<씬 추가
	template<typename T>
	bool	addState( unsigned int StateID )
	{
		//<씬 찾기
		StateListIter iter = findState( StateID );
		//<끝까지 못찾았다면
		if( iter == m_stateList.end() )
		{
			State *pState = new T;
			//<씬 추가
			insertState( StateID, pState );
			return true;
		}
		//<씬이 있다면 false리턴
		return false;
	}

	//< 씬 업뎃
	void updateState(float fDeltaTime);
	//< 랜더 씬
	void renderState( HDC hdc );
	//< 씬 바꾸기
	bool changeState( unsigned int StateID );
	//< 씬 지우기
	void deleteState( const unsigned int StateID );
	//< 이벤트 처리
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );
	//< 찾기( 씬 )
	State* findStatePtr( unsigned int StateID );
	//< 현재 씬 리턴
	State* nowScene(void) { return m_State; }

	//> 임계영역 얻기
	inline CRITICAL_SECTION* getCS()				{ return &m_cs; }
	//> 로딩율 설정
	inline void setLoading(float perLoading)		{ m_perLoading = perLoading; }
	//> 로딩율 얻기
	inline float getLoading()						{ return m_perLoading; }

	inline void setLoadID(int loadID)				{ m_curLoadID = loadID; }			
	inline int* getLoadID()							{ return &m_curLoadID; }

private :

	//< 삽입
	void insertState( unsigned int StateID , State*	pState );
	//< 찾기( 이터 )
	StateListIter findState( unsigned int StateID );
	
	//< 모두 지우기
	void deleteStateAll( void );

private :
	//< 현재 씬
	State *m_State;
	//< 씬 저장 리스트
	StateList m_stateList;	

	//> 로딩율 변수
	float		m_perLoading;

	//> 임계 영역
	CRITICAL_SECTION	m_cs;

	//> 현재 로딩하는 씬 ID
	int			m_curLoadID;
};

#define STATE_MGR Singleton<StateMgr>::GetInstance()