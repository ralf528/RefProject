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


//<초기화
bool Inventory::init(void)
{
	//< 아이템 이미지 추가
	RC_MGR->addImage( imgID_POTION_1 , L"Data/Resource/item/Potion_Confusion.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_2 , L"Data/Resource/item/Potion_Cure.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_3 , L"Data/Resource/item/Potion_Identify.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_4 , L"Data/Resource/item/Potion_Regen.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_5 , L"Data/Resource/item/Potion_Unknown.bmp", 0, 0, RM_TRANS );
	RC_MGR->addImage( imgID_POTION_6 , L"Data/Resource/item/Potion_Venom.bmp", 0, 0, RM_TRANS );
	
	//< 아이템 이미지 추가
	RC_MGR->addImage( imgID_INVEN_POTION_1 , L"Data/Resource/Image/Interface/item_01.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_2 , L"Data/Resource/Image/Interface/item_02.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_3 , L"Data/Resource/Image/Interface/item_03.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_4 , L"Data/Resource/Image/Interface/item_04.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_5 , L"Data/Resource/Image/Interface/item_05.bmp", 40, 40, RM_TRANS );
	RC_MGR->addImage( imgID_INVEN_POTION_6 , L"Data/Resource/Image/Interface/item_06.bmp", 40, 40, RM_TRANS );

	//< 아이템 버튼
	for (int i = 0; i < 4; i++)
	{
		m_m_button_Item[i].init( 
			L"Data/Resource/Image/Interface/no_item.bmp",
			L"Data/Resource/Image/Interface/no_item.bmp",
			L"Data/Resource/Image/Interface/no_item.bmp",
			40,40 );
		m_m_button_Item[i].setRectPos( 920 +((40*i)+(10*i)),WINSIZE_Y-50, ALIGN_LEFT_TOP );
	}

	//< 리스트 초기화
	m_itemList.clear();

	return false;
}

//<삭제
void Inventory::release(void)
{
	m_itemList.clear();
}

//<인벤토리 랜더
void Inventory::renderInven(HDC hdc)
{
	//< 아이템 버튼
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

		//< 칸 이동 (5칸씩 랜더)
		if (++x >= 4)
		{
			x = 0;
			y++;
		}
	}
}

//<아이템 보관
bool Inventory::addItem(unsigned int item)
{
	m_itemList.push_back( item );
	LOG_MGR->addLog( "아이템 획득 : %d" , item );
	return true;
}

//<아이템 사용
unsigned int Inventory::useItem(unsigned int index)
{
	//< 아이템 없으면 리턴
	if( index > m_itemList.size() )
	{
		return ITEM_END;
	}

	//< 해당 인덱스의 아이템 삭제 후 리턴
	item_iter iter = m_itemList.begin();
	for( size_t i = 1 ; i<index ; i++,++iter )
	{

	}

	//< 리턴값 저장
	unsigned int rtn = *iter;
	m_itemList.erase( iter );
	return rtn;
}