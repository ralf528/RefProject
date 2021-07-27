#include "stdafx.h"
#include "PlayerCharacter.h"
//#include "goblin.h"
//#include "mon_bug.h"
//#include "Boss_naid.h"
//#include "ghoul.h"
//#include "Boss_gyuriel.h"
//#include "Dark_spider.h"
//#include "Human_knight.h"
//#include "Human_thief.h"
//#include "Ghost.h"
#include "WorldManager.h"
#include "SceneLobby.h"
#include "ScenePlayGame.h"
#include "Scene/Chat/ChattingGame.h"

using namespace myUTIL;
using namespace keyInput;
using namespace collision;

ScenePlayGame::ScenePlayGame(void)
    :m_playingGame(true)
{
    chatting = new ChattingGame;
    checkEnter = 0;
}

ScenePlayGame::~ScenePlayGame(void)
{
    release();
}

//< �ʱ�ȭ
bool ScenePlayGame::init(void)
{
    //< ī�޶� �ʱ�ȭ
    CAMERA->init();
    //< ��ũ�� ���� �߰�
    RC_MGR->addImage(imgID_SCREENBUFFER, SCREEN_X, SCREEN_Y);
    //< ���� UI �̹��� �߰�
    RC_MGR->addImage(imgID_GAME_UI, L"Data/Resource/gameUI/IngameUI.bmp", 0, 0, RM_TRANS);
    //< �þ� ȿ��
    RC_MGR->addImage(imgID_SIGHT, L"Data/Resource/gameUI/�þ�.bmp", 0, 0, RM_ALPHA32);
    //< ����Ʈ����
    RC_MGR->addImage(imgID_LITE_MAPING, L"Data/Resource/gameUI/����Ʈ����alpha.bmp", 0, 0, RM_ALPHA32);
    //< Ÿ�� ȿ��
    RC_MGR->addImage(imgID_HITEFF1, L"Data/Resource/effect/GetHit_tong.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_HITEFF2, L"Data/Resource/effect/GetHit_Ghost.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_HITEFF3, L"Data/Resource/effect/GetHit_Bug.bmp", 0, 0, RM_TRANS);

    STATE_MGR->setLoading(30);

    //< ���� �߻��� �ʱ�ȭ
    srand(GetTickCount());
    //���ʱ�ȭ
    m_World = new WorldManager;
    m_World->init();

    STATE_MGR->setLoading(80);

    //ĳ���� ���� �ʱ�ȭ
    m_player = new PlayerCharacter();
    m_player->Init();
    //< ���� �Ŵ����� ĳ���� ����
    MON_MGR->setDestPlayer(m_player->GetCharacter());

    //ĳ���� ��ġ �ʱ�ȭ
    m_player->GetCharacter()->setPos(m_World->GetSpawnPos());

    //���� ����� �÷���
    //SOUND_MGR->soundPlay(SOUND_INGAME);

    LOG_MGR->addLog("%s", "�÷��̾� �ʱ�ȭ");

    //< UI �ʱ�ȭ
    initUI();
    //< ä��â
    chatting->init();

    STATE_MGR->setLoading(100); Sleep(500);

    return true;
}
//< ������Ʈ
void ScenePlayGame::update(float fDeltaTime)
{
    static DWORD ffff = GetTickCount();
    if (GetTickCount() - ffff >= 5000)
    {
        POINT pos = m_player->GetCharacter()->getPos();
        LOG_MGR->addLog("��ǥ : %d / %d", pos.x, pos.y);
        ffff = GetTickCount();
    }

    CAMERA->update();

    //< �˾�â�� ������ ����
    if (POPUP_MGR->getCheckPopup_ON() != true)
    {
        //< ä��â �Է��� ����������
        //if( chatting->getChatingOn() == false )
        {
            //< ĳ���� ����&������Ʈ
            m_player->Update(fDeltaTime);
        }
        //< ĳ���� ������ ��(��) ã��
        m_World->aroundLine(m_player->GetCharacter()->getPos(), m_player->GetCharacter()->getAroundVertex());

        //< ĳ���Ϳ� ���� �浹üũ
        if (m_World->collision(m_player->GetCharacter()->getPos(), m_player->GetCharacter()->getAroundVertex()))
        {
            //< �浹 �Ǿ��ٸ� ���� ��ġ��
            m_player->GetCharacter()->setPosToPrev();
        }
        //< ĳ���Ϳ� ������Ʈ �浹üũ
        E_TileBrush objTemp = m_World->collisionObject(m_player->GetCharacter()->getPos());
        if (0 != objTemp)
        {
            m_player->GetCharacter()->gainCollider(objTemp);
        }

        //> ��Ż�� �浹 �� �̵�
        if (m_World->IsColPortal(m_player->GetCharacter()->getPos()) == true)
        {
            initByPortal(m_player->GetCharacter()->getPos());
        }

        //< ���Ϳ� ���� �浹 üũ
        for (size_t i = 0; i < MON_MGR->getSize(); i++)
        {
            //< ������ ��(��) ã��
            m_World->aroundLine(MON_MGR->getMonster(i)->getPos(), MON_MGR->getMonster(i)->getAroundVertex());
            //< ���� ���� �浹 üũ
            if (true == m_World->collision(MON_MGR->getMonster(i)->getPos(), MON_MGR->getMonster(i)->getAroundVertex()))
            {
                //< �浹 �Ǿ��ٸ� ���� ��ġ��
                MON_MGR->getMonster(i)->setPosToPrev();
            }
        }
        //< ���� ������Ʈ
        MON_MGR->update(fDeltaTime);
        //< ĳ���� ��ġ ����
        m_player->GetCharacter()->setRect();

        for (int i = 0; i < MAX_SKILL_COUNT; i++)
        {
            if (m_button_Skill[i].getPlayButtonAni() == true)
            {
                //< �ִϸ��̼� ������
                m_button_Skill[i].inPlayButtonAni(false);
                //< Ŭ�� ������
                m_button_Skill[i].inClickButton(false);
            }
        }

        //< ä��â ������Ʈ
        chatting->update( mousePos );

    }
    //< �˾�â�� ������ ����
    if (POPUP_MGR->getCheckPopup_ON() == true)
    {
        //< �˾� ����
        POPUP_MGR->updatePopup();
        //< 2�� �˾�( �˾����� ������ư �Ǻ� )
        int tempFlag = POPUP_MGR->buttonStatePopup();

        //< �Ҵ��� ���� �ʾҴٸ�
        if (tempFlag == false)
        {
            //< �˾�â ����
        }
    }
}

//< ����
void ScenePlayGame::render(HDC hdc)
{
    if (NULL != hdc)
    {
        //< ��ũ�� ���� �ҷ�����
        ImageNode *imgScreen = RC_MGR->findImage(imgID_SCREENBUFFER);
        screenDC = imgScreen->getMemDC();
        RECT screenRect;
        SetRect(&screenRect, 0, 0, SCREEN_X, SCREEN_Y);
        //< ��ũ�� �����
        FillRect(screenDC, &screenRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

        //<Ÿ�ϸ� ���
        m_World->render(screenDC);
        //<���� �� ���
        m_World->renderWall(screenDC);

        m_player->Render(hdc);

        //<�������
        MON_MGR->render( screenDC );
        MON_MGR->renderUnitList(screenDC);
        //< �þ� ȿ��
#ifdef __RELEASE
        RENDER_MGR->render(screenDC, imgID_SIGHT, 0, 0);
#endif
        //<ĳ���� ���
        //m_player->render( screenDC );

        //< ���� ȭ�� ����
        imgScreen->render(hdc, 0, 0);
        //< UI ����
        renderUI(hdc);
        //< ä��â ����
        chatting->render( hdc );
    }

    //< �˾�â�� ������ ����
    if (POPUP_MGR->getCheckPopup_ON() == true)
    {
        //< �˾�â ����
        POPUP_MGR->renderPopup(hdc);

        for (int i = 0; i < 4; i++)
        {
            m_button_Skill[i].inPlayButtonAni(false);
            m_button_Skill[i].inCheckMouseOn(false);
            m_button_Skill[i].inClickButton(false);
        }
    }
}
//< ����
void ScenePlayGame::release(void)
{
    if( NULL != chatting ){ chatting->release(); }
    SAFE_DELETE( chatting );

    SAFE_RELEASE(m_player);
    SAFE_DELETE(m_World);
    //SOUND_MGR->soundStop(SOUND_INGAME);
}

//< UI �ε�
void ScenePlayGame::initUI(void)
{
    //< ��ų��ư
    m_button_Skill[0].init(
        L"Data/Resource/Image/Interface/skill_Attack.bmp",
        L"Data/Resource/Image/Interface/skill_Attack_02.bmp",
        L"Data/Resource/Image/Interface/skill_Attack_NO.bmp",
        40, 40);
    m_button_Skill[1].init(
        L"Data/Resource/Image/Interface/skill_Dash.bmp",
        L"Data/Resource/Image/Interface/skill_Dash_02.bmp",
        L"Data/Resource/Image/Interface/skill_Dash_NO.bmp",
        40, 40);
    m_button_Skill[2].init(
        L"Data/Resource/Image/Interface/skill_All.bmp",
        L"Data/Resource/Image/Interface/skill_All_02.bmp",
        L"Data/Resource/Image/Interface/skill_All_NO.bmp",
        40, 40);
    m_button_Skill[3].init(
        L"Data/Resource/Image/Interface/skill_Heal_02.bmp",
        L"Data/Resource/Image/Interface/skill_Heal_02.bmp",
        L"Data/Resource/Image/Interface/skill_Heal_NO.bmp",
        40, 40);
    //< ������ ��ư
    m_m_button_Item[0].init(
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    m_m_button_Item[1].init(
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    m_m_button_Item[2].init(
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    m_m_button_Item[3].init(
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        L"Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    for (int i = 0; i < 4; i++)
    {
        //< ��ų��ư 
        m_button_Skill[i].setRectPos(150 + ((40 * i) + (10 * i)), WINSIZE_Y - 50, ALIGN_LEFT_TOP);
        //< �����۹�ư 
        m_m_button_Item[i].setRectPos(920 + ((40 * i) + (10 * i)), WINSIZE_Y - 50, ALIGN_RIGHT_TOP);
    }

    //< ĳ���� �̸�
    m_charName.inSetRect(450, 607 - 20, 830, 666 - 20);
    m_charName.LoadText(m_charName.getRect(), L"HY������M", 25, ALIGN_CENTER, 255, 255, 255);

    //< ���ݹ�
    m_stat[0].init(
        L"Data/Resource/Image/Interface/stat_T.bmp",
        L"Data/Resource/Image/Interface/stat_T.bmp",
        L"Data/Resource/Image/Interface/stat_T.bmp",
        120, 42);
    m_stat[1].init(
        L"Data/Resource/Image/Interface/stat_S.bmp",
        L"Data/Resource/Image/Interface/stat_S.bmp",
        L"Data/Resource/Image/Interface/stat_S.bmp",
        120, 42);
    m_stat[2].init(
        L"Data/Resource/Image/Interface/stat_M.bmp",
        L"Data/Resource/Image/Interface/stat_M.bmp",
        L"Data/Resource/Image/Interface/stat_M.bmp",
        120, 42);
    for (int i = 0; i < 3; i++)
    {
        m_stat[i].setRectPos(570 + ((120 * i) + (10 * i)), 640, ALIGN_RIGHT_TOP);
    }
    //< ���� ǥ��
    m_stat_S.inSetRect(m_stat[0].getRect().left + 35, m_stat[0].getRect().top + 42, m_stat[0].getRect().right, m_stat[0].getRect().bottom + 42);
    m_stat_Q.inSetRect(m_stat[1].getRect().left + 35, m_stat[1].getRect().top + 42, m_stat[1].getRect().right, m_stat[1].getRect().bottom + 42);
    m_stat_M.inSetRect(m_stat[2].getRect().left + 35, m_stat[2].getRect().top + 42, m_stat[2].getRect().right, m_stat[2].getRect().bottom + 42);
    m_stat_S.LoadText(m_stat_S.getRect(), L"HY������M", 20, ALIGN_CENTER, 255, 255, 255);
    m_stat_Q.LoadText(m_stat_Q.getRect(), L"HY������M", 20, ALIGN_CENTER, 255, 255, 255);
    m_stat_M.LoadText(m_stat_M.getRect(), L"HY������M", 20, ALIGN_CENTER, 255, 255, 255);

    //< ������ ��
    m_bar_experience_back.load(L"Data/Resource/Image/Interface/UI_lvup_NO.bmp", 380, 19, RM_TRANS);
    m_bar_experience.load(L"Data/Resource/Image/Interface/UI_lvup.bmp", 760, 19, RM_TRANS);
    //< ����ġ ǥ��
    m_bar_experience_string.inSetRect(450, 690, 450 + 380, 690 + 19);
    m_bar_experience_string.LoadText(m_bar_experience_string.getRect(), L"HY������M", 15, ALIGN_CENTER, 255, 255, 255);

    //< ü�¹� 
    m_bar_live_back.load(L"Data/Resource/Image/Interface/UI_live_NO.bmp", 380, 19, RM_TRANS);
    m_bar_live.load(L"Data/Resource/Image/Interface/UI_live.bmp", 760, 19, RM_TRANS);
    //< ü�¹� ǥ��
    m_bar_live_string.inSetRect(100, 10, 100 + 380, 10 + 19);
    m_bar_live_string.LoadText(m_bar_live_string.getRect(), L"HY������M", 15, ALIGN_CENTER, 255, 255, 255);

    //< ������
    m_bar_mana_back.load(L"Data/Resource/Image/Interface/UI_mana_NO.bmp", 380, 19, RM_TRANS);
    m_bar_mana.load(L"Data/Resource/Image/Interface/UI_mana.bmp", 760, 19, RM_TRANS);
    //< ������ ǥ�� 
    m_bar_mana_string.inSetRect(100, 37, 100 + 380, 37 + 19);
    m_bar_mana_string.LoadText(m_bar_mana_string.getRect(), L"HY������M", 15, ALIGN_CENTER, 255, 255, 255);

    //< ���� ǥ��
    m_lv_bar.init(
        L"Data/Resource/Image/Interface/UI_LV.bmp",
        L"Data/Resource/Image/Interface/UI_LV.bmp",
        L"Data/Resource/Image/Interface/UI_LV.bmp",
        81, 47);
    m_lv_bar.setRectPos(10, 10, ALIGN_LEFT_TOP);

    //< ���� ǥ��
    m_lv_bar_string.LoadText(m_lv_bar.getRect(), L"HY������M", 25, ALIGN_CENTER, 255, 255, 255);

    //< ������ 
    m_stage.inSetRect(1150, 10, 1260, 109);
    m_stage.LoadText(m_stage.getRect(), L"HY������M", 50, ALIGN_CENTER, 255, 255, 255);

    //< ĳ���� ����
    m_charState.inSetRect(500, 10, 500 + 90, 10 + 50);
    m_charState.LoadText(m_charState.getRect(), L"HY������M", 20, ALIGN_CENTER, 255, 255, 255);
}

//< UI �׸���
void ScenePlayGame::renderUI(HDC hdc)
{
    if (NULL != hdc)
    {
        //< ���ڿ� ����
        TCHAR tempStr[_MAX_FNAME];

        //< �������ͽ� ���ڿ�
		static TCHAR *belief[] = { TEXT("����"), TEXT("������ġ"), TEXT("����Ű"), TEXT("�����ƽ�"), TEXT("Ÿ����") };
		static TCHAR *tribe[] = { TEXT("�����ΰ�"), TEXT("��Ÿ��ν�"), TEXT("����"), TEXT("�𵥵�") };
		static TCHAR *job[] = { TEXT("����"), TEXT("����"), TEXT("��ó"), TEXT("������") };
		static TCHAR *condition[] = { TEXT(""), TEXT("��"), TEXT("��ȭ"), TEXT("��ȭ"), TEXT("����") };

        //< ĳ���� ��ǥ, ��ǥ �ε��� ǥ��
        //swprintf_s(tempStr, "x : %3d,   y : %3d", m_player->getPos().x/TILE_SIZE_X, m_player->getPos().y/TILE_SIZE_Y );
        //TextOut( hdc, SCREEN_X - 250, 400, tempStr, lstrlen(tempStr) );
        //swprintf_s(tempStr, "x : %3d,   y : %3d", m_player->getPos().x, m_player->getPos().y );
        //TextOut( hdc, SCREEN_X - 250, 430, tempStr, lstrlen(tempStr) );

        //< �� ���� ����
        int moveBar = 0;

        //< ��ų 
        for (int i = 0; i < MAX_SKILL_COUNT; i++)
        {
            m_button_Skill[i].render(hdc);
            //m_m_button_Item[i].render( hdc );
        }

        //< ĳ���� ����
        swprintf_s(tempStr, _MAX_FNAME, TEXT("%s"), condition[m_player->GetCharacter()->getCondition()]);
        m_charState.OutputText(hdc, tempStr);
        //Rectangle( hdc, m_charState.getRect().left, m_charState.getRect().top, m_charState.getRect().right, m_charState.getRect().bottom );

        swprintf_s(tempStr, _MAX_FNAME, TEXT("%s %s %s"), belief[m_player->GetCharacter()->getBelief()], tribe[m_player->GetCharacter()->getTribe()], job[m_player->GetCharacter()->getJob()]);
        //< ĳ���� �̸�
        m_charName.OutputText(hdc, tempStr);
        //Rectangle( hdc, m_charName.getRect().left, m_charName.getRect().top, m_charName.getRect().right, m_charName.getRect().bottom );
        //< ����ǥ��
        for (int i = 0; i < 3; i++)
        {
            m_stat[i].render(hdc);
        }
        //< ���� ǥ��
        swprintf_s(tempStr, _MAX_FNAME, TEXT("��:%2d"), m_player->GetCharacter()->getStrong());
        m_stat_S.OutputText(hdc, tempStr);
        swprintf_s(tempStr, _MAX_FNAME, TEXT("��:%2d"), m_player->GetCharacter()->getAgility());
        m_stat_Q.OutputText(hdc, tempStr);
        swprintf_s(tempStr, _MAX_FNAME, TEXT("��:%2d"), m_player->GetCharacter()->getIntel());
        m_stat_M.OutputText(hdc, tempStr);

        //< ����ġ��
        m_bar_experience_back.render(hdc, 450, 690);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->GetCharacter()->getLevelInfo().getNowExp()) / m_player->GetCharacter()->getLevelInfo().getMaxExp()) * 380));
        m_bar_experience.render(hdc, 450, 690, 380, 19, moveBar, 0, 760, 19);
        swprintf_s(tempStr, 256, TEXT("%d/%d"), m_player->GetCharacter()->getLevelInfo().getNowExp(), m_player->GetCharacter()->getLevelInfo().getMaxExp());
        //< ����ġ ǥ��
        m_bar_experience_string.OutputText(hdc, tempStr);

        //< ü�¹�
        m_bar_live_back.render(hdc, 100, 10);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->GetCharacter()->getHP()) / m_player->GetCharacter()->getMaxHP()) * 380));
        m_bar_live.render(hdc, 100, 10, 380, 19, moveBar, 0, 760, 19);
        swprintf_s(tempStr, 256, TEXT("%d/%d"), m_player->GetCharacter()->getHP(), m_player->GetCharacter()->getMaxHP());
        //< ü�¹� ǥ��
        m_bar_live_string.OutputText(hdc, tempStr);

        //< ������
        m_bar_mana_back.render(hdc, 100, 37);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->GetCharacter()->getMP()) / m_player->GetCharacter()->getMaxMP()) * 380));
        m_bar_mana.render(hdc, 100, 37, 380, 19, moveBar, 0, 760, 19);
        swprintf_s(tempStr, 256, TEXT("%d/%d"), m_player->GetCharacter()->getMP(), m_player->GetCharacter()->getMaxMP());
        //< ������ ǥ��
        m_bar_mana_string.OutputText(hdc, tempStr);

        //< ���� ǥ��
        m_lv_bar.render(hdc);
        swprintf_s(tempStr, 256, TEXT("LV.%d"), m_player->GetCharacter()->getLevelInfo().getNowLevel());
        m_lv_bar_string.OutputText(hdc, tempStr);

        //< ���� ����
        swprintf_s(tempStr, TEXT("%d��"), m_World->getNowFloor());
        m_stage.OutputText(hdc, tempStr);

        //< �÷��̾� �κ��丮 ǥ��
        m_player->GetCharacter()->renderInven(hdc);
    }
}

//< �̺�Ʈó��
LRESULT ScenePlayGame::StateProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (POPUP_MGR->getCheckPopup_ON())
    {
        return POPUP_MGR->PopupProc(wnd, msg, wparam, lparam);
    }
    else
    {
        if (chatting && chatting->getChatingOn() == false)
        {
            m_player->StateProc(wnd, msg, wparam, lparam);
        }

        switch (msg)
        {
        case WM_CHAR:
        {
            //< ä��â �Է��� ����������
            if (chatting && chatting->getChatingOn() == false)
            {
                switch (wparam)
                {
                case 'a':
                case 'A':
                {
                    //< �뽬 ��ư-------------------------------------------------
                    m_button_Skill[1].inClickButton(true);
                }
                break;
                case 's':
                case 'S':
                {
                    //< ��ų ��ư-------------------------------------------------
                    m_button_Skill[2].inClickButton(true);
                }
                break;
                case 'd':
                case 'D':
                {
                    //< ��ų ��ư-------------------------------------------------
                    m_button_Skill[3].inClickButton(true);
                }
                break;
                }
            }
        }
        break;
        case WM_KEYDOWN:
        {
            //< ä��â �Է��� ����������
            if (chatting && chatting->getChatingOn() == false)
            {
                switch (wparam)
                {
                case VK_SPACE:
                {
                    //< ���� ��ư-------------------------------------------------
                    m_button_Skill[0].inClickButton(true);
                }
                break;
                }
            }

            switch (wparam)
            {
            case VK_ESCAPE:
                //pause
                m_playingGame = false;
                break;
            }
            break;
        }
        }
    }

    if (NULL != chatting)
    {
        return chatting->StateProc(wnd, msg, wparam, lparam);
    }

    return (DefWindowProc(wnd, msg, wparam, lparam));
}

//< ��Ż �� �ʱ�ȭ
void ScenePlayGame::initByPortal(POINT &destPos)
{
    //< ��Ż�� �浹 üũ
    if (true == m_World->inPortal(destPos))
    {
        m_player->GetCharacter()->setPos(m_World->GetSpawnPos());
    }
}