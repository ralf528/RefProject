#include "stdafx.h"
#include "ImageNode.h"
#include "ResourceMgr.h"

ResourceMgr::ResourceMgr(void)
{
	m_resourceList.clear();
}
ResourceMgr::~ResourceMgr(void)
{
	//< ����
	release();
}


//< ���Ͽ��� �߰�
unsigned int ResourceMgr::addImage( const unsigned int UID, const TCHAR *filePath,
								   int cx, int cy, BYTE loadType )
{
	//< ����Ʈ���� ID �˻�
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< �ߺ� Ȯ��
	if( iter != m_resourceList.end() )
	{
		//< �ߺ��̹Ƿ� ����ó��
		return UID;
	}

	//< �߰�
	ImageNode *image = new ImageNode( UID );
	if( image->load( filePath, cx, cy, loadType ) == Object::EMPTYOBJ )
	{
		//�� �̹������ �����ϰ� ����ó��
		image->release();
		return Object::EMPTYOBJ;
	}
	//< ������ �߰�
	insertRC( UID, image );

	return UID;
}
//< rc���Ͽ��� �߰�
unsigned int ResourceMgr::addImage( const unsigned int ResouceID, BYTE loadType )
{
	return Object::EMPTYOBJ;
}
//< �� �̹��� �߰�
unsigned int ResourceMgr::addImage( const unsigned int UID, int width, int height , BYTE loadType )
{
	//< ã��
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< �ߺ� Ȯ��
	if( iter != m_resourceList.end() )
	{
		// ����ó��
		return UID;
	}
	//�� �̹��� ����
	ImageNode *image = new ImageNode( UID );
	if( image->load( width, height, loadType ) == Object::EMPTYOBJ )
	{
		image->release();
		return Object::EMPTYOBJ;
	}
	//< �̹��� �߰�
	insertRC( UID, image );

	return UID;
}
//< ����
void ResourceMgr::release( void )
{
	removeAllRC();
}

//< ���ҽ� �߰�
// ���� : �ܺο��� �Ҵ��ؼ� ���� ��� ������ ���ҽ� �Ŵ�������
void ResourceMgr::insertRC( unsigned int UID, Object *obj )
{
	//< �߰�
	m_resourceList.insert( make_pair( UID, obj ) );
}
//< ���ҽ� ã��
Object* ResourceMgr::findRC( unsigned int UID )
{
	//< ã��
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< ã�Ҵٸ� ����
	if( iter != m_resourceList.end() )
	{
		return iter->second;
	}
	//< ������ NULL ����
	return NULL;
}
//< �̹��� ã��
ImageNode* ResourceMgr::findImage( unsigned int UID )
{
	//< ã��
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< ã�Ҵٸ� ����
	if( iter != m_resourceList.end() )
	{
		//< �ٿ�ĳ����..
		return dynamic_cast<ImageNode*>(iter->second);
	}
	//< ������ NULL ����
	return NULL;
}
//< ���ҽ� ����
void ResourceMgr::removeRC( unsigned int UID )
{
	//< ã��
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< ã�Ҵٸ� ����
	if( iter != m_resourceList.end() )
	{
		//< ����
		iter->second->release();
		delete iter->second;
		iter->second=NULL;
		//< ����Ʈ���� ����
		iter = m_resourceList.erase( iter );
	}
}

//< ���ҽ� ��� ����
void ResourceMgr::removeAllRC( void )
{
	Map_ObjList_iter iter = m_resourceList.begin();

	//������ ��ұ��� �ݺ�
	for( ; iter != m_resourceList.end() ; )
	{
		//< Ȯ��
		if( NULL != iter->second )
		{
			//< ����
			iter->second->release();
			delete iter->second;
			iter->second=NULL;
			//< ����Ʈ���� ����
			iter = m_resourceList.erase( iter );
		}
		else
		{
			 ++iter;
		}

	}
	//< ����
	m_resourceList.clear();
}