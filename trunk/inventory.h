#pragma once

#include "Singleton.h"
#include "ButtonClass.h"

class character;

class Inventory
{
	typedef std::list<unsigned int>		itemList;
	typedef itemList::iterator			item_iter;
public:
	Inventory(void);
	~Inventory(void);

public:
	bool init(void);
	void release(void);
	void renderInven(HDC hdc);
	
	bool addItem(unsigned int item);
	int RemoveItem(unsigned int index);

	//<아이템 사용
	unsigned int useItem(character* OwnerCharacter, unsigned int index);


private:
	//< 아이템 리스트
	itemList m_itemList;

	//< 인벤 칸
	ButtonClass m_m_button_Item[4];
};