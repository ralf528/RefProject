#include "stdafx.h"
#include "PlayerCharacter.h"
#include "cWarrior.h"

void PlayerCharacter::Init()
{
    m_character = new cWarrior();
    m_character->init();
}

void PlayerCharacter::Release()
{
    SAFE_DELETE(m_character);
}

void PlayerCharacter::Update(float fDeltaTime)
{
    if (m_character)
    {
        m_character->update(fDeltaTime);
    }
}

void PlayerCharacter::Render(HDC hdc)
{
    if (!hdc)
    {
        return;
    }

#ifdef __RELEASE
    //< ¶óÀÌÆ® ¸ÊÇÎ
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
        {
            m_character->ProcessSkill(1);
        }
        break;
        case 's':
        case 'S':
        {
            m_character->ProcessSkill(2);
        }
        break;
        case 'd':
        case 'D':
        {
            m_character->ProcessSkill(3);
        }
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