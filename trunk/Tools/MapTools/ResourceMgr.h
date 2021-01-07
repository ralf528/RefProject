#pragma once

#include "Singleton.h"
#include "Object.h"

class ImageNode;

class ResourceMgr
{
private:
	//< �̹��� ����Ʈ
	typedef std::map< unsigned int, Object* >	Map_ObjList;
	//< �̹��� ����Ʈ �ݺ���
	typedef Map_ObjList::iterator				Map_ObjList_iter;

//< ������, �Ҹ���
private:
	ResourceMgr(void);
	~ResourceMgr(void);
	//<�̱���
	SINGLETON( ResourceMgr );

//< �������̽�
public:
	//< ���Ͽ��� �߰�
	unsigned int addImage( const unsigned int UID, const char *filePath,
		int cx = 0, int cy = 0, BYTE loadType = RM_NORMAL );
	//< rc���Ͽ��� �߰�
	unsigned int addImage( const unsigned int ResouceID, BYTE loadType = RM_NORMAL );
	//< �� �̹��� �߰�
	unsigned int addImage( const unsigned int UID, int width, int height , BYTE loadType = RM_NORMAL );
	//< ����
	virtual void release( void );

	//< ���ҽ� �߰�
	void insertRC( unsigned int UID, Object *obj );
	//< ���ҽ� ã��
	Object* findRC( unsigned int UID );
	//< �̹��� ã��
	ImageNode* findImage( unsigned int UID );
	//< ���ҽ� ����
	void removeRC( unsigned int UID );

	//< ���ҽ� ��� ����
	void removeAllRC( void );

//< ��� ����
private:
	//< ���ҽ� ����Ʈ
	Map_ObjList m_resourceList;
};

#define RC_MGR Singleton<ResourceMgr>::getInstance()
