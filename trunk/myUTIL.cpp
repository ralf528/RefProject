#include "stdafx.h"
#include <cmath>
#include "Timer.h"
#include "myUTIL.h"

using namespace myUTIL;
using namespace math;
using namespace collision;
using namespace window;
using namespace keyInput;
using namespace animation;

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
		bool moveToPt(POINT *originPos, POINT *destPos, float speed )
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
				return false;
			}

			theta = acosf(x_ / h_);		//<acos ( ºñÀ²·Î °¢µµ °¢µµ ±¸ÇÏ±â)

			if (h_ <= 5.0f)	//<¹üÀ§°¡ °¡±î¿ö Áö¸é ÀÌµ¿ÇÏÁö ¾Êµµ·Ï..
			{
				return true;
			}
			else
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
				return false;
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
		//< Å°°³¼ö
		const int KEYMAX = 256;
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
	}//keyInput

	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	// ¡Ù¦¬¦¡ 2015.04, FPS Å¸ÀÌ¸Ó, Ackashic. ¦¡¦¬¡Ù
	//¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬
	namespace FpsTime
	{
		Timer	m_pTimer;		//< ½Ã°£ °ü¸® °´Ã¼

		//< ÃÊ±âÈ­
		void initFpsTime(void)
		{
			//Å¸ÀÌ¸Ó »ý¼º
			//m_pTimer = new JN_Timer;
			//Å¸ÀÌ¸Ó ÃÊ±âÈ­
			m_pTimer.init();
		}
		//< ÇØÁ¦
		void releaseFpsTime(void)
		{
			/*if( NULL != m_pTimer )
			{
			delete m_pTimer;
			m_pTimer=NULL;
			}*/
		}

		//< ÇÁ·Î±×·¥ ½ÃÀÛ ÈÄ Èê·¯°£ ÀüÃ¼ ½Ã°£ ¾ò±â
		float getWorldTime(void)
		{
			return m_pTimer.getWorldTime();
		}
		//< ÇÁ·¹ÀÓ´ç °æ°ú½Ã°£( ÇÑ ÇÁ·¹ÀÓ )
		float getElapsedTime(void)
		{
			return m_pTimer.getElapsedTime();
		}
		//< ÇÁ·¹ÀÓ Å¸ÀÓ ¾÷µ¥ÀÌÆ®( ±âº» FPS 60 )
		void fpsTimeUpdate( float fLock )
		{
			/*if( NULL == m_pTimer )
			{
			return;
			}*/
			m_pTimer.tick( fLock );
		}
		//< ÇÁ·¹ÀÓ ·»´õ¸µ ÇÏ±â
		void renderFps( HDC hdc, unsigned long textColor )
		{
			char szBuf[_MAX_FNAME];
			//std::string strFrame;

			//ÇöÀç »ö»ó
			DWORD dwCurColor = GetTextColor( hdc );
			//º¯°æ »ö»ó
			SetBkMode( hdc, TRANSPARENT );
			SetTextColor( hdc, textColor );

            //ÇÁ·¹ÀÓ
            sprintf_s(szBuf, "FramePerSec : %d", m_pTimer.getFrameRate());
            TextOut(hdc, 0, 0, szBuf, strlen(szBuf));
            //¿ùµå Å¸ÀÓ
            sprintf_s(szBuf, "WorldTime : %f", m_pTimer.getWorldTime());
            TextOut(hdc, 0, 20, szBuf, strlen(szBuf));
            //ÇÁ·¹ÀÓ´ç °æ°ú ½Ã°£
            sprintf_s(szBuf, "ElapseTime : %f", m_pTimer.getElapsedTime());
            TextOut(hdc, 0, 40, szBuf, strlen(szBuf));
            //µ¿±âÈ­ ºñÀ²
            sprintf_s(szBuf, "TimeRate : %f", m_pTimer.getTimeRate());
            TextOut(hdc, 0, 60, szBuf, strlen(szBuf));
			
			SetBkMode( hdc, OPAQUE );
			SetTextColor( hdc, dwCurColor );
		}
		//< ½Ã°£ µ¿±âÈ­ º¯¼ö
		float getTimeRate( void )
		{
			return m_pTimer.getTimeRate();
		}
	};

	namespace Animation
	{
		void setAniInfo( unsigned int imgID, LPANI_INFO aniInfo, bool startFlag, bool loop, bool playContinue, int cx, int cy, int aniSpeed )
		{
			SAFE_DELETE( aniInfo );
			aniInfo = new ANI_INFO;
			//< ÀÌ¹ÌÁö »çÀÌÁî
            SIZE idleAniSize; //RC_MGR->findImage(imgID)->getSize();
            idleAniSize.cx = 0;
            idleAniSize.cy = 0;
			//< ÇÁ·¹ÀÓ ¼ö
			aniInfo->frameCntX = cx;
			aniInfo->frameCntY = cy;
			//< ÇÁ·¹ÀÓ´ç ÀÌ¹ÌÁö »çÀÌÁî
			aniInfo->aniSize.cx = idleAniSize.cx / aniInfo->frameCntX;
			aniInfo->aniSize.cy = idleAniSize.cy / aniInfo->frameCntY;

			aniInfo->frameSpeed = aniSpeed;
			aniInfo->nowFrame = 0;
			aniInfo->nowFrameY = 0;
			aniInfo->lastTime = GetTickCount();
			aniInfo->flag=startFlag;
			aniInfo->loop=loop;
			aniInfo->playAni=playContinue;
		}

		void updateAni( LPANI_INFO info )
		{
			if(NULL!=info && true == info->flag)
			{
				DWORD curTime = GetTickCount();

				if( info->lastTime + info->frameSpeed <= curTime )
				{
					info->nowFrame++;

					info->lastTime=curTime;

					if(info->frameCntX <= info->nowFrame)
					{
						if( info->playAni == false )
						{
							info->nowFrame=info->frameCntX-1;
							info->flag=false;
							return;
						}
						info->nowFrame=0;
						if( info->loop == false )
						{
							info->flag=false;
						}
					}
				}
			}
		}
	}
}//< namespace end
