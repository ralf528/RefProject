#pragma once

#include "Singleton.h"
#include "monster.h"
#include "character.h"

class MonsterMgr
{
private:
	//< 몬스터 리스트
	typedef std::vector< Monster* >		Vec_monList;
	//< 몬스터 리스트 반복자
	typedef Vec_monList::iterator		monsterList_iter;

	//< 유닛 랜더 리스트
	typedef std::multimap< LONG , Unit* >	unitRenderList;
	//< 유닛 랜더 리스트
	typedef unitRenderList::iterator		renderList_iter;

	//< 캐릭터 리스트
	//typedef std::map< char*, character* >	map_playerList;
	//< 캐릭터 리스트 반복자
	//typedef map_playerList::iterator		playerList_iter;
	
private:
	MonsterMgr(void);
	~MonsterMgr(void);

	SINGLETON(MonsterMgr);

public:
	//< 초기화
	bool init(void);
	//< 해제
	void release(void);
	//< 갱신
	void update(void);
	//< 그리기
	void render(HDC hdc);

	//< 대상 플레이어 연결
	void setDestPlayer( character *player );
	//< 아더 플레이어 연결
	void setOtherPlayer( character *other );

	//< 몬스터 추가
	void addMonster(Monster *mon);
	//< 충돌체크
	bool collision( character &player );
	//< 피격 체크
	bool beShotCheck( character &player );
	//< 마법 피격 체크
	bool beShotSkillCheck( character &player );
	//< 타격 체크
	bool ShotCheck( character &player );

	size_t getSize(void) { return m_monsterList.size(); }
	Monster* getMonster( int i ) { return m_monsterList[i]; }

	//< 보스 몬스터
	void setBossMonster(Monster *boss) { m_boss = boss; }
	Monster* getBossMonster() { return m_boss; }

	//< 유닛 리스트 추가
	void addUnitList( Unit *unit );
	//< 유닛 리스트 랜더
	void renderUnitList( HDC hdc );
	//< 유닛 리스트 해제
	void releaseUnitList(void);
	//< 유닛 해제
	bool releaseCertain(Unit *unit);

private:
	//< 몬스터 리스트
	Vec_monList			m_monsterList;
	//< 플레이어 리스트
	//map_playerList		m_playerList;
	//< 현재 플레이어
	character *			m_destPlayer;
	//< 아더 플레이어
	character *			m_otherPlayer;

	unitRenderList		m_renderList;
	renderList_iter		m_otherIter;

	//< 보스 몬스터
	Monster *m_boss;
};

#define MON_MGR Singleton<MonsterMgr>::GetInstance()