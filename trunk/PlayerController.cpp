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

	//< �κ��丮 ����
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
    �ڵ�����϶� ���� ����� ���� ã�� �̵� �� �����Ѵ�.

    1. ���� �Ŵ������� ���� ����� ���� ã�� Ÿ������ ���Ѵ�.
    2. �ش� ���� ��ġ�� ��ã��
    3. ��ų �� ����
    */

    if (m_pTarget == nullptr)
    {
        // ���� Ÿ���� ���ٸ� Ÿ���� ã�´�.
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
    //< ����Ʈ ����
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

//< �κ��丮 ����
void PlayerController::RenderInventory(HDC hdc)
{
	//< �κ��丮 ����
	m_inventory->renderInven(hdc);
}