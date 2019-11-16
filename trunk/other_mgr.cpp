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


//< �ʱ�ȭ
bool Other_manager::init(void)
{
	m_otherList.clear();

	return true;
}
//< ������Ʈ
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
//< ����
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

//< �߰�
void Other_manager::addOther(char* ID, otherCharacter* other)
{
	//< �ߺ� �˻�
	other_map_iter iter = m_otherList.find( ID );
	//< �ߺ��̸�
	if( iter != m_otherList.end() )
	{
		//< �ߺ� �߰�
		LOG_MGR->addLog( "other(%s) �ߺ� �߰�", ID );
		return;
	}
	//< �ߺ� �ƴϸ�
	m_otherList.insert( make_pair(ID, other) );
}

//< �˻�
otherCharacter* Other_manager::findOther(char* ID)
{
	//�˻�
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

//< ����
void Other_manager::deleteOther(char* ID)
{
	//�˻�
	//other_map_iter iter = m_otherList.find( ID );
	////< ���̵� �ִٸ�
	//if( iter != m_otherList.end() )
	//{
	//	if( NULL != iter->second )
	//	{
	//		//iter->second->release();
	//		delete iter->second;
	//		iter->second = NULL;
	//	}
	//	//< �ƴ� ����
	//	m_otherList.erase(iter);
	//}
}
//< ��ü ����
void Other_manager::deleteAll(void)
{
	//other_map_iter iter = m_otherList.begin();
	////< ��ü �ݺ�
	//for( ; iter != m_otherList.end() ;  )
	//{
	//	if( NULL != iter->second )
	//	{
	//		//< NULL�� �ƴϸ� ���� �� ���ͷ����� ��ȯ
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

//< �޽��� �ޱ�
void Other_manager::receiveMessage(char* ID, int state)
{
	//< �˻�
	//other_map_iter iter = m_otherList.find( ID );
	//if( iter != m_otherList.end() )
	//{
	//	//< ���� ����
	//	iter->second->receiveState( state );
	//}
}