#include "stdafx.h"
#include "ImageNode.h"
#include "ResourceMgr.h"

ResourceMgr::ResourceMgr(void)
{
	m_resourceList.clear();
}
ResourceMgr::~ResourceMgr(void)
{
	//< 해제
	release();
}


//< 파일에서 추가
unsigned int ResourceMgr::addImage( const unsigned int UID, const TCHAR *filePath,
								   int cx, int cy, BYTE loadType )
{
	//< 리스트에서 ID 검색
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< 중복 확인
	if( iter != m_resourceList.end() )
	{
		//< 중복이므로 에러처리
		return UID;
	}

	//< 추가
	ImageNode *image = new ImageNode( UID );
	if( image->load( filePath, cx, cy, loadType ) == Object::EMPTYOBJ )
	{
		//빈 이미지라면 해제하고 에러처리
		image->release();
		return Object::EMPTYOBJ;
	}
	//< 데이터 추가
	insertRC( UID, image );

	return UID;
}
//< rc파일에서 추가
unsigned int ResourceMgr::addImage( const unsigned int ResouceID, BYTE loadType )
{
	return Object::EMPTYOBJ;
}
//< 빈 이미지 추가
unsigned int ResourceMgr::addImage( const unsigned int UID, int width, int height , BYTE loadType )
{
	//< 찾기
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< 중복 확인
	if( iter != m_resourceList.end() )
	{
		// 에러처리
		return UID;
	}
	//빈 이미지 생성
	ImageNode *image = new ImageNode( UID );
	if( image->load( width, height, loadType ) == Object::EMPTYOBJ )
	{
		image->release();
		return Object::EMPTYOBJ;
	}
	//< 이미지 추가
	insertRC( UID, image );

	return UID;
}
//< 삭제
void ResourceMgr::release( void )
{
	removeAllRC();
}

//< 리소스 추가
// 주의 : 외부에서 할당해서 넣을 경우 관리는 리소스 매니저에서
void ResourceMgr::insertRC( unsigned int UID, Object *obj )
{
	//< 추가
	m_resourceList.insert( make_pair( UID, obj ) );
}
//< 리소스 찾기
Object* ResourceMgr::findRC( unsigned int UID )
{
	//< 찾기
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< 찾았다면 리턴
	if( iter != m_resourceList.end() )
	{
		return iter->second;
	}
	//< 없으면 NULL 리턴
	return NULL;
}
//< 이미지 찾기
ImageNode* ResourceMgr::findImage( unsigned int UID )
{
	//< 찾기
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< 찾았다면 리턴
	if( iter != m_resourceList.end() )
	{
		//< 다운캐스팅..
		return dynamic_cast<ImageNode*>(iter->second);
	}
	//< 없으면 NULL 리턴
	return NULL;
}
//< 리소스 삭제
void ResourceMgr::removeRC( unsigned int UID )
{
	//< 찾기
	Map_ObjList_iter iter = m_resourceList.find( UID );
	//< 찾았다면 리턴
	if( iter != m_resourceList.end() )
	{
		//< 삭제
		iter->second->release();
		delete iter->second;
		iter->second=NULL;
		//< 리스트에서 삭제
		iter = m_resourceList.erase( iter );
	}
}

//< 리소스 모두 삭제
void ResourceMgr::removeAllRC( void )
{
	Map_ObjList_iter iter = m_resourceList.begin();

	//마지막 요소까지 반복
	for( ; iter != m_resourceList.end() ; )
	{
		//< 확인
		if( NULL != iter->second )
		{
			//< 삭제
			iter->second->release();
			delete iter->second;
			iter->second=NULL;
			//< 리스트에서 삭제
			iter = m_resourceList.erase( iter );
		}
		else
		{
			 ++iter;
		}

	}
	//< 정리
	m_resourceList.clear();
}