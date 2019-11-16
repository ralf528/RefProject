#pragma once

#include "Singleton.h"
#include "ButtonClass.h"

class Inventory
{
	typedef std::list<unsigned int>		itemList;
	typedef itemList::iterator			item_iter;
public:
	Inventory(void);
	~Inventory(void);

public:
	//<초기화
	bool init(void);
	//<삭제
	void release(void);
	//<인벤토리 랜더
	void renderInven(HDC hdc);
	//<아이템 보관
	bool addItem(unsigned int item);
	//<아이템 사용
	unsigned int useItem(unsigned int index);

private:
	//< 아이템 리스트
	itemList m_itemList;
	//< 아이템 창 활성화 여부
	bool m_flag;

	//< 인벤 칸
	ButtonClass m_m_button_Item[4];
};