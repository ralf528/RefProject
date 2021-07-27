#include "stdafx.h"

#include "../ImageNode.h"
#include "../MY_FontMgr.h"

#include "../PopupMgr.h"

//#include "../SceneLogin.h"
#include "../SceneLobby.h"
#include "../ScenePlayGame.h"

#include "../PopupBox.h"
#include "../CheckBox.h"

#include "sceneLoading.h"
#include "SceneChoiceChar.h"
#include "process.h "

//> 로딩 쓰레드
unsigned int CALLBACK loadingThread(void* arg)
{
	//> 임계 영역 설정
	ENTER_SECTION;
	int* id = (int*)arg;

	STATE_MGR->changeState(*id);

	//> 임계영역 나가기
	LEAVE_SECTION;
	return 0;
}

SceneChoiceChar::SceneChoiceChar(void)
{
	//< 폰트 할당
	m_font = new MY_Font;
	m_fontBox1 = new MY_Font;
	m_fontBox2 = new MY_Font;

	//< 배경 이미지
	m_image = new PopupBox;

	//< 입력판
	m_StateBox1 = new PopupBox;
	m_StateBox2 = new PopupBox;

	//< 팝업창 체크

	//< 체크박스 종족
	checkBox_Box1_01 = new CheckBox;
	checkBox_Box1_02 = new CheckBox;
	checkBox_Box1_03 = new CheckBox;
	checkBox_Box1_04 = new CheckBox;
	//< 체크박스 직업
	checkBox_Box2_01 = new CheckBox;
	checkBox_Box2_02 = new CheckBox;
	checkBox_Box2_03 = new CheckBox;
	checkBox_Box2_04 = new CheckBox;

	//< 버튼
	button_START_GAME = new ButtonClass;
	button_BACK = new ButtonClass;
	button_STATE = POPUP_NONE;
}

SceneChoiceChar::~SceneChoiceChar(void)
{
	release();
}


//< 초기화
bool SceneChoiceChar::init( void ) 
{
	//< 배경이미지
	m_image->init(L"Data/Resource/Image/background_Login.bmp",WINSIZE_X,WINSIZE_Y );
	m_image->setRectPos( 0,0, ALIGN_LEFT_TOP );
	//----------------------------------------------------------------------------
	//< 버튼 초기화
	button_START_GAME->init(
		L"Data/Resource/Image/button_START.bmp",
		L"Data/Resource/Image/button_START_02.bmp",400, 130);
	//< 폰트
	button_START_GAME->loadFont(L"게임 시작", button_START_GAME->getRect(),
		L"HY헤드라인M",
		60, ALIGN_CENTER, 255,255,255 );
	button_START_GAME->setRectPos( WINSIZE_X/2, WINSIZE_Y/10 *9 -30, ALIGN_CENTER );

	//< 버튼 확인
	button_BACK->init(L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_BACK->loadFont(L"뒤로가기", button_BACK->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	button_BACK->setRectPos( WINSIZE_X -40, WINSIZE_Y -40, ALIGN_RIGHT_BOTTOM );
	//---------------------------------------------------------------------------------
	//< 입력판 
	m_StateBox1->init(L"Data/Resource/Image/Popup_Box5.bmp", 540, 440 );
	m_StateBox1->setRectPos( WINSIZE_X/2-300, WINSIZE_Y/2-70, ALIGN_CENTER );
	//< 입력판 
	m_StateBox2->init(L"Data/Resource/Image/Popup_Box5.bmp", 540, 440 );
	m_StateBox2->setRectPos( WINSIZE_X/2+300, WINSIZE_Y/2-70, ALIGN_CENTER );

	POINT inputBoard1 = m_StateBox1->getCenter();
	POINT inputBoard2 = m_StateBox2->getCenter();
	//---------------------------------------------------------------------------------
	//< 버튼 체크박스 1
	checkBox_Box1_01->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box1_01->loadFont(L"늑대인간", checkBox_Box1_01->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_01->setRectPos( inputBoard1.x, inputBoard1.y -70, ALIGN_CENTER );

	//< 버튼 체그박스 2
	checkBox_Box1_02->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box1_02->loadFont(L"켄타우루스", checkBox_Box1_02->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_02->setRectPos( inputBoard1.x, inputBoard1.y , ALIGN_CENTER );

	//< 버튼 체크박스 3
	checkBox_Box1_03->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box1_03->loadFont(L"엘프", checkBox_Box1_03->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_03->setRectPos( inputBoard1.x, inputBoard1.y + 70, ALIGN_CENTER );

	//< 버튼 체그박스 4
	checkBox_Box1_04->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box1_04->loadFont(L"언데드", checkBox_Box1_04->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_04->setRectPos( inputBoard1.x, inputBoard1.y + 140, ALIGN_CENTER );
	//---------------------------------------------------------------------------------
	//< 버튼 체크박스 1
	checkBox_Box2_01->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box2_01->loadFont(L"전사", checkBox_Box2_01->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_01->setRectPos( inputBoard2.x, inputBoard2.y -70, ALIGN_CENTER );

	//< 버튼 체그박스 2
	checkBox_Box2_02->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box2_02->loadFont(L"도둑", checkBox_Box2_02->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_02->setRectPos( inputBoard2.x, inputBoard2.y , ALIGN_CENTER );

	//< 버튼 체크박스 3
	checkBox_Box2_03->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box2_03->loadFont(L"궁수", checkBox_Box2_03->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_03->setRectPos( inputBoard2.x, inputBoard2.y + 70, ALIGN_CENTER );

	//< 버튼 체그박스 4
	checkBox_Box2_04->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box2_04->loadFont(L"마법사", checkBox_Box2_04->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_04->setRectPos( inputBoard2.x, inputBoard2.y + 140, ALIGN_CENTER );
	//---------------------------------------------------------------------------------
	//< 처음은 허용 상태로 만들기
	checkBox_Box1_01->inCheckBox( CHECK_BOX_ON );
	checkBox_Box2_01->inCheckBox( CHECK_BOX_ON );
	//---------------------------------------------------------------------------------
	//< 폰트
	m_fontBox1->LoadText(L"종족", m_StateBox1->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );
	//< 폰트
	m_fontBox2->LoadText(L"직업", m_StateBox2->getRect(),
		L"HY헤드라인M",
		30, ALIGN_CENTER, 255,255,255 );

	return true;
}
//< 업데이트
void SceneChoiceChar::update(float fDeltaTime)
{
	//< 팝업이 켜지 않았다면 갱신하지 않기
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< 버튼 위치 받기
		button_START_GAME->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_START_GAME->getRect() ));
		button_START_GAME->update();
		//< 버튼 확인
		button_BACK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_BACK->getRect() ));
		button_BACK->update();

		//< 체크박스 
		checkBox_Box1_01->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_01->getRect() ));
		checkBox_Box1_01->update(); 
		checkBox_Box1_02->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_02->getRect() ));
		checkBox_Box1_02->update();
		checkBox_Box1_03->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_03->getRect() ));
		checkBox_Box1_03->update(); 
		checkBox_Box1_04->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_04->getRect() ));
		checkBox_Box1_04->update();
		//< 체크박스 
		checkBox_Box2_01->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_01->getRect() ));
		checkBox_Box2_01->update(); 
		checkBox_Box2_02->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_02->getRect() ));
		checkBox_Box2_02->update();
		checkBox_Box2_03->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_03->getRect() ));
		checkBox_Box2_03->update(); 
		checkBox_Box2_04->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_04->getRect() ));
		checkBox_Box2_04->update();
	}

	//< 팝업창이 열려있지 않으면 실행
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< 로그인 버튼-------------------------------------------------
		//< 버튼이 눌리고, 애니메이션이 재생되었다면 씬전환
		if( button_START_GAME->getClickButton() == true &&
			button_START_GAME->getPlayButtonAni() == true )
		{
            LOG_MGR->addLog("게임을 시작합니다");

            STATE_MGR->setLoadID(SCENE_PLAYGAME);

            //< 로딩씬 추가
            STATE_MGR->addState<sceneLoading>(SCENE_LOADING);
            //< 게임 씬 추가
            STATE_MGR->addState<ScenePlayGame>(SCENE_PLAYGAME);
            
            STATE_MGR->changeState(SCENE_LOADING);

            //< 기존씬삭제
            STATE_MGR->deleteState(SCENE_SELECT);

            unsigned int threadID;
            //> 로딩 쓰레드 생성
            _beginthreadex(NULL, 0, loadingThread, STATE_MGR->getLoadID(), 0, &threadID);

			return;
		}

		//< 뒤로가기
		if( button_BACK->getPlayButtonAni() == true )
		{
			button_BACK->inClickButton( false );
			button_BACK->inPlayButtonAni( false );
			//< 클릭 리턴
            button_STATE = POPUP_NO_POPUP;

			//< 씬전환
			STATE_MGR->addState<SceneLobby>(SCENE_LOBBY);
			STATE_MGR->changeState( SCENE_LOBBY );
			//< 기존씬삭제
			STATE_MGR->deleteState( SCENE_SELECT );

			return;
		}

		//체크박스--------------------------------------------------------
		//< 버튼 1
		if( checkBox_Box1_01->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box1_01->inCheckMouseOn( false );
			checkBox_Box1_01->inClickButton( false );
			checkBox_Box1_01->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box1_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box1_01->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//< 버튼 2
		if( checkBox_Box1_02->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box1_02->inCheckMouseOn( false );
			checkBox_Box1_02->inClickButton( false );
			checkBox_Box1_02->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box1_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box1_02->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//< 버튼 3
		if( checkBox_Box1_03->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box1_03->inCheckMouseOn( false );
			checkBox_Box1_03->inClickButton( false );
			checkBox_Box1_03->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box1_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box1_03->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//< 버튼 4
		if( checkBox_Box1_04->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box1_04->inCheckMouseOn( false );
			checkBox_Box1_04->inClickButton( false );
			checkBox_Box1_04->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box1_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_03->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_03->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box1_04->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//체크박스--------------------------------------------------------
		//< 버튼 1
		if( checkBox_Box2_01->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box2_01->inCheckMouseOn( false );
			checkBox_Box2_01->inClickButton( false );
			checkBox_Box2_01->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box2_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box2_01->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//< 버튼 2
		if( checkBox_Box2_02->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box2_02->inCheckMouseOn( false );
			checkBox_Box2_02->inClickButton( false );
			checkBox_Box2_02->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box2_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box2_02->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//< 버튼 3
		if( checkBox_Box2_03->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box2_03->inCheckMouseOn( false );
			checkBox_Box2_03->inClickButton( false );
			checkBox_Box2_03->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box2_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box2_03->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
		//< 버튼 4
		if( checkBox_Box2_04->getPlayButtonAni() == true )
		{
			//< 상태 돌리기
			checkBox_Box2_04->inCheckMouseOn( false );
			checkBox_Box2_04->inClickButton( false );
			checkBox_Box2_04->inPlayButtonAni( false );

			//< 비허용의 체크박스가 ON이라면 OFF로 바꾸기
			if( checkBox_Box2_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_03->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_03->inCheckBox( CHECK_BOX_OFF );
			}
			//< 체크상태로 만들기
			checkBox_Box2_04->inCheckBox( CHECK_BOX_ON );

			//< 클릭 리턴
			button_STATE = POPUP_NONE;
		}
	}
	//< 팝업창이 켜지면 갱신
	else
	{
		//< 팝업 갱신
		POPUP_MGR->updatePopup();
		//< 2차 팝업( 팝업에서 눌린버튼 판별 )
		int tempFlag = POPUP_MGR->buttonStatePopup();

		//< 할당이 되지 않았다면
		if( tempFlag == false )
		{
			//< 팝업창 끄기
		}
	}

	//< 박스 배경판 업데이트
	m_StateBox1->update();
	m_StateBox2->update();
}
//< 랜더
void SceneChoiceChar::render( HDC hdc ) 
{
	//< 배경이미지
	m_image->renderNone( hdc );
	//<임시-----------------------------------------------------------
#ifdef _DEBUG
	if( NULL != hdc )
	{
		m_font->OutputText( hdc, 
			L"캐릭터 선택 씬",
			0,0,
			L"HY얕은샘물M",
			65,
			0,0,0 );
	}
	//< 마우스가 올라가 있는 상태면
	if( button_START_GAME->getCheckMouseOn() == true )
	{
		TextOut( hdc, 200,0, L"충돌",4);
	}
	else
	{
		TextOut( hdc, 200,0, L"비충돌",6);
	}
#endif
	//-------------------------------------------------------------
	//< 버튼 랜더
	button_START_GAME->render( hdc );
	button_BACK->render( hdc );

	//< 팝업창이 켜지면 랜더
	if( POPUP_MGR->getCheckPopup_ON() == true )
	{
		//< 팝업창 랜더
		POPUP_MGR->renderPopup( hdc );
	}

	//< 입력판
	m_StateBox1->renderNone( hdc );
	m_StateBox2->renderNone( hdc );

	//< 체크박스
	checkBox_Box1_01->render( hdc );
	checkBox_Box1_02->render( hdc );
	checkBox_Box1_03->render( hdc );
	checkBox_Box1_04->render( hdc );
	//< 체크박스
	checkBox_Box2_01->render( hdc );
	checkBox_Box2_02->render( hdc );
	checkBox_Box2_03->render( hdc );
	checkBox_Box2_04->render( hdc );

	//< 폰트
	m_fontBox1->OutputText( hdc, 0, 0, 0, -290 );
	m_fontBox2->OutputText( hdc, 0, 0, 0, -290 );
}

//< 해제
void SceneChoiceChar::release( void ) 
{
	//< 폰트 삭제
	SAFE_DELETE( m_font );
	SAFE_DELETE( m_fontBox1 );
	SAFE_DELETE( m_fontBox2 );

	//< 버튼 삭제
	if( button_START_GAME != NULL ){ button_START_GAME->release(); }
	SAFE_DELETE( button_START_GAME );
	if( button_BACK != NULL ) { button_BACK->release();}
	SAFE_DELETE( button_BACK );

	//< 배경 이미지
	if( m_image != NULL ){ m_image->release(); }
	SAFE_DELETE( m_image );

	//< 입력판
	if( m_StateBox1 != NULL ){ m_StateBox1->release(); }
	SAFE_DELETE( m_StateBox1 );
	if( m_StateBox2 != NULL ){ m_StateBox2->release(); }
	SAFE_DELETE( m_StateBox2 );

	//< 체크박스
	if( checkBox_Box1_01 != NULL ){ checkBox_Box1_01->release(); }
	SAFE_DELETE( checkBox_Box1_01 );
	if( checkBox_Box1_02 != NULL ){ checkBox_Box1_02->release(); }
	SAFE_DELETE( checkBox_Box1_02 );
	if( checkBox_Box1_03 != NULL ){ checkBox_Box1_03->release(); }
	SAFE_DELETE( checkBox_Box1_03 );
	if( checkBox_Box1_04 != NULL ){ checkBox_Box1_04->release(); }
	SAFE_DELETE( checkBox_Box1_04 );
	//< 체크박스
	if( checkBox_Box2_01 != NULL ){ checkBox_Box2_01->release(); }
	SAFE_DELETE( checkBox_Box2_01 );
	if( checkBox_Box2_02 != NULL ){ checkBox_Box2_02->release(); }
	SAFE_DELETE( checkBox_Box2_02 );
	if( checkBox_Box2_03 != NULL ){ checkBox_Box2_03->release(); }
	SAFE_DELETE( checkBox_Box2_03 );
	if( checkBox_Box2_04 != NULL ){ checkBox_Box2_04->release(); }
	SAFE_DELETE( checkBox_Box2_04 );

	//로비 사운드 종료
	//SOUND_MGR->soundStop(SOUND_LOBBY);
}

//< 이벤트처리
LRESULT	SceneChoiceChar::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	//< 네트워크 이벤트
	/*case WM_MYSOCKET_NOTIFY:
		{
			TCPIP_CLIENT->onMySocketNotify(wparam, lparam);
		}
		break;*/
	case WM_LBUTTONUP :
		{
			//< 로그인 버튼-------------------------------------------------
			if( button_START_GAME->getCheckMouseOn() == true )
			{
				button_START_GAME->inClickButton( true );
				
				break;
			}
			//< 뒤로가기 버튼-------------------------------------------------
			if( button_BACK->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				button_BACK->inClickButton( true );
				
			}
			//< 체크박스-------------------------------------------------
			//< 1
			if( checkBox_Box1_01->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box1_01->inClickButton( true );
			}
			//< 2
			if( checkBox_Box1_02->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box1_02->inClickButton( true );
			}
			//< 3
			if( checkBox_Box1_03->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box1_03->inClickButton( true );
			}
			//< 4
			if( checkBox_Box1_04->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box1_04->inClickButton( true );	
			}
			//< 체크박스-------------------------------------------------
			//< 1
			if( checkBox_Box2_01->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box2_01->inClickButton( true );
			}
			//< 2
			if( checkBox_Box2_02->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box2_02->inClickButton( true );
			}
			//< 3
			if( checkBox_Box2_03->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box2_03->inClickButton( true );
			}
			//< 4
			if( checkBox_Box2_04->getCheckMouseOn() == true )
			{
				//< 클릭으로 상태 변경
				checkBox_Box2_04->inClickButton( true );
			}
		}
		break;
		//< 마우스 위치 받기
	case WM_MOUSEMOVE :
		{
			mousePos.x = LOWORD( lparam );
			mousePos.y = HIWORD( lparam );
		}
		break;
	case WM_KEYDOWN :
		{
			switch( wparam )
			{
			case VK_RETURN :
				{
					button_START_GAME->inClickButton( true );
				}
				break;
			}
		}
		break;
	case VK_ESCAPE :
		//PostQuitMessage(0);
		break;
	}

	return (DefWindowProc( wnd ,msg,wparam,lparam));
}