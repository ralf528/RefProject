#pragma once

#include "Singleton.h"
#include "monster.h"
#include "character.h"

class MonsterMgr
{
private:
	//< ���� ����Ʈ
	typedef std::vector< Monster* >		Vec_monList;
	//< ���� ����Ʈ �ݺ���
	typedef Vec_monList::iterator		monsterList_iter;

	//< ���� ���� ����Ʈ
	typedef std::multimap< LONG , Unit* >	unitRenderList;
	//< ���� ���� ����Ʈ
	typedef unitRenderList::iterator		renderList_iter;

	//< ĳ���� ����Ʈ
	//typedef std::map< char*, character* >	map_playerList;
	//< ĳ���� ����Ʈ �ݺ���
	//typedef map_playerList::iterator		playerList_iter;
	
private:
	MonsterMgr(void);
	~MonsterMgr(void);

	SINGLETON(MonsterMgr);

public:
	//< �ʱ�ȭ
	bool init(void);
	//< ����
	void release(void);
	//< ����
	void update(void);
	//< �׸���
	void render(HDC hdc);

	//< ��� �÷��̾� ����
	void setDestPlayer( character *player );
	//< �ƴ� �÷��̾� ����
	void setOtherPlayer( character *other );

	//< ���� �߰�
	void addMonster(Monster *mon);
	//< �浹üũ
	bool collision( character &player );
	//< �ǰ� üũ
	bool beShotCheck( character &player );
	//< ���� �ǰ� üũ
	bool beShotSkillCheck( character &player );
	//< Ÿ�� üũ
	bool ShotCheck( character &player );

	size_t getSize(void) { return m_monsterList.size(); }
	Monster* getMonster( int i ) { return m_monsterList[i]; }

	//< ���� ����
	void setBossMonster(Monster *boss) { m_boss = boss; }
	Monster* getBossMonster() { return m_boss; }

	//< ���� ����Ʈ �߰�
	void addUnitList( Unit *unit );
	//< ���� ����Ʈ ����
	void renderUnitList( HDC hdc );
	//< ���� ����Ʈ ����
	void releaseUnitList(void);
	//< ���� ����
	bool releaseCertain(Unit *unit);

private:
	//< ���� ����Ʈ
	Vec_monList			m_monsterList;
	//< �÷��̾� ����Ʈ
	//map_playerList		m_playerList;
	//< ���� �÷��̾�
	character *			m_destPlayer;
	//< �ƴ� �÷��̾�
	character *			m_otherPlayer;

	unitRenderList		m_renderList;
	renderList_iter		m_otherIter;

	//< ���� ����
	Monster *m_boss;
};

#define MON_MGR Singleton<MonsterMgr>::GetInstance()