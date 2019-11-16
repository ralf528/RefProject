#include "stdafx.h"
//#include "otherCharacter.h"
#include "other_mgr.h"

Other_manager::Other_manager(void)
{
	init();
}
Other_manager::~Other_manager(void)
{
	deleteAll();
}


//< 초기화
bool Other_manager::init(void)
{
	m_otherList.clear();

	return true;
}
//< 업데이트
void Other_manager::update(void)
{
	/*other_map_iter iter = m_otherList.begin();
	for( ; iter != m_otherList.end() ; ++iter )
	{
		if( NULL != iter->second )
		{
			iter->second->update();
		}
	}*/
}
//< 랜더
void Other_manager::render(HDC hdc)
{
	/*other_map_iter iter = m_otherList.begin();
	for( ; iter != m_otherList.end() ; ++iter )
	{
		if( NULL != iter->second )
		{
			iter->second->render(hdc);
		}
	}*/
}

//< 추가
void Other_manager::addOther(char* ID, otherCharacter* other)
{
	//< 중복 검사
	other_map_iter iter = m_otherList.find( ID );
	//< 중복이면
	if( iter != m_otherList.end() )
	{
		//< 중복 추가
		LOG_MGR->addLog( "other(%s) 중복 추가", ID );
		return;
	}
	//< 중복 아니면
	m_otherList.insert( make_pair(ID, other) );
}

//< 검색
otherCharacter* Other_manager::findOther(char* ID)
{
	//검색
	other_map_iter iter = m_otherList.find( ID );
	if( iter != m_otherList.end() )
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

//< 삭제
void Other_manager::deleteOther(char* ID)
{
	//검색
	//other_map_iter iter = m_otherList.find( ID );
	////< 아이디가 있다면
	//if( iter != m_otherList.end() )
	//{
	//	if( NULL != iter->second )
	//	{
	//		//iter->second->release();
	//		delete iter->second;
	//		iter->second = NULL;
	//	}
	//	//< 아더 삭제
	//	m_otherList.erase(iter);
	//}
}
//< 전체 삭제
void Other_manager::deleteAll(void)
{
	//other_map_iter iter = m_otherList.begin();
	////< 전체 반복
	//for( ; iter != m_otherList.end() ;  )
	//{
	//	if( NULL != iter->second )
	//	{
	//		//< NULL이 아니면 삭제 후 이터레이터 반환
	//		delete iter->second;
	//		iter->second = NULL;
	//		iter = m_otherList.erase(iter);
	//	}
	//	else
	//	{
	//		++iter;
	//	}
	//}
	//m_otherList.clear();
}

//< 메시지 받기
void Other_manager::receiveMessage(char* ID, int state)
{
	//< 검색
	//other_map_iter iter = m_otherList.find( ID );
	//if( iter != m_otherList.end() )
	//{
	//	//< 상태 전달
	//	iter->second->receiveState( state );
	//}
}