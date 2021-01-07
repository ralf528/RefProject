#pragma once

#include "Singleton.h"

//< °ÔÀÓ¾À »óÅÂ
enum
{
	SCENE_LOGIN,
	SCENE_TITLE,
	SCENE_LOBBY,
	SCENE_SELECT,
	SCENE_PLAYGAME,
	SCENE_RANK,	
};

class State;

//< »óÅÂ(¾À)¸Þ´ÏÀú
class StateMgr
{
private:
	//¾À ¸®½ºÆ® ¸Ê
	typedef std::map< unsigned int, State* >			StateList;
	//¾À ¸®½ºÆ® ¹Ýº¹ÀÚ
	typedef std::map< unsigned int, State* >::iterator	StateListIter;

private:
	StateMgr(void);
	~StateMgr(void);
	//½Ì±ÛÅæ
	SINGLETON( StateMgr );

public:
	//<¾À Ãß°¡
	template<typename T>
	bool	addState( unsigned int StateID )
	{
		//<¾À Ã£±â
		StateListIter iter = findState( StateID );
		//<³¡±îÁö ¸øÃ£¾Ò´Ù¸é
		if( iter == m_stateList.end() )
		{
			State *pState = new T;
			//<¾À Ãß°¡
			insertState( StateID, pState );
			return true;
		}
		//<¾ÀÀÌ ÀÖ´Ù¸é false¸®ÅÏ
		return false;
	}

	//< ¾À ¾÷µ«
	void updateState( void );
	//< ·£´õ ¾À
	void renderState( HDC hdc );
	//< ¾À ¹Ù²Ù±â
	bool changeState( unsigned int StateID );
	//< ¾À Áö¿ì±â
	void deleteState( const unsigned int StateID );
	//< ÀÌº¥Æ® Ã³¸®
	virtual LRESULT StateProc( HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam );

private :

	//< »ðÀÔ
	void insertState( unsigned int StateID , State*	pState );
	//< Ã£±â( ÀÌÅÍ )
	StateListIter findState( unsigned int StateID );
	//< Ã£±â( ¾À )
	State* findStatePtr( unsigned int StateID );
	//< ¸ðµÎ Áö¿ì±â
	void deleteStateAll( void );

private :
	//< ÇöÀç ¾À
	State *m_State;
	//< ¾À ÀúÀå ¸®½ºÆ®
	StateList m_stateList;	
};

#define STATE_MGR Singleton<StateMgr>::getInstance()