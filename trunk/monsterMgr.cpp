#include "stdafx.h"
#include "monsterMgr.h"
#include "UnitClass/mon_bug.h"
#include "UnitClass/Boss_gyuriel.h"
#include "UnitClass/Boss_naid.h"
//#include "character.h"

//< ĳ���Ͱ� �׾��� ��
static bool g_dieFlag = false;

MonsterMgr::MonsterMgr(void)
{
	init();
}

MonsterMgr::~MonsterMgr(void)
{
	release();
}

//< �ʱ�ȭ
bool MonsterMgr::init(void)
{
	m_renderList.clear();
	m_monsterList.clear();
	

	return true;
}

//< ����
void MonsterMgr::release(void)
{
	//< ������ ��ұ��� �ݺ�
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		//< Ȯ��
		if( NULL != m_monsterList[i] )
		{
			delete m_monsterList[i];
			m_monsterList[i]=NULL;
		}
	}
	//< ����
	releaseUnitList();
	m_monsterList.clear();
	g_dieFlag = false;
}

//< ����
void MonsterMgr::update(float fDeltaTime)
{
	/////////////////////////////////////////////////////////////////////
	//�ƴ�ĳ����
	if( NULL != m_otherPlayer )
	{
		//< ĳ���Ϳ� ������ �浹üũ
		collision( *m_otherPlayer );	
		//< ���� �ǰ� üũ
		beShotCheck( *m_otherPlayer );
		//< ���� ���� �ǰ� üũ
		beShotSkillCheck( *m_otherPlayer );
		//< ���� Ÿ�� üũ
		ShotCheck( *m_otherPlayer );
	}
	/////////////////////////////////////////////////////////////////////////////

	//< ĳ���Ϳ� ������ �浹üũ
	collision( *m_destPlayer );	
	//< ���� �ǰ� üũ
	beShotCheck( *m_destPlayer );
	//< ���� ���� �ǰ� üũ
	beShotSkillCheck( *m_destPlayer );
	//< ���� Ÿ�� üũ
	ShotCheck( *m_destPlayer );

	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{	
			if( NULL != m_otherPlayer )
			{
				if(  m_otherPlayer->getHP() > 0 )
				{
					//< ����� �÷��̾� ����
					POINT pos = m_monsterList[i]->getPos();
					if(math::distancePtToPt(pos, m_destPlayer->getPos())
						<= math::distancePtToPt(pos, m_otherPlayer->getPos()) )
					{
						//< �ν�
						m_monsterList[i]->recog(m_destPlayer->getPos());
						//< �̵�
						m_monsterList[i]->move(m_destPlayer->getPos());
						//< ����
						m_monsterList[i]->attack(m_destPlayer->getPos());
					}
					else
					{
						//< �ν�
						m_monsterList[i]->recog(m_otherPlayer->getPos());
						//< �̵�
						m_monsterList[i]->move(m_otherPlayer->getPos());
						//< ����
						m_monsterList[i]->attack(m_otherPlayer->getPos());
					}
				}
			}
			else 
			{
				if(  m_destPlayer->getHP() > 0 )
				{
				//< �ν�
				m_monsterList[i]->recog(m_destPlayer->getPos());
				//< �̵�
				m_monsterList[i]->move(m_destPlayer->getPos());
				//< ����
				m_monsterList[i]->attack(m_destPlayer->getPos());
				}
			}
			//< ������Ʈ
			m_monsterList[i]->update(fDeltaTime);
		}
	}
}

//< �׸���
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

//< ��� �÷��̾� ����
void MonsterMgr::setDestPlayer( character *player )
{
	//< ���Ḹ �ϰ� ������ �ۿ��� ó��
	m_destPlayer = player;
	addUnitList(player);
}

//< �ƴ� �÷��̾� ����
void MonsterMgr::setOtherPlayer( character *other )
{
	m_otherPlayer = other;
	addUnitList(other);
}

//< ���� �߰�
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
		//< 5�������� ���� ���� ����
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

//< ĳ���Ϳ� �浹üũ
bool MonsterMgr::collision( character &player )
{

	bool rtn = false;
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] )
		{
			//< �̵� & �浹 üũ
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
//< �ǰ� üũ
bool MonsterMgr::beShotCheck( character &player )
{
	//< ĳ���� ���� �浹ü�� ��Ȱ��ȭ ���¸� ����
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
				//< ���Ͱ� ����ִٸ� �˻�	
				if( m_monsterList[i]->getStateFlag() != STATE_DIE )
                {
                    unsigned int getExp = 0;
                    //���Ͱ� Ÿ�ݹ޾�����
                    if (true == m_monsterList[i]->beHit(player.getDamage()))
                    {
                        getExp = m_monsterList[i]->getExp();
                        //< ���Ͱ� �׾��ٸ� ����ġ ����
                        player.gainExp(getExp);
                        //< �� ĳ���͸� ���� ����
                        if (&player == m_destPlayer)
                        {
                            //GAME_DATA->addScore(10);
                        }
                    }

					player.setBallFlag( false );
					//< �Ѹ����� �ǰ� �ް� ����
					return true;
				}
			}
		}
	}
	return false;
}

//< ���� �ǰ� üũ
bool MonsterMgr::beShotSkillCheck( character &player )
{
	//< ĳ���� ���� �浹ü�� ��Ȱ��ȭ ���¸� ����
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
				//< ���Ͱ� ����ִٸ� �˻�
				if( m_monsterList[i]->getStateFlag() != STATE_DIE )
				{
					//���Ͱ� Ÿ�ݹ޾�����
					if( true == m_monsterList[i]->beHit(WHOLE_SKILL_DAMAGE) )
					{
						//< ���Ͱ� �׾��ٸ� ����ġ ����
						player.gainExp( m_monsterList[i]->getExp() );
						//< �� ĳ���͸� ���� ����
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

//< Ÿ�� üũ
bool MonsterMgr::ShotCheck( character &player )
{
	for( size_t i=0 ; i<m_monsterList.size() ; i++ )
	{
		if( NULL != m_monsterList[i] && true == m_monsterList[i]->getBallFlag() )
		{
			if( true == collision::isColCirAndRect( m_monsterList[i]->getBallRect(), player.getRect() ) )
			{
                // ĳ���Ͱ� Ÿ�ݹ޾�����
                int dmg = m_monsterList[i]->getDamage();
                m_monsterList[i]->setBallFlag(false);
                player.beHit(dmg);

                //< �ƴ��� �׾��� ��
                if (player.getHP() <= 0 && &player == m_otherPlayer)
                {
                    LOG_MGR->addLog("PLAYER DIE");
                }
				
				if(0 >= player.getHP() && g_dieFlag == false)
				{
					//< �÷��̾� �ڽŸ�
					if(&player == m_destPlayer)
					{
						g_dieFlag = true;
						//POPUP_MGR->getCheckPopup_ON();
						POPUP_MGR->changePopup( POPUP_GAME_OVER );
						//< �ʱ�ȭ
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

//< ���� ����Ʈ �߰�
void MonsterMgr::addUnitList( Unit *unit )
{
	LONG y = unit->getPos().y;
	m_renderList.insert( make_pair(y, unit));
}
//< ���� ����Ʈ ����
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

	//������ ��ұ��� �ݺ�
	for( ; iter != m_renderList.end(); ++iter )
	{
		//< Ȯ��
		Unit	*unit = iter->second;
		if( NULL != unit )
		{
			unit->render(hdc);
		}	
	}
}
//< ���� ����Ʈ ����
void MonsterMgr::releaseUnitList(void)
{
	m_renderList.clear();
}

//< ���� ����
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
