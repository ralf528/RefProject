#pragma once

#include "Singleton.h"

class ImageNode;
class ImageClass;

class AniMgr
{
private:
	AniMgr(void);
	~AniMgr(void);

	SINGLETON(AniMgr);

private:

	void init(void);

	//����Ʈ �ʱ�ȭ
	void effectInit(void);
	//�ִϸ��̼�
	void updateAni(LPANI_INFO aniInfo);
	
public:
	void release(void);
	void render(HDC hdc,int ID, int cx, int cy);

	void animation(int ID);
	
	void setRender(bool isRender){m_isRender = isRender;}
private:

	ImageNode *m_image;
	LPANI_INFO m_info;

	bool m_isRender;
	int flag;
};

#define ANI_MGR Singleton<AniMgr>::GetInstance()
