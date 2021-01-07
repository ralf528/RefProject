#pragma once

#include "Singleton.h"
#include "Object.h"

class ImageNode;

class ResourceMgr
{
private:
	//< 이미지 리스트
	typedef std::map< unsigned int, Object* >	Map_ObjList;
	//< 이미지 리스트 반복자
	typedef Map_ObjList::iterator				Map_ObjList_iter;

//< 생성자, 소멸자
private:
	ResourceMgr(void);
	~ResourceMgr(void);
	//<싱글톤
	SINGLETON( ResourceMgr );

//< 인터페이스
public:
	//< 파일에서 추가
	unsigned int addImage( const unsigned int UID, const char *filePath,
		int cx = 0, int cy = 0, BYTE loadType = RM_NORMAL );
	//< rc파일에서 추가
	unsigned int addImage( const unsigned int ResouceID, BYTE loadType = RM_NORMAL );
	//< 빈 이미지 추가
	unsigned int addImage( const unsigned int UID, int width, int height , BYTE loadType = RM_NORMAL );
	//< 삭제
	virtual void release( void );

	//< 리소스 추가
	void insertRC( unsigned int UID, Object *obj );
	//< 리소스 찾기
	Object* findRC( unsigned int UID );
	//< 이미지 찾기
	ImageNode* findImage( unsigned int UID );
	//< 리소스 삭제
	void removeRC( unsigned int UID );

	//< 리소스 모두 삭제
	void removeAllRC( void );

//< 멤버 변수
private:
	//< 리소스 리스트
	Map_ObjList m_resourceList;
};

#define RC_MGR Singleton<ResourceMgr>::getInstance()
