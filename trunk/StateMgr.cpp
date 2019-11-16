#include "stdafx.h"
#include "StateMgr.h"
#include "State.h"

StateMgr::StateMgr(void)
	:m_State(NULL)
{
	//> 임계 영역 초기화
	InitializeCriticalSection(&m_cs);
}
StateMgr::~StateMgr(void)
{
	//> 임계 영역 해제
	DeleteCriticalSection(&m_cs);
	//<모든 씬 정리
	deleteStateAll();
}

//< 씬 업뎃
void StateMgr::updateState( void )
{
	if(NULL != m_State)
	{
		m_State->update();
	}
}
//< 랜더 씬
void StateMgr::renderState( HDC hdc )
{
	if(NULL != m_State)
	{
		m_State->render(hdc);
	}
}
//< 씬 바꾸기
bool StateMgr::changeState( unsigned int StateID )
{
	//< 씬찾기
	State *newState = findStatePtr( StateID );

	//< 변경씬 체크
	if( NULL != newState )
	{
		//< 새로운씬 초기화
		newState->init();

		//< 이전씬 해제
		if( NULL != m_State )
		{
			m_State->release();
		}
		//< 새로운 씬 설정
		m_State = newState;

		//씬이 변경 되었다면
		return true;
	}
	//씬이 변경되지 않았다면
	return false;
}

//< 삽입
void StateMgr::insertState( unsigned int StateID , State*	pState )
{
	m_stateList.insert( make_pair(StateID,pState) );
}
//< 찾기( 이터 )
StateMgr::StateListIter StateMgr::findState( unsigned int StateID )
{
	return m_stateList.find( StateID );
}
//< 찾기( 씬 )
State* StateMgr::findStatePtr( unsigned int StateID )
{
	//찾았다면
	if( findState( StateID ) != m_stateList.end() )
	{
		//씬을 리턴
		return m_stateList[StateID];
	}
	return NULL;
}
//< 모두 지우기
void StateMgr::deleteStateAll( void )
{
	//< 모두지우기
	StateListIter	iter = m_stateList.begin();

	//마지막 요소까지 반복
	for( ; iter != m_stateList.end(); )
	{
		//< 확인
		State	*State = iter->second;
		if( NULL != State )
		{
			//상태 해제
			State->release();
			delete iter->second;
			iter->second=NULL;
			//리스트에서 삭제
			iter = m_stateList.erase( iter );
		}
		else
		{
			++iter;
		}		
	}
	//< 정리
	m_stateList.clear();
}

//< 씬지우기
void StateMgr::deleteState( const unsigned int StateID )
{
	StateListIter iter = m_stateList.find( StateID );

	if( iter != m_stateList.end() )
	{
		iter->second->release();
		delete iter->second;
		iter->second = NULL;
		m_stateList.erase( iter );
	}
}

//< 이벤트 처리
LRESULT StateMgr::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	if( NULL != m_State )
	{
		return m_State->StateProc( wnd , msg, wparam , lparam );
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}