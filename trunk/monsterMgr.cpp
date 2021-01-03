#include "stdafx.h"
#include "monsterMgr.h"
#include "UnitClass/mon_bug.h"
#include "UnitClass/Boss_gyuriel.h"
#include "UnitClass/Boss_naid.h"
//#include "character.h"

//< 캐릭터가 죽었을 때
static bool g_dieFlag = false;

MonsterMgr::MonsterMgr(void)
{
	init();
}

MonsterMgr::~MonsterMgr(void)
{
	release();
}

//< 초기화
bool MonsterMgr::init(void)
{
	m_renderList.clear();
	m_monsterList.clear();
	

	return true;
}

//< 해제
void MonsterMgr::release(void)
{
	//< 마지막 요소까지 반복
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		//< 확인
		if( NULL != m_monsterList[i] )
		{
			delete m_monsterList[i];
			m_monsterList[i]=NULL;
		}
	}
	//< 정리
	releaseUnitList();
	m_monsterList.clear();
	g_dieFlag = false;
}

//< 갱신
void MonsterMgr::update(float fDeltaTime)
{
	/////////////////////////////////////////////////////////////////////
	//아더캐릭터
	if( NULL != m_otherPlayer )
	{
		//< 캐릭터와 몬스터의 충돌체크
		collision( *m_otherPlayer );	
		//< 몬스터 피격 체크
		beShotCheck( *m_otherPlayer );
		//< 몬스터 마법 피격 체크
		beShotSkillCheck( *m_otherPlayer );
		//< 몬스터 타격 체크
		ShotCheck( *m_otherPlayer );
	}
	/////////////////////////////////////////////////////////////////////////////

	//< 캐릭터와 몬스터의 충돌체크
	collision( *m_destPlayer );	
	//< 몬스터 피격 체크
	beShotCheck( *m_destPlayer );
	//< 몬스터 마법 피격 체크
	beShotSkillCheck( *m_destPlayer );
	//< 몬스터 타격 체크
	ShotCheck( *m_destPlayer );

	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{	
			if( NULL != m_otherPlayer )
			{
				if(  m_otherPlayer->getHP() > 0 )
				{
					//< 가까운 플레이어 공격
					POINT pos = m_monsterList[i]->getPos();
					if(math::distancePtToPt(pos, m_destPlayer->getPos())
						<= math::distancePtToPt(pos, m_otherPlayer->getPos()) )
					{
						//< 인식
						m_monsterList[i]->recog(m_destPlayer->getPos());
						//< 이동
						m_monsterList[i]->move(m_destPlayer->getPos());
						//< 공격
						m_monsterList[i]->attack(m_destPlayer->getPos());
					}
					else
					{
						//< 인식
						m_monsterList[i]->recog(m_otherPlayer->getPos());
						//< 이동
						m_monsterList[i]->move(m_otherPlayer->getPos());
						//< 공격
						m_monsterList[i]->attack(m_otherPlayer->getPos());
					}
				}
			}
			else 
			{
				if(  m_destPlayer->getHP() > 0 )
				{
				//< 인식
				m_monsterList[i]->recog(m_destPlayer->getPos());
				//< 이동
				m_monsterList[i]->move(m_destPlayer->getPos());
				//< 공격
				m_monsterList[i]->attack(m_destPlayer->getPos());
				}
			}
			//< 업데이트
			m_monsterList[i]->update(fDeltaTime);
		}
	}
}

//< 그리기
void MonsterMgr::render(HDC hdc)
{
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{
			m_monsterList[i]->render(hdc);
		}
	}
}

//< 대상 플레이어 연결
void MonsterMgr::setDestPlayer( character *player )
{
	//< 연결만 하고 해제는 밖에서 처리
	m_destPlayer = player;
	addUnitList(player);
}

//< 아더 플레이어 연결
void MonsterMgr::setOtherPlayer( character *other )
{
	m_otherPlayer = other;
	addUnitList(other);
}

//< 몬스터 추가
void MonsterMgr::CreateMonster(tileType type, int x, int y)
{
	Monster *mon = nullptr;

	switch (type)
	{
	case TILE_MON_01:
		mon = new mon_bug();// boss_naid;
		break;
	case TILE_MON_02:
		mon = new mon_bug();//mon_bug;
		break;
	case TILE_MON_03:
		mon = new mon_bug();//ghoul;
		break;
	case TILE_MON_04:
		mon = new mon_bug();//Dark_spider;
		break;
	case TILE_MON_05:
		mon = new mon_bug();//Ghost;
		break;
	case TILE_MON_06:
		mon = new mon_bug();//Human_thief;
		break;
	case TILE_MON_07:
		mon = new mon_bug;
		break;
	case TILE_MON_08:
		//< 5층에서만 보스 몬스터 생성
		//if (m_nowFloor % 5 == 0)
		{
			mon = new Gyuriel;
			MON_MGR->setBossMonster(mon);
		}
		break;
	}

	if (mon != nullptr)
	{
		mon->setPos(x, y);
		addMonster(mon);
	}
}

void MonsterMgr::addMonster(Monster *mon)
{
	m_monsterList.push_back( mon );
	addUnitList(mon);
}

//< 캐릭터와 충돌체크
bool MonsterMgr::collision( character &player )
{

	bool rtn = false;
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{
			//< 이동 & 충돌 체크
			if( true == m_monsterList[i]->collision(player.getPos() ) )
			{
				m_monsterList[i]->setPosToPrev();
				player.setPosToPrev();
				rtn = true;
			}
		}
	}


	return rtn;
}
//< 피격 체크
bool MonsterMgr::beShotCheck( character &player )
{
	//< 캐릭터 공격 충돌체가 비활성화 상태면 종료
	if( false == player.getBallFlag() )
	{
		return false;
	}

	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{
			if( true == collision::isColCirAndRect( m_monsterList[i]->getRect(), player.getBallRect() ) )
			{
				//< 몬스터가 살아있다면 검사	
				if( m_monsterList[i]->getStateFlag() != STATE_DIE )
                {
                    unsigned int getExp = 0;
                    //몬스터가 타격받았을떄
                    if (true == m_monsterList[i]->beHit(player.getDamage()))
                    {
                        getExp = m_monsterList[i]->getExp();
                        //< 몬스터가 죽었다면 경험치 증가
                        player.gainExp(getExp);
                        //< 내 캐릭터만 점수 증가
                        if (&player == m_destPlayer)
                        {
                            //GAME_DATA->addScore(10);
                        }
                    }

					player.setBallFlag( false );
					//< 한마리만 피격 받고 종료
					return true;
				}
			}
		}
	}
	return false;
}

//< 마법 피격 체크
bool MonsterMgr::beShotSkillCheck( character &player )
{
	//< 캐릭터 공격 충돌체가 비활성화 상태면 종료
	if( false == player.getSkillBallFlag() )
	{
		return false;
	}
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{
			if( true == collision::isColCirAndRect( m_monsterList[i]->getRect(), player.getSkillRect() ) )
			{
				//< 몬스터가 살아있다면 검사
				if( m_monsterList[i]->getStateFlag() != STATE_DIE )
				{
					//몬스터가 타격받았을떄
					if( true == m_monsterList[i]->beHit(WHOLE_SKILL_DAMAGE) )
					{
						//< 몬스터가 죽었다면 경험치 증가
						player.gainExp( m_monsterList[i]->getExp() );
						//< 내 캐릭터만 점수 증가
						if( &player == m_destPlayer )
						{
							//GAME_DATA->addScore(10);
						}
					}
				}
			}
		}
	}

	return false;
}

//< 타격 체크
bool MonsterMgr::ShotCheck( character &player )
{
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] && true == m_monsterList[i]->getBallFlag() )
		{
			if( true == collision::isColCirAndRect( m_monsterList[i]->getBallRect(), player.getRect() ) )
			{
                // 캐릭터가 타격받았을떄
                int dmg = m_monsterList[i]->getDamage();
                m_monsterList[i]->setBallFlag(false);
                player.beHit(dmg);

                //< 아더가 죽었을 때
                if (player.getHP() <= 0 && &player == m_otherPlayer)
                {
                    LOG_MGR->addLog("PLAYER DIE");
                }
				
				if(0 >= player.getHP() && g_dieFlag == false)
				{
					//< 플레이어 자신만
					if(&player == m_destPlayer)
					{
						g_dieFlag = true;
						//POPUP_MGR->getCheckPopup_ON();
						POPUP_MGR->changePopup( POPUP_GAME_OVER );
						//< 초기화
						//POPUP_MGR->initPopup();
					}
				}
			}
		}
	}
	return false;
}

Monster* MonsterMgr::GetNearMonster(POINT pos)
{
    Monster* result = nullptr;

    for (auto each : m_monsterList)
    {
        if (result == nullptr)
        {
            result = each;
            continue;
        }

        int x = each->getPos().x - pos.x;
        int y = each->getPos().y - pos.y;

        double dist = sqrt((x * x) + (y * y));
    }

    return result;
}

//< 유닛 리스트 추가
void MonsterMgr::addUnitList( Unit *unit )
{
	LONG y = unit->getPos().y;
	m_renderList.insert( make_pair(y, unit));
}
//< 유닛 리스트 랜더
void MonsterMgr::renderUnitList( HDC hdc )
{
	releaseUnitList();
	for(size_t i = 0 ; i < m_monsterList.size() ; i++ )
	{
		addUnitList(m_monsterList[i]);
	}
	if( m_destPlayer != NULL )
	{
		addUnitList(m_destPlayer);
	}	
	if( m_otherPlayer != NULL )
	{
		addUnitList(m_otherPlayer);
	}
	renderList_iter	iter = m_renderList.begin();

	//마지막 요소까지 반복
	for( ; iter != m_renderList.end(); ++iter )
	{
		//< 확인
		Unit	*unit = iter->second;
		if( NULL != unit )
		{
			unit->render(hdc);
		}	
	}
}
//< 유닛 리스트 해제
void MonsterMgr::releaseUnitList(void)
{
	m_renderList.clear();
}

//< 유닛 해제
bool MonsterMgr::releaseCertain(Unit *unit)
{
	for(renderList_iter iter = m_renderList.begin() ; iter != m_renderList.end() ; ++iter)
	{
		Unit *eraseIter = iter->second;
		if(unit == eraseIter)
		{
			//m_renderList.erase(iter);
			m_otherPlayer = NULL;
			return true;
		}

	}
	return false;
}
