#pragma once

#include "Scene.h"

//��Ʈ �Ŵ���
class MY_FontMgr;
//�̹��� ���
class ImageNode;
//< ��
class tileMap;

class ScenePlayGame : public Scene
{
public:
	ScenePlayGame(void);
	virtual ~ScenePlayGame(void);

public :
	//< �ʱ�ȭ
	virtual bool init( void ) ;
	//< ������Ʈ
	virtual void update( void ) ;
	//< ����
	virtual void render( HDC hdc ) ;
	//< ����
	virtual void release( void ) ;

	//< �̺�Ʈó��
	virtual LRESULT	StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :
	//< ���������� ����
	bool m_playingGame;

	//Ÿ�ϸ� ����
	tileMap *m_map;
};