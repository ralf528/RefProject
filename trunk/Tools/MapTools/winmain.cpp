#include "stdafx.h"

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, Àü¿ªº¯¼ö, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
HINSTANCE	g_hInst;								//ÀÎ½ºÅÏ½º ÇÚµé ¼±¾ð (¿î¿µÃ¼Á¦¿¡¼­ Á¤ÇØÁÙ ¹øÈ£)
HWND		g_hWnd;									//À©µµ¿ì ÇÚµé ¼±¾ð (À©µµ¿ì¸¦ ´ëÇ¥ÇÏ´Â ¹øÈ£)
//< Àü¿ª¹®ÀÚ¿­
TCHAR  		g_ClassName[128] = _T("Ackashic");		//Å¬·¡½º ÀÌ¸§
TCHAR  		g_WinName[128] = _T("Ackashic");		//À©µµ¿ì ÀÌ¸§
//< ¸Þ´º
LPCTSTR		lpszClass=TEXT("Menu");

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, ÇÔ¼ö ÇÁ·ÎÅä Å¸ÀÔ, Ackashic. ¦¡¦¬¡Ù(ÇÔ¼öÀÇ ¿øÇü ¼±¾ð)
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
//< À©µµ¿ì Á¤ÀÇ ¹× µî·Ï
void	registWnd( void );
//< À©µµ¿ì »ý¼º ¹× º¸¿©ÁÖ±â
bool	createWnd( void );
//< À©µµ¿ì ÇÁ·Î½ÃÁ®
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, À©µµ¿ì ¸ÞÀÎ ÇÔ¼ö, Ackashic. ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// apientry			==  winmainÇÔ¼öÀÇ È£Ãâ ¹æ½Ä
// hInstance		==	ÇÁ·Î±×·¥ÀÇ ÀÎ½ºÅÏ½º ÇÚµé(À©µµ¿ìÁî ¿î¿µÃ¼Á¦¿¡¼­ Á¤ÇØÁÙ À©µµ¿ìÀÇ ÄÚµå¹øÈ£(°íÀ¯¸í»ç))
// hPrevInstance	==	¹Ù·Î ¾Õ¿¡ ½ÇÇàµÈ ÇÁ·Î±×·¥ÀÇ ÀÎ½ºÅÏ½º ÇÚµé
// lpszCmdParam		==	½ÇÇà Á÷ÈÄ¿¡ ¿­ ÆÄÀÏÀÇ °æ·Î°¡ Àü´ÞµÈ´Ù.
// nCmdShow			==  À©µµ¿ì¸¦ È­¸é¿¡ Ãâ·ÂÇÒ ¹æ¹ý('À©µµ¿ì¸¦ È°¼ºÈ­ ÇÏ¿© º¸¿©ÁØ´Ù'¶ó´Â ÀÇ¹Ì, ¶Ç´Â ¼û±ä´Ù.)
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	//< Àü¿ªÀÎ½ºÅÏ½º
	g_hInst = hInstance;
	
	//< 1. Á¤ÀÇ / 2. µî·Ï 
	registWnd();

	//< 3. »ý¼º 
	if( false == createWnd() )
	{
		//< À©µµ¿ì »ý¼º½ÇÆÐ
		return 0;
	}

	//< ÃÊ±âÈ­
	if( GAME_MGR->init() == false )
	{
		return 0;
	}
	
	//< 4. À©µµ¿ì¸¦ È­¸é¿¡ º¸¿©ÁØ´Ù
	ShowWindow(g_hWnd, nCmdShow);

	//< 5. ¸Þ¼¼Áö ·çÇÁ
	WPARAM wparam = GAME_MGR->msgLoop();

	//< Á¤¸®
	GAME_MGR->release();
		
	return wparam;
}

//< 1. À©µµ¿ì Á¤ÀÇ, 2. µî·Ï
void	registWnd( void )
{
	WNDCLASS	WndClass;		//À©µµ¿ì Å¬·¡½º ¼±¾ð

	//< 1 À©µµ¿ì Å¬·¡½º ÀÛ¼º (À©µµ¿ìÀÇ ¼Ó¼ºÀ» Á¤ÀÇ ÇÑ´Ù)
	WndClass.cbClsExtra		= 0;									//À©µµ¿ìÁî°¡ ³»ºÎÀûÀ¸·Î »ç¿ëÇÒ ¿©ºÐ¸Þ¸ð¸®	
	WndClass.cbWndExtra		= 0;									//À©µµ¿ìÁî°¡ ³»ºÎÀûÀ¸·Î »ç¿ëÇÒ ¿©ºÐ¸Þ¸ð¸®
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//¹è°æ»ö»ó ÁöÁ¤
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//Ä¿¼­¸¦ ¼³Á¤ÇÑ´Ù(¸®¼Ò½º¸¦ ÅëÇØ¼­ ¿øÇÏ´Â ±×·¡ÇÈ¸¦ µî·Ï ÇÒ¼öµµ ÀÖ´Ù)
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//¾ÆÀÌÄÜÀ» ÀÐ´Â´Ù(¸®¼Ò½º¸¦ ÅëÇØ¼­ ¿øÇÏ´Â ±×·¡ÇÈ¸¦ µî·Ï ÇÒ¼öµµ ÀÖ´Ù)
	WndClass.hInstance		= g_hInst;								//À©µµ¿ì Å¬·¡½ºÀÇ ÀÎ½ºÅÏ½º(À©µµ¿ìÁî ¿î¿µÃ¼Á¦¿¡¼­ Á¤ÇØÁÙ À©µµ¿ìÀÇ ÄÚµå¹øÈ£(°íÀ¯¸í»ç))
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//À©µµ¿ì ÇÁ·Î½ÃÀúÀÇ ÀÌ¸§(À©µµ¿ìÀÇ ¸Þ½ÃÁö Ã³¸® ÇÔ¼ö¸¦ ÁöÁ¤)
	WndClass.lpszClassName	= g_ClassName;							//À©µµ¿ì Å¬·¡½ºÀÇ ÀÌ¸§(¾îµð±îÁö³ª Å¬·¡½º ÀÌ¸§ÀÏ »ÓÀÌ´Ù)
	WndClass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);			//¸Þ´ºÀÇ ÀÌ¸§(¸®¼Ò½º ¿¡µðÅÍ ÀÇÇØ º°µµ·Î ¸¸µé¾îÁü, »ç¿ëÀ» ¾ÈÇÏ¸é NULL)
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//À©µµ¿ìÀÇ ½ºÅ¸ÀÏ(À©µµ¿ìÀÇ Å©±â°¡ º¯ÇÒ¶§ ´Ù½Ã ±×¸°´Ù.)

	//< 2 Å¬·¡½º¸¦ µî·ÏÇÑ´Ù (Á¤ÀÇÇÑ À©µµ¿ì Å¬·¡½º¸¦ µî·ÏÇÑ´Ù)
	RegisterClass(&WndClass);								
}

//< 3. À©µµ¿ì »ý¼º
bool	createWnd( void )
{
	//< À©µµ¿ìÃ¢ Å©±â ¸¸µé±â.
	int width = WINSIZE_X + GetSystemMetrics(SM_CXFRAME) * 4;
	int hegith = WINSIZE_Y + GetSystemMetrics(SM_CYFRAME ) * 4 +
		GetSystemMetrics(SM_CYCAPTION);
	
	//< À©µµ¿ìÃ¢ Áß¾ÓÀ¸·Î ¿À°Ô ¸¸µé±â
	int screenX = GetSystemMetrics( SM_CXSCREEN );
	int screenY = GetSystemMetrics( SM_CYSCREEN );
	int startX = screenX / 2 - WINSIZE_X/2;
	int startY = screenY / 2 - WINSIZE_Y/2;
	
	//< 3 À©µµ¿ì¸¦ ¸¸µç´Ù (¸Þ¸ð¸® »ó¿¡ À©µµ¿ì¸¦ »ý¼ºÇÑ´Ù)
	g_hWnd = CreateWindow(g_ClassName,				// À©µµ¿ìÅ¬·¡½º ¹®ÀÚ¿­ 
		g_WinName,									// Å¸ÀÌÆ²¹Ù¿¡ ³ªÅ¸³¯ ¹®ÀÚ¿­
		WS_OVERLAPPEDWINDOW,						// À©µµ¿ìÀÇ ÇüÅÂ ¿É¼Ç(OR ¿¬»êÀÚ »ç¿ë)Å¸ÀÌÆ²¹Ù, ½ºÅ©·Ñ¹Ù, Å©±âÁ¶Àý°¡´É µîµî
		startX, startY,								// À©µµ¿ì ½ÃÀÛÀ§Ä¡
		width, hegith,								// À©µµ¿ì Å©±â
		NULL,										// ºÎ¸ðÀ©µµ¿ìÀÇ ÇÚµé (ºÎ¸ð À©µµ¿ì°¡ ¾ø°í ÀÚ½ÅÀÌ ÃÖ»óÀ§ À©µµ¿ì ÀÏ¶§ NULL)
		(HMENU)NULL,								// ¸Þ´ºÀÇ ÇÚµé (¸Þ´º¸¦ »ç¿ë ¾ÈÇÏ¹Ç·Î NULL)			
		g_hInst,									// ÀÎ½ºÅÏ½º
		NULL);										// createStruct¶ó´Â ±¸Á¶Ã¼ÀÇ ÁÖ¼Ò (¿©·¯°³ÀÇ À©µµ¿ì¸¦ ¸¸µé¶§ »ç¿ë µÇ³ª °ÅÀÇ »ç¿ëÇÏÁö ¾Ê´Â´Ù.)

	if( NULL == g_hWnd )
	{
		//< À©µµ¿ì »ý¼º ½ÇÆÐ ¸Þ¼¼Áö Ã³¸®
		return false;
	}	

	return true;
}

//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
// ¡Ù¦¬¦¡ 2015.04, À©µµ¿ì ÇÁ·Î½ÃÀú, Crazy.(¸Þ¼¼Áö Ã³¸® ÇÔ¼ö) ¦¡¦¬¡Ù
//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam, LPARAM lParam)
{
	return GAME_MGR->WndProc( hWnd, iMessage, wParam,lParam );
}
