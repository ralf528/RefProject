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
	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	// ≧收式 2015.04, 熱з婦溼, Ackashic. 式收≧
	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	namespace math
	{		
		//< 舒薄餌檜曖 剪葬 
		//pt1擎 晦遽薄(src), pt2朝 跡瞳渠鼻(dest)
		float		distancePtToPt( const POINT &pt1, const POINT &pt2 )
		{
			//< 陛煎 滲嬪榆
			float	width = static_cast<float>(pt2.x) - pt1.x;
			//< 撮煎 滲嬪榆
			float	height = static_cast<float>(pt2.y) - pt1.y;

			//< 綿滲曖 望檜(綿滲掘ж朝л熱)
			// float hypotenuse  = hypotf( static_cast<double>(width), static_cast<double>(height));

			//< 奩��
			// return static_cast<float>(hypotenuse);

			float hypotenuse  = sqrt( (width * width) + (height *height ) );

			return hypotenuse;
		}

		//< 薄 檜翕
		bool moveToPt(POINT *originPos, POINT *destPos, float speed )
		{
			float theta;

			float x_;
			float y_;
			float h_;

			x_ = static_cast<float>(destPos->x - originPos->x);	//<壽滲
			y_ = static_cast<float>(destPos->y - originPos->y);	//<堪檜
			h_ = sqrt((x_ * x_) + (y_ * y_));					//<綿滲

			if (0 == h_)			//綿滲檜 0檜賊 碟賅陛 0檜 腎嘎煎 謙猿
			{
				return false;
			}

			theta = acosf(x_ / h_);		//<acos ( 綠徽煎 陝紫 陝紫 掘ж晦)

			if (h_ <= 5.0f)	//<彰嬪陛 陛梱錶 雖賊 檜翕ж雖 彊紫煙..
			{
				return true;
			}
			else
			{				
				//<y 滲嬪榆檜 曄熱橾 唳辦
				if (y_ > 0)
				{
					//滲嬪榆 * 樓紫虜躑 檜翕
					originPos->x += static_cast<LONG>(cos(theta)*speed);
					originPos->y += static_cast<LONG>(sin(theta)*speed);
				}
				//<y 滲嬪榆檜 擠熱橾 唳辦
				else
				{
					//滲嬪榆 * 樓紫虜躑 檜翕
					originPos->x += static_cast<LONG>(cos(theta)*speed);
					originPos->y -= static_cast<LONG>(sin(theta)*speed);
				}
				return false;
			}
		}

		//< 陝紫 啗骯
		float calcAnglePtToPt(POINT *destPos, POINT *srcPos)
		{
			float x_;		
			float y_;		
			float h_;		
			float theta;	

			x_ = static_cast<float>(destPos->x - srcPos->x);	//<壽滲
			y_ = static_cast<float>(destPos->y - srcPos->y);	//<堪檜
			h_ = sqrt((x_ * x_) + (y_ * y_));					//<綿滲

			if (0 == h_)			//綿滲檜 0檜賊 碟賅陛 0檜 腎嘎煎 謙猿
			{
				return 0.f;
			}

			//if (y_ < 0)//等蘋腦お
			if (y_ > 0)//孺紫辦
			{
				//<陝紫
				theta = acosf(x_ / h_);
				//<acos л熱朝 陝紫蒂 塭蛤寰戲煎 葬欐ж晦 陽僥縑
				//<180.f / 3.14f 擊 培ж罹 陝紫煎 夥脯邀
				return theta*(180.f / 3.14f);
			}
			else
			{
				//<acos ( 綠徽煎 陝紫 陝紫 掘ж晦)
				theta = 2*3.14f - acosf(x_ / h_);
				//<acos л熱朝 陝紫蒂 塭蛤寰戲煎 葬欐ж晦 陽僥縑
				//<180.f / 3.14f 擊 培ж罹 陝紫煎 夥脯邀
				return (theta*(180.f / 3.14f));
			}		
		}
	}//math

	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	// ≧收式 2015.04, 醱給婦溼, Ackashic. 式收≧
	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	namespace collision
	{
		//< 薄 餌陝
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
		//< 餌陝 餌陝
		bool isColRectAndRect( const RECT &rc1, const RECT &rc2 )
		{
			if( rc1.left < rc2.right && rc2.left < rc1.right && 
				rc1.top < rc2.bottom && rc2.top < rc1.bottom )
			{
				return true;
			}

			return false;
		}
		//< 錳 薄
		bool isColPtInCircle( const POINT &pt, const RECT &circle )
		{
			//< 錳曖 醞薄擊 掘ж堅
			POINT	cirCenterPt;
			cirCenterPt.x = (circle.right + circle.left)/2;
			cirCenterPt.y = (circle.bottom + circle.top)/2;

			//< 錳曖 奩雖葷 掘ж堅
			float	radius = static_cast<float>((circle.right - circle.left)/2);

			//< 錳曖 醞薄婁 棻艇и薄曖 剪葬蒂 掘п憮
			float	distance = distancePtToPt( cirCenterPt, pt );
			//< 奩雖葷爾棻 濛剪釭 偽戲賊 醱給
			return distance < radius;
		}
		//< 錳 錳
		bool isColCirAndCir( const RECT &cir1, const RECT &cir2 )
		{
			//< c1 醞薄婁 奩雖葷
			//< 錳曖 醞薄擊 掘ж堅
			POINT	c1CenterPt;
			c1CenterPt.x = (cir1.right + cir1.left)/2;
			c1CenterPt.y = (cir1.bottom + cir1.top)/2;

			//< 錳曖 奩雖葷 掘ж堅
			float	radius1 = static_cast<float>((cir1.right - cir1.left)/2);

			//< c2 醞薄婁 奩雖葷
			POINT	c2CenterPt;

			c2CenterPt.x = (cir2.right + cir2.left)/2;
			c2CenterPt.y = (cir2.bottom + cir2.top)/2;

			//< 錳曖 奩雖葷 掘ж堅
			float	radius2 = static_cast<float>((cir2.right - cir2.left)/2);


			//< c1醞薄婁 c2醞薄婁曖 剪葬蒂 啗骯
			//< 錳曖 醞薄婁 棻艇и薄曖 剪葬蒂 掘п憮
			float	distance = distancePtToPt( c1CenterPt, c2CenterPt );
			//< 舒薄餌曖 剪葬陛 <= c1奩雖葷 + c2奩雖葷 : 醱給 

			//< 奩雖葷爾棻 濛剪釭 偽戲賊 醱給
			return distance < (radius1 +radius2);
		}
		//< 錳 餌陝
		bool isColCirAndRect( const RECT &cir, const RECT &rc )
		{
			//< 餌陝⑽ 錳曖(薄)
			POINT	cirPt;
			//< 錳曖 撫攪薄
			POINT	cirCenter;
			cirCenter.x = (cir.right+cir.left)/2;
			cirCenter.y = (cir.bottom+cir.top)/2;

			//< 鼻(Cx,T)
			cirPt.x = cirCenter.x;
			cirPt.y = cir.top;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ж(Cx,B)
			cirPt.x = cirCenter.x;
			cirPt.y = cir.bottom;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< 謝(L,Cy)
			cirPt.x = cir.left;
			cirPt.y = cirCenter.y;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< 辦
			cirPt.x = cir.right;
			cirPt.y = cirCenter.y;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< 錳婁 餌陝⑽(薄)曖 醱給

			//< 餌陝⑽曖 陝薄

			//< 謝鼻
			cirPt.x = rc.left;
			cirPt.y = rc.top;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< 辦鼻
			cirPt.x = rc.right;
			cirPt.y = rc.top;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< 謝ж
			cirPt.x = rc.left;
			cirPt.y = rc.bottom;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< 辦ж
			cirPt.x = rc.right;
			cirPt.y = rc.bottom;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< 醱給橈擠
			return false;
		}

		//摹婁 錳曖 醱給 羹觼
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

			//剪葬 掘ж晦
			distance = sqrtf( (mx-center.x) * (mx-center.x) + (my-center.y) * (my-center.y) );

			//剪葬 羹觼
			if( distance < r )
			{
				return true;
			}
			return false;
		}
	}

	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	// ≧收式 2015.04, 孺紫辦 婦溼, Ackashic. 式收≧
	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	namespace window
	{
		//< ん醴蝶
		bool		isFocus;

		//< ん醴蝶籀葬
		void			setFocusMainWindow( bool focus )
		{
			isFocus = focus;
		}
		//< 詭檣 孺紫辦ん醴蝶�挫�
		bool			isFocusWindow( void )
		{
			return isFocus;
		}
	}

	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	// ≧收式 2015.04, 酈殮溘 婦溼, Ackashic. 式收≧
	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收

	namespace keyInput
	{
		//< 酈偃熱
		const int KEYMAX = 256;
		//< 酈棻遴籀葬
		bool		keyDown[ KEYMAX ];
		//< 機籀葬辨
		bool		keyUp[ KEYMAX ];

		//< 酈賅萇 Ы楚斜 蟾晦��
		void		initKey( void )
		{	//< 棻遴酈蟾晦��
			memset( keyDown , 0, sizeof( bool ) * KEYMAX );
			//< 機酈蟾晦��
			memset( keyUp , 0, sizeof( bool ) * KEYMAX );
		}

		//< 酈揚葡籀葬
		bool		isKeyDown( int keyValue )
		{
			//< ん醴蝶陛 氈擊 唳辦縑虜 籀葬 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					return true;
				}
			}

			return false;
		}

		//< Ы楚斜�挫�
		bool		isToggle( int keyValue )
		{
			//< ん醴蝶陛 氈擊 唳辦縑虜 籀葬 
			if( true == isFocusWindow() )
			{
				if( GetKeyState( keyValue ) & 0x8001 )
				{
					return true;
				}
			}

			return false;
		}
		//< 酈 и廓 援葷籀葬
		bool		onceKeyDown( int keyValue )
		{
			//< ん醴蝶陛 氈擊 唳辦縑虜 籀葬 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					//< 檜瞪酈陛 揚葬雖 彊懊擊陽虜 籀葬
					if( false == keyDown[ keyValue ] )
					{
						keyDown[ keyValue ] = true;
						return true;
					}
				}
				else
				{	//< 檜瞪Ы楚斜 犒掘
					keyDown[ keyValue ] = false;	
				}
			}
			return false;	
		}
		//< 酈 и廓 陲籀葬
		bool		onceKeyUp( int keyValue )
		{
			//< ん醴蝶陛 氈擊 唳辦縑虜 籀葬 
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
						//< 檜瞪Ы楚斜 犒掘
						keyDown[ keyValue ] = false;
						return true;
					}

				}
			}

			return false;
		}
	}//keyInput

	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	// ≧收式 2015.04, FPS 顫檜該, Ackashic. 式收≧
	//收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收
	namespace FpsTime
	{
		Timer	m_pTimer;		//< 衛除 婦葬 偌羹

		//< 蟾晦��
		void initFpsTime(void)
		{
			m_pTimer.init();
		}
		//< п薯
		void releaseFpsTime(void)
		{
		}

		//< Щ煎斜極 衛濛 �� �篞秣� 瞪羹 衛除 橢晦
		float getWorldTime(void)
		{
			return m_pTimer.getWorldTime();
		}
		//< Щ溯歜渡 唳婁衛除( и Щ溯歜 )
		float getElapsedTime(void)
		{
			return m_pTimer.getElapsedTime();
		}
		//< Щ溯歜 顫歜 機等檜お( 晦獄 FPS 60 )
		void fpsTimeUpdate( float fLock )
		{
			m_pTimer.tick( fLock );
		}
		//< Щ溯歜 溶渦葭 ж晦
		void renderFps( HDC hdc, unsigned long textColor )
		{
			char szBuf[_MAX_FNAME];
			//std::string strFrame;

			//⑷營 儀鼻
			DWORD dwCurColor = GetTextColor( hdc );
			//滲唳 儀鼻
			SetBkMode( hdc, TRANSPARENT );
			SetTextColor( hdc, textColor );

            //Щ溯歜
            sprintf_s(szBuf, "FramePerSec : %d", m_pTimer.getFrameRate());
            TextOut(hdc, 0, 60, szBuf, strlen(szBuf));
            //錯萄 顫歜
            sprintf_s(szBuf, "WorldTime : %f", m_pTimer.getWorldTime());
            TextOut(hdc, 0, 80, szBuf, strlen(szBuf));
            //Щ溯歜渡 唳婁 衛除
            sprintf_s(szBuf, "ElapseTime : %f", m_pTimer.getElapsedTime());
            TextOut(hdc, 0, 100, szBuf, strlen(szBuf));
            //翕晦�� 綠徽
            sprintf_s(szBuf, "TimeRate : %f", m_pTimer.getTimeRate());
            TextOut(hdc, 0, 120, szBuf, strlen(szBuf));
			
			SetBkMode( hdc, OPAQUE );
			SetTextColor( hdc, dwCurColor );
		}
		//< 衛除 翕晦�� 滲熱
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
			//< 檜嘐雖 餌檜鍔
            SIZE idleAniSize; //RC_MGR->findImage(imgID)->getSize();
            idleAniSize.cx = 0;
            idleAniSize.cy = 0;
			//< Щ溯歜 熱
			aniInfo->frameCntX = cx;
			aniInfo->frameCntY = cy;
			//< Щ溯歜渡 檜嘐雖 餌檜鍔
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
