#include "stdafx.h"

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 瞪羲滲熱, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
HINSTANCE	g_hInst;								//檣蝶欐蝶 с菟 摹樹 (遴艙羹薯縑憮 薑п還 廓��)
HWND		g_hWnd;									//孺紫辦 с菟 摹樹 (孺紫辦蒂 渠ルж朝 廓��)
//< 瞪羲僥濠翮
TCHAR  		g_ClassName[128] = _T("Ackashic");		//贗楚蝶 檜葷
TCHAR  		g_WinName[128] = _T("Ackashic");		//孺紫辦 檜葷
//< 詭景
LPCTSTR		lpszClass=TEXT("Menu");

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, л熱 Щ煎饜 顫殮, Ackashic. 式收≧(л熱曖 錳⑽ 摹樹)
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
//< 孺紫辦 薑曖 塽 蛔煙
void	registWnd( void );
//< 孺紫辦 儅撩 塽 爾罹輿晦
bool	createWnd( void );
//< 孺紫辦 Щ煎衛螳
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 孺紫辦 詭檣 л熱, Ackashic. 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// apientry			==  winmainл熱曖 ��轎 寞衝
// hInstance		==	Щ煎斜極曖 檣蝶欐蝶 с菟(孺紫辦鍔 遴艙羹薯縑憮 薑п還 孺紫辦曖 囀萄廓��(堅嶸貲餌))
// hPrevInstance	==	夥煎 擅縑 褒ч脹 Щ煎斜極曖 檣蝶欐蝶 с菟
// lpszCmdParam		==	褒ч 霜�醴� 翮 だ橾曖 唳煎陛 瞪殖脹棻.
// nCmdShow			==  孺紫辦蒂 �飛橦� 轎溘й 寞徹('孺紫辦蒂 �側瘓� ж罹 爾罹遽棻'塭朝 曖嘐, 傳朝 獗曹棻.)
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	//< 瞪羲檣蝶欐蝶
	g_hInst = hInstance;
	
	//< 1. 薑曖 / 2. 蛔煙 
	registWnd();

	//< 3. 儅撩 
	if( false == createWnd() )
	{
		//< 孺紫辦 儅撩褒ぬ
		return 0;
	}

	//< 蟾晦��
	if( GAME_MGR->init() == false )
	{
		return 0;
	}
	
	//< 4. 孺紫辦蒂 �飛橦� 爾罹遽棻
	ShowWindow(g_hWnd, nCmdShow);

	//< 5. 詭撮雖 瑞Щ
	WPARAM wparam = GAME_MGR->msgLoop();

	//< 薑葬
	GAME_MGR->release();
		
	return wparam;
}

//< 1. 孺紫辦 薑曖, 2. 蛔煙
void	registWnd( void )
{
	WNDCLASS	WndClass;		//孺紫辦 贗楚蝶 摹樹

	//< 1 孺紫辦 贗楚蝶 濛撩 (孺紫辦曖 樓撩擊 薑曖 и棻)
	WndClass.cbClsExtra		= 0;									//孺紫辦鍔陛 頂睡瞳戲煎 餌辨й 罹碟詭賅葬	
	WndClass.cbWndExtra		= 0;									//孺紫辦鍔陛 頂睡瞳戲煎 餌辨й 罹碟詭賅葬
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//寡唳儀鼻 雖薑
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//醴憮蒂 撲薑и棻(葬模蝶蒂 鱔п憮 錳ж朝 斜楚а蒂 蛔煙 й熱紫 氈棻)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//嬴檜夔擊 檗朝棻(葬模蝶蒂 鱔п憮 錳ж朝 斜楚а蒂 蛔煙 й熱紫 氈棻)
	WndClass.hInstance		= g_hInst;								//孺紫辦 贗楚蝶曖 檣蝶欐蝶(孺紫辦鍔 遴艙羹薯縑憮 薑п還 孺紫辦曖 囀萄廓��(堅嶸貲餌))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//孺紫辦 Щ煎衛盪曖 檜葷(孺紫辦曖 詭衛雖 籀葬 л熱蒂 雖薑)
	WndClass.lpszClassName	= g_ClassName;							//孺紫辦 贗楚蝶曖 檜葷(橫蛤梱雖釭 贗楚蝶 檜葷橾 閨檜棻)
	WndClass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);			//詭景曖 檜葷(葬模蝶 縑蛤攪 曖п 滌紫煎 虜菟橫颶, 餌辨擊 寰ж賊 NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//孺紫辦曖 蝶顫橾(孺紫辦曖 觼晦陛 滲й陽 棻衛 斜萼棻.)

	//< 2 贗楚蝶蒂 蛔煙и棻 (薑曖и 孺紫辦 贗楚蝶蒂 蛔煙и棻)
	RegisterClass(&WndClass);								
}

//< 3. 孺紫辦 儅撩
bool	createWnd( void )
{
	//< 孺紫辦璽 觼晦 虜菟晦.
	int width = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 4;
	int hegith = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 4 +
		GetSystemMetrics(SM_CYCAPTION);
	
	//< 孺紫辦璽 醞懈戲煎 螃啪 虜菟晦
	int screenX = GetSystemMetrics( SM_CXSCREEN );
	int screenY = GetSystemMetrics( SM_CYSCREEN );
	int startX = screenX / 2 - WINSIZE_X/2;
	int startY = screenY / 2 - WINSIZE_Y/2;
	
	//< 3 孺紫辦蒂 虜萇棻 (詭賅葬 鼻縑 孺紫辦蒂 儅撩и棻)
	g_hWnd = CreateWindow(g_ClassName,				// 孺紫辦贗楚蝶 僥濠翮 
		g_WinName,									// 顫檜ぎ夥縑 釭顫陳 僥濠翮
		WS_OVERLAPPEDWINDOW,						// 孺紫辦曖 ⑽鷓 褫暮(OR 翱骯濠 餌辨)顫檜ぎ夥, 蝶觼煤夥, 觼晦褻瞰陛棟 蛔蛔
		startX, startY,								// 孺紫辦 衛濛嬪纂
		width, hegith,								// 孺紫辦 觼晦
		NULL,										// 睡賅孺紫辦曖 с菟 (睡賅 孺紫辦陛 橈堅 濠褐檜 譆鼻嬪 孺紫辦 橾陽 NULL)
		(HMENU)NULL,								// 詭景曖 с菟 (詭景蒂 餌辨 寰ж嘎煎 NULL)			
		g_hInst,									// 檣蝶欐蝶
		NULL);										// createStruct塭朝 掘褻羹曖 輿模 (罹楝偃曖 孺紫辦蒂 虜菟陽 餌辨 腎釭 剪曖 餌辨ж雖 彊朝棻.)

	if( NULL == g_hWnd )
	{
		//< 孺紫辦 儅撩 褒ぬ 詭撮雖 籀葬
		return false;
	}	

	return true;
}

//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
// ≧收式 2015.04, 孺紫辦 Щ煎衛盪, Crazy.(詭撮雖 籀葬 л熱) 式收≧
//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam, LPARAM lParam)
{
	return GAME_MGR->WndProc( hWnd, iMessage, wParam,lParam );
}
