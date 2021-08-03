#include "stdafx.h"
#include "inventory.h"

Inventory::Inventory(void)
{
	init();
}
Inventory::~Inventory(void)
{
	release();
}


//<�ʱ�ȭ
bool Inventory::init(void)
{
	//< ������ �̹��� �߰�
	RC_MGR->addImage( imgID_POTION_1 , L"Data/Resource/item/Potion_Confusion.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_2 , L"Data/Resource/item/Potion_Cure.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_3 , L"Data/Resource/item/Potion_Identify.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_4 , L"Data/Resource/item/Potion_Regen.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_5 , L"Data/Resource/item/Potion_Unknown.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_6 , L"Data/Resource/item/Potion_Venom.bmp", 0, 0, RM_TRANS );
	
	//< ������ �̹��� �߰�
	RC_MGR->addImage( imgID_INVEN_POTION_1 , L"Data/Resource/Image/Interface/item_01.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_2 , L"Data/Resource/Image/Interface/item_02.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_3 , L"Data/Resource/Image/Interface/item_03.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_4 , L"Data/Resource/Image/Interface/item_04.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_5 , L"Data/Resource/Image/Interface/item_05.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_6 , L"Data/Resource/Image/Interface/item_06.bmp", 40, 40, RM_TRANS );

	//< ������ ��ư
	for (int i = 0; i < 4; i++)
	{
		m_m_button_Item[i].init( 
			L"Data/Resource/Image/Interface/no_item.bmp",
			L"Data/Resource/Image/Interface/no_item.bmp",
			L"Data/Resource/Image/Interface/no_item.bmp",
			40,40 );
		m_m_button_Item[i].setRectPos( 920 +((40*i)+(10*i)),WINSIZE_Y-50, ALIGN_LEFT_TOP );
	}

	//< ����Ʈ �ʱ�ȭ
	m_itemList.clear();

	return false;
}

//<����
void Inventory::release(void)
{
	m_itemList.clear();
}

//<�κ��丮 ����
void Inventory::renderInven(HDC hdc)
{
	//< ������ ��ư
	for (int i = 0; i < 4; i++)
	{
		m_m_button_Item[i].render( hdc );
	}

	item_iter iter = m_itemList.begin();

	int count =0;
	int x = 0, y = 0;
	for (; iter != m_itemList.end(); ++iter)
	{
		if (count < 4)
		{
			unsigned int id = (*iter) - ITEM_FIRST + imgID_INVEN_POTION_1;
			RENDER_MGR->render(hdc, id, 920 + ((40 * count) + (10 * count)), WINSIZE_Y - 50);
			count++;
		}

		//< ĭ �̵� (5ĭ�� ����)
		if (++x >= 4)
		{
			x = 0;
			y++;
		}
	}
}

//<������ ����
bool Inventory::addItem(unsigned int item)
{
	m_itemList.push_back( item );
	LOG_MGR->addLog( "������ ȹ�� : %d" , item );

	return true;
}

//< ������ ����
int Inventory::RemoveItem(unsigned int index)
{
	//< �ش� �ε����� ������ ���� �� ����
	item_iter iter = m_itemList.begin();
	for (size_t i = 1; i < index; i++, ++iter)
	{

	}

	//< ���ϰ� ����
	unsigned int rtn = *iter;
	m_itemList.erase(iter);
	return rtn;
}

//<������ ���
unsigned int Inventory::useItem(character* OwnerCharacter, unsigned int index)
{
	if (OwnerCharacter == nullptr)
	{
		return ITEM_END;
	}

	//< ������ ������ ����
	if (index > m_itemList.size())
	{
		return ITEM_END;
	}

	//< �ش� �ε����� ������ ID
	unsigned int itemID = RemoveItem(index);
	
	// item type �� ���� ��� ȿ�� �ο�

	//<ȥ���̸� ���� �ߵ�
	if (ITEM_POTION_VENOM == itemID)
	{
		itemID = ITEM_FIRST + rand() % (ITEM_END - ITEM_FIRST);
	}

	switch (itemID)
	{
	case ITEM_POTION_CONFUSION:	//< ȥ��
		//< �����̻�
		//m_state.m_condition = CONDITION_NORMAL;
		break;
	case ITEM_POSION_CURE:	//< ���
		//< ü�� ����
		//MODULE_MGR->AddSkillModule()
		OwnerCharacter->incHP(50);
		break;
	//case ITEM_POTION_IDENTFY:	//< ��
	//	m_state.m_condition = CONDITION_POISON;
	//	m_conDeley.m_deley = 6000;
	//	m_conDeley.m_lastTime = GetTickCount();
	//	break;
	//case ITEM_POTION_REGEN: //< ��ȭ
	//	m_state.m_str -= 3;
	//	if (getStrong() < 0) m_state.m_str = 1;
	//	m_state.m_agl -= 3;
	//	if (getAgility() < 0) m_state.m_agl = 1;
	//	m_state.m_int -= 3;
	//	if (getIntel() < 0) m_state.m_int = 1;
	//	break;
	case ITEM_POTION_UNKNOWN: //< ��ȭ
		/*OwnerCharacter->m_state.m_str += 3;
		OwnerCharacter->m_state.m_agl += 3;
		OwnerCharacter->m_state.m_int += 3;*/
		break;
	}

	//SOUND_MGR->soundPlay(SOUND_BGM9);

	return itemID;
}