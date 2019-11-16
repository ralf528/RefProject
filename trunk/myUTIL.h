#pragma once
/*
	������Ʈ�� �������� ���Ǵ� �Լ�
*/
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
		bool	moveToPt(POINT *originPos, POINT *destPos,float speed = 3.f);
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
	}//keyInput
	
	//��������������������������������������������������������������������������������������������������������������
	// �٦��� 2015.04, FPS Ÿ�̸�, Ackashic. ������
	//��������������������������������������������������������������������������������������������������������������
	namespace FpsTime
	{
		//< �ʱ�ȭ
		void initFpsTime(void);
		//< ����
		void releaseFpsTime(void);
		//< ���α׷� ���� �� �귯�� ��ü �ð� ���
		float getWorldTime(void);
		//< �����Ӵ� ����ð�( �� ������ )
		float getElapsedTime(void);
		//< ������ Ÿ�� ������Ʈ( �⺻ FPS 60 )
		void fpsTimeUpdate( float fLock = 60.0f );
		//< ������ ������ �ϱ�
		void renderFps( HDC hdc, unsigned long textColor = RGB(0,0,0) );
		//< �ð� ����ȭ ����
		float getTimeRate( void );
	};

	namespace animation
	{
		//�ִϸ��̼� ����
		void setAniInfo( unsigned int imgID, LPANI_INFO aniInfo, bool startFlag, bool loop, bool playContinue, int cx, int cy = 1, int aniSpeed = 50);
		//����
		void updateAni( LPANI_INFO aniInfo );
	}

}//< namespace end