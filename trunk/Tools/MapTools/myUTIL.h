#pragma once
/*
	������Ʈ�� �������� ���Ǵ� �Լ�
*/

enum MOUSE_STATE
{
	MOUSE_BTN_NONE,
	MOUSE_BTN_DOWN,
	MOUSE_BTN_UP,
	MOUSE_BTN_PRESS,
	MOUSE_END,
};

enum MOUSE_BUTTON
{
	MOUSE_LBUTTON,
	MOUSE_RBUTTON,
	MOUSE_MBUTTON,
	MOUSE_BUTTON_END,
};

namespace myUTIL
{
	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, ���а���, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace math
	{		
		//< ���������� �Ÿ�
		float	distancePtToPt( const POINT &pt1, const POINT &pt2 );
		//< �� �̵�
		void	moveToPt(POINT *originPos, POINT *destPos,float speed = 3.f);
		//< ���� ���
		float	calcAnglePtToPt(POINT *destPos, POINT *srcPos);
	}//math
	    
	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, �浹����, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace collision
	{
		//< �� �簢
		bool	 isColPtInRect( const POINT &pt , const RECT &rc );
		//< �簢 �簢
		bool	 isColRectAndRect( const RECT &rc1, const RECT &rc2 );
		//< �� ��
		bool	 isColPtInCircle( const POINT &pt, const RECT &circle );
		//< �� ��
		bool	 isColCirAndCir( const RECT &cir1, const RECT &cir2 );
		//< �� �簢
		bool	 isColCirAndRect( const RECT &cir, const RECT &rc );
		//���� ���� �浹 üũ
		bool	isColLineAndCir( POINT &pos1, POINT &pos2, POINT &center , float r );
	}//collision

	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, ������ ����, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace window
	{
		//< ��Ŀ��ó��
		void			setFocusMainWindow( bool focus );
		//< ���� ��������Ŀ��Ȯ��
		bool			isFocusWindow( void );
	}//window
	
	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, Ű�Է� ����, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace keyInput
	{
		//< Ű��� �÷��� �ʱ�ȭ
		void		initKey( void );
		//< Ű����ó��
		bool		isKeyDown( int keyValue );
		//< �÷���Ȯ��
		bool		isToggle( int keyValue );
		//< Ű �ѹ� ����ó��
		bool		onceKeyDown( int keyValue );
		//< Ű �ѹ� ��ó��
		bool		onceKeyUp( int keyValue );

		//////////////////////////////////////////////////////////////////////
		// ���콺
		//////////////////////////////////////////////////////////////////////
		//> ���콺 ������Ʈ
		void mouseUpdate();

		//> ���콺 ���� ���
		bool getMouseState(const int mouseState);

		//> ���콺 ��ġ ����
		void setMousePos(POINT* mousePos);
		//> ���콺 ��ġ ���
		POINT getMousePos();

		//> �ش� ���콺 ��ư �ٿ� Ȯ��
		bool isMouseDown(MOUSE_BUTTON mouseBtn);
		//> �ش� ���콺 ��ư �� Ȯ��
		bool isMouseUp(MOUSE_BUTTON mouseBtn);
		//> �ش� ���콺 ��ư ���� Ȯ��
		bool isMousePress(MOUSE_BUTTON mouseBtn);
	}//keyInput
	
}//< namespace end