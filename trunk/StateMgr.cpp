#include "stdafx.h"
#include "StateMgr.h"
#include "State.h"

StateMgr::StateMgr(void)
	:m_State(NULL)
{
	//> �Ӱ� ���� �ʱ�ȭ
	InitializeCriticalSection(&m_cs);
}
StateMgr::~StateMgr(void)
{
	//> �Ӱ� ���� ����
	DeleteCriticalSection(&m_cs);
	//<��� �� ����
	deleteStateAll();
}

//< �� ����
void StateMgr::updateState( void )
{
	if(NULL != m_State)
	{
		m_State->update();
	}
}
//< ���� ��
void StateMgr::renderState( HDC hdc )
{
	if(NULL != m_State)
	{
		m_State->render(hdc);
	}
}
//< �� �ٲٱ�
bool StateMgr::changeState( unsigned int StateID )
{
	//< ��ã��
	State *newState = findStatePtr( StateID );

	//< ����� üũ
	if( NULL != newState )
	{
		//< ���ο�� �ʱ�ȭ
		newState->init();

		//< ������ ����
		if( NULL != m_State )
		{
			m_State->release();
		}
		//< ���ο� �� ����
		m_State = newState;

		//���� ���� �Ǿ��ٸ�
		return true;
	}
	//���� ������� �ʾҴٸ�
	return false;
}

//< ����
void StateMgr::insertState( unsigned int StateID , State*	pState )
{
	m_stateList.insert( make_pair(StateID,pState) );
}
//< ã��( ���� )
StateMgr::StateListIter StateMgr::findState( unsigned int StateID )
{
	return m_stateList.find( StateID );
}
//< ã��( �� )
State* StateMgr::findStatePtr( unsigned int StateID )
{
	//ã�Ҵٸ�
	if( findState( StateID ) != m_stateList.end() )
	{
		//���� ����
		return m_stateList[StateID];
	}
	return NULL;
}
//< ��� �����
void StateMgr::deleteStateAll( void )
{
	//< ��������
	StateListIter	iter = m_stateList.begin();

	//������ ��ұ��� �ݺ�
	for( ; iter != m_stateList.end(); )
	{
		//< Ȯ��
		State	*State = iter->second;
		if( NULL != State )
		{
			//���� ����
			State->release();
			delete iter->second;
			iter->second=NULL;
			//����Ʈ���� ����
			iter = m_stateList.erase( iter );
		}
		else
		{
			++iter;
		}		
	}
	//< ����
	m_stateList.clear();
}

//< �������
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

//< �̺�Ʈ ó��
LRESULT StateMgr::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	if( NULL != m_State )
	{
		return m_State->StateProc( wnd , msg, wparam , lparam );
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}