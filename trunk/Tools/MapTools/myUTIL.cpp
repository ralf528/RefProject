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
	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, ���а���, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace math
	{		
		//< ���������� �Ÿ� 
		//pt1�� ������(src), pt2�� �������(dest)
		float		distancePtToPt( const POINT &pt1, const POINT &pt2 )
		{
			//< ���� ������
			float	width = static_cast<float>(pt2.x) - pt1.x;
			//< ���� ������
			float	height = static_cast<float>(pt2.y) - pt1.y;

			//< ������ ����(�������ϴ��Լ�)
			// float hypotenuse  = hypotf( static_cast<double>(width), static_cast<double>(height));

			//< ��ȯ
			// return static_cast<float>(hypotenuse);

			float hypotenuse  = sqrt( (width * width) + (height *height ) );

			return hypotenuse;
		}

		//< �� �̵�
		void moveToPt(POINT *originPos, POINT *destPos, float speed )
		{
			float theta;

			float x_;
			float y_;
			float h_;

			x_ = static_cast<float>(destPos->x - originPos->x);	//<�غ�
			y_ = static_cast<float>(destPos->y - originPos->y);	//<����
			h_ = sqrt((x_ * x_) + (y_ * y_));					//<����

			if (0 == h_)			//������ 0�̸� �и� 0�� �ǹǷ� ����
			{
				return;
			}

			theta = acosf(x_ / h_);		//<acos ( ������ ���� ���� ���ϱ�)

			if (h_ > 5.0f)	//<������ ����� ���� �̵����� �ʵ���..
			{
				//<y �������� ����� ���
				if (y_ > 0)
				{
					//������ * �ӵ���ŭ �̵�
					originPos->x += static_cast<LONG>(cos(theta)*speed);
					originPos->y += static_cast<LONG>(sin(theta)*speed);
				}
				//<y �������� ������ ���
				else
				{
					//������ * �ӵ���ŭ �̵�
					originPos->x += static_cast<LONG>(cos(theta)*speed);
					originPos->y -= static_cast<LONG>(sin(theta)*speed);
				}
			}
		}

		//< ���� ���
		float calcAnglePtToPt(POINT *destPos, POINT *srcPos)
		{
			float x_;		
			float y_;		
			float h_;		
			float theta;	

			x_ = static_cast<float>(destPos->x - srcPos->x);	//<�غ�
			y_ = static_cast<float>(destPos->y - srcPos->y);	//<����
			h_ = sqrt((x_ * x_) + (y_ * y_));					//<����

			if (0 == h_)			//������ 0�̸� �и� 0�� �ǹǷ� ����
			{
				return 0.f;
			}

			//if (y_ < 0)//��ī��Ʈ
			if (y_ > 0)//������
			{
				//<����
				theta = acosf(x_ / h_);
				//<acos �Լ��� ������ �������� �����ϱ� ������
				//<180.f / 3.14f �� ���Ͽ� ������ �ٲ���
				return theta*(180.f / 3.14f);
			}
			else
			{
				//<acos ( ������ ���� ���� ���ϱ�)
				theta = 2*3.14f - acosf(x_ / h_);
				//<acos �Լ��� ������ �������� �����ϱ� ������
				//<180.f / 3.14f �� ���Ͽ� ������ �ٲ���
				return (theta*(180.f / 3.14f));
			}		
		}
	}//math

	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, �浹����, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace collision
	{
		//< �� �簢
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
		//< �簢 �簢
		bool isColRectAndRect( const RECT &rc1, const RECT &rc2 )
		{
			if( rc1.left < rc2.right && rc2.left < rc1.right && 
				rc1.top < rc2.bottom && rc2.top < rc1.bottom )
			{
				return true;
			}

			return false;
		}
		//< �� ��
		bool isColPtInCircle( const POINT &pt, const RECT &circle )
		{
			//< ���� ������ ���ϰ�
			POINT	cirCenterPt;
			cirCenterPt.x = (circle.right + circle.left)/2;
			cirCenterPt.y = (circle.bottom + circle.top)/2;

			//< ���� ������ ���ϰ�
			float	radius = static_cast<float>((circle.right - circle.left)/2);

			//< ���� ������ �ٸ������� �Ÿ��� ���ؼ�
			float	distance = distancePtToPt( cirCenterPt, pt );
			//< ���������� �۰ų� ������ �浹
			return distance < radius;
		}
		//< �� ��
		bool isColCirAndCir( const RECT &cir1, const RECT &cir2 )
		{
			//< c1 ������ ������
			//< ���� ������ ���ϰ�
			POINT	c1CenterPt;
			c1CenterPt.x = (cir1.right + cir1.left)/2;
			c1CenterPt.y = (cir1.bottom + cir1.top)/2;

			//< ���� ������ ���ϰ�
			float	radius1 = static_cast<float>((cir1.right - cir1.left)/2);

			//< c2 ������ ������
			POINT	c2CenterPt;

			c2CenterPt.x = (cir2.right + cir2.left)/2;
			c2CenterPt.y = (cir2.bottom + cir2.top)/2;

			//< ���� ������ ���ϰ�
			float	radius2 = static_cast<float>((cir2.right - cir2.left)/2);


			//< c1������ c2�������� �Ÿ��� ���
			//< ���� ������ �ٸ������� �Ÿ��� ���ؼ�
			float	distance = distancePtToPt( c1CenterPt, c2CenterPt );
			//< �������� �Ÿ��� <= c1������ + c2������ : �浹 

			//< ���������� �۰ų� ������ �浹
			return distance < (radius1 +radius2);
		}
		//< �� �簢
		bool isColCirAndRect( const RECT &cir, const RECT &rc )
		{
			//< �簢�� ����(��)
			POINT	cirPt;
			//< ���� ������
			POINT	cirCenter;
			cirCenter.x = (cir.right+cir.left)/2;
			cirCenter.y = (cir.bottom+cir.top)/2;

			//< ��(Cx,T)
			cirPt.x = cirCenter.x;
			cirPt.y = cir.top;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ��(Cx,B)
			cirPt.x = cirCenter.x;
			cirPt.y = cir.bottom;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ��(L,Cy)
			cirPt.x = cir.left;
			cirPt.y = cirCenter.y;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ��
			cirPt.x = cir.right;
			cirPt.y = cirCenter.y;

			if( isColPtInRect( cirPt,rc ) == true ) 
			{
				return true;
			}

			//< ���� �簢��(��)�� �浹

			//< �簢���� ����

			//< �»�
			cirPt.x = rc.left;
			cirPt.y = rc.top;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< ���
			cirPt.x = rc.right;
			cirPt.y = rc.top;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< ����
			cirPt.x = rc.left;
			cirPt.y = rc.bottom;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< ����
			cirPt.x = rc.right;
			cirPt.y = rc.bottom;

			if( isColPtInCircle( cirPt, cir ) == true ) 
			{
				return true;
			}

			//< �浹����
			return false;
		}

		//���� ���� �浹 üũ
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

			//�Ÿ� ���ϱ�
			distance = sqrtf( (mx-center.x) * (mx-center.x) + (my-center.y) * (my-center.y) );

			//�Ÿ� üũ
			if( distance < r )
			{
				return true;
			}
			return false;
		}
	}

	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, ������ ����, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace window
	{
		//< ��Ŀ��
		bool		isFocus;
		//< Ű����
		const int KEYMAX = 256;

		//< ��Ŀ��ó��
		void			setFocusMainWindow( bool focus )
		{
			isFocus = focus;
		}
		//< ���� ��������Ŀ��Ȯ��
		bool			isFocusWindow( void )
		{
			return isFocus;
		}
	}

	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, Ű�Է� ����, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������

	namespace keyInput
	{
		//< Ű�ٿ�ó��
		bool		keyDown[ KEYMAX ];
		//< ��ó����
		bool		keyUp[ KEYMAX ];

		//< Ű��� �÷��� �ʱ�ȭ
		void		initKey( void )
		{	//< �ٿ�Ű�ʱ�ȭ
			memset( keyDown , 0, sizeof( bool ) * KEYMAX );
			//< ��Ű�ʱ�ȭ
			memset( keyUp , 0, sizeof( bool ) * KEYMAX );
		}

		//< Ű����ó��
		bool		isKeyDown( int keyValue )
		{
			//< ��Ŀ���� ���� ��쿡�� ó�� 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					return true;
				}
			}

			return false;
		}

		//< �÷���Ȯ��
		bool		isToggle( int keyValue )
		{
			//< ��Ŀ���� ���� ��쿡�� ó�� 
			if( true == isFocusWindow() )
			{
				if( GetKeyState( keyValue ) & 0x8001 )
				{
					return true;
				}
			}

			return false;
		}
		//< Ű �ѹ� ����ó��
		bool		onceKeyDown( int keyValue )
		{
			//< ��Ŀ���� ���� ��쿡�� ó�� 
			if( true == isFocusWindow() )
			{
				if( GetAsyncKeyState( keyValue ) & 0x8000 )
				{
					//< ����Ű�� ������ �ʾ������� ó��
					if( false == keyDown[ keyValue ] )
					{
						keyDown[ keyValue ] = true;
						return true;
					}
				}
				else
				{	//< �����÷��� ����
					keyDown[ keyValue ] = false;	
				}
			}
			return false;	
		}
		//< Ű �ѹ� ��ó��
		bool		onceKeyUp( int keyValue )
		{
			//< ��Ŀ���� ���� ��쿡�� ó�� 
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
						//< �����÷��� ����
						keyDown[ keyValue ] = false;
						return true;
					}

				}
			}

			return false;
		}

		//////////////////////////////////////////////////////////////////////
		// ���콺 ó��
		//////////////////////////////////////////////////////////////////////
		//> ���콺 ���� ����
		BYTE mouseCurState[MOUSE_BUTTON_END];
		//> ���콺 ���� ����
		BYTE mouseOldState[MOUSE_BUTTON_END];
		//> ���콺 ��� ����
		BYTE mouseMapState[MOUSE_BUTTON_END];

		//> ���콺 ��ġ
		POINT mousePos;

		//> ���콺 ��ġ ����
		void setMousePos(POINT* _mousePos) 
		{
			mousePos = *_mousePos;
		}
		//> ���콺 ��ġ ���
		POINT getMousePos() 
		{
			return mousePos;
		}

		//> �ش� ���콺 ��ư �ٿ� Ȯ��
		bool isMouseDown(MOUSE_BUTTON mouseBtn) 
		{ 
			return mouseMapState[mouseBtn] == MOUSE_BTN_DOWN;
		}
		//> �ش� ���콺 ��ư �� Ȯ��
		bool isMouseUp(MOUSE_BUTTON mouseBtn) 
		{ 
			return mouseMapState[mouseBtn] == MOUSE_BTN_UP;
		}
		//> �ش� ���콺 ��ư ���� Ȯ��
		bool isMousePress(MOUSE_BUTTON mouseBtn)
		{
			return mouseMapState[mouseBtn] == MOUSE_BTN_PRESS;
		}

		//> ���콺 ������Ʈ
		void mouseUpdate()
		{

			//> ���� ���콺 ������ ���� ���콺 ������ ����
			memcpy(mouseOldState, mouseCurState, sizeof(mouseOldState));

			//> ���� ���콺 ���� �� ��� ���콺 ���� �ʱ�ȭ
			memset(mouseCurState, 0, sizeof(mouseCurState));
			memset(mouseMapState, 0, sizeof(mouseMapState));

			//< ��Ŀ���� ���� ��쿡�� ó�� 
			if( true == isFocusWindow() )
			{
				//> ���� ���콺�� ������ ����
				mouseCurState[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000)? 1: 0;	//> �¹�ư
				mouseCurState[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000)? 1: 0;	//> ���ư
				mouseCurState[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000)? 1: 0;	//> �߰���ư

			}


			for(int i=0; i<MOUSE_BUTTON_END; i++)
			{
				if(0 == mouseOldState[i] && 1 == mouseCurState[i])
				{
					mouseMapState[i] = MOUSE_BTN_DOWN;	//> Ŭ�� �ٿ�
				}
				else if	(1 == mouseOldState[i] && 0 == mouseCurState[i])	
				{
					mouseMapState[i] = MOUSE_BTN_UP;		//> Ŭ�� ��
				}
				else if	(1 == mouseOldState[i] && 1 == mouseCurState[i])
				{
					mouseMapState[i] = MOUSE_BTN_PRESS;	//> ������ �ִ���
				}
			}

		}
	}//keyInput

}//< namespace end
