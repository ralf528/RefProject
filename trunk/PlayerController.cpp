#include "stdafx.h"
#include "inventory.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
	m_inventory = nullptr;
}

PlayerController::~PlayerController()
{

}

void PlayerController::Init()
{
    m_character = new character();
    m_character->init();

	//< 인벤토리 생성
	SAFE_DELETE(m_inventory);
	m_inventory = new Inventory;

    SetAutoMode(false);
    SAFE_DELETE(m_pTarget);
}

void PlayerController::Release()
{
    SAFE_DELETE(m_character);
	SAFE_DELETE(m_inventory);
    SAFE_DELETE(m_pTarget);
}

void PlayerController::Update(float fDeltaTime)
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

void PlayerController::Render(HDC hdc)
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

character* PlayerController::GetCharacter()
{
    return m_character;
}

LRESULT PlayerController::StateProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
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

		case '1':
		case '2':
		case '3':
		case '4':
			UseItem((int)(wparam - '0'));
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

void PlayerController::AddItem(int InObjectID)
{
	if (m_inventory != nullptr)
	{
		m_inventory->addItem(InObjectID);
	}
}

bool PlayerController::UseItem(int InItemID)
{
	if (m_character == nullptr || m_inventory == nullptr)
	{
		return false;
	}

	if (InItemID <= 0)
	{
		return false;
	}

	m_inventory->useItem(m_character, InItemID);

	return true;
}

void PlayerController::ProcessInputKey()
{
	/*
	if( onceKeyDown( '1' ) )	{		useIndex = 1;	}
	if( onceKeyDown( '2' ) )	{		useIndex = 2;	}
	if( onceKeyDown( '3' ) )	{		useIndex = 3;	}
	if( onceKeyDown( '4' ) )	{		useIndex = 4;	}*/
}

//< 인벤토리 랜더
void PlayerController::RenderInventory(HDC hdc)
{
	//< 인벤토리 랜더
	m_inventory->renderInven(hdc);
}