#pragma once

#include "Object.h"

class ImageNode : public Object
{
public:
	ImageNode( void );
	ImageNode( unsigned int id );
	virtual ~ImageNode(void);

	//< �ε�
	unsigned int load( const TCHAR *imagePath , int cx = 0, int cy = 0 , BYTE mode = RM_NORMAL );
	//< RC�ε�
	unsigned int load( const int resourceID , BYTE mode = RM_NORMAL );
	//< ���̹��������(�ش� ũ��� ���̹��� ����� )����Ʈ�� ������� ĥ�Ѵ�.
	unsigned int load( int cx , int cy, BYTE mode = RM_NORMAL  );

	//< ����
	void		render( HDC hdc, int x , int y );
	void		render( HDC hdc, int x , int y, int destCX , int destCY, 
						int scrX , int srcY , int srcCX, int srcCY );
	//< ���ĺ���
	void		renderAlpha( HDC hdc, int x , int y, BYTE alpha = 150 );

	//< ũ������� ����
	void renderSize( HDC hdc, int x, int y, int width, int height );

	//< ����
	void		release( void );

	//< �ܺο��� MEMDC���
	inline HDC	getMemDC( void )	{ return m_memDC;	}
	//< ��������
	inline SIZE getSize( void )		{ return m_size;	}

	//< ���������� DC�ʱ�ȭ�ϱ�
	void			clearDC( DWORD color );

private:
	//< �ʱ�ȭ
	void		init( void );
	//< ��������
	bool		setImageInfo( void );

private:
	//< �޸�DC
	HDC			m_memDC;
	//< ��Ʈ���ڵ�
	HBITMAP		m_bit,m_obit;
	//< ���μ��λ�����
	SIZE		m_size;
	//< ���
	TCHAR		m_path[ _MAX_FNAME ];
	//< �̹��� ���� ���
	BYTE		m_renderMode;
	//< �÷�Ű
	DWORD		m_colorKey;
	//< ���� �ε� Ÿ��
	BYTE		m_fileloadType;
};

