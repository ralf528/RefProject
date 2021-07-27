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

//< 초기화
bool ScenePlayGame::init(void)
{
    //< 카메라 초기화
    CAMERA->init();
    //< 스크린 버퍼 추가
    RC_MGR->addImage(imgID_SCREENBUFFER, SCREEN_X, SCREEN_Y);
    //< 게임 UI 이미지 추가
    RC_MGR->addImage(imgID_GAME_UI, L"Data/Resource/gameUI/IngameUI.bmp", 0, 0, RM_TRANS);
    //< 시야 효과
    RC_MGR->addImage(imgID_SIGHT, L"Data/Resource/gameUI/시야.bmp", 0, 0, RM_ALPHA32);
    //< 라이트맵핑
    RC_MGR->addImage(imgID_LITE_MAPING, L"Data/Resource/gameUI/라이트맵핑alpha.bmp", 0, 0, RM_ALPHA32);
    //< 타격 효과
    RC_MGR->addImage(imgID_HITEFF1, L"Data/Resource/effect/GetHit_tong.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_HITEFF2, L"Data/Resource/effect/GetHit_Ghost.bmp", 0, 0, RM_TRANS);
    RC_MGR->addImage(imgID_HITEFF3, L"Data/Resource/effect/GetHit_Bug.bmp", 0, 0, RM_TRANS);

    STATE_MGR->setLoading(30);

    //< 난수 발생기 초기화
    srand(GetTickCount());
    //맵초기화
    m_World = new WorldManager;
    m_World->init();

    STATE_MGR->setLoading(80);

    //캐릭터 정보 초기화
    m_player = new PlayerCharacter();
    m_player->Init();
    //< 몬스터 매니저에 캐릭터 연결
    MON_MGR->setDestPlayer(m_player->GetCharacter());

    //캐릭터 위치 초기화
    m_player->GetCharacter()->setPos(m_World->GetSpawnPos());

    //게임 배경음 플레이
    //SOUND_MGR->soundPlay(SOUND_INGAME);

    LOG_MGR->addLog("%s", "플레이씬 초기화");

    //< UI 초기화
    initUI();
    //< 채팅창
    chatting->init();

    STATE_MGR->setLoading(100); Sleep(500);

    return true;
}
//< 업데이트
void ScenePlayGame::update(float fDeltaTime)
{
    static DWORD ffff = GetTickCount();
    if (GetTickCount() - ffff >= 5000)
    {
        POINT pos = m_player->GetCharacter()->getPos();
        LOG_MGR->addLog("좌표 : %d / %d", pos.x, pos.y);
        ffff = GetTickCount();
    }

    CAMERA->update();

    //< 팝업창이 없을때 갱신
    if (POPUP_MGR->getCheckPopup_ON() != true)
    {
        //< 채팅창 입력이 꺼져있을때
        //if( chatting->getChatingOn() == false )
        {
            //< 캐릭터 무브&업데이트
            m_player->Update(fDeltaTime);
        }
        //< 캐릭터 주위의 선(벽) 찾기
        m_World->aroundLine(m_player->GetCharacter()->getPos(), m_player->GetCharacter()->getAroundVertex());

        //< 캐릭터와 맵의 충돌체크
        if (m_World->collision(m_player->GetCharacter()->getPos(), m_player->GetCharacter()->getAroundVertex()))
        {
            //< 충돌 되었다면 이전 위치로
            m_player->GetCharacter()->setPosToPrev();
        }
        //< 캐릭터와 오브젝트 충돌체크
        E_TileBrush objTemp = m_World->collisionObject(m_player->GetCharacter()->getPos());
        if (0 != objTemp)
        {
            m_player->GetCharacter()->gainCollider(objTemp);
        }

        //> 포탈과 충돌 시 이동
        if (m_World->IsColPortal(m_player->GetCharacter()->getPos()) == true)
        {
            initByPortal(m_player->GetCharacter()->getPos());
        }

        //< 몬스터와 맵의 충돌 체크
        for (size_t i = 0; i < MON_MGR->getSize(); i++)
        {
            //< 주위의 선(벽) 찾기
            m_World->aroundLine(MON_MGR->getMonster(i)->getPos(), MON_MGR->getMonster(i)->getAroundVertex());
            //< 벽에 대한 충돌 체크
            if (true == m_World->collision(MON_MGR->getMonster(i)->getPos(), MON_MGR->getMonster(i)->getAroundVertex()))
            {
                //< 충돌 되었다면 이전 위치로
                MON_MGR->getMonster(i)->setPosToPrev();
            }
        }
        //< 몬스터 업데이트
        MON_MGR->update(fDeltaTime);
        //< 캐릭터 위치 갱신
        m_player->GetCharacter()->setRect();

        for (int i = 0; i < MAX_SKILL_COUNT; i++)
        {
            if (m_button_Skill[i].getPlayButtonAni() == true)
            {
                //< 애니메이션 돌리기
                m_button_Skill[i].inPlayButtonAni(false);
                //< 클릭 돌리기
                m_button_Skill[i].inClickButton(false);
            }
        }

        //< 채팅창 업데이트
        chatting->update( mousePos );

    }
    //< 팝업창이 켜지면 갱신
    if (POPUP_MGR->getCheckPopup_ON() == true)
    {
        //< 팝업 갱신
        POPUP_MGR->updatePopup();
        //< 2차 팝업( 팝업에서 눌린버튼 판별 )
        int tempFlag = POPUP_MGR->buttonStatePopup();

        //< 할당이 되지 않았다면
        if (tempFlag == false)
        {
            //< 팝업창 끄기
        }
    }
}

//< 랜더
void ScenePlayGame::render(HDC hdc)
{
    if (NULL != hdc)
    {
        //< 스크린 버퍼 불러오기
        ImageNode *imgScreen = RC_MGR->findImage(imgID_SCREENBUFFER);
        screenDC = imgScreen->getMemDC();
        RECT screenRect;
        SetRect(&screenRect, 0, 0, SCREEN_X, SCREEN_Y);
        //< 스크린 지우기
        FillRect(screenDC, &screenRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

        //<타일맵 출력
        m_World->render(screenDC);
        //<맵의 벽 출력
        m_World->renderWall(screenDC);

        m_player->Render(hdc);

        //<몬스터출력
        MON_MGR->render( screenDC );
        MON_MGR->renderUnitList(screenDC);
        //< 시야 효과
#ifdef __RELEASE
        RENDER_MGR->render(screenDC, imgID_SIGHT, 0, 0);
#endif
        //<캐릭터 출력
        //m_player->render( screenDC );

        //< 게임 화면 랜더
        imgScreen->render(hdc, 0, 0);
        //< UI 랜더
        renderUI(hdc);
        //< 채팅창 랜더
        chatting->render( hdc );
    }

    //< 팝업창이 켜지면 랜더
    if (POPUP_MGR->getCheckPopup_ON() == true)
    {
        //< 팝업창 랜더
        POPUP_MGR->renderPopup(hdc);

        for (int i = 0; i < 4; i++)
        {
            m_button_Skill[i].inPlayButtonAni(false);
            m_button_Skill[i].inCheckMouseOn(false);
            m_button_Skill[i].inClickButton(false);
        }
    }
}
//< 해제
void ScenePlayGame::release(void)
{
    if( NULL != chatting ){ chatting->release(); }
    SAFE_DELETE( chatting );

    SAFE_RELEASE(m_player);
    SAFE_DELETE(m_World);
    //SOUND_MGR->soundStop(SOUND_INGAME);
}

//< UI 로딩
void ScenePlayGame::initUI(void)
{
    //< 스킬버튼
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
    //< 아이템 버튼
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
        //< 스킬버튼 
        m_button_Skill[i].setRectPos(150 + ((40 * i) + (10 * i)), WINSIZE_Y - 50, ALIGN_LEFT_TOP);
        //< 아이템버튼 
        m_m_button_Item[i].setRectPos(920 + ((40 * i) + (10 * i)), WINSIZE_Y - 50, ALIGN_RIGHT_TOP);
    }

    //< 캐릭터 이름
    m_charName.inSetRect(450, 607 - 20, 830, 666 - 20);
    m_charName.LoadText(m_charName.getRect(), L"HY헤드라인M", 25, ALIGN_CENTER, 255, 255, 255);

    //< 스텟바
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
    //< 스텟 표시
    m_stat_S.inSetRect(m_stat[0].getRect().left + 35, m_stat[0].getRect().top + 42, m_stat[0].getRect().right, m_stat[0].getRect().bottom + 42);
    m_stat_Q.inSetRect(m_stat[1].getRect().left + 35, m_stat[1].getRect().top + 42, m_stat[1].getRect().right, m_stat[1].getRect().bottom + 42);
    m_stat_M.inSetRect(m_stat[2].getRect().left + 35, m_stat[2].getRect().top + 42, m_stat[2].getRect().right, m_stat[2].getRect().bottom + 42);
    m_stat_S.LoadText(m_stat_S.getRect(), L"HY헤드라인M", 20, ALIGN_CENTER, 255, 255, 255);
    m_stat_Q.LoadText(m_stat_Q.getRect(), L"HY헤드라인M", 20, ALIGN_CENTER, 255, 255, 255);
    m_stat_M.LoadText(m_stat_M.getRect(), L"HY헤드라인M", 20, ALIGN_CENTER, 255, 255, 255);

    //< 경험지 바
    m_bar_experience_back.load(L"Data/Resource/Image/Interface/UI_lvup_NO.bmp", 380, 19, RM_TRANS);
    m_bar_experience.load(L"Data/Resource/Image/Interface/UI_lvup.bmp", 760, 19, RM_TRANS);
    //< 경험치 표시
    m_bar_experience_string.inSetRect(450, 690, 450 + 380, 690 + 19);
    m_bar_experience_string.LoadText(m_bar_experience_string.getRect(), L"HY헤드라인M", 15, ALIGN_CENTER, 255, 255, 255);

    //< 체력바 
    m_bar_live_back.load(L"Data/Resource/Image/Interface/UI_live_NO.bmp", 380, 19, RM_TRANS);
    m_bar_live.load(L"Data/Resource/Image/Interface/UI_live.bmp", 760, 19, RM_TRANS);
    //< 체력바 표시
    m_bar_live_string.inSetRect(100, 10, 100 + 380, 10 + 19);
    m_bar_live_string.LoadText(m_bar_live_string.getRect(), L"HY헤드라인M", 15, ALIGN_CENTER, 255, 255, 255);

    //< 마나바
    m_bar_mana_back.load(L"Data/Resource/Image/Interface/UI_mana_NO.bmp", 380, 19, RM_TRANS);
    m_bar_mana.load(L"Data/Resource/Image/Interface/UI_mana.bmp", 760, 19, RM_TRANS);
    //< 마나바 표시 
    m_bar_mana_string.inSetRect(100, 37, 100 + 380, 37 + 19);
    m_bar_mana_string.LoadText(m_bar_mana_string.getRect(), L"HY헤드라인M", 15, ALIGN_CENTER, 255, 255, 255);

    //< 레벨 표시
    m_lv_bar.init(
        L"Data/Resource/Image/Interface/UI_LV.bmp",
        L"Data/Resource/Image/Interface/UI_LV.bmp",
        L"Data/Resource/Image/Interface/UI_LV.bmp",
        81, 47);
    m_lv_bar.setRectPos(10, 10, ALIGN_LEFT_TOP);

    //< 레벨 표시
    m_lv_bar_string.LoadText(m_lv_bar.getRect(), L"HY헤드라인M", 25, ALIGN_CENTER, 255, 255, 255);

    //< 층도달 
    m_stage.inSetRect(1150, 10, 1260, 109);
    m_stage.LoadText(m_stage.getRect(), L"HY헤드라인M", 50, ALIGN_CENTER, 255, 255, 255);

    //< 캐릭터 상태
    m_charState.inSetRect(500, 10, 500 + 90, 10 + 50);
    m_charState.LoadText(m_charState.getRect(), L"HY헤드라인M", 20, ALIGN_CENTER, 255, 255, 255);
}

//< UI 그리기
void ScenePlayGame::renderUI(HDC hdc)
{
    if (NULL != hdc)
    {
        //< 문자열 조합
        TCHAR tempStr[_MAX_FNAME];

        //< 스테이터스 문자열
		static TCHAR *belief[] = { TEXT("지드"), TEXT("마가츠치"), TEXT("나아키"), TEXT("보레아스"), TEXT("타나토") };
		static TCHAR *tribe[] = { TEXT("늑대인간"), TEXT("켄타우로스"), TEXT("엘프"), TEXT("언데드") };
		static TCHAR *job[] = { TEXT("전사"), TEXT("도적"), TEXT("아처"), TEXT("마법사") };
		static TCHAR *condition[] = { TEXT(""), TEXT("독"), TEXT("강화"), TEXT("약화"), TEXT("무적") };

        //< 캐릭터 좌표, 좌표 인덱스 표시
        //swprintf_s(tempStr, "x : %3d,   y : %3d", m_player->getPos().x/TILE_SIZE_X, m_player->getPos().y/TILE_SIZE_Y );
        //TextOut( hdc, SCREEN_X - 250, 400, tempStr, lstrlen(tempStr) );
        //swprintf_s(tempStr, "x : %3d,   y : %3d", m_player->getPos().x, m_player->getPos().y );
        //TextOut( hdc, SCREEN_X - 250, 430, tempStr, lstrlen(tempStr) );

        //< 바 전용 변수
        int moveBar = 0;

        //< 스킬 
        for (int i = 0; i < MAX_SKILL_COUNT; i++)
        {
            m_button_Skill[i].render(hdc);
            //m_m_button_Item[i].render( hdc );
        }

        //< 캐릭터 상태
        swprintf_s(tempStr, _MAX_FNAME, TEXT("%s"), condition[m_player->GetCharacter()->getCondition()]);
        m_charState.OutputText(hdc, tempStr);
        //Rectangle( hdc, m_charState.getRect().left, m_charState.getRect().top, m_charState.getRect().right, m_charState.getRect().bottom );

        swprintf_s(tempStr, _MAX_FNAME, TEXT("%s %s %s"), belief[m_player->GetCharacter()->getBelief()], tribe[m_player->GetCharacter()->getTribe()], job[m_player->GetCharacter()->getJob()]);
        //< 캐릭터 이름
        m_charName.OutputText(hdc, tempStr);
        //Rectangle( hdc, m_charName.getRect().left, m_charName.getRect().top, m_charName.getRect().right, m_charName.getRect().bottom );
        //< 스텟표시
        for (int i = 0; i < 3; i++)
        {
            m_stat[i].render(hdc);
        }
        //< 스텟 표시
        swprintf_s(tempStr, _MAX_FNAME, TEXT("힘:%2d"), m_player->GetCharacter()->getStrong());
        m_stat_S.OutputText(hdc, tempStr);
        swprintf_s(tempStr, _MAX_FNAME, TEXT("민:%2d"), m_player->GetCharacter()->getAgility());
        m_stat_Q.OutputText(hdc, tempStr);
        swprintf_s(tempStr, _MAX_FNAME, TEXT("지:%2d"), m_player->GetCharacter()->getIntel());
        m_stat_M.OutputText(hdc, tempStr);

        //< 경험치바
        m_bar_experience_back.render(hdc, 450, 690);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->GetCharacter()->getLevelInfo().getNowExp()) / m_player->GetCharacter()->getLevelInfo().getMaxExp()) * 380));
        m_bar_experience.render(hdc, 450, 690, 380, 19, moveBar, 0, 760, 19);
        swprintf_s(tempStr, 256, TEXT("%d/%d"), m_player->GetCharacter()->getLevelInfo().getNowExp(), m_player->GetCharacter()->getLevelInfo().getMaxExp());
        //< 경험치 표시
        m_bar_experience_string.OutputText(hdc, tempStr);

        //< 체력바
        m_bar_live_back.render(hdc, 100, 10);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->GetCharacter()->getHP()) / m_player->GetCharacter()->getMaxHP()) * 380));
        m_bar_live.render(hdc, 100, 10, 380, 19, moveBar, 0, 760, 19);
        swprintf_s(tempStr, 256, TEXT("%d/%d"), m_player->GetCharacter()->getHP(), m_player->GetCharacter()->getMaxHP());
        //< 체력바 표시
        m_bar_live_string.OutputText(hdc, tempStr);

        //< 마나바
        m_bar_mana_back.render(hdc, 100, 37);

        moveBar = static_cast<int>(380 - ((static_cast<float>(m_player->GetCharacter()->getMP()) / m_player->GetCharacter()->getMaxMP()) * 380));
        m_bar_mana.render(hdc, 100, 37, 380, 19, moveBar, 0, 760, 19);
        swprintf_s(tempStr, 256, TEXT("%d/%d"), m_player->GetCharacter()->getMP(), m_player->GetCharacter()->getMaxMP());
        //< 마나바 표시
        m_bar_mana_string.OutputText(hdc, tempStr);

        //< 레벨 표시
        m_lv_bar.render(hdc);
        swprintf_s(tempStr, 256, TEXT("LV.%d"), m_player->GetCharacter()->getLevelInfo().getNowLevel());
        m_lv_bar_string.OutputText(hdc, tempStr);

        //< 도달 층수
        swprintf_s(tempStr, TEXT("%d층"), m_World->getNowFloor());
        m_stage.OutputText(hdc, tempStr);

        //< 플레이어 인벤토리 표시
        m_player->GetCharacter()->renderInven(hdc);
    }
}

//< 이벤트처리
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
            //< 채팅창 입력이 꺼져있을때
            if (chatting && chatting->getChatingOn() == false)
            {
                switch (wparam)
                {
                case 'a':
                case 'A':
                {
                    //< 대쉬 버튼-------------------------------------------------
                    m_button_Skill[1].inClickButton(true);
                }
                break;
                case 's':
                case 'S':
                {
                    //< 스킬 버튼-------------------------------------------------
                    m_button_Skill[2].inClickButton(true);
                }
                break;
                case 'd':
                case 'D':
                {
                    //< 스킬 버튼-------------------------------------------------
                    m_button_Skill[3].inClickButton(true);
                }
                break;
                }
            }
        }
        break;
        case WM_KEYDOWN:
        {
            //< 채팅창 입력이 꺼져있을때
            if (chatting && chatting->getChatingOn() == false)
            {
                switch (wparam)
                {
                case VK_SPACE:
                {
                    //< 공격 버튼-------------------------------------------------
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

//< 포탈 후 초기화
void ScenePlayGame::initByPortal(POINT &destPos)
{
    //< 포탈과 충돌 체크
    if (true == m_World->inPortal(destPos))
    {
        m_player->GetCharacter()->setPos(m_World->GetSpawnPos());
    }
}