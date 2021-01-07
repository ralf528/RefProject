#include "stdafx.h"
#include "PlayerCharacter.h"

void PlayerCharacter::Init()
{
    m_character = new character();
    m_character->init();
    SetAutoMode(false);
    SAFE_DELETE(m_pTarget);
}

void PlayerCharacter::Release()
{
    SAFE_DELETE(m_character);
    SAFE_DELETE(m_pTarget);
}

void PlayerCharacter::Update(float fDeltaTime)
{
    if (m_character)
    {
        m_character->update(fDeltaTime);
    }

    /*
    자동모드일때 가장 가까운 적을 찾아 이동 후 공격한다.

    1. 몬스터 매니저에서 가장 가까운 적을 찾아 타겟으로 정한다.
    2. 해당 적의 위치로 길찾기
    3. 스킬 및 공격
    */

    if (m_pTarget == nullptr)
    {
        // 현재 타겟이 없다면 타겟을 찾는다.
        //m_pTarget = MON_MGR->getMonster();
    }
}

void PlayerCharacter::Render(HDC hdc)
{
    if (!hdc)
    {
        return;
    }

#ifdef __RELEASE
    //< 라이트 맵핑
    SIZE ltmpSZ = RC_MGR->findImage(imgID_LITE_MAPING)->getSize();
    RENDER_MGR->render(screenDC, imgID_LITE_MAPING, m_character->getPos().x - ltmpSZ.cx / 2 - CAMERA->getX(), m_character->getPos().y - ltmpSZ.cy / 2 - RENDER_OFFSET_Y - CAMERA->getY());
#endif
}

character* PlayerCharacter::GetCharacter()
{
    return m_character;
}

LRESULT PlayerCharacter::StateProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (!m_character)
        return DefWindowProc(wnd, msg, wparam, lparam);

    switch (msg)
    {
    case WM_CHAR:
    {
        switch (wparam)
        {
        case 'a':
        case 'A':
            m_character->ProcessSkill(1);
        break;

        case 'q':
        case 'Q':
            m_character->ProcessSkill(2);
        break;

        case 'd':
        case 'D':
            m_character->ProcessSkill(3);
        break;

        case 'z':
        case 'Z':
            SetAutoMode(!IsAutoMode());
        break;
        }
    }
    break;

    case WM_KEYDOWN:
    {
        switch (wparam)
        {
        case VK_SPACE:
        {
            m_character->ProcessSkill(0);
        }
        break;

        case VK_RETURN:
            break;

        case VK_ESCAPE:
            break;
        }
        break;
    }
    }

    return (DefWindowProc(wnd, msg, wparam, lparam));
}

void PlayerCharacter::ProcessInputKey()
{

}