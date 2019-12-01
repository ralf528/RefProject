#include "stdafx.h"
#include "cWarrior.h"
//#include "otherCharacter.h"
//#include "goblin.h"
//#include "mon_bug.h"
//#include "Boss_naid.h"
//#include "ghoul.h"
//#include "Boss_gyuriel.h"
//#include "Dark_spider.h"
//#include "Human_knight.h"
//#include "Human_thief.h"
//#include "Ghost.h"
#include "tileMap.h"
#include "SceneLobby.h"
#include "ScenePlayGame.h"
//#include "ChattingGame.h"

using namespace myUTIL;
using namespace keyInput;
using namespace collision;

ScenePlayGame::ScenePlayGame(void)
    :m_playingGame(true)
{
    //chatting = new ChattingGame;
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
    RC_MGR->addImage(imgID_GAME_UI, "Data/Resource/gameUI/IngameUI.bmp", 0, 0, RM_TRANS);
    //< �þ� ȿ��
    RC_MGR->addImage(imgID_SIGHT, "Data/Resource/gameUI/�þ�.bmp", 0, 0, RM_ALPHA32);
    //< ����Ʈ����
    RC_MGR->addImage(imgID_LITE_MAPING, "Data/Resource/gameUI/����Ʈ����alpha.bmp", 0, 0, RM_ALPHA32);
    //< Ÿ�� ȿ��
    RC_MGR->addImage(imgID_GETHIT_1, "Data/Resource/effect/GetHit_tong.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_GETHIT_2, "Data/Resource/effect/GetHit_Ghost.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_GETHIT_3, "Data/Resource/effect/GetHit_Bug.bmp", 0, 0, RM_TRANS);

    STATE_MGR->setLoading(30);

    //< ���� �߻��� �ʱ�ȭ
    srand(GetTickCount());
    //���ʱ�ȭ
    m_map = new tileMap;
    m_map->init();

    STATE_MGR->setLoading(80);

    //ĳ���� ���� �ʱ�ȭ
    m_player = new cWarrior;
    m_player->init();
    //< ���� �Ŵ����� ĳ���� ����
    MON_MGR->setDestPlayer(m_player);
    //MON_MGR->setOtherPlayer( &m_other );

    //m_other->init();

    //ĳ���� ��ġ �ʱ�ȭ
    m_player->setPos(m_map->getCharPos());
    //m_other->setPos( m_map->getCharPos() );

    //���� ����� �÷���
    //SOUND_MGR->soundPlay(SOUND_INGAME);

    LOG_MGR->addLog("%s", "�÷��̾� �ʱ�ȭ");


    //< �����ϴ� other�� ���
    {

        //m_other = new otherCharacter;
        //m_other->init();
        //MON_MGR->setOtherPlayer( m_other );
        //m_other->setPos( m_map->getCharPos() );

        //> �� �ʱ�ȭ ���� ����(Ŭ���̾�Ʈ, ȣ��Ʈx)
        m_isMapInit = false;
        //> ���� �ʱ�ȭ ���� ����(Ŭ���̾�Ʈ, ȣ��Ʈx)
        m_isMonsterInit = false;
        //> �÷��̾� �ʱ�ȭ ���� ����(Ŭ���̾�Ʈ, ȣ��Ʈx)
        m_isPlayerInit = false;

    }

    //< UI �ʱ�ȭ
    initUI();
    //< ä��â
    //chatting->init();

    STATE_MGR->setLoading(90); Sleep(100);

    static DWORD lastTime = GetTickCount();
    int i = 0;
    /*while (!m_isMapInit || !m_isMonsterInit || !m_isPlayerInit)
    {
        DWORD curTime = GetTickCount();
        if ((curTime - lastTime) >= 1000)
        {
            lastTime = GetTickCount();
        }
    }*/

    STATE_MGR->setLoading(100); Sleep(500);

    return true;
}
//< ������Ʈ
void ScenePlayGame::update(void)
{
    static DWORD ffff = GetTickCount();
    if (GetTickCount() - ffff >= 5000)
    {
        POINT pos = m_player->getPos();
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
            m_player->update();
        }
        //< ĳ���� ������ ��(��) ã��
        m_map->aroundLine(m_player->getPos(), m_player->getAroundVertex());

        //< ĳ���Ϳ� ���� �浹üũ
        if (m_map->collision(m_player->getPos(), m_player->getAroundVertex()))
        {
            //< �浹 �Ǿ��ٸ� ���� ��ġ��
            m_player->setPosToPrev();
        }
        //< �ƴ� ĳ���Ϳ� ���� �浹üũ
        //if( true == m_map->collision( m_other->getPos(), m_other->getAroundVertex() ) )
        //{
        //	//< �浹 �Ǿ��ٸ� ���� ��ġ��
        //	m_other->setPosToPrev();
        //}
        //< ĳ���Ϳ� ������Ʈ �浹üũ
        tileType objTemp = m_map->collisionObject(m_player->getPos());
        if (0 != objTemp)
        {
            m_player->gainCollider(objTemp);
        }
        //< �ƴ� ĳ���� �浹üũ
        /*if(NULL != m_other)
        {
            objTemp = m_map->collisionObject( m_other->getPos() );
            if( 0 != objTemp )
            {
                m_other->gainCollider( objTemp );
            }
        }*/
        //< ��Ż�� �浹 üũ
        //if( true == m_map->inPortal( m_player->getPos() ) )
        //{
        //	m_player->setPos( m_map->getCharPos() );
        //	m_other->setPos( m_map->getCharPos() );
        //}
        //initByPortal( m_player->getPos() );


        //> ȥ�ڸ� ��Ż�� ������
        if ((m_map->IsColPortal(m_player->getPos()) == true) && false == POPUP_MGR->getCheckPopup_ON())
        {
            POPUP_MGR->changePopup(POPUP_GAME_WAIT_USER);
            //POPUP_MGR->initPopup();
        }
        else if (m_map->IsColPortal(m_player->getPos()) == false && POPUP_GAME_WAIT_USER == POPUP_MGR->GetNowPopUp())
        {
            POPUP_MGR->changePopup(POPUP_NONE);
        }
        //> ȣ��Ʈ
        //if(true == HOST_SERVER->getHostis())
        //{
        //	//> �����ڰ� ���� ���
        //	if(NULL != m_other)
        //	{
        //		//> �� ��� ��Ż�� ������
        //		if(m_map->IsColPortal(m_player->getPos()) == true && m_map->IsColPortal(m_other->getPos()) == true)
        //		{
        //			//> �̵�
        //			initByPortal(m_player->getPos());
        //		}
        //	}
        //	else
        //	{
        //		//> ��Ż�� �浹 �� �̵�
        //		if(m_map->IsColPortal(m_player->getPos()) == true)
        //		{
        //			initByPortal(m_player->getPos());
        //		}
        //	}
        //}

        //< ���Ϳ� ���� �浹 üũ
        for (size_t i = 0; i < MON_MGR->getSize(); i++)
        {
            //< ������ ��(��) ã��
            m_map->aroundLine(MON_MGR->getMonster(i)->getPos(), MON_MGR->getMonster(i)->getAroundVertex());
            //< ���� ���� �浹 üũ
            if (true == m_map->collision(MON_MGR->getMonster(i)->getPos(), MON_MGR->getMonster(i)->getAroundVertex()))
            {
                //< �浹 �Ǿ��ٸ� ���� ��ġ��
                MON_MGR->getMonster(i)->setPosToPrev();
            }
        }
        //< ���� ������Ʈ
        MON_MGR->update();
        //< ĳ���� ��ġ ����
        m_player->setRect();

        //< �ƴ��� �����߳�
        //if(NULL != m_other)
        //{
        //	//< �ƴ� ĳ���� ������ ��(��) ã��
        //	m_map->aroundLine( m_other->getPos(), m_other->getAroundVertex() );
        //	//< �ƴ� ĳ���Ϳ� ���� �浹üũ
        //	if( true == m_map->collision( m_other->getPos(), m_other->getAroundVertex() ) )
        //	{
        //		//< �浹 �Ǿ��ٸ� ���� ��ġ��
        //		m_other->setPosToPrev();
        //	}
        //	objTemp = m_map->collisionObject( m_other->getPos() );
        //	if( 0 != objTemp )
        //	{
        //		m_other->gainCollider( objTemp );
        //	}
        //	//< �ƴ�ĳ����
        //	m_other->update();
        //}

        //< ���� ��ư-------------------------------------------------
        if (m_button_Skill[0].getPlayButtonAni() == true)
        {
            //< �ִϸ��̼� ������
            m_button_Skill[0].inPlayButtonAni(false);
            //< Ŭ�� ������
            m_button_Skill[0].inClickButton(false);
        }
        //< �뽬 ��ư-------------------------------------------------
        if (m_button_Skill[1].getPlayButtonAni() == true)
        {
            //< �ִϸ��̼� ������
            m_button_Skill[1].inPlayButtonAni(false);
            //< Ŭ�� ������
            m_button_Skill[1].inClickButton(false);
        }
        //< ��ų ��ư-------------------------------------------------
        if (m_button_Skill[2].getPlayButtonAni() == true)
        {
            //< �ִϸ��̼� ������
            m_button_Skill[2].inPlayButtonAni(false);
            //< Ŭ�� ������
            m_button_Skill[2].inClickButton(false);
        }

        //< ä��â ������Ʈ
        //chatting->update( mousePos );

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

    //< ĳ���� ��ġ ����
    /*if(true == HOST_SERVER->getHostis() && true == HOST_SERVER->getIsConnector())
    {
        static DWORD flag = GetTickCount();
        if(GetTickCount() - flag >= 1000)
        {
            LOG_MGR->addLog("[HOST][SEND]");
            LOG_MGR->addLog("P2P_CHAR_POS_UPDATE");
            PACKET packet;
            packet.m_charPosUpdate.m_length = sizeof(P2P_CHARPOSUPDATE);
            packet.m_charPosUpdate.m_type = P2P_CHAR_POS_UPDATE;
            packet.m_charPosUpdate.host = m_player->getPos();
            if(NULL == m_other)
            {
                POINT unPos = {0, 0};
                packet.m_charPosUpdate.other = unPos;
            }
            else
            {
                packet.m_charPosUpdate.other = m_other->getPos();
            }
            HOST_SERVER->sendOtherPlayer((char*)&packet, packet.m_monster.m_length);
            flag = GetTickCount();
        }
    }*/
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
        m_map->render(screenDC);
        //<���� �� ���
        m_map->renderWall(screenDC);

        //< ����Ʈ ����
#ifdef __RELEASE
        SIZE ltmpSZ = RC_MGR->findImage(imgID_LITE_MAPING)->getSize();
        RENDER_MGR->render(screenDC, imgID_LITE_MAPING, m_player->getPos().x - ltmpSZ.cx / 2 - CAMERA->getX(), m_player->getPos().y - ltmpSZ.cy / 2 - RENDER_OFFSET_Y - CAMERA->getY());
#endif

        //<�������
        MON_MGR->render( screenDC );
        MON_MGR->renderUnitList(screenDC);
        //< �þ� ȿ��
#ifdef __RELEASE
        RENDER_MGR->render(screenDC, imgID_SIGHT, 0, 0);
#endif
        //<ĳ���� ���
        //m_player->render( screenDC );

        //< �ƴ��� �����߳�
        /*if(NULL != m_other)
        {
            m_other->render( screenDC );
        }*/

        //< ���� ȭ�� ����
        imgScreen->render(hdc, 0, 0);
        //< UI ����
        renderUI(hdc);
        //< ä��â ����
        //chatting->render( hdc );
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
    //if( NULL != chatting ){ chatting->release(); }
    //SAFE_DELETE( chatting );

    SAFE_DELETE(m_player);
    //SAFE_DELETE( m_other );
    SAFE_DELETE(m_map);
    //SOUND_MGR->soundStop(SOUND_INGAME);
}

//< UI �ε�
void ScenePlayGame::initUI(void)
{
    //< ��ų��ư
    m_button_Skill[0].init(
        "Data/Resource/Image/Interface/skill_Attack.bmp",
        "Data/Resource/Image/Interface/skill_Attack_02.bmp",
        "Data/Resource/Image/Interface/skill_Attack_NO.bmp",
        40, 40);
    m_button_Skill[1].init(
        "Data/Resource/Image/Interface/skill_Dash.bmp",
        "Data/Resource/Image/Interface/skill_Dash_02.bmp",
        "Data/Resource/Image/Interface/skill_Dash_NO.bmp",
        40, 40);
    m_button_Skill[2].init(
        "Data/Resource/Image/Interface/skill_All.bmp",
        "Data/Resource/Image/Interface/skill_All_02.bmp",
        "Data/Resource/Image/Interface/skill_All_NO.bmp",
        40, 40);
    m_button_Skill[3].init(
        "Data/Resource/Image/Interface/skill_Heal_02.bmp",
        "Data/Resource/Image/Interface/skill_Heal_02.bmp",
        "Data/Resource/Image/Interface/skill_Heal_NO.bmp",
        40, 40);
    //< ������ ��ư
    m_m_button_Item[0].init(
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    m_m_button_Item[1].init(
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    m_m_button_Item[2].init(
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        40, 40);
    m_m_button_Item[3].init(
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
        "Data/Resource/Image/Interface/no_item.bmp",
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
    m_charName.LoadText(m_charName.getRect(), "HY������M", 25, ALIGN_CENTER, 255, 255, 255);

    //< ���ݹ�
    m_stat[0].init(
        "Data/Resource/Image/Interface/stat_T.bmp",
        "Data/Resource/Image/Interface/stat_T.bmp",
        "Data/Resource/Image/Interface/stat_T.bmp",
        120, 42);
    m_stat[1].init(
        "Data/Resource/Image/Interface/stat_S.bmp",
        "Data/Resource/Image/Interface/stat_S.bmp",
        "Data/Resource/Image/Interface/stat_S.bmp",
        120, 42);
    m_stat[2].init(
        "Data/Resource/Image/Interface/stat_M.bmp",
        "Data/Resource/Image/Interface/stat_M.bmp",
        "Data/Resource/Image/Interface/stat_M.bmp",
        120, 42);
    for (int i = 0; i < 3; i++)
    {
        m_stat[i].setRectPos(570 + ((120 * i) + (10 * i)), 640, ALIGN_RIGHT_TOP);
    }
    //< ���� ǥ��
    m_stat_S.inSetRect(m_stat[0].getRect().left + 35, m_stat[0].getRect().top + 42, m_stat[0].getRect().right, m_stat[0].getRect().bottom + 42);
    m_stat_Q.inSetRect(m_stat[1].getRect().left + 35, m_stat[1].getRect().top + 42, m_stat[1].getRect().right, m_stat[1].getRect().bottom + 42);
    m_stat_M.inSetRect(m_stat[2].getRect().left + 35, m_stat[2].getRect().top + 42, m_stat[2].getRect().right, m_stat[2].getRect().bottom + 42);
    m_stat_S.LoadText(m_stat_S.getRect(), "HY������M", 20, ALIGN_CENTER, 255, 255, 255);
    m_stat_Q.LoadText(m_stat_Q.getRect(), "HY������M", 20, ALIGN_CENTER, 255, 255, 255);
    m_stat_M.LoadText(m_stat_M.getRect(), "HY������M", 20, ALIGN_CENTER, 255, 255, 255);

    //< ������ ��
    m_bar_experience_back.load("Data/Resource/Image/Interface/UI_lvup_NO.bmp", 380, 19, RM_TRANS);
    m_bar_experience.load("Data/Resource/Image/Interface/UI_lvup.bmp", 760, 19, RM_TRANS);
    //< ����ġ ǥ��
    m_bar_experience_string.inSetRect(450, 690, 450 + 380, 690 + 19);
    m_bar_experience_string.LoadText(m_bar_experience_string.getRect(), "HY������M", 15, ALIGN_CENTER, 255, 255, 255);

    //< ü�¹� 
    m_bar_live_back.load("Data/Resource/Image/Interface/UI_live_NO.bmp", 380, 19, RM_TRANS);
    m_bar_live.load("Data/Resource/Image/Interface/UI_live.bmp", 760, 19, RM_TRANS);
    //< ü�¹� ǥ��
    m_bar_live_string.inSetRect(100, 10, 100 + 380, 10 + 19);
    m_bar_live_string.LoadText(m_bar_live_string.getRect(), "HY������M", 15, ALIGN_CENTER, 255, 255, 255);

    //< ������
    m_bar_mana_back.load("Data/Resource/Image/Interface/UI_mana_NO.bmp", 380, 19, RM_TRANS);
    m_bar_mana.load("Data/Resource/Image/Interface/UI_mana.bmp", 760, 19, RM_TRANS);
    //< ������ ǥ�� 
    m_bar_mana_string.inSetRect(100, 37, 100 + 380, 37 + 19);
    m_bar_mana_string.LoadText(m_bar_mana_string.getRect(), "HY������M", 15, ALIGN_CENTER, 255, 255, 255);

    //< ���� ǥ��
    m_lv_bar.init(
        "Data/Resource/Image/Interface/UI_LV.bmp",
        "Data/Resource/Image/Interface/UI_LV.bmp",
        "Data/Resource/Image/Interface/UI_LV.bmp",
        81, 47);
    m_lv_bar.setRectPos(10, 10, ALIGN_LEFT_TOP);

    //< ���� ǥ��
    m_lv_bar_string.LoadText(m_lv_bar.getRect(), "HY������M", 25, ALIGN_CENTER, 255, 255, 255);

    //< ������ 
    m_stage.inSetRect(1150, 10, 1260, 109);
    m_stage.LoadText(m_stage.getRect(), "HY������M", 50, ALIGN_CENTER, 255, 255, 255);

    //< ĳ���� ����
    m_charState.inSetRect(500, 10, 500 + 90, 10 + 50);
    m_charState.LoadText(m_charState.getRect(), "HY������M", 20, ALIGN_CENTER, 255, 255, 255);
}

//< UI �׸���
void ScenePlayGame::renderUI(HDC hdc)
{
    if (NULL != hdc)
    {
        //< ���ڿ� ����
        TCHAR tempStr[_MAX_FNAME];

        //< �������ͽ� ���ڿ�
        static char *belief[] = { "����","������ġ","����Ű","�����ƽ�","Ÿ����" };
        static char *tribe[] = { "�����ΰ�","��Ÿ��ν�","����","�𵥵�" };
        static char *job[] = { "����","����","��ó","������" };
        static char *condition[] = { "","��","��ȭ","��ȭ", "����" };

        //< ĳ���� ��ǥ, ��ǥ �ε��� ǥ��
        //sprintf_s(tempStr, "x : %3d,   y : %3d", m_player->getPos().x/TILE_SIZE_X, m_player->getPos().y/TILE_SIZE_Y );
        //TextOut( hdc, SCREEN_X - 250, 400, tempStr, lstrlen(tempStr) );
        //sprintf_s(tempStr, "x : %3d,   y : %3d", m_player->getPos().x, m_player->getPos().y );
        //TextOut( hdc, SCREEN_X - 250, 430, tempStr, lstrlen(tempStr) );

        //< �� ���� ����
        int moveBar = 0;

        //< ��ų 
        for (int i = 0; i < 4; i++)
        {
            m_button_Skill[i].render(hdc);
            //m_m_button_Item[i].render( hdc );
        }

        //< ĳ���� ����
        sprintf_s(tempStr, _MAX_FNAME, "%s", condition[m_player->getCondition()]);
        m_charState.OutputText(hdc, tempStr);
        //Rectangle( hdc, m_charState.getRect().left, m_charState.getRect().top, m_charState.getRect().right, m_charState.getRect().bottom );

        sprintf_s(tempStr, _MAX_FNAME, "%s %s %s", belief[m_player->getBelief()], tribe[m_player->getTribe()], job[m_player->getJob()]);
        //< ĳ���� �̸�
        m_charName.OutputText(hdc, tempStr);
        //Rectangle( hdc, m_charName.getRect().left, m_charName.getRect().top, m_charName.getRect().right, m_charName.getRect().bottom );
        //< ����ǥ��
        for (int i = 0; i < 3; i++)
        {
            m_stat[i].render(hdc);
        }
        //< ���� ǥ��
        sprintf_s(tempStr, _MAX_FNAME, "��:%2d", m_player->getStrong());
        m_stat_S.OutputText(hdc, tempStr);
        sprintf_s(tempStr, _MAX_FNAME, "��:%2d", m_player->getAgility());
        m_stat_Q.OutputText(hdc, tempStr);
        sprintf_s(tempStr, _MAX_FNAME, "��:%2d", m_player->getIntel());
        m_stat_M.OutputText(hdc, tempStr);

        //< ����ġ��
        m_bar_experience_back.render(hdc, 450, 690);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->getLevelInfo().getNowExp()) / m_player->getLevelInfo().getMaxExp()) * 380));
        m_bar_experience.render(hdc, 450, 690, 380, 19, moveBar, 0, 760, 19);
        sprintf_s(tempStr, 256, "%d/%d", m_player->getLevelInfo().getNowExp(), m_player->getLevelInfo().getMaxExp());
        //< ����ġ ǥ��
        m_bar_experience_string.OutputText(hdc, tempStr);

        //< ü�¹�
        m_bar_live_back.render(hdc, 100, 10);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->getHP()) / m_player->getMaxHP()) * 380));
        m_bar_live.render(hdc, 100, 10, 380, 19, moveBar, 0, 760, 19);
        sprintf_s(tempStr, 256, "%d/%d", m_player->getHP(), m_player->getMaxHP());
        //< ü�¹� ǥ��
        m_bar_live_string.OutputText(hdc, tempStr);

        //< ������
        m_bar_mana_back.render(hdc, 100, 37);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->getMP()) / m_player->getMaxMP()) * 380));
        m_bar_mana.render(hdc, 100, 37, 380, 19, moveBar, 0, 760, 19);
        sprintf_s(tempStr, 256, "%d/%d", m_player->getMP(), m_player->getMaxMP());
        //< ������ ǥ��
        m_bar_mana_string.OutputText(hdc, tempStr);

        //< ���� ǥ��
        m_lv_bar.render(hdc);
        sprintf_s(tempStr, 256, "LV.%d", m_player->getLevelInfo().getNowLevel());
        m_lv_bar_string.OutputText(hdc, tempStr);

        //< ���� ����
        sprintf_s(tempStr, "%d��", m_map->getNowFloor());
        m_stage.OutputText(hdc, tempStr);

        //< �÷��̾� �κ��丮 ǥ��
        m_player->renderInven(hdc);
    }
}

//< �̺�Ʈó��
LRESULT ScenePlayGame::StateProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //< �˾�â�� ������ ����
    if (POPUP_MGR->getCheckPopup_ON() != true)
    {
        switch (msg)
        {
        case WM_CHAR:
        {
            //< ä��â �Է��� ����������
            //if( chatting->getChatingOn() == false )
            {
                switch (wparam)
                {
                case 'a':
                {
                    //< �뽬 ��ư-------------------------------------------------
                    m_button_Skill[1].inClickButton(true);
                }
                break;
                case 's':
                {
                    //< ��ų ��ư-------------------------------------------------
                    m_button_Skill[2].inClickButton(true);
                }
                break;
                }
            }
        }
        break;
        case WM_KEYDOWN:
        {
            //< ä��â �Է��� ����������
            //if( chatting->getChatingOn() == false )
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
            case VK_RETURN:
            {
                //< ä��â �Է��� ����������
                //chatting->changeChattingOn();
                //if( chatting->getChatingOn() == false )
                //{
                //	//< ä��â Ű��
                //	chatting->inChatingView( );
                //}
            }
            break;
            case VK_ESCAPE:
                //pause
                m_playingGame = false;
                break;
            }
            break;
        }
        }
    }
    else
    {
        return POPUP_MGR->PopupProc(wnd, msg, wparam, lparam);
    }

    /*if(NULL != chatting)
    {
        return chatting->StateProc( wnd, msg, wparam, lparam );
    }*/

    return (DefWindowProc(wnd, msg, wparam, lparam));
}

//< ��Ż �� �ʱ�ȭ
void ScenePlayGame::initByPortal(POINT &destPos)
{
    //< ��Ż�� �浹 üũ
    if (true == m_map->inPortal(destPos))
    {
        m_player->setPos(m_map->getCharPos());
    }
}