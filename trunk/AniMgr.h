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
	void Init(void);
	
public:
	void release(void);
	static void Render(HDC hdc, LPANI_INFO info, POINT pos, int dir, int RCID);
    static void SetAnimInfo(LPANI_INFO info, SIZE size, int countX, int countY, float speed, bool bFlag, bool bLoop, bool bPlay);
    static void UpdateAni(LPANI_INFO aniInfo);
};

#define ANI_MGR Singleton<AniMgr>::GetInstance()
