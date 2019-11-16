#pragma once

//< �̹��� ��� ���漱�� 
class ImageNode;

class RenderMgr
{
private:
	RenderMgr(void);
	~RenderMgr(void);
	//< �̱���
	SINGLETON( RenderMgr );
public:
	//< �ʱ�ȭ
	void			init( void );
	
	//< ������
	//< �׳� ����
	void			render( HDC hdc , const unsigned int UID, int x, int y );
	//< �������� ����
	void			render( HDC hdc, const unsigned int UID, 
							int x , int y, int destWidth, int destHieght, 
							int srcX, int srcY, int srcWidth, int srcHeight,
							BYTE alphaValue = 0);

	//< ȭ�鿡 ���� ��� ( hdc �ʿ� ���� )
	void			renderFrame( void );
	//< ����� �ʱ�ȭ
	void			clearBack( int brush = WHITE_BRUSH );
	//< ����
	void			release( void );

	//< ����DC���
	HDC				getMainDC( void );
	//< ��DC���
	HDC				getBackDC( void );	
	
//< �������
private:
	//< ���� DC
	HDC				m_mainDC;
	//< �� ���� �̹���
	ImageNode		*m_imgBack;
	// ������ ��Ʈ(������ ����� ����, update ȣ�� )
	RECT			m_winRect;
};

#define RENDER_MGR Singleton<RenderMgr>::GetInstance()
