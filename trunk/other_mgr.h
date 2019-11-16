#pragma once

class otherCharacter;

class Other_manager
{
	//< ���̵�, ĳ���� ����
	typedef std::map<char*, otherCharacter*>				other_map;
	typedef std::map<char*, otherCharacter*>::iterator		other_map_iter;
private:
	Other_manager(void);
	~Other_manager(void);

	SINGLETON( Other_manager );

public:
	//< �ʱ�ȭ
	bool init(void);
	//< ������Ʈ
	void update(void);
	//< ����
	void render(HDC hdc);

	//< �߰�
	void addOther(char* ID, otherCharacter* other);
	//< �˻�
	otherCharacter* findOther(char* ID);
	//< ����
	void deleteOther(char* ID);
	//< ��ü ����
	void deleteAll(void);

	//< �޽��� �ޱ�
	void receiveMessage(char* ID, int state);

private:
	//< �ƴ� ĳ���� ����Ʈ
	other_map m_otherList;
};

#define OTHER_MGR Singleton<Other_manager>::getInstance()