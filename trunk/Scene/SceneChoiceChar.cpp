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

//> �ε� ������
unsigned int CALLBACK loadingThread(void* arg)
{
	//> �Ӱ� ���� ����
	ENTER_SECTION;
	int* id = (int*)arg;

	STATE_MGR->changeState(*id);

	//> �Ӱ迵�� ������
	LEAVE_SECTION;
	return 0;
}

SceneChoiceChar::SceneChoiceChar(void)
{
	//< ��Ʈ �Ҵ�
	m_font = new MY_Font;
	m_fontBox1 = new MY_Font;
	m_fontBox2 = new MY_Font;

	//< ��� �̹���
	m_image = new PopupBox;

	//< �Է���
	m_StateBox1 = new PopupBox;
	m_StateBox2 = new PopupBox;

	//< �˾�â üũ

	//< üũ�ڽ� ����
	checkBox_Box1_01 = new CheckBox;
	checkBox_Box1_02 = new CheckBox;
	checkBox_Box1_03 = new CheckBox;
	checkBox_Box1_04 = new CheckBox;
	//< üũ�ڽ� ����
	checkBox_Box2_01 = new CheckBox;
	checkBox_Box2_02 = new CheckBox;
	checkBox_Box2_03 = new CheckBox;
	checkBox_Box2_04 = new CheckBox;

	//< ��ư
	button_START_GAME = new ButtonClass;
	button_BACK = new ButtonClass;
	button_STATE = POPUP_NONE;
}

SceneChoiceChar::~SceneChoiceChar(void)
{
	release();
}


//< �ʱ�ȭ
bool SceneChoiceChar::init( void ) 
{
	//< ����̹���
	m_image->init(L"Data/Resource/Image/background_Login.bmp",WINSIZE_X,WINSIZE_Y );
	m_image->setRectPos( 0,0, ALIGN_LEFT_TOP );
	//----------------------------------------------------------------------------
	//< ��ư �ʱ�ȭ
	button_START_GAME->init(
		L"Data/Resource/Image/button_START.bmp",
		L"Data/Resource/Image/button_START_02.bmp",400, 130);
	//< ��Ʈ
	button_START_GAME->loadFont(L"���� ����", button_START_GAME->getRect(),
		L"HY������M",
		60, ALIGN_CENTER, 255,255,255 );
	button_START_GAME->setRectPos( WINSIZE_X/2, WINSIZE_Y/10 *9 -30, ALIGN_CENTER );

	//< ��ư Ȯ��
	button_BACK->init(L"Data/Resource/Image/button_OK.bmp",
		L"Data/Resource/Image/button_OK_02.bmp",
		200, 50 );
	button_BACK->loadFont(L"�ڷΰ���", button_BACK->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	button_BACK->setRectPos( WINSIZE_X -40, WINSIZE_Y -40, ALIGN_RIGHT_BOTTOM );
	//---------------------------------------------------------------------------------
	//< �Է��� 
	m_StateBox1->init(L"Data/Resource/Image/Popup_Box5.bmp", 540, 440 );
	m_StateBox1->setRectPos( WINSIZE_X/2-300, WINSIZE_Y/2-70, ALIGN_CENTER );
	//< �Է��� 
	m_StateBox2->init(L"Data/Resource/Image/Popup_Box5.bmp", 540, 440 );
	m_StateBox2->setRectPos( WINSIZE_X/2+300, WINSIZE_Y/2-70, ALIGN_CENTER );

	POINT inputBoard1 = m_StateBox1->getCenter();
	POINT inputBoard2 = m_StateBox2->getCenter();
	//---------------------------------------------------------------------------------
	//< ��ư üũ�ڽ� 1
	checkBox_Box1_01->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box1_01->loadFont(L"�����ΰ�", checkBox_Box1_01->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_01->setRectPos( inputBoard1.x, inputBoard1.y -70, ALIGN_CENTER );

	//< ��ư ü�׹ڽ� 2
	checkBox_Box1_02->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box1_02->loadFont(L"��Ÿ��罺", checkBox_Box1_02->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_02->setRectPos( inputBoard1.x, inputBoard1.y , ALIGN_CENTER );

	//< ��ư üũ�ڽ� 3
	checkBox_Box1_03->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box1_03->loadFont(L"����", checkBox_Box1_03->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_03->setRectPos( inputBoard1.x, inputBoard1.y + 70, ALIGN_CENTER );

	//< ��ư ü�׹ڽ� 4
	checkBox_Box1_04->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box1_04->loadFont(L"�𵥵�", checkBox_Box1_04->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box1_04->setRectPos( inputBoard1.x, inputBoard1.y + 140, ALIGN_CENTER );
	//---------------------------------------------------------------------------------
	//< ��ư üũ�ڽ� 1
	checkBox_Box2_01->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box2_01->loadFont(L"����", checkBox_Box2_01->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_01->setRectPos( inputBoard2.x, inputBoard2.y -70, ALIGN_CENTER );

	//< ��ư ü�׹ڽ� 2
	checkBox_Box2_02->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box2_02->loadFont(L"����", checkBox_Box2_02->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_02->setRectPos( inputBoard2.x, inputBoard2.y , ALIGN_CENTER );

	//< ��ư üũ�ڽ� 3
	checkBox_Box2_03->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60 );
	checkBox_Box2_03->loadFont(L"�ü�", checkBox_Box2_03->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_03->setRectPos( inputBoard2.x, inputBoard2.y + 70, ALIGN_CENTER );

	//< ��ư ü�׹ڽ� 4
	checkBox_Box2_04->init(L"Data/Resource/Image/on_off_choice.bmp",
		L"Data/Resource/Image/on_off_choice_02.bmp",
		L"Data/Resource/Image/on_off_choice2.bmp",
		L"Data/Resource/Image/on_off_choice2_02.bmp",
		430, 60  );
	checkBox_Box2_04->loadFont(L"������", checkBox_Box2_04->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	checkBox_Box2_04->setRectPos( inputBoard2.x, inputBoard2.y + 140, ALIGN_CENTER );
	//---------------------------------------------------------------------------------
	//< ó���� ��� ���·� �����
	checkBox_Box1_01->inCheckBox( CHECK_BOX_ON );
	checkBox_Box2_01->inCheckBox( CHECK_BOX_ON );
	//---------------------------------------------------------------------------------
	//< ��Ʈ
	m_fontBox1->LoadText(L"����", m_StateBox1->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );
	//< ��Ʈ
	m_fontBox2->LoadText(L"����", m_StateBox2->getRect(),
		L"HY������M",
		30, ALIGN_CENTER, 255,255,255 );

	return true;
}
//< ������Ʈ
void SceneChoiceChar::update(float fDeltaTime)
{
	//< �˾��� ���� �ʾҴٸ� �������� �ʱ�
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< ��ư ��ġ �ޱ�
		button_START_GAME->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_START_GAME->getRect() ));
		button_START_GAME->update();
		//< ��ư Ȯ��
		button_BACK->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, button_BACK->getRect() ));
		button_BACK->update();

		//< üũ�ڽ� 
		checkBox_Box1_01->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_01->getRect() ));
		checkBox_Box1_01->update(); 
		checkBox_Box1_02->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_02->getRect() ));
		checkBox_Box1_02->update();
		checkBox_Box1_03->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_03->getRect() ));
		checkBox_Box1_03->update(); 
		checkBox_Box1_04->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box1_04->getRect() ));
		checkBox_Box1_04->update();
		//< üũ�ڽ� 
		checkBox_Box2_01->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_01->getRect() ));
		checkBox_Box2_01->update(); 
		checkBox_Box2_02->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_02->getRect() ));
		checkBox_Box2_02->update();
		checkBox_Box2_03->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_03->getRect() ));
		checkBox_Box2_03->update(); 
		checkBox_Box2_04->inCheckMouseOn( myUTIL::collision::isColPtInRect( mousePos, checkBox_Box2_04->getRect() ));
		checkBox_Box2_04->update();
	}

	//< �˾�â�� �������� ������ ����
	if( POPUP_MGR->getCheckPopup_ON() == false )
	{
		//< �α��� ��ư-------------------------------------------------
		//< ��ư�� ������, �ִϸ��̼��� ����Ǿ��ٸ� ����ȯ
		if( button_START_GAME->getClickButton() == true &&
			button_START_GAME->getPlayButtonAni() == true )
		{
            LOG_MGR->addLog("������ �����մϴ�");

            STATE_MGR->setLoadID(SCENE_PLAYGAME);

            //< �ε��� �߰�
            STATE_MGR->addState<sceneLoading>(SCENE_LOADING);
            //< ���� �� �߰�
            STATE_MGR->addState<ScenePlayGame>(SCENE_PLAYGAME);
            
            STATE_MGR->changeState(SCENE_LOADING);

            //< ����������
            STATE_MGR->deleteState(SCENE_SELECT);

            unsigned int threadID;
            //> �ε� ������ ����
            _beginthreadex(NULL, 0, loadingThread, STATE_MGR->getLoadID(), 0, &threadID);

			return;
		}

		//< �ڷΰ���
		if( button_BACK->getPlayButtonAni() == true )
		{
			button_BACK->inClickButton( false );
			button_BACK->inPlayButtonAni( false );
			//< Ŭ�� ����
            button_STATE = POPUP_NO_POPUP;

			//< ����ȯ
			STATE_MGR->addState<SceneLobby>(SCENE_LOBBY);
			STATE_MGR->changeState( SCENE_LOBBY );
			//< ����������
			STATE_MGR->deleteState( SCENE_SELECT );

			return;
		}

		//üũ�ڽ�--------------------------------------------------------
		//< ��ư 1
		if( checkBox_Box1_01->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box1_01->inCheckMouseOn( false );
			checkBox_Box1_01->inClickButton( false );
			checkBox_Box1_01->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box1_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box1_01->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//< ��ư 2
		if( checkBox_Box1_02->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box1_02->inCheckMouseOn( false );
			checkBox_Box1_02->inClickButton( false );
			checkBox_Box1_02->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box1_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box1_02->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//< ��ư 3
		if( checkBox_Box1_03->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box1_03->inCheckMouseOn( false );
			checkBox_Box1_03->inClickButton( false );
			checkBox_Box1_03->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box1_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box1_03->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//< ��ư 4
		if( checkBox_Box1_04->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box1_04->inCheckMouseOn( false );
			checkBox_Box1_04->inClickButton( false );
			checkBox_Box1_04->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box1_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box1_03->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box1_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box1_03->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box1_04->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//üũ�ڽ�--------------------------------------------------------
		//< ��ư 1
		if( checkBox_Box2_01->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box2_01->inCheckMouseOn( false );
			checkBox_Box2_01->inClickButton( false );
			checkBox_Box2_01->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box2_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box2_01->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//< ��ư 2
		if( checkBox_Box2_02->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box2_02->inCheckMouseOn( false );
			checkBox_Box2_02->inClickButton( false );
			checkBox_Box2_02->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box2_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_03->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_03->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box2_02->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//< ��ư 3
		if( checkBox_Box2_03->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box2_03->inCheckMouseOn( false );
			checkBox_Box2_03->inClickButton( false );
			checkBox_Box2_03->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box2_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_04->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_04->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box2_03->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
		//< ��ư 4
		if( checkBox_Box2_04->getPlayButtonAni() == true )
		{
			//< ���� ������
			checkBox_Box2_04->inCheckMouseOn( false );
			checkBox_Box2_04->inClickButton( false );
			checkBox_Box2_04->inPlayButtonAni( false );

			//< ������� üũ�ڽ��� ON�̶�� OFF�� �ٲٱ�
			if( checkBox_Box2_01->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_02->getCheckBox() == CHECK_BOX_ON ||
				checkBox_Box2_03->getCheckBox() == CHECK_BOX_ON )
			{
				checkBox_Box2_01->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_02->inCheckBox( CHECK_BOX_OFF );
				checkBox_Box2_03->inCheckBox( CHECK_BOX_OFF );
			}
			//< üũ���·� �����
			checkBox_Box2_04->inCheckBox( CHECK_BOX_ON );

			//< Ŭ�� ����
			button_STATE = POPUP_NONE;
		}
	}
	//< �˾�â�� ������ ����
	else
	{
		//< �˾� ����
		POPUP_MGR->updatePopup();
		//< 2�� �˾�( �˾����� ������ư �Ǻ� )
		int tempFlag = POPUP_MGR->buttonStatePopup();

		//< �Ҵ��� ���� �ʾҴٸ�
		if( tempFlag == false )
		{
			//< �˾�â ����
		}
	}

	//< �ڽ� ����� ������Ʈ
	m_StateBox1->update();
	m_StateBox2->update();
}
//< ����
void SceneChoiceChar::render( HDC hdc ) 
{
	//< ����̹���
	m_image->renderNone( hdc );
	//<�ӽ�-----------------------------------------------------------
#ifdef _DEBUG
	if( NULL != hdc )
	{
		m_font->OutputText( hdc, 
			L"ĳ���� ���� ��",
			0,0,
			L"HY��������M",
			65,
			0,0,0 );
	}
	//< ���콺�� �ö� �ִ� ���¸�
	if( button_START_GAME->getCheckMouseOn() == true )
	{
		TextOut( hdc, 200,0, L"�浹",4);
	}
	else
	{
		TextOut( hdc, 200,0, L"���浹",6);
	}
#endif
	//-------------------------------------------------------------
	//< ��ư ����
	button_START_GAME->render( hdc );
	button_BACK->render( hdc );

	//< �˾�â�� ������ ����
	if( POPUP_MGR->getCheckPopup_ON() == true )
	{
		//< �˾�â ����
		POPUP_MGR->renderPopup( hdc );
	}

	//< �Է���
	m_StateBox1->renderNone( hdc );
	m_StateBox2->renderNone( hdc );

	//< üũ�ڽ�
	checkBox_Box1_01->render( hdc );
	checkBox_Box1_02->render( hdc );
	checkBox_Box1_03->render( hdc );
	checkBox_Box1_04->render( hdc );
	//< üũ�ڽ�
	checkBox_Box2_01->render( hdc );
	checkBox_Box2_02->render( hdc );
	checkBox_Box2_03->render( hdc );
	checkBox_Box2_04->render( hdc );

	//< ��Ʈ
	m_fontBox1->OutputText( hdc, 0, 0, 0, -290 );
	m_fontBox2->OutputText( hdc, 0, 0, 0, -290 );
}

//< ����
void SceneChoiceChar::release( void ) 
{
	//< ��Ʈ ����
	SAFE_DELETE( m_font );
	SAFE_DELETE( m_fontBox1 );
	SAFE_DELETE( m_fontBox2 );

	//< ��ư ����
	if( button_START_GAME != NULL ){ button_START_GAME->release(); }
	SAFE_DELETE( button_START_GAME );
	if( button_BACK != NULL ) { button_BACK->release();}
	SAFE_DELETE( button_BACK );

	//< ��� �̹���
	if( m_image != NULL ){ m_image->release(); }
	SAFE_DELETE( m_image );

	//< �Է���
	if( m_StateBox1 != NULL ){ m_StateBox1->release(); }
	SAFE_DELETE( m_StateBox1 );
	if( m_StateBox2 != NULL ){ m_StateBox2->release(); }
	SAFE_DELETE( m_StateBox2 );

	//< üũ�ڽ�
	if( checkBox_Box1_01 != NULL ){ checkBox_Box1_01->release(); }
	SAFE_DELETE( checkBox_Box1_01 );
	if( checkBox_Box1_02 != NULL ){ checkBox_Box1_02->release(); }
	SAFE_DELETE( checkBox_Box1_02 );
	if( checkBox_Box1_03 != NULL ){ checkBox_Box1_03->release(); }
	SAFE_DELETE( checkBox_Box1_03 );
	if( checkBox_Box1_04 != NULL ){ checkBox_Box1_04->release(); }
	SAFE_DELETE( checkBox_Box1_04 );
	//< üũ�ڽ�
	if( checkBox_Box2_01 != NULL ){ checkBox_Box2_01->release(); }
	SAFE_DELETE( checkBox_Box2_01 );
	if( checkBox_Box2_02 != NULL ){ checkBox_Box2_02->release(); }
	SAFE_DELETE( checkBox_Box2_02 );
	if( checkBox_Box2_03 != NULL ){ checkBox_Box2_03->release(); }
	SAFE_DELETE( checkBox_Box2_03 );
	if( checkBox_Box2_04 != NULL ){ checkBox_Box2_04->release(); }
	SAFE_DELETE( checkBox_Box2_04 );

	//�κ� ���� ����
	//SOUND_MGR->soundStop(SOUND_LOBBY);
}

//< �̺�Ʈó��
LRESULT	SceneChoiceChar::StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch( msg )
	{
	//< ��Ʈ��ũ �̺�Ʈ
	/*case WM_MYSOCKET_NOTIFY:
		{
			TCPIP_CLIENT->onMySocketNotify(wparam, lparam);
		}
		break;*/
	case WM_LBUTTONUP :
		{
			//< �α��� ��ư-------------------------------------------------
			if( button_START_GAME->getCheckMouseOn() == true )
			{
				button_START_GAME->inClickButton( true );
				
				break;
			}
			//< �ڷΰ��� ��ư-------------------------------------------------
			if( button_BACK->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				button_BACK->inClickButton( true );
				
			}
			//< üũ�ڽ�-------------------------------------------------
			//< 1
			if( checkBox_Box1_01->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box1_01->inClickButton( true );
			}
			//< 2
			if( checkBox_Box1_02->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box1_02->inClickButton( true );
			}
			//< 3
			if( checkBox_Box1_03->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box1_03->inClickButton( true );
			}
			//< 4
			if( checkBox_Box1_04->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box1_04->inClickButton( true );	
			}
			//< üũ�ڽ�-------------------------------------------------
			//< 1
			if( checkBox_Box2_01->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box2_01->inClickButton( true );
			}
			//< 2
			if( checkBox_Box2_02->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box2_02->inClickButton( true );
			}
			//< 3
			if( checkBox_Box2_03->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box2_03->inClickButton( true );
			}
			//< 4
			if( checkBox_Box2_04->getCheckMouseOn() == true )
			{
				//< Ŭ������ ���� ����
				checkBox_Box2_04->inClickButton( true );
			}
		}
		break;
		//< ���콺 ��ġ �ޱ�
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