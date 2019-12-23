#include "stdafx.h"
#include "monsterMgr.h"
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

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////	//< ���� ��Ʈ��ũ ��ġ ����
	//if(true == HOST_SERVER->getHostis() && HOST_SERVER->getIsConnector())
	//{
	//	static DWORD flag = GetTickCount();
	//	if(GetTickCount() - flag >= 2000)
	//	{
	//		LOG_MGR->addLog("[HOST][SEND]");
	//		LOG_MGR->addLog("P2P_MON_POS_UPDATE");
	//		PACKET packet;
	//		memset(&packet, -1, sizeof(P2P_MONSTERUPDATE_EX));
	//		packet.m_monserUpdateEx.m_length = sizeof(P2P_MONSTERUPDATE_EX);
	//		packet.m_monserUpdateEx.m_type = P2P_MON_POS_UPDATE;
	//		packet.m_monserUpdateEx.size = MON_MGR->getSize();

	//		for(int i=0, j=0; i<(packet.m_monserUpdateEx.size) ; i++)
	//		{
	//			//packet.m_monserUpdate.pos[i] = MON_MGR->getMonster(i)->getPos();
	//			//packet.m_monserUpdate.state[i] = MON_MGR->getMonster(i)->getStateFlag();

	//			packet.m_monserUpdateEx.state[j] = MON_MGR->getMonster(i)->getStateFlag();
	//			//< �������� ���� ���ʹ� ���� ����
	//			if(packet.m_monserUpdateEx.state[j] == STATE_IDLE
	//				|| packet.m_monserUpdateEx.state[j] == STATE_DIE)
	//			{
	//				continue;
	//			}
	//			//< ���� ���� �� �ִ�
	//			if(40 == i)
	//			{
	//				break;
	//			}

	//			packet.m_monserUpdateEx.monsterIndex[j] = i;
	//			packet.m_monserUpdateEx.pos[j] = MON_MGR->getMonster(i)->getPos();
	//			LOG_MGR->addLog("���� %d��", i);
	//			j++;
	//		}
	//		HOST_SERVER->sendOtherPlayer((char*)&packet, packet.m_monster.m_length);

	//		flag = GetTickCount();
	//	}
	//}
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
void MonsterMgr::addMonster(Monster *mon)
{
	m_monsterList.push_back( mon );
	addUnitList(mon);
	//< ȣ��Ʈ���
	//if(true == HOST_SERVER->getHostis())
	//{
	//	//< ���� ���� ������
	//	LOG_MGR->addLog("[HOST][SEND]");
	//	LOG_MGR->addLog("P2P_MON_POS_INIT");
	//	PACKET packet;
	//	packet.m_monster.m_length = sizeof(P2P_MONSTER);
	//	packet.m_monster.m_type = P2P_MON_POS_INIT;
	//	packet.m_monster.pos = mon->getPos();
	//	packet.m_monster.kind = mon->getMonsterKind();

	//	HOST_SERVER->sendOtherPlayer((char*)&packet, packet.m_monster.m_length);
	//}
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
					//< ȣ��Ʈ�� ��쿡
					//if(true == HOST_SERVER->getHostis())
					//{						
					//	unsigned int getExp = 0;
					//	//���Ͱ� Ÿ�ݹ޾�����
  			//			if( true == m_monsterList[i]->beHit(player.getDamage()) )
					//	{
					//		getExp = m_monsterList[i]->getExp();
					//		//< ���Ͱ� �׾��ٸ� ����ġ ����
					//		player.gainExp( getExp );
					//		//< �� ĳ���͸� ���� ����
					//		if( &player == m_destPlayer )
					//		{
					//			GAME_DATA->addScore(10);
					//		}
					//	}

					//	//< ����
					//	PACKET packet;
					//	packet.m_monsterDie.m_length = sizeof(P2P_MONSTERDIE);
					//	packet.m_monsterDie.m_type = P2P_MON_DEAD;
					//	packet.m_monsterDie.m_index = player.getConnectionIndex();
					//	packet.m_monsterDie.exp = getExp;
					//	packet.m_monsterDie.pos = m_monsterList[i]->getPos();
					//	packet.m_monsterDie.monsterIndex = i;
					//	packet.m_monsterDie.dmg = player.getDamage();

					//	HOST_SERVER->sendOtherPlayer((char*)&packet, packet.m_monsterDie.m_length);
					//}

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
				//< ȣ��Ʈ������ 
				//if(true == HOST_SERVER->getHostis())
				//{
				//	//�ɸ��Ͱ� Ÿ�ݹ޾�����
				//	int dmg = m_monsterList[i]->getDamage();
				//	m_monsterList[i]->setBallFlag(false);
				//	player.beHit( dmg );

				//	//< �ƴ��� �׾��� ��
				//	if(player.getHP() <= 0 && &player == m_otherPlayer)
				//	{
				//		LOG_MGR->addLog("PLAYER DIE");
				//		PACKET packet;
				//		packet.m_basicMsg.m_length = sizeof(BASIC_MSG);
				//		packet.m_basicMsg.m_type = P2P_ASYNC_HP_0;

				//		HOST_SERVER->sendCertainPlayer((char*)&packet, packet.m_basicMsg.m_length, player.getConnectionIndex());
				//	}
				//	
				//	if(true == HOST_SERVER->getIsConnector())
				//	{
				//		LOG_MGR->addLog("[HOST][SEND]");
				//		LOG_MGR->addLog("P2P_MON_ATTACK_UPDATE");

				//		//< ����
				//		PACKET packet;
				//		packet.m_charHit.m_length = sizeof(P2P_CHARHIT);
				//		packet.m_charHit.m_type = P2P_MON_ATTACK_UPDATE;
				//		packet.m_charHit.m_index = player.getConnectionIndex();
				//		packet.m_charHit.dmg = dmg;
				//		packet.m_charHit.pos = player.getPos();

				//		HOST_SERVER->sendOtherPlayer((char*)&packet, packet.m_charHit.m_length);
				//	}
				//}
				
				if(0 >= player.getHP() && g_dieFlag == false)
				{
					//< �÷��̾� �ڽŸ�
					//if(&player == m_destPlayer)
					//{
					//	g_dieFlag = true;
					//	//POPUP_MGR->getCheckPopup_ON();
					//	POPUP_MGR->changePopup( POPUP_GAME_OVER );
					//	//< �ʱ�ȭ
					//	//POPUP_MGR->initPopup();

					//	if(HOST_SERVER->getHostis() == true)
					//	{
					//		PACKET packet;
					//		packet.m_rankInsert.m_length = sizeof(RANK_INSERT);
					//		packet.m_rankInsert.m_type = CS_INSERT_RANKING;
					//		packet.m_rankInsert.m_rankInfo.m_floor = GAME_DATA->GetNowFloor();
					//		packet.m_rankInsert.m_rankInfo.m_job = 1;
					//		strcpy_s(packet.m_rankInsert.m_rankInfo.m_nickName, GAME_DATA->getUserId());
					//		packet.m_rankInsert.m_rankInfo.m_score = GAME_DATA->getScore();
					//		packet.m_rankInsert.m_rankInfo.m_tribe = 1;
					//		TCPIP_CLIENT->sendPacket(packet);
					//	}
					//	else
					//	{
					//		//> ȣ��Ʈ���� �����ٰ� �˸�
					//		PACKET packet;
					//		packet.m_deadExit.m_length = sizeof(P2P_DEADEXIT);
					//		packet.m_deadExit.m_type = P2P_DEAD_EXIT;
					//		packet.m_deadExit.m_index = player.getConnectionIndex();
					//		TCPIP_CLIENT->sendPacket(packet);
					//	}
					//}

				}
			}
		}
	}
	return false;
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
