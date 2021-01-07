#include "stdafx.h"
#include <cmath>
#include "myUTIL.h"

using namespace myUTIL;
using namespace math;
using namespace collision;
using namespace window;
using namespace keyInput;

namespace myUTIL
{
	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	// ¡Ù¦¬¦¡ 2015.04, ¼öÇÐ°ü·Ã, Ackashic. ¦¡¦¬¡Ù
	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	namespace math
	{		
		//< µÎÁ¡»çÀÌÀÇ °Å¸® 
		//pt1Àº ±âÁØÁ¡(src), pt2´Â ¸ñÀû´ë»ó(dest)
		float		distancePtToPt( const POINT &pt1, const POINT &pt2 )
		{
			//< °¡·Î º¯À§·®
			float	width = static_cast<float>(pt2.x) - pt1.x;
			//< ¼¼·Î º¯À§·®
			float	height = static_cast<float>(pt2.y) - pt1.y;

			//< ºøº¯ÀÇ ±æÀÌ(ºøº¯±¸ÇÏ´ÂÇÔ¼ö)
			// float hypotenuse  = hypotf( static_cast<double>(width), static_cast<double>(height));

			//< ¹ÝÈ¯
			// return static_cast<float>(hypotenuse);

			float hypotenuse  = sqrt( (width * width) + (height *height ) );

			return hypotenuse;
		}

		//< Á¡ ÀÌµ¿
		void moveToPt(POINT *originPos, POINT *destPos, float speed )
		{
			float theta;

			float x_;
			float y_;
			float h_;

			x_ = static_cast<float>(destPos->x - originPos->x);	//<¹Øº¯
			y_ = static_cast<float>(destPos->y - originPos->y);	//<³ôÀÌ
			h_ = sqrt((x_ * x_) + (y_ * y_));					//<ºøº¯

			if (0 == h_)			//ºøº¯ÀÌ 0ÀÌ¸é ºÐ¸ð°¡ 0ÀÌ µÇ¹Ç·Î Á¾·á
			{
				return;
			}

			theta = acosf(x_ / h_);		//<acos ( ºñÀ²·Î °¢µµ °¢µµ ±¸ÇÏ±â)

			if (h_ > 5.0f)	//<¹üÀ§°¡ °¡±î¿ö Áö¸é ÀÌµ¿ÇÏÁö ¾Êµµ·Ï..
			{
				//<y º¯À§·®ÀÌ ¾ç¼öÀÏ °æ¿ì
				if (y_ > 0)
				{
					//º¯À§·® * ¼Óµµ¸¸Å­ ÀÌµ¿
					originPos->x += static_cast<LONG>(cos(theta)*speed);
					originPos->y += static_cast<LONG>(sin(theta)*speed);
				}
				//<y º¯À§·®ÀÌ À½¼öÀÏ °æ¿ì
				else
				{
					//º¯À§·® * ¼Óµµ¸¸Å­ ÀÌµ¿
					originPos->x += static_cast<LONG>(cos(theta)*speed);
					originPos->y -= static_cast<LONG>(sin(theta)*speed);
				}
			}
		}

		//< °¢µµ °è»ê
		float calcAnglePtToPt(POINT *destPos, POINT *srcPos)
		{
			float x_;		
			float y_;		
			float h_;		
			float theta;	

			x_ = static_cast<float>(destPos->x - srcPos->x);	//<¹Øº¯
			y_ = static_cast<float>(destPos->y - srcPos->y);	//<³ôÀÌ
			h_ = sqrt((x_ * x_) + (y_ * y_));					//<ºøº¯

			if (0 == h_)			//ºøº¯ÀÌ 0ÀÌ¸é ºÐ¸ð°¡ 0ÀÌ µÇ¹Ç·Î Á¾·á
			{
				return 0.f;
			}

			//if (y_ < 0)//µ¥Ä«¸£Æ®
			if (y_ > 0)//À©µµ¿ì
			{
				//<°¢µµ
				theta = acosf(x_ / h_);
				//<acos ÇÔ¼ö´Â °¢µµ¸¦ ¶óµð¾ÈÀ¸·Î ¸®ÅÏÇÏ±â ¶§¹®¿¡
				//<180.f / 3.14f À» °öÇÏ¿© °¢µµ·Î ¹Ù²ãÁÜ
				return theta*(180.f / 3.14f);
			}
			else
			{
				//<acos ( ºñÀ²·Î °¢µµ °¢µµ ±¸ÇÏ±â)
				theta = 2*3.14f - acosf(x_ / h_);
				//<acos ÇÔ¼ö´Â °¢µµ¸¦ ¶óµð¾ÈÀ¸·Î ¸®ÅÏÇÏ±â ¶§¹®¿¡
				//<180.f / 3.14f À» °öÇÏ¿© °¢µµ·Î ¹Ù²ãÁÜ
				return (theta*(180.f / 3.14f));
			}		
		}
	}//math

	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	// ¡Ù¦¬¦¡ 2015.04, Ãæµ¹°ü·Ã, Ackashic. ¦¡¦¬¡Ù
	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	namespace collision
	{
		//< Á¡ »ç°¢
		bool isColPtInRect( const POINT &pt , const RECT &rc )
		{
			//< 
			/*if( PtInRect( &rc,pt) == true )
			{
			return true;
			}*/

			if( rc.left < pt.x && pt.x < rc.right &&
				rc.top < pt.y && pt.y < rc.bottom )
			{
				return true;
			}
			return false;
		}
		//< »ç°¢ »ç°¢
		bool isColRectAndRect( const RECT &rc1, const RECT &rc2 )
		{
			if( rc1.left < rc2.right && rc2.left < rc1.right && 
				rc1.top < rc2.bottom && rc2.top < rc1.bottom )
			{
				return true;
			}

			return false;
		}
		//< ¿ø Á¡
		bool isColPtInCircle( const POINT &pt, const RECT &circle )
		{
			//< ¿øÀÇ ÁßÁ¡À» ±¸ÇÏ°í
			POINT	cirCenterPt;
			cirCenterPt.x = (circle.right + circle.left)/2;
			cirCenterPt.y = (circle.bottom + circle.top)/2;

			//< ¿øÀÇ ¹ÝÁö¸§ ±¸ÇÏ°í
			float	radius = static_cast<float>((circle.right - circle.left)/2);

			//< ¿øÀÇ ÁßÁ¡°ú ´Ù¸¥ÇÑÁ¡ÀÇ °Å¸®¸¦ ±¸ÇØ¼­
			float	distance = distancePtToPt( cirCenterPt, pt );
			//< ¹ÝÁö¸§º¸´Ù ÀÛ°Å³ª °°À¸¸é Ãæµ¹
			return distance < radius;
		}
		//< ¿ø ¿ø
		bool isColCirAndCir( const RECT &cir1, const RECT &cir2 )
		{
			//< c1 ÁßÁ¡°ú ¹ÝÁö¸§
			//< ¿øÀÇ ÁßÁ¡À» ±¸ÇÏ°í
			POINT	c1CenterPt;
			c1CenterPt.x = (cir1.right + cir1.left)/2;
			c1CenterPt.y = (cir1.bottom + cir1.top)/2;

			//< ¿øÀÇ ¹ÝÁö¸§ ±¸ÇÏ°í
			float	radius1 = static_cast<float>((cir1.right - cir1.left)/2);

			//< c2 ÁßÁ¡°ú ¹ÝÁö¸§
			POINT	c2CenterPt;

			c2CenterPt.x = (cir2.right + cir2.left)/2;
			c2CenterPt.y = (cir2.bottom + cir2.top)/2;

			//< ¿øÀÇ ¹ÝÁö¸§ ±¸ÇÏ°í
			float	radius2 = static_cast<float>((cir2.right - cir2.left)/2);


			//< c1ÁßÁ¡°ú c2ÁßÁ¡°úÀÇ °Å¸®¸¦ °è»ê
			//< ¿øÀÇ ÁßÁ¡°ú ´Ù¸¥ÇÑÁ¡ÀÇ °Å¸®¸¦ ±¸ÇØ¼­
			float	distance = distancePtToPt( c1CenterPt, c2CenterPt );
			//< µÎÁ¡»çÀÇ °Å¸®°¡ <= c1¹ÝÁö¸§ + c2¹ÝÁö¸§ : Ãæµ¹ 

			//< ¹ÝÁö¸§º¸´Ù ÀÛ°Å³ª °°À¸¸é Ãæµ¹
			return distance < (radius1 +radius2);
		}
		//< ¿ø »ç°¢
		bool isColCirAndRect( const RECT &cir, const RECT &rc )
		{
			//< »ç°¢Çü ¿øÀÇ(Á¡)
			POINT	cirPt;
			//< ¿øÀÇ ¼¾ÅÍÁ¡
			POINT	cirCenter;
			cirCenter.x = (cir.right+cir.left)/2;
			cirCenter.y = (cir.bottom+cir.top)/2;

			//< »ó(Cx,T)
			cirPt.x = cirCenter.x;
			cirPt.y = cir.top;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ÇÏ(Cx,B)
			cirPt.x = cirCenter.x;
			cirPt.y = cir.bottom;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ÁÂ(L,Cy)
			cirPt.x = cir.left;
			cirPt.y = cirCenter.y;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ¿ì
			cirPt.x = cir.right;
			cirPt.y = cirCenter.y;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ¿ø°ú »ç°¢Çü(Á¡)ÀÇ Ãæµ¹

			//< »ç°¢ÇüÀÇ °¢Á¡

			//< ÁÂ»ó
			cirPt.x = rc.left;
			cirPt.y = rc.top;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< ¿ì»ó
			cirPt.x = rc.right;
			cirPt.y = rc.top;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< ÁÂÇÏ
			cirPt.x = rc.left;
			cirPt.y = rc.bottom;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< ¿ìÇÏ
			cirPt.x = rc.right;
			cirPt.y = rc.bottom;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< Ãæµ¹¾øÀ½
			return false;
		}

		//¼±°ú ¿øÀÇ Ãæµ¹ Ã¼Å©
		bool isColLineAndCir( POINT &pos1, POINT &pos2, POINT &center , float r )
		{
			POINT vec = { pos2.x - pos1.x , pos2.y - pos1.y };

			float dx, dy;
			float t;
			float mx, my;

			float distance;

			dx = static_cast<float>(center.x - pos1.x);
			dy = static_cast<float>(center.y - pos1.y);

			t = ( vec.x * dx + vec.y * dy ) / ( vec.x * vec.x + vec.y * vec.y );

			if( t<0.0f ) t=0.0f;
			if( t>1.0f ) t=1.0f;

			mx = vec.x * t + pos1.x;
			my = vec.y * t + pos1.y;

			//°Å¸® ±¸ÇÏ±â
			distance = sqrtf( (mx-center.x) * (mx-center.x) + (my-center.y) * (my-center.y) );

			//°Å¸® Ã¼Å©
			if( distance < r )
			{
				return true;
			}
			return false;
		}
	}

	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	// ¡Ù¦¬¦¡ 2015.04, À©µµ¿ì °ü·Ã, Ackashic. ¦¡¦¬¡Ù
	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	namespace window
	{
		//< Æ÷Ä¿½º
		bool		isFocus;
		//< Å°°³¼ö
		const int KEYMAX = 256;

		//< Æ÷Ä¿½ºÃ³¸®
		void			setFocusMainWindow( bool focus )
		{
			isFocus = focus;
		}
		//< ¸ÞÀÎ À©µµ¿ìÆ÷Ä¿½ºÈ®ÀÎ
		bool			isFocusWindow( void )
		{
			return isFocus;
		}
	}

	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	// ¡Ù¦¬¦¡ 2015.04, Å°ÀÔ·Â °ü·Ã, Ackashic. ¦¡¦¬¡Ù
	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬

	namespace keyInput
	{
		//< Å°´Ù¿îÃ³¸®
		bool		keyDown[ KEYMAX ];
		//< ¾÷Ã³¸®¿ë
		bool		keyUp[ KEYMAX ];

		//< Å°¸ðµç ÇÃ·¡±× ÃÊ±âÈ­
		void		initKey( void )
		{	//< ´Ù¿îÅ°ÃÊ±âÈ­
			memset( keyDown , 0, sizeof( bool ) * KEYMAX );
			//< ¾÷Å°ÃÊ±âÈ­
			memset( keyUp , 0, sizeof( bool ) * KEYMAX );
		}

		//< Å°´­¸²Ã³¸®
		bool		isKeyDown( int keyValue )
		{
			//< Æ÷Ä¿½º°¡ ÀÖÀ» °æ¿ì¿¡¸¸ Ã³¸® 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					return true;
				}
			}

			return false;
		}

		//< ÇÃ·¡±×È®ÀÎ
		bool		isToggle( int keyValue )
		{
			//< Æ÷Ä¿½º°¡ ÀÖÀ» °æ¿ì¿¡¸¸ Ã³¸® 
			if( true == isFocusWindow() )
			{
				if( GetKeyState( keyValue ) & 0x8001 )
				{
					return true;
				}
			}

			return false;
		}
		//< Å° ÇÑ¹ø ´©¸§Ã³¸®
		bool		onceKeyDown( int keyValue )
		{
			//< Æ÷Ä¿½º°¡ ÀÖÀ» °æ¿ì¿¡¸¸ Ã³¸® 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					//< ÀÌÀüÅ°°¡ ´­¸®Áö ¾Ê¾ÒÀ»¶§¸¸ Ã³¸®
					if( false == keyDown[ keyValue ] )
					{
						keyDown[ keyValue ] = true;
						return true;
					}
				}
				else
				{	//< ÀÌÀüÇÃ·¡±× º¹±¸
					keyDown[ keyValue ] = false;	
				}
			}
			return false;	
		}
		//< Å° ÇÑ¹ø ¶«Ã³¸®
		bool		onceKeyUp( int keyValue )
		{
			//< Æ÷Ä¿½º°¡ ÀÖÀ» °æ¿ì¿¡¸¸ Ã³¸® 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					keyDown[ keyValue ] = true;
				}
				else
				{	
					if( true == keyDown[ keyValue ] )
					{
						//< ÀÌÀüÇÃ·¡±× º¹±¸
						keyDown[ keyValue ] = false;
						return true;
					}

				}
			}

			return false;
		}

		//////////////////////////////////////////////////////////////////////
		// ¸¶¿ì½º Ã³¸®
		//////////////////////////////////////////////////////////////////////
		//> ¸¶¿ì½º ÇöÀç »óÅÂ
		BYTE mouseCurState[MOUSE_BUTTON_END];
		//> ¸¶¿ì½º ÀÌÀü »óÅÂ
		BYTE mouseOldState[MOUSE_BUTTON_END];
		//> ¸¶¿ì½º °á°ú »óÅÂ
		BYTE mouseMapState[MOUSE_BUTTON_END];

		//> ¸¶¿ì½º À§Ä¡
		POINT mousePos;

		//> ¸¶¿ì½º À§Ä¡ ¼¼ÆÃ
		void setMousePos(POINT* _mousePos) 
		{
			mousePos = *_mousePos;
		}
		//> ¸¶¿ì½º À§Ä¡ ¾ò±â
		POINT getMousePos() 
		{
			return mousePos;
		}

		//> ÇØ´ç ¸¶¿ì½º ¹öÆ° ´Ù¿î È®ÀÎ
		bool isMouseDown(MOUSE_BUTTON mouseBtn) 
		{ 
			return mouseMapState[mouseBtn] == MOUSE_BTN_DOWN;
		}
		//> ÇØ´ç ¸¶¿ì½º ¹öÆ° ¾÷ È®ÀÎ
		bool isMouseUp(MOUSE_BUTTON mouseBtn) 
		{ 
			return mouseMapState[mouseBtn] == MOUSE_BTN_UP;
		}
		//> ÇØ´ç ¸¶¿ì½º ¹öÆ° ´­¸² È®ÀÎ
		bool isMousePress(MOUSE_BUTTON mouseBtn)
		{
			return mouseMapState[mouseBtn] == MOUSE_BTN_PRESS;
		}

		//> ¸¶¿ì½º ¾÷µ¥ÀÌÆ®
		void mouseUpdate()
		{

			//> ÇöÀç ¸¶¿ì½º Á¤º¸¸¦ ÀÌÀü ¸¶¿ì½º Á¤º¸¿¡ º¹»ç
			memcpy(mouseOldState, mouseCurState, sizeof(mouseOldState));

			//> ÇöÀç ¸¶¿ì½º Á¤º¸ ¹× °á°ú ¸¶¿ì½º Á¤º¸ ÃÊ±âÈ­
			memset(mouseCurState, 0, sizeof(mouseCurState));
			memset(mouseMapState, 0, sizeof(mouseMapState));

			//< Æ÷Ä¿½º°¡ ÀÖÀ» °æ¿ì¿¡¸¸ Ã³¸® 
			if( true == isFocusWindow() )
			{
				//> ÇöÀç ¸¶¿ì½ºÀÇ Á¤º¸¸¦ ¼³Á¤
				mouseCurState[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000)? 1: 0;	//> ÁÂ¹öÆ°
				mouseCurState[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000)? 1: 0;	//> ¿ì¹öÆ°
				mouseCurState[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000)? 1: 0;	//> Áß°£¹öÆ°

			}


			for(int i=0; i<MOUSE_BUTTON_END; i++)
			{
				if(0 == mouseOldState[i] && 1 == mouseCurState[i])
				{
					mouseMapState[i] = MOUSE_BTN_DOWN;	//> Å¬¸¯ ´Ù¿î
				}
				else if	(1 == mouseOldState[i] && 0 == mouseCurState[i])	
				{
					mouseMapState[i] = MOUSE_BTN_UP;		//> Å¬¸¯ ¾÷
				}
				else if	(1 == mouseOldState[i] && 1 == mouseCurState[i])
				{
					mouseMapState[i] = MOUSE_BTN_PRESS;	//> ´©¸£°í ÀÖ´ÂÁß
				}
			}

		}
	}//keyInput

}//< namespace end
