#include "stdafx.h"
#include "AniMgr.h"
#include "ImageNode.h"
#include "ImageNode.h"

AniMgr::AniMgr(void)
{
	Init();
}

AniMgr::~AniMgr(void)
{
	release();
}

void AniMgr::Init(void)
{

}

void AniMgr::Render(HDC hdc, LPANI_INFO info, POINT pos, int dir, int RCID)
{
    if (!info)
    {
        return;
    }

    int offsetY = RENDER_OFFSET_Y;
    if (RCID == imgID_WARRIOR_ATK)
    {
        offsetY = RENDER_OFFSET_Y * 2;
    }

    SIZE siz = info->aniSize;
    RENDER_MGR->render(hdc, RCID,
        pos.x - siz.cx / 2 - CAMERA->getX(), pos.y - siz.cy / 2 - offsetY - CAMERA->getY(),
        siz.cx, siz.cy,
        info->nowFrame * siz.cx, dir * siz.cy,
        siz.cx, siz.cy);
}

void AniMgr::release(void)
{
}

void AniMgr::SetAnimInfo(LPANI_INFO info, SIZE size, int countX, int countY, int speed, bool bFlag, bool bLoop, bool bPlay)
{
    if (info == nullptr)
    {
        return;
    }

    //< 프레임 수
    info->frameCntX = countX;
    info->frameCntY = countY;
    //< 프레임당 이미지 사이즈
    info->aniSize.cx = size.cx / info->frameCntX;
    info->aniSize.cy = size.cy / info->frameCntY;

    info->frameSpeed = speed;
    info->nowFrame = 0;
    info->nowFrameY = DIR_D;
    info->lastTime = GetTickCount();
    info->flag = bFlag;
    info->loop = bLoop;
    info->playAni = bPlay;
}

void AniMgr::UpdateAni(LPANI_INFO aniInfo)
{
    if (aniInfo && aniInfo->flag)
    {
        DWORD curTime = GetTickCount();

        if (aniInfo->lastTime + aniInfo->frameSpeed <= curTime)
        {
            aniInfo->nowFrame++;

            aniInfo->lastTime = curTime;

            if (aniInfo->frameCntX <= aniInfo->nowFrame)
            {
                if (aniInfo->playAni == false)
                {
                    aniInfo->nowFrame = aniInfo->frameCntX - 1;
                    aniInfo->flag = false;
                    return;
                }
                aniInfo->nowFrame = 0;
                if (aniInfo->loop == false)
                {
                    aniInfo->flag = false;
                }
            }
        }
    }
}