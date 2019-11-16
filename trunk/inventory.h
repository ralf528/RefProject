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
	//<�ʱ�ȭ
	bool init(void);
	//<����
	void release(void);
	//<�κ��丮 ����
	void renderInven(HDC hdc);
	//<������ ����
	bool addItem(unsigned int item);
	//<������ ���
	unsigned int useItem(unsigned int index);

private:
	//< ������ ����Ʈ
	itemList m_itemList;
	//< ������ â Ȱ��ȭ ����
	bool m_flag;

	//< �κ� ĭ
	ButtonClass m_m_button_Item[4];
};